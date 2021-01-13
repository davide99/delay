#include "DB.h"
#include <string>
#include "../Math/Integers.h"

IO::DB::DB() : db(Consts::DB::Name) {
    this->db.exec("PRAGMA temp_store=MEMORY;");

    //Create the database if it doesn't exist
    if (!exists())
        create();
}

bool IO::DB::exists() {
    try {
        SQLite::Statement query(this->db,
                                "SELECT COUNT(*) FROM sqlite_master WHERE name=? OR name=?");
        query.bind(1, Consts::DB::RecordingsTable);
        query.bind(2, Consts::DB::TmpRecordTable);

        if (query.executeStep())
            return query.getColumns<int, 1>() == 2;
    } catch (const std::exception &e) {}

    return false;
}

bool IO::DB::create() {
    try {
        this->db.exec("CREATE TABLE IF NOT EXISTS " + Consts::DB::RecordingsTable + " (" +
                      "hash INT NOT NULL, " +
                      "songId INT NOT NULL, " +
                      "time INT NOT NULL, " +
                      "PRIMARY KEY (hash, songId, time)");

    } catch (const std::exception &e) {
        e.what();
        return false;
    }

    return true;
}

bool IO::DB::drop() {
    try {
        this->db.exec("DROP TABLE '" + Consts::DB::RecordingsTable + "'");
        this->db.exec("DROP TABLE '" + Consts::DB::TmpRecordTable + "'");
    } catch (const std::exception &e) {
        e.what();
        return false;
    }

    return true;
}

bool IO::DB::insertSong(const std::string &name, const Core::Links &links) {
    std::uint64_t id;
    id = this->db.execAndGet("SELECT MAX(songId) FROM '" + Consts::DB::RecordingsTable + "'").getInt64() + 1;

    //Insert Links
    std::string s = "INSERT INTO " + Consts::DB::RecordingsTable + " (hash, songId, time) VALUES ";

    for (const auto &link : links) {
        s += "(";
        s += Math::Integers::toHex(link.getHash()); //hex for speed purposes
        s += ",";
        s += Math::Integers::toHex(id);
        s += ",";
        s += Math::Integers::toHex(link.getTime());
        s += "),";
    }

    s.pop_back(); //Remove last (useless) ","

    try {
        this->db.exec(s);
    } catch (const std::exception &e) {
        e.what();
        return false;
    }

    return true;
}

bool IO::DB::searchIdGivenLinks(const Core::Links &links, std::uint64_t &id, std::uint64_t *commonLinks) {
    //Create the temporary in memory table
    try {
        this->db.exec("CREATE TEMPORARY TABLE " + Consts::DB::TmpRecordTable + " (" +
                      "hash INT NOT NULL, " +
                      "start INT NOT NULL, " +
                      "PRIMARY KEY (hash, start))");
    } catch (const std::exception &e) {
        e.what();
        return false;
    }

    //Insert recording links in the temporary table
    std::string s = "INSERT INTO " + Consts::DB::TmpRecordTable + " VALUES ";

    for (const auto &link : links) {
        s += "(";
        s += Math::Integers::toHex(link.getHash());
        s += ",";
        s += Math::Integers::toHex(link.getTime());
        s += "),";
    }

    s.pop_back(); //Remove last (useless) ","

    try {
        this->db.exec(s);
    } catch (const std::exception &e) {
        e.what();
        return false;
    }

    //Perform the real query to find similarities
    std::string query_s =
            //selected songId, number of common links
            "SELECT " + Consts::DB::RecordingsTable + ".songId, COUNT(*) AS n " +
            //inner join the songs table and the temporary table
            "FROM " + Consts::DB::RecordingsTable + " INNER JOIN " + Consts::DB::TmpRecordTable + " " +
            //join condition: the hash has to be the same
            "ON " + Consts::DB::RecordingsTable + ".hash=" + Consts::DB::TmpRecordTable + ".hash " +
            //since the recording is a piece of the full song, so the whole recording has to be shifted of a non
            //negative amount of time w.r.t. to original song
            "WHERE " + Consts::DB::RecordingsTable + ".time>=" + Consts::DB::TmpRecordTable + ".start " +
            //the common links are grouped if the time difference between the original song links and the recording
            //ones is the same
            "GROUP BY " + Consts::DB::RecordingsTable + ".time-" + Consts::DB::TmpRecordTable + ".start, songId " +
            //the more links in common the better
            "ORDER BY n DESC";

    SQLite::Statement query(this->db, query_s);

    try {
        if(query.executeStep()){
            //found something && is it above the minimum threshold
            if (query.getColumn(1).getInt64() > Consts::Links::MinHint)
                id = query.getColumn(0).getInt();

            //should we return the number of common links?
            if (commonLinks != nullptr)
                *commonLinks = query.getColumn(1).getInt64();
        }
    } catch (const std::exception &e) {
        e.what();
        return false;
    }

    return true;
}

#include "DB.h"
#include <string>
#include <iostream>
#include <fstream>
#include "../Math/Integers.h"

IO::DB::DB() : db(":memory:", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {
    create();
}

bool IO::DB::create() {
    try {
        this->db.exec("CREATE TABLE " + Consts::DB::TracksTable + " (" +
                      "hash INT NOT NULL, " +
                      "trackId INT NOT NULL, " +
                      "time INT NOT NULL, " +
                      "PRIMARY KEY (hash, trackId, time))");
    } catch (const std::exception &e) {
        e.what();
        return false;
    }

    return true;
}

bool IO::DB::insertTrack(const unsigned int &id, const Core::Links &links) {
    //Insert Links
    std::string s = "INSERT INTO " + Consts::DB::TracksTable + " (hash, trackId, time) VALUES ";

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

std::int64_t IO::DB::findDelay() {
    //Perform the real query to find similarities
    std::string query_s =
            //selected trackId, number of common links
            "SELECT t1.trackId, COUNT(*) AS n, t1.time-t2.time "
            //inner join the songs table and the temporary table
            "FROM " + Consts::DB::TracksTable + " AS t1 INNER JOIN " + Consts::DB::TracksTable + " AS t2 "
                                                                                                 //join condition: the hash has to be the same
                                                                                                 "ON t1.hash=t2.hash " +
            //but different ids
            "AND t1.trackId!=t2.trackId " +
            //since the recording is a piece of the full song, so the whole recording has to be shifted of a non
            //negative amount of time w.r.t. to original song
            "WHERE t1.time>=t2.time " +
            //the common links are grouped if the time difference between the original song links and the recording
            //ones is the same
            "GROUP BY t1.time-t2.time, t1.trackId " +
            //the more links in common the better
            "ORDER BY n DESC";

    std::cout << query_s << std::endl;

    SQLite::Statement query(this->db, query_s);

    try {
        if (query.executeStep()) {
            std::cout << "common:" << query.getColumn(1).getInt() << std::endl;
            return query.getColumn(2).getInt64();
        }
    } catch (const std::exception &e) {
        e.what();
        return false;
    }

    return true;
}

void IO::DB::saveCommonToCSV(const std::string &csvName, float windowDuration) {
    std::ofstream csvFile(csvName);

    std::string query_s =
            "SELECT t1.time, t2.time "
            "FROM " + Consts::DB::TracksTable + " AS t1 INNER JOIN " + Consts::DB::TracksTable + " AS t2 " +
            "ON t1.hash=t2.hash AND t1.trackId=1 AND t2.trackId=2";

    SQLite::Statement query(this->db, query_s);

    try {
        while (query.executeStep()) { //Row by row
            csvFile << ((float) query.getColumn(0).getInt64()) * windowDuration << ","
                    << ((float) query.getColumn(1).getInt64()) * windowDuration << "\n";
        }
    } catch (const std::exception &e) {
        e.what();
    }

    csvFile.close();
}

#include "DB.h"
#include <string>

IO::DB::DB() {
    //Setup the account
    mariadb::account_ref acc = mariadb::account::create(
            Consts::DB::Hostname,
            Consts::DB::Username,
            Consts::DB::Password
    );

    //Create connection
    this->conn = mariadb::connection::create(acc);

    if (!exists())
        create();

    //Prepare the statements
    this->insSongInfoStmt = this->conn->create_statement(
            "INSERT INTO " + Consts::DB::InfoTableFull + " (name) VALUES (?)");
    this->selSongById = this->conn->create_statement(
            "SELECT name FROM " + Consts::DB::InfoTableFull + " WHERE id = ?");
}

bool IO::DB::exists() {
    try {
        mariadb::result_set_ref result = this->conn->query(
                "SELECT table_name FROM information_schema.tables WHERE table_schema='" + Consts::DB::Name + "' " +
                "OR table_name='" + Consts::DB::RecordingsTable + "' " +
                "OR table_name='" + Consts::DB::InfoTable + "' " +
                "OR table_name='" + Consts::DB::TmpRecordTable + "'");

        return result->row_count() == 3;
    } catch (const std::exception &e) {}

    return false;
}

bool IO::DB::create() {
    try {
        this->conn->execute("CREATE DATABASE IF NOT EXISTS " + Consts::DB::Name);

        this->conn->execute("CREATE TABLE IF NOT EXISTS " + Consts::DB::InfoTableFull + " (" +
                            "id " + Consts::DB::UInt + " NOT NULL AUTO_INCREMENT PRIMARY KEY," +
                            "name VARCHAR(200) NOT NULL)");

        this->conn->execute("CREATE TABLE IF NOT EXISTS " + Consts::DB::RecordingsTableFull + " (" +
                            "hash " + Consts::DB::UInt64 + " NOT NULL, " +
                            "songId " + Consts::DB::UInt + " NOT NULL, " +
                            "time " + Consts::DB::UInt64 + " NOT NULL, " +
                            "PRIMARY KEY (hash, songId, time), " +
                            "FOREIGN KEY (songId) REFERENCES " + Consts::DB::InfoTableFull + "(id))");

    } catch (const std::exception &e) {
        return false;
    }

    return true;
}

bool IO::DB::drop() {
    try {
        this->conn->execute("DROP DATABASE IF EXISTS " + Consts::DB::Name);
    } catch (const std::exception &e) {
        return false;
    }

    return true;
}

bool IO::DB::insertSong(const std::string &name, const Core::Links &links) {
    //Insert song details into musicinfo table and get its PK
    mariadb::u64 id;

    try {
        this->insSongInfoStmt->set_string(0, name);
        id = this->insSongInfoStmt->insert();
    } catch (const std::exception &e) {
        return false;
    }

    //Insert Links
    std::string s = "INSERT INTO " + Consts::DB::RecordingsTableFull + " (hash, songId, time) VALUES ";

    for (const auto &link : links) {
        s += "(";
        s += std::to_string(link.getHash());
        s += ",";
        s += std::to_string(id);
        s += ",";
        s += std::to_string(link.getTime());
        s += "),";
    }

    s.pop_back(); //Remove last (useless) ","

    try {
        conn->insert(s);
    } catch (const std::exception &e) {
        return false;
    }

    return true;
}

std::string IO::DB::getSongNameById(const std::uint64_t &id) {
    mariadb::result_set_ref result;

    try {
        this->selSongById->set_unsigned64(0, id);
        result = this->selSongById->query();
    } catch (const std::exception &e) {
        return "";
    }

    if (result->next())
        return result->get_string("name");
    else
        return "";
}

bool IO::DB::searchIdGivenLinks(std::uint64_t &id, const Core::Links &links) {
    //Create the temporary table
    try {
        this->conn->execute("CREATE TEMPORARY TABLE " + Consts::DB::TmpRecordTableFull + " (" +
                            "hash " + Consts::DB::UInt64 + " NOT NULL, " +
                            "start " + Consts::DB::UInt64 + " NOT NULL, " +
                            "PRIMARY KEY (hash, start)" +
                            ") ENGINE = MEMORY");
    } catch (const std::exception &e) {
        return false;
    }

    //Insert recording links in the temporary table
    std::string s = "INSERT INTO " + Consts::DB::TmpRecordTableFull + " VALUES ";

    for (const auto &link : links) {
        s += "(";
        s += std::to_string(link.getHash());
        s += ",";
        s += std::to_string(link.getTime());
        s += "),";
    }

    s.pop_back(); //Remove last (useless) ","

    try {
        conn->insert(s);
    } catch (const std::exception &e) {
        return false;
    }

    //Perform the real query to find similarities
    mariadb::result_set_ref result;

    try {
        result = this->conn->query(
                "SELECT " + Consts::DB::RecordingsTableFull + ".songId, COUNT(*) AS n " +
                "FROM " + Consts::DB::RecordingsTableFull + " INNER JOIN " + Consts::DB::TmpRecordTableFull + " " +
                "ON " + Consts::DB::RecordingsTableFull + ".hash=" + Consts::DB::TmpRecordTableFull + ".hash " +
                "WHERE " + Consts::DB::RecordingsTableFull + ".time>=" + Consts::DB::TmpRecordTableFull + ".start " +
                "GROUP BY " + Consts::DB::RecordingsTableFull + ".time-" + Consts::DB::TmpRecordTableFull +
                ".start, songId " +
                "ORDER BY n DESC");

        if (result->next() && result->get_unsigned64(1) > Consts::DB::MinHint)
            id = result->get_unsigned32(0);

#ifdef DEBUG
        std::cout << ">>Number of common hashes: " << result->get_unsigned64(1) << std::endl;
#endif
    } catch (const std::exception &e) {
        return false;
    }

    return true;
}

IO::DB::~DB() {
    this->conn->disconnect();
}

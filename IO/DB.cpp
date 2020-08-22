#include "DB.h"
#include "../Consts.h"
#include <mariadb++/account.hpp>
#include <sstream>

IO::DB::DB() {
    //Setup the account
    mariadb::account_ref acc = mariadb::account::create(
            Consts::DB::Hostname,
            Consts::DB::Username,
            Consts::DB::Password
    );

    //Create connection
    this->conn = mariadb::connection::create(acc);

    //Prepare the statements
    this->insSongInfoStmt = this->conn->create_statement("INSERT INTO " + Consts::DB::Name + ".musicinfo (name) (?)");
    this->selSongById = this->conn->create_statement(
            "SELECT name FROM " + Consts::DB::Name + ".musicinfo WHERE id = ?");
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
    std::stringstream ss;
    ss << "INSERT INTO " << Consts::DB::Name << ".links (hash, songId, time) VALUES ";

    for (const auto &link : links)
        ss << "(" << link.getHash() << "," << id << "," << link.getTime() << ")";

    ss.seekp(-1, std::ios_base::end);
    ss << ";";

    try {
        conn->insert(ss.str());
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

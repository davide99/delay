#ifndef IO_DB_H
#define IO_DB_H

#include <mariadb++/connection.hpp>
#include <mariadb++/statement.hpp>
#include <cstdint>
#include "../Core/Links.h"

namespace IO {
    class DB {
    private:
        mariadb::connection_ref conn;

        mariadb::statement_ref insSongInfoStmt, selSongById;
    public:
        DB();

        ~DB();

        bool exists();

        bool create();

        bool drop();

        bool insertSong(const std::string &name, const Core::Links &links);

        bool searchIdGivenLinks(std::uint64_t &id, const Core::Links &links);

        std::string getSongNameById(const std::uint64_t &id);
    };
}

#endif

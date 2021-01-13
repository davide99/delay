#ifndef IO_DB_H
#define IO_DB_H

#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/Statement.h>
#include <cstdint>
#include "../Core/Links.h"

namespace IO {
    /**
     * Class to manage the database
     */
    class DB {
    private:
        SQLite::Database db;

    public:
        DB();

        /**
         * @return true if the database exists, false otherwise
         */
        bool exists();

        /**
         * Create the database
         * @return true if no errors occurred, false otherwise
         */
        bool create();

        /**
         * Drop the database
         * @return true if no errors occurred, false otherwise
         */
        bool drop();

        /**
         * Insert a song in the database
         * @param name  Name of the song
         * @param links Song's links
         * @return true if no errors occurred, false otherwise
         */
        bool insertSong(const std::string &name, const Core::Links &links);

        /**
         * Try to find a match for a recording
         * @param links         Recoding's links
         * @param id            Output: found id, untouched if not found
         * @param commonLinks   Output: optional, pointer to common links found
         * @return true if a match is found, false otherwise
         */
        bool searchIdGivenLinks(const Core::Links &links, std::uint64_t &id, std::uint64_t *commonLinks = nullptr);
    };
}

#endif

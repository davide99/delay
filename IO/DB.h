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
         * Insert a song in the database
         * @param id  Name of the song
         * @param links Song's links
         * @return true if no errors occurred, false otherwise
         */
        bool insertTrack(const unsigned int &id, const Core::Links &links);

        /**
         * Try to find a match for a recording
         * @param links         Recoding's links
         * @param id            Output: found id, untouched if not found
         * @param commonLinks   Output: optional, pointer to common links found
         * @return true if a match is found, false otherwise
         */
        std::int64_t findDelay();

        void saveCommonToCSV(const std::string &csvName, float windowDuration);

    private:
        /**
         * Create the database
         * @return true if no errors occurred, false otherwise
         */
        bool create();
    };
}

#endif

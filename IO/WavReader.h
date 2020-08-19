#ifndef IO_WAVREADER_H
#define IO_WAVREADER_H

#include <string>
#include <vector>
#include <cstdint>

struct Chunk;

namespace IO {
    class WavReader {

    private:
        std::vector<int16_t> data;
    public:
        explicit WavReader(const std::string &fileName);

        const std::vector<int16_t> &getData();

    private:
        static bool
        findChunk(const uint8_t *id, Chunk &chunk, std::ifstream &wavFile, const bool &isBigEndian, bool iterate);
    };
}

#endif

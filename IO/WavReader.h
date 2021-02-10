#ifndef IO_WAVREADER_H
#define IO_WAVREADER_H

#include <string>
#include <vector>
#include <cstdint>
#include <cstdio>
#include "GenericReader.h"

struct Chunk;

namespace IO {
    /**
     * Class to read WAV files
     */
    class WavReader : public GenericReader {

    private:
        std::vector<float> data;
        std::FILE *wavFile;
        const bool isBigEndian;
        std::size_t numberOfSamples;

    public:
        explicit WavReader(const std::string &fileName);

        ~WavReader();

        [[nodiscard]] const float *ptrAt(const std::size_t &pos) const override;

        [[nodiscard]] const std::size_t &getNumberOfSamples() const override;

    private:
        bool findChunk(const uint8_t *id, Chunk &chunk, const bool &iterate);
    };
}

#endif

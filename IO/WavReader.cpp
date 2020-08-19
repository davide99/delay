#include "WavReader.h"
#include "../Utils.h"
#include "../Math/Integers.h"
#include "../Consts.h"
#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstring>
#include <iterator>

/*
 * http://soundfile.sapp.org/doc/WaveFormat/
 * https://sites.google.com/site/musicgapi/technical-documents/wav-file-format#wavefileheader
 */

constexpr uint8_t idSize = 4u;

#pragma pack(push, 1)
struct Chunk {
    uint8_t id[idSize];
    uint32_t size;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct FmtChunk {
    //Chunk defined above
    uint16_t compressionCode;
    uint16_t channels;
    uint32_t sampleRate;
    uint32_t averageBytePerSec;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
};
#pragma pack(pop)


//Chunk IDs
constexpr uint8_t RiffID[] = {0x52u, 0x49u, 0x46u, 0x46u};
constexpr uint8_t WaveID[] = {0x57u, 0x41u, 0x56u, 0x45u};
constexpr uint8_t FmtID[] = {0x66u, 0x6Du, 0x74u, 0x20u};
constexpr uint8_t DataID[] = {0x64u, 0x61u, 0x74u, 0x61u};


static bool checkFmtChunk(const FmtChunk &fmtChunk) {
    return (fmtChunk.compressionCode == 1u) &&              //PCM
           (fmtChunk.channels == Consts::Channels) &&
           (fmtChunk.sampleRate == Consts::SampleRate) &&
           (fmtChunk.bitsPerSample == Consts::BitsPerSample);
}

bool IO::WavReader::findChunk(const uint8_t *id, Chunk &chunk, std::ifstream &wavFile, const bool &isBigEndian,
                          const bool iterate = true) {
    bool found;

    do {
        try {
            wavFile.read(reinterpret_cast<char *>(&chunk), sizeof(Chunk));
        } catch (const std::ifstream::failure &e) {
            return false;
        }

        if (isBigEndian)
            chunk.size = Math::Integers::little2Big(chunk.size);

        found = !std::memcmp(chunk.id, id, idSize);

        if (!found)
            try {
                wavFile.seekg(chunk.size, std::ios_base::cur);
            } catch (const std::ifstream::failure &e) {
                return false;
            }

    } while (iterate && !found);

    return true;
}

IO::WavReader::WavReader(const std::string &fileName) {
    Chunk chunk{};
    bool isBigEndian;

    if (!Utils::fileExists(fileName))
        throw std::runtime_error("Can't open file: " + fileName);

    isBigEndian = Utils::isBigEndian();

    std::ifstream wavFile(fileName, std::ios::binary);
    wavFile.exceptions(std::ifstream::failbit | std::ifstream::badbit | std::ifstream::eofbit);

    //Read riff chunk
    {
        if (!this->findChunk(RiffID, chunk, wavFile, isBigEndian, false))
            throw std::runtime_error(fileName + " is not a WAV file");

        uint8_t riffType[idSize];
        wavFile.read(reinterpret_cast<char *>(&riffType), sizeof(riffType));

        if (std::memcmp(riffType, WaveID, idSize) != 0)
            throw std::runtime_error("Invalid RIFF chunk in: " + fileName);
    }

    //Read fmt chunk, it might not be the immediately after the riff chunk
    {
        if (!this->findChunk(FmtID, chunk, wavFile, isBigEndian))
            throw std::runtime_error(fileName + " is malformed");

        FmtChunk fmtChunk{};
        wavFile.read(reinterpret_cast<char *>(&fmtChunk), sizeof(FmtChunk));

        if (!checkFmtChunk(fmtChunk))
            throw std::runtime_error("WAV is not in the correct format");
    }

    size_t numberOfSamples;

    //Read data chunk
    {
        if (!this->findChunk(DataID, chunk, wavFile, isBigEndian))
            throw std::runtime_error(fileName + " is malformed");

        numberOfSamples = (chunk.size << 3u) / (Consts::Channels * Consts::BitsPerSample);
    }

    this->data.resize(numberOfSamples);
    wavFile.read(reinterpret_cast<char *>(this->data.data()), numberOfSamples * Consts::BitsPerSample >> 3u);

    if (isBigEndian)
        for (auto &sample : this->data)
            sample = Math::Integers::little2Big(sample);

    wavFile.close();
}

const std::vector<int16_t> &IO::WavReader::getData() {
    return this->data;
}

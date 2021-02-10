#include "WavReader.h"
#include "../Utils/Utils.h"
#include "../Math/Integers.h"
#include "../Consts.h"
#include <iostream>
#include <cstdint>
#include <cstring>
#include <algorithm>

/*
 * http://soundfile.sapp.org/doc/WaveFormat/
 * https://sites.google.com/site/musicgapi/technical-documents/wav-file-format#wavefileheader
 */

constexpr std::uint8_t idSize = 4u;

struct Chunk { //Generic chunk
    std::uint8_t id[idSize];
    std::uint32_t size;
} __attribute__((packed));

struct FmtChunk {
    //Chunk defined above
    std::uint16_t compressionCode;
    std::uint16_t channels;
    std::uint32_t sampleRate;
    std::uint8_t padding[6];
    std::uint16_t bitsPerSample;
} __attribute__((packed));


//Chunk IDs
constexpr std::uint8_t RiffID[] = {0x52u, 0x49u, 0x46u, 0x46u}; //RIFF
constexpr std::uint8_t WaveID[] = {0x57u, 0x41u, 0x56u, 0x45u}; //WAVE
constexpr std::uint8_t FmtID[] = {0x66u, 0x6Du, 0x74u, 0x20u};  //fmt_
constexpr std::uint8_t DataID[] = {0x64u, 0x61u, 0x74u, 0x61u}; //DATA

//Check if the WAV has the correct characteristics
static bool checkFmtChunk(const FmtChunk &fmtChunk) {
    return (fmtChunk.compressionCode == 1u) &&                  //PCM
           (fmtChunk.channels == Consts::Audio::Channels) &&
           (fmtChunk.sampleRate == Consts::Audio::SampleRate) &&
           (fmtChunk.bitsPerSample == Consts::Audio::BitsPerSample);
}

//Iterate through the WAV file to find a chunk given the id
bool IO::WavReader::findChunk(const uint8_t *id, Chunk &chunk, const bool &iterate) {
    bool found;

    do {
        if (std::fread(&chunk, sizeof(Chunk), 1, wavFile) < 0)
            return false;

        if (isBigEndian)
            chunk.size = Math::Integers::BSwap(chunk.size);

        found = !std::memcmp(chunk.id, id, idSize); //Compare with the given id

        if (!found)
            //seek from the current position ahead of chunk.size bytes
            if (std::fseek(wavFile, chunk.size, SEEK_CUR))
                return false;

    } while (iterate && !found);

    return true;
}

IO::WavReader::WavReader(const std::string &fileName) :
        isBigEndian(Utils::isBigEndian()),
        wavFile(std::fopen(fileName.c_str(), "rb")) {

    Chunk chunk{};

    if (wavFile == nullptr)
        throw std::runtime_error("Can't open file: " + fileName);

    //Read riff chunk
    {
        if (!findChunk(RiffID, chunk, false))
            throw std::runtime_error(fileName + " is not a WAV file");

        std::uint8_t riffType[idSize];
        std::fread(&riffType, sizeof(riffType), 1, wavFile);

        if (std::memcmp(riffType, WaveID, idSize) != 0)
            throw std::runtime_error("Invalid RIFF chunk in: " + fileName);
    }

    //Read fmt chunk, it might not be the immediately after the riff chunk
    {
        if (!findChunk(FmtID, chunk, true))
            throw std::runtime_error(fileName + " is malformed");

        FmtChunk fmtChunk{};
        std::fread(&fmtChunk, sizeof(FmtChunk), 1, wavFile);

        if (!checkFmtChunk(fmtChunk))
            throw std::runtime_error("WAV is not in the correct format");
    }

    //Read data chunk
    {
        if (!findChunk(DataID, chunk, true))
            throw std::runtime_error(fileName + " is malformed");

        numberOfSamples = (chunk.size << 3u) / (Consts::Audio::Channels * Consts::Audio::BitsPerSample);
    }

    //For whatever reason using a vector instead of a plain old array makes valgrind not complain
    std::vector<std::int16_t> iData;
    iData.resize(numberOfSamples); //Resize to avoid reallocations
    this->data.resize(numberOfSamples);

    //Read the samples
    std::fread(iData.data(), Consts::Audio::BitsPerSample >> 3u, numberOfSamples, wavFile);

    if (isBigEndian)
        for (auto &sample : iData)
            sample = Math::Integers::BSwap(sample);

    //Convert the int16 to a float
    std::transform(iData.begin(), iData.end(), this->data.data(), [](const std::int16_t &i) -> float {
        return i;
    });
}

IO::WavReader::~WavReader() {
    std::fclose(wavFile);
}

const float *IO::WavReader::ptrAt(const size_t &pos) const {
    return data.data() + pos;
}

const std::size_t &IO::WavReader::getNumberOfSamples() const {
    return numberOfSamples;
}


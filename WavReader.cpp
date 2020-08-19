#include "WavReader.h"
#include "Utils.h"
#include "Math/Integers.h"
#include "Consts.h"
#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstring>
#include <iterator>

/*
 * http://soundfile.sapp.org/doc/WaveFormat/
 * https://sites.google.com/site/musicgapi/technical-documents/wav-file-format#wavefileheader
 */

#pragma pack(push, 1)
struct RiffChunk {
    uint8_t id[4];
    uint32_t size;
    uint8_t riffType[4];
};
#pragma pack(pop)

#pragma pack(push, 1)
struct FmtChunk {
    uint8_t id[4];
    uint32_t size;
    uint16_t compressionCode;
    uint16_t channels;
    uint32_t sampleRate;
    uint32_t averageBytePerSec;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct GenericChunk {
    uint8_t id[4];
    uint32_t size;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DataChunk {
    uint8_t id[4];
    uint32_t size;
};
#pragma pack(pop)

static bool checkRiffChunk(const RiffChunk &riffChunk) {
    uint8_t RIFF[] = {0x52u, 0x49u, 0x46u, 0x46u};
    uint8_t WAVE[] = {0x57u, 0x41u, 0x56u, 0x45u};

    return (!memcmp(riffChunk.id, RIFF, 4)) &&      //RIFF
           (!memcmp(riffChunk.riffType, WAVE, 4));  //WAVE
}

static bool isFmtChunk(const GenericChunk &chunk) {
    uint8_t fmt[] = {0x66u, 0x6Du, 0x74u, 0x20u};

    return !memcmp(chunk.id, fmt, 4);
}

static bool checkFmtChunk(const FmtChunk &fmtChunk) {
    return (fmtChunk.compressionCode == 1u) &&              //PCM
           (fmtChunk.channels == Consts::ChannelNumber) &&
           (fmtChunk.sampleRate == Consts::SampleRate) &&
           (fmtChunk.bitsPerSample == Consts::BitsPerSample);
}

static bool isDataChunk(const GenericChunk &chunk) {
    uint8_t fmt[] = {0x64u, 0x61u, 0x74u, 0x61u};   //data

    return !memcmp(chunk.id, fmt, 4);
}

WavReader::WavReader(const std::string &fileName) {
    if (!Utils::fileExists(fileName))
        throw std::runtime_error("Can't open file: " + fileName);

    bool isBigEndian = Utils::isBigEndian();

    std::ifstream wavFile(fileName, std::ios::binary);

    //Read riff chunk
    RiffChunk riffChunk{};
    wavFile.read(reinterpret_cast<char *>(&riffChunk), sizeof(RiffChunk));

    if (!checkRiffChunk(riffChunk))
        throw std::runtime_error("Invalid RIFF chunk in: " + fileName);

    /*
     * Start reading subchunks, there might be other subchunks that aren't
     * fmt subchunk and need to be discarded
     */
    GenericChunk chunk{};
    while (true) {
        wavFile.read(reinterpret_cast<char *>(&chunk), sizeof(GenericChunk));

        if (isBigEndian)
            chunk.size = Math::Integers::little2Big(chunk.size);

        if (isFmtChunk(chunk))
            break;
        else
            wavFile.seekg(chunk.size, std::ios_base::cur);
    }

    FmtChunk fmtChunk{};
    std::memcpy(&fmtChunk, &chunk, sizeof(GenericChunk));

    wavFile.read(reinterpret_cast<char *>(&fmtChunk.compressionCode), sizeof(FmtChunk) - sizeof(GenericChunk));

    if (!checkFmtChunk(fmtChunk))
        throw std::runtime_error("WAV is not in the correct format");

    //Read data chunk
    while (true) {
        wavFile.read(reinterpret_cast<char *>(&chunk), sizeof(GenericChunk));

        if (isBigEndian)
            chunk.size = Math::Integers::little2Big(chunk.size);

        if (isDataChunk(chunk))
            break;
        else
            wavFile.seekg(chunk.size, std::ios_base::cur);
    }

    DataChunk dataChunk{};
    std::memcpy(&dataChunk, &chunk, sizeof(GenericChunk));

    size_t numberOfSamples = (dataChunk.size << 3u) / (fmtChunk.channels * fmtChunk.bitsPerSample);

    this->data.resize(numberOfSamples);
    wavFile.read(reinterpret_cast<char*>(this->data.data()), numberOfSamples * fmtChunk.bitsPerSample >> 3u);

    wavFile.close();
}

const std::vector<int16_t> &WavReader::getData() {
    return this->data;
}

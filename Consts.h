#ifndef CONSTS_H
#define CONSTS_H

#include <cstdint>
#include <string>
#include <array>

namespace Consts {
    constexpr uint16_t Channels = 1u;
    constexpr uint32_t SampleRate = 8000u;
    constexpr uint16_t BitsPerSample = 16u;

    constexpr uint16_t WinSize = 512u;
    constexpr uint16_t Overlap = 256u;
    constexpr uint16_t StepSize = WinSize - Overlap;
    constexpr uint16_t FFTOutSize = WinSize / 2 + 1;
    constexpr uint16_t FreqBins = FFTOutSize;

    constexpr std::array<uint8_t, 10> Bands = {11, 22, 35, 50, 69, 91, 117, 149, 187, 231};
    constexpr std::uint8_t C = 32u;
    constexpr std::uint8_t NPeaks = 3u;
    constexpr std::uint8_t PeakRange = 5u;
    constexpr std::uint16_t MinFreq = 100u;
    constexpr std::uint16_t MaxFreq = 2000u;

    constexpr float MinWinDistanceF = 1.0f;
    constexpr float MaxWinDistanceF = 3.0f;

    namespace DB {
        const std::string Hostname = "localhost";
        const std::string Username = "root";
        const std::string Password = "davide";
        const std::string Name = "musiclibrary";

        //Table names
        const std::string RecordingsTable = Name + ".recordings";
        const std::string InfoTable = Name + ".musicinfo";
        const std::string TmpRecordTable = Name + "._recordings";

        //Table fields
        const std::string UInt64 = "BIGINT UNSIGNED";
        const std::string UInt = "INT UNSIGNED";

        constexpr std::uint64_t MinHint = 15;
    }
}

#endif

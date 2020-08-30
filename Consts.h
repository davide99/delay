#ifndef CONSTS_H
#define CONSTS_H

#include <cstdint>
#include <string>
#include <array>

namespace Consts {
    constexpr std::uint16_t Channels = 1u;
    constexpr std::uint32_t SampleRate = 8000u;
    constexpr std::uint16_t BitsPerSample = 16u;

    constexpr std::uint16_t WinSize = 512u;
    constexpr std::uint16_t Overlap = 256u;
    constexpr std::uint16_t StepSize = WinSize - Overlap;
    constexpr std::uint16_t FreqBins = WinSize / 2;

    namespace Window {
        constexpr std::uint16_t MelStart = 250u;
        constexpr std::uint16_t MelStep = 200u;

        constexpr float FreqBinStep = ((float) SampleRate) / WinSize;
    }

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
        const std::string RecordingsTable = "recordings";
        const std::string InfoTable = "musicinfo";
        const std::string TmpRecordTable = "_recording";

        const std::string RecordingsTableFull = Name + "." + RecordingsTable;
        const std::string InfoTableFull = Name + "." + InfoTable;
        const std::string TmpRecordTableFull = Name + "." + TmpRecordTable;

        //Table fields
        const std::string UInt64 = "BIGINT UNSIGNED";
        const std::string UInt = "INT UNSIGNED";

        constexpr std::uint64_t MinHint = 15;
    }
}

#endif

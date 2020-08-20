#ifndef CONSTS_H
#define CONSTS_H

#include <cstdint>
#include <array>

namespace Consts {
    constexpr uint16_t Channels = 1u;
    constexpr uint32_t SampleRate = 8000u;
    constexpr uint16_t BitsPerSample = 16u;

    constexpr uint16_t WinSize = 512u;
    constexpr uint16_t Overlap = 256u;
    constexpr uint16_t FFTOutSize = WinSize / 2 + 1;
    constexpr uint16_t FreqBins = FFTOutSize;

    constexpr std::array<uint8_t, 10> Bands = {11, 22, 35, 50, 69, 91, 117, 149, 187, 231};
    constexpr std::uint8_t C = 32u;
    constexpr std::uint8_t NPeaks = 3u;
    constexpr std::uint8_t PeakRange = 5u;
    constexpr std::uint16_t MinFreq = 100u;
    constexpr std::uint16_t MaxFreq = 2000u;
}

#endif

#ifndef CONSTS_H
#define CONSTS_H

#include <cstdint>

namespace Consts {
    constexpr uint16_t Channels = 1u;
    constexpr uint32_t SampleRate = 8000u;
    constexpr uint16_t BitsPerSample = 16u;

    constexpr uint16_t WinSize = 512u;
    constexpr uint16_t Overlap = 256u;
    constexpr uint16_t FFTOutSize = WinSize / 2 + 1;
    constexpr uint16_t FreqBins = FFTOutSize;
}

#endif

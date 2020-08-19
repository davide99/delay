#ifndef CONSTS_H
#define CONSTS_H

#include <cstdint>

namespace Consts {
    constexpr uint16_t Channels = 1u;
    constexpr uint32_t SampleRate = 8000u;
    constexpr uint16_t BitsPerSample = 16u;

    constexpr uint16_t WinSize = 512u;
}

#endif

#ifndef MATH_WINDOW_H
#define MATH_WINDOW_H

#include "../Consts.h"
#include <array>

namespace Math::Window {
    namespace {
        bool winInitialized = false;
        std::array<float, Consts::WinSize> window;

        bool binsInitialized = false;
        std::array<float, Consts::FreqBins> freqBins;
    }

    const std::array<float, Consts::WinSize> &get();

    const std::array<float, Consts::FreqBins> &getFreqBins();
}

#endif

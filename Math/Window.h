#ifndef MATH_WINDOW_H
#define MATH_WINDOW_H

#include "../Consts.h"
#include <array>

namespace Math::Window {
    namespace {
        bool winInitialized = false;
        float window[Consts::WinSize];

        bool binsInitialized = false;
        std::array<float, Consts::FreqBins> freqBins;
    }

    float *get();

    const std::array<float, Consts::FreqBins> &getFreqBins();
}

#endif

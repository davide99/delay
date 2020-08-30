#ifndef MATH_WINDOW_H
#define MATH_WINDOW_H

#include "../Consts.h"
#include <array>
#include <vector>

namespace Math::Window {
    namespace {
        bool winInitialized = false;
        std::array<float, Consts::WinSize> window;

        bool binsInitialized = false;
        std::array<float, Consts::FreqBins> freqBins;

        bool melBandsInitialized = false;
        std::vector<int> bands;

        bool bandsMapInitialized = false;
        std::array<int, Consts::FreqBins> bandsMap;
    }

    const std::array<float, Consts::WinSize> &get();

    const std::array<float, Consts::FreqBins> &getFreqBins();

    const std::vector<int> &getBands();

    const int &getBandIndex(const int &band);
}

#endif

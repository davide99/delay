#ifndef CORE_PEAKSFINDER_H
#define CORE_PEAKSFINDER_H

#include "../Math/FFTWindow.h"
#include "Peak.h"
#include <vector>
#include <cstdint>

namespace Core {
    std::vector<Core::Peak>
    findPeaks(const Math::FFTWindow &fftWindow, const size_t &window, const int &bandStart, const int &bandEnd);
}

#endif

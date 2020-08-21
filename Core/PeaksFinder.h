#ifndef CORE_PEAKSFINDER_H
#define CORE_PEAKSFINDER_H

#include "../Math/FFTWindow.h"
#include "Peak.h"
#include <vector>
#include <cstdint>

namespace Core {
    std::vector<Core::Peak>
    findPeaks(const Math::FFTWindow &fftWindow, std::uint_fast8_t bandStart, std::uint_fast8_t bandEnd,
              std::size_t window);
}

#endif

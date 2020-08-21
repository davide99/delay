#ifndef CORE_PEAKSFINDER_H
#define CORE_PEAKSFINDER_H

#include "../Math/FFTWindow.h"
#include "../MaxFixedHeap.h"
#include "Peak.h"
#include <vector>

namespace Core {
    std::vector<Core::Peak>
    findPeaks(const Math::FFTWindow &fftWindow, uint8_t bandStart, uint8_t bandEnd, size_t window);
}

#endif

#ifndef CORE_PEAKSFINDER_H
#define CORE_PEAKSFINDER_H

#include "../Math/FFTWindow.h"
#include "../MaxFixedHeap.h"
#include "Peak.h"
#include <vector>

namespace Core {
    std::vector<Peak> findPeaks(const Math::FFTWindow &fftWindow, uint8_t bandStart, uint8_t bandEnd);
}

#endif

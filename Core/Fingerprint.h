#ifndef CORE_FINGERPRINT_H
#define CORE_FINGERPRINT_H

#include <vector>
#include "Peak.h"
#include "../Math/Spectrogram.h"

namespace Core::Fingerprint {
    std::vector<Core::Peak> compute(const Math::Spectrogram& spectrogram);
}


#endif

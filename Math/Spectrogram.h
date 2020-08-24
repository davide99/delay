#ifndef MATH_SPECTROGRAM_H
#define MATH_SPECTROGRAM_H

#include <vector>
#include "../Consts.h"
#include "FFTWindow.h"

namespace Math {
    class Spectrogram {

    public:
        explicit Spectrogram(const std::vector<float>& data);

    private:
        std::vector<FFTWindow> fftWindows;
    public:
        FFTWindow operator[](size_t pos) const;
        [[nodiscard]] std::size_t size() const;
    };
}

#endif
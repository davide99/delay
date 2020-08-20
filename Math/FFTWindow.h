#ifndef STRUCTURES_FFTWINDOW_H
#define STRUCTURES_FFTWINDOW_H

#include <array>
#include <vector>
#include <complex>
#include "../Consts.h"

namespace Math {
    class FFTWindow {
        friend class Spectrogram;

    private:
        std::array<std::complex<float>, Consts::FFTOutSize> data;
        float time{};

    public:
        [[nodiscard]] const std::array<std::complex<float>, Consts::FFTOutSize> &getData() const {
            return data;
        }

        [[nodiscard]] const float &getTime() const {
            return time;
        }
    };
}


#endif

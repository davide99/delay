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
        std::array<float, Consts::FFTOutSize> magnitudes;
        float time{};

    public:
        [[nodiscard]] const std::array<float, Consts::FFTOutSize> &getMagnitudes() const {
            return magnitudes;
        }

        [[nodiscard]] const float &getTime() const {
            return time;
        }
    };
}


#endif

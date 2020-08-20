#ifndef MATH_SPECTROGRAM_H
#define MATH_SPECTROGRAM_H

#include <vector>
#include <array>
#include <complex>
#include <list>
#include "../Consts.h"

namespace Math {
    class Spectrogram {
    public:
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

    public:
        explicit Spectrogram(const std::vector<float>& data);

    private:
        std::list<FFTWindow> fftWindows;
    public:
        FFTWindow operator[](size_t pos) const;
    };
}

#endif

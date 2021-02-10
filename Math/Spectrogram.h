#ifndef MATH_SPECTROGRAM_H
#define MATH_SPECTROGRAM_H

#include <vector>
#include <queue>
#include "../Consts.h"
#include "FFTWindow.h"
#include "../IO/GenericReader.h"

namespace Math {
    /**
     * Class to compute the spectrogram given the samples
     */
    class Spectrogram {

    public:
        /**
         * Constructs the spectrogram
         * @param reader the reader
         */
        explicit Spectrogram(const IO::GenericReader &reader);

    private:
        std::deque<FFTWindow> fftWindows;
    public:
        /**
         * Get a specific FFT window
         * @param pos what window
         * @return the window
         */
        const FFTWindow &operator[](std::size_t pos) const;

        /**
         * @return the number of FFT windows
         */
        [[nodiscard]] std::size_t size() const;
    };
}

#endif

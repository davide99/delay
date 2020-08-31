#ifndef MATH_WINDOW_H
#define MATH_WINDOW_H

#include "../Consts.h"
#include <array>
#include <vector>

namespace Math::Window {
    //Nameless namespace to make them "private"
    namespace {
        bool winInitialized = false;
        std::array<float, Consts::Window::Size> window; //Hann

        bool binsInitialized = false;
        std::array<float, Consts::Window::FreqBins> freqBins; //Frequencies of each bin

        bool melBandsInitialized = false;
        std::vector<int> bands; //Bands to divide the FFT window in

        bool bandsMapInitialized = false;
        std::array<int, Consts::Window::FreqBins> bandsMap; //Mapping between frequency index and band index
    }

    /**
     * @return the Hann window
     */
    const std::array<float, Consts::Window::Size> &get();

    /**
     * @return the frequencies bin array
     */
    const std::array<float, Consts::Window::FreqBins> &getFreqBins();

    /**
     * @return the bands to divie the FFT window in
     */
    const std::vector<int> &getBands();

    /**
     * Given the frequency index w.r.t. freqBins return the index of
     * the corresponding band w.r.t. bands
     * @param freqIndex
     * @return
     */
    const int &getBandIndex(const int &freqIndex);
}

#endif

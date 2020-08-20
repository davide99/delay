#include "Window.h"
#include <type_traits>
#include <cmath>

float *Math::Window::get() {
    if (!Math::Window::winInitialized)
        for (std::remove_const_t<decltype(Consts::WinSize)> i = 0; i < Consts::WinSize; i++)
            window[i] = (float) (0.5f * (1 - std::cos(2 * M_PI * i / (Consts::WinSize - 1)))); //Hanning

    return Math::Window::window;
}

const std::array<float, Consts::FreqBins> &Math::Window::getFreqBins() {
    if (!Math::Window::binsInitialized)
        for (std::remove_const_t<decltype(Consts::FreqBins)> i = 0; i < Consts::FreqBins; i++)
            freqBins[i] = (Consts::SampleRate / 2.0f) * ((float) i / Consts::FreqBins);

    return Math::Window::freqBins;
}

#include "Window.h"
#include <cmath>

const std::array<float, Consts::WinSize> &Math::Window::get() {
    if (!Math::Window::winInitialized) {
        for (int i = 0; i < Consts::WinSize; i++)
            window[i] = (float) (0.5f * (1 - std::cos(2 * M_PI * i / (Consts::WinSize - 1)))); //Hanning

        Math::Window::winInitialized = true;
    }

    return Math::Window::window;
}

const std::array<float, Consts::FreqBins> &Math::Window::getFreqBins() {
    if (!Math::Window::binsInitialized) {
        for (int i = 0; i < Consts::FreqBins; i++)
            freqBins[i] = (Consts::SampleRate / 2.0f) * ((float) i / Consts::FreqBins);

        Math::Window::binsInitialized = true;
    }

    return Math::Window::freqBins;
}

#include "Window.h"
#include <cmath>
#include <iostream>

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

const std::vector<int> &Math::Window::getBands() {
    if (!Math::Window::melBandsInitialized) {
        int freqIndex;
        float factor = 700.0f / Consts::Window::FreqBinStep;

        for (auto mel = Consts::Window::MelStart;; mel += Consts::Window::MelStep) {
            freqIndex = (int) std::round(factor * (std::pow(10.0f, (float) mel / 2595.0f) - 1.0f));

            if (freqIndex > Consts::FreqBins)
                break;
            else
                bands.push_back(freqIndex);
        }

        Math::Window::melBandsInitialized = true;
    }

    return Math::Window::bands;
}

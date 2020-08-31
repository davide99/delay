#include "Window.h"
#include <cmath>

const std::array<float, Consts::Window::Size> &Math::Window::get() {
    if (!Math::Window::winInitialized) {
        for (int i = 0; i < Consts::Window::Size; i++)
            window[i] = (float) (0.5f * (1 - std::cos(2 * M_PI * i / (Consts::Window::Size - 1)))); //Hanning

        Math::Window::winInitialized = true;
    }

    return Math::Window::window;
}

const std::array<float, Consts::Window::FreqBins> &Math::Window::getFreqBins() {
    if (!Math::Window::binsInitialized) {
        for (int i = 0; i < Consts::Window::FreqBins; i++)
            freqBins[i] = (Consts::Audio::SampleRate / 2.0f) * ((float) i / Consts::Window::FreqBins);

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

            if (freqIndex > Consts::Window::FreqBins)
                break;
            else
                bands.push_back(freqIndex);
        }

        Math::Window::melBandsInitialized = true;
    }

    return Math::Window::bands;
}

const int &Math::Window::getBandIndex(const int &freqIndex) {
    if (!Math::Window::bandsMapInitialized) {
        const auto &bandsVec = getBands();
        auto it = bandsVec.begin();
        int bandIndex = 0;

        for (int i = 0; i < Consts::Window::FreqBins; i++) {
            if (i >= *it && it != bandsVec.end()) { //next band?
                it++;
                bandIndex++;
            }

            bandsMap[i] = bandIndex;
        }

        Math::Window::bandsMapInitialized = true;
    }

    return Math::Window::bandsMap[freqIndex];
}

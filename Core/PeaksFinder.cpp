#include "PeaksFinder.h"
#include "../Math/Window.h"
#include <complex>

std::vector<Core::Peak>
Core::findPeaks(const Math::FFTWindow &fftWindow, uint8_t bandStart, uint8_t bandEnd, size_t window) {
    MaxFixedHeap<Peak> peaks(Consts::NPeaks);
    float pl, pi, pr;

    for (uint8_t i = bandStart; i < bandEnd; i++) {
        //Get the current peak value
        pi = std::abs(fftWindow.getData()[i]);
        pl = pr = -1;

        //Extract respectively 5 complex element after and before i
        //Are there 5 element before and after actually?
        if (i - Consts::PeakRange >= bandStart)
            std::max_element(
                    fftWindow.getData().begin() + i - Consts::PeakRange,
                    fftWindow.getData().begin() + i - 1,
                    [](std::complex<float> const &l, std::complex<float> const &r) -> bool {
                        return std::abs(l) < std::abs(r);
                    });

        if (i + Consts::PeakRange + 1 <= bandEnd)
            std::max_element(
                    fftWindow.getData().begin() + i + 1,
                    fftWindow.getData().begin() + i + Consts::PeakRange + 1,
                    [](std::complex<float> const &l, std::complex<float> const &r) -> bool {
                        return std::abs(l) < std::abs(r);
                    });

        if (pi >= pl || pi >= pr) {
            float peakFreq = Math::Window::getFreqBins()[i];

            if ((peakFreq >= Consts::MinFreq) && (peakFreq <= Consts::MaxFreq))
                peaks.push(Peak(i, pi, window, fftWindow.getTime()));
        }
    }

    return peaks.data();
}

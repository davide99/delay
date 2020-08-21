#include "PeaksFinder.h"
#include "../Math/Window.h"
#include "../MaxFixedHeap.h"

std::vector<Core::Peak>
Core::findPeaks(const Math::FFTWindow &fftWindow, std::uint_fast8_t bandStart, std::uint_fast8_t bandEnd,
                std::size_t window) {
    MaxFixedHeap<Peak> peaks(Consts::NPeaks);
    float pNeighbour, pCurrent;
    decltype(bandStart) indexLeft, indexRight;

    for (std::uint_fast8_t i = bandStart; i < bandEnd; i++) {
        //Get the current peak value
        pCurrent = fftWindow.getMagnitudes()[i];

        //Extract respectively 5 complex element after and before i
        //Are there 5 element before and after actually?
        indexLeft = i - Consts::PeakRange >= bandStart ? i - Consts::PeakRange : bandStart;
        indexRight = i + Consts::PeakRange + 1 <= bandEnd ? i + Consts::PeakRange + 1 : bandEnd;
        pNeighbour = *std::max_element(fftWindow.getMagnitudes().begin() + indexLeft,
                                       fftWindow.getMagnitudes().begin() + indexRight);

        if (pCurrent == pNeighbour) {
            float peakFreq = Math::Window::getFreqBins()[i];

            if ((peakFreq >= Consts::MinFreq) && (peakFreq <= Consts::MaxFreq))
                peaks.push(Peak(i, pCurrent, window, fftWindow.getTime()));
        }
    }

    return peaks.data();
}

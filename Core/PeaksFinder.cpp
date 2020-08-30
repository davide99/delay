#include "PeaksFinder.h"
#include "../MaxFixedHeap.h"

std::vector<Core::Peak>
Core::findPeaks(const Math::FFTWindow &fftWindow, const size_t &window, const int &bandStart, const int &bandEnd) {

    Utils::MaxFixedHeap<Peak, Consts::NPeaks> peaks;
    float magCurrent, freqCurrent;
    int indexLeft, indexRight, j;
    bool ok;

    for (int i = bandStart; i <= bandEnd; i++) {
        freqCurrent = Math::Window::getFreqBins()[i];
        if ((freqCurrent < Consts::MinFreq) || (freqCurrent > Consts::MaxFreq))
            continue;

        //Get the current peak value
        magCurrent = fftWindow.getMagnitudes()[i];

        //Extract respectively 5 complex element after and before i
        //Are there 5 element before and after actually?
        indexLeft = i - Consts::PeakRange >= bandStart ? i - Consts::PeakRange : bandStart;
        indexRight = i + Consts::PeakRange + 1 <= bandEnd ? i + Consts::PeakRange + 1 : bandEnd;

        for (; indexLeft != i && (ok = fftWindow.getMagnitudes()[indexLeft] < magCurrent); indexLeft++);
        if (!ok)
            continue;

        for (j = i + 1; j <= indexRight && (ok = fftWindow.getMagnitudes()[j] < magCurrent); j++);
        if (!ok) {
            i = j - 1;
            continue;
        }

        peaks.push(Peak(i, magCurrent, window, fftWindow.getTime()));
    }

    return peaks.data();
}

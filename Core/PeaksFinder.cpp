#include "PeaksFinder.h"
#include "../Math/Window.h"
#include "../MaxFixedHeap.h"

std::vector<Core::Peak>
Core::findPeaks(const Math::FFTWindow &fftWindow, const size_t &window, const int &bandStart, const int &bandEnd) {

    MaxFixedHeap<Peak> peaks(Consts::NPeaks);
    float pNeighbour, pCurrent, peakFreq;
    int indexLeft, indexRight;
    bool ok;

    for (int i = bandStart; i <= bandEnd; i++) {
        peakFreq = Math::Window::getFreqBins()[i];
        if ((peakFreq < Consts::MinFreq) || (peakFreq > Consts::MaxFreq))
            continue;

        //Get the current peak value
        pCurrent = fftWindow.getMagnitudes()[i];

        //Extract respectively 5 complex element after and before i
        //Are there 5 element before and after actually?
        indexLeft = i - Consts::PeakRange >= bandStart ? i - Consts::PeakRange : bandStart;
        indexRight = i + Consts::PeakRange + 1 <= bandEnd ? i + Consts::PeakRange + 1 : bandEnd;

        for (; indexLeft != i && (ok = fftWindow.getMagnitudes()[indexLeft] < pCurrent); indexLeft++);
        if (!ok)
            continue;

        for (; indexRight != i && (ok = fftWindow.getMagnitudes()[indexRight] < pCurrent); indexRight--);
        if (!ok)
            continue;

        peaks.push(Peak(i, pCurrent, window, fftWindow.getTime()));
    }

    return peaks.data();
}

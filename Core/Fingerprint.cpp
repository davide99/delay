#include "Fingerprint.h"
#include "../Utils/MaxFixedHeap.h"
#include "PeaksFinder.h"
#include "../Math/Window.h"
#include <cstdint>

std::vector<Core::Peak> Core::Fingerprint::compute(const Math::Spectrogram &spectrogram) {
    int currBand, nextBand;
    std::vector<Peak> peakVec;
    Utils::MaxFixedHeap<Peak, Consts::NPeaks> tmp;

    const auto &bands = Math::Window::getBands();

    //For each band
    for (std::size_t b = 0; b < bands.size() - 1; b++) {
        currBand = bands[b];
        nextBand = bands[b + 1];

        //For each window in the spectrogram
        for (std::size_t i = 0; i < spectrogram.size(); i++) {

            //Every C, or at the end of the window, add tmp to peakList nad reset tmp
            if (i % Consts::C == 0 || i == spectrogram.size() - 1) {
                peakVec.insert(peakVec.end(), tmp.begin(), tmp.end());
                tmp.clear();
            }

            //Extract between band
            std::vector<Peak> foundPeaks = findPeaks(spectrogram[i], i, currBand, nextBand - 1);
            for (const auto &peak : foundPeaks)
                tmp.push(peak);
        }
    }

    std::sort(peakVec.begin(), peakVec.end());
    return peakVec;
}

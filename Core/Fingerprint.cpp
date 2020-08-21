#include "Fingerprint.h"
#include "../MaxFixedHeap.h"
#include "PeaksFinder.h"
#include <cstdint>

std::vector<Core::Peak> Core::Fingerprint::compute(const Math::Spectrogram &spectrogram) {
    std::uint_fast8_t currBand, nextBand;
    std::vector<Peak> peakVec;
    MaxFixedHeap<Peak> tmp(Consts::NPeaks);

    //For each band
    for (std::size_t b = 0; b < Consts::Bands.size() - 1; b++) {
        currBand = Consts::Bands[b];
        nextBand = Consts::Bands[b + 1];

        //For each window in the spectrogram
        for (std::size_t i = 0; i < spectrogram.size(); i++) {

            //Every C, or at the end of the window, add tmp to peakList nad reset tmp
            if (i % Consts::C == 0 || i == spectrogram.size() - 1) {
                peakVec.insert(peakVec.end(), tmp.begin(), tmp.end());
                tmp.clear();
            }

            //Extract between band
            std::vector<Peak> foundPeaks = findPeaks(spectrogram[i], currBand, nextBand - 1, i);
            for (const auto &peak : foundPeaks)
                tmp.push(peak);
        }
    }

    std::sort(peakVec.begin(), peakVec.end());
    return peakVec;
}

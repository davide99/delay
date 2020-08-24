#include "Links.h"
#include <algorithm>

Core::Links::Links(const std::vector<Peak> &peakVec) {
    //Time distance between each window
    float timeStep = (float) Consts::StepSize / Consts::SampleRate;
    std::size_t windowDistance = Consts::MaxWinDistanceF / timeStep;

    std::vector<Peak> tmpPeaks;

    for (auto it = peakVec.begin(); it != peakVec.end(); it++) {
        std::copy_if(
                (it - windowDistance >= peakVec.begin() ? it - windowDistance : peakVec.begin()),
                (it + windowDistance <= peakVec.end() ? it + windowDistance : peakVec.end()),
                std::back_inserter(tmpPeaks),
                [&it](const Peak &a) -> bool {
                    return (std::abs(a.getTime() - it->getTime()) >= Consts::MinWinDistanceF) && (a.compareBand(*it));
                });

        for (const auto &a:tmpPeaks)
            this->push_back(Link(*it, a));

        tmpPeaks.clear();
    }
}

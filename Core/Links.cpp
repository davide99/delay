#include "Links.h"
#include <algorithm>

Core::Links::Links(const std::vector<Peak> &peakVec) {
    float timeStep = (float) Consts::StepSize / Consts::SampleRate;
    std::size_t windowDistance = Consts::maxWinDistance / timeStep;

    for (auto it = peakVec.begin() + windowDistance; it != peakVec.end(); it++) {
        std::vector<Peak> tmpPeaks;

        std::copy_if(
                (it - windowDistance >= peakVec.begin() ? it - windowDistance : peakVec.begin()),
                it - 1,
                std::back_inserter(tmpPeaks),
                [&it](const Peak &a) -> bool {
                    return ((a.getTime() - it->getTime()) >= Consts::minWinDistance) && (a.compareBand(*it));
                    //return ((std::abs(a.getTime() - it->getTime())) >= Consts::minWinDistance) && (a.compareBand(*it));
                });

        for (const auto &a:tmpPeaks)
            this->push_back(Link(*it, a));
    }
}

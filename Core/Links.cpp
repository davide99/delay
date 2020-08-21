#include "Links.h"
#include <algorithm>

Core::Links::Links(const std::vector<Peak> &peakVec) {
    for (auto it = peakVec.begin(); it != peakVec.end() - 1; it++) {
        std::vector<Peak> tmpPeaks;

        std::copy_if(it + 1, peakVec.end(),         //Sub vector from it+1 to the end
                     std::back_inserter(tmpPeaks),
                     [&it](const Peak &a) -> bool {
                         float delta = a.getTime() - it->getTime();

                         /*
                          * Time difference must be between 1 and 3 and
                          * the peaks should be in the same band
                          */

                         return (delta >= 1.0f) && (delta < 3.0f) && (a.compareBand(*it));
                     });

        for (const auto &a:tmpPeaks)
            this->push_back(Link(*it, a));
    }
}

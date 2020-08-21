#include "Links.h"
#include <algorithm>

Core::Links::Links(const std::vector<Peak> &peakVec) {
    for (auto it = peakVec.begin(); it != peakVec.end() - 1; it++) {
        std::vector<Peak> tmpPeaks;

        std::copy_if(it + 1, peakVec.end(),         //Sub vector from it+1 to the end
                     std::back_inserter(tmpPeaks),
                     [&it](const Peak &a) -> bool {
                         bool b;

                         //Time difference not less than 1
                         b = a.getTime() - it->getTime() >= 1.0f;
                         //Time difference not more than 3
                         b = b && a.getTime() - it->getTime() < 3.0f;
                         //In the same band too
                         b = b && a.compareBand(*it);

                         return b;
                     });

        for (const auto &a:tmpPeaks)
            this->push_back(Link(*it, a));
    }
}

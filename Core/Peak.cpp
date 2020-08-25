#include "Peak.h"
#include <algorithm>

const int &Core::Peak::getFreqIndex() const {
    return this->freqIndex;
}

const std::size_t &Core::Peak::getWindow() const {
    return this->window;
}

std::size_t Core::Peak::getBand() const {
    auto iter = std::lower_bound(Consts::Bands.begin(), Consts::Bands.end(), this->freqIndex);

    if (iter != Consts::Bands.end())
        return std::distance(Consts::Bands.begin(), iter);
    else
        return SIZE_MAX;
}

bool Core::Peak::sameBand(const Peak &peak) const {
    int thisBand = this->getBand();

    return (thisBand == peak.getBand()) && (thisBand != SIZE_MAX);
}

bool Core::Peak::operator<(const Peak &peak) const {
    return this->power < peak.power;
}

const float &Core::Peak::getTime() const {
    return this->time;
}

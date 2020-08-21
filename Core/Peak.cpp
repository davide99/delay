#include "Peak.h"

const decltype(Consts::FreqBins) &Core::Peak::getFreqIndex() const {
    return this->freqIndex;
}

const std::size_t &Core::Peak::getWindow() const {
    return this->window;
}

int Core::Peak::getBand() const {
    for (int i = 0; i < Consts::Bands.size() - 1; i++)
        if (Consts::Bands[i + 1] > this->freqIndex)
            return i;

    return -1;
}

bool Core::Peak::compareBand(Peak peak) const {
    int thisBand = this->getBand();

    return (thisBand == peak.getBand()) && (thisBand != -1);
}

bool Core::Peak::operator<(const Peak &peak) const {
    return this->power < peak.power;
}

const float &Core::Peak::getTime() const {
    return this->time;
}

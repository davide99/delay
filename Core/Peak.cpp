#include "Peak.h"

const int &Core::Peak::getFreqIndex() const {
    return this->freqIndex;
}

const std::size_t &Core::Peak::getWindow() const {
    return this->window;
}

bool Core::Peak::sameBand(const Peak &peak) const {
    return this->bandIndex == peak.bandIndex;
}

bool Core::Peak::operator<(const Peak &peak) const {
    return this->power < peak.power;
}

const float &Core::Peak::getTime() const {
    return this->time;
}

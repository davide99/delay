#include "Peak.h"
#include "../Math/Window.h"
#include <algorithm>

const int &Core::Peak::getFreqIndex() const {
    return this->freqIndex;
}

const std::size_t &Core::Peak::getWindow() const {
    return this->window;
}

std::size_t Core::Peak::getBand() const {
    const auto &bands = Math::Window::getBands();
    auto iter = std::lower_bound(bands.begin(), bands.end(), this->freqIndex);

    if (iter != bands.end())
        return std::distance(bands.begin(), iter);
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

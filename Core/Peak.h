#ifndef STRUCTURES_PEAK_H
#define STRUCTURES_PEAK_H

#include "../Consts.h"
#include <cstdint>
#include <type_traits>

namespace Core{
    class Peak {
    private:
        std::remove_const_t<decltype(Consts::FreqBins)> freqIndex;
        float power;
        std::size_t window;
        float time;

    public:
        Peak(decltype(Consts::FreqBins) freqIndex, float power, std::size_t window, float time) :
                freqIndex(freqIndex), power(power), window(window), time(time) {};

        [[nodiscard]] const decltype(Consts::FreqBins) &getFreqIndex() const;

        [[nodiscard]] const std::size_t &getWindow() const;

        [[nodiscard]] const float &getTime() const;

        [[nodiscard]] bool compareBand(Peak peak) const;

        bool operator<(const Peak &peak) const;

    private:
        [[nodiscard]] int getBand() const;

    };
}


#endif

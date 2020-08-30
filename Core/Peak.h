#ifndef STRUCTURES_PEAK_H
#define STRUCTURES_PEAK_H

#include "../Consts.h"
#include <cstdint>
#include <type_traits>
#include "../Math/Window.h"

namespace Core {
    class Peak {
    private:
        int freqIndex;
        float power;
        std::size_t window;
        float time;
        int bandIndex;

    public:
        Peak(const int &freqIndex, const float &power, const std::size_t &window, const float &time) :
                freqIndex(freqIndex), power(power), window(window), time(time),
                bandIndex(Math::Window::getBandIndex(freqIndex)) {};

        [[nodiscard]] const int &getFreqIndex() const;

        [[nodiscard]] const std::size_t &getWindow() const;

        [[nodiscard]] const float &getTime() const;

        [[nodiscard]] bool sameBand(const Peak &peak) const;

        bool operator<(const Peak &peak) const;

    };
}


#endif

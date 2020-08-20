#ifndef MATH_INTEGERS_H
#define MATH_INTEGERS_H

#include <cstdint>

namespace Math::Integers {
    uint64_t little2Big(const uint64_t &x);

    uint32_t little2Big(const uint32_t &x);

    uint16_t little2Big(const uint16_t &x);

    int16_t little2Big(const int16_t &x);
}

#endif

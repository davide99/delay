#ifndef MATH_INTEGERS_H
#define MATH_INTEGERS_H

#include <cstdint>
#include <string>

namespace Math::Integers {
    std::uint64_t BSwap(const std::uint64_t &x);

    std::uint32_t BSwap(const std::uint32_t &x);

    std::uint16_t BSwap(const std::uint16_t &x);

    std::int16_t BSwap(const std::int16_t &x);

    std::int64_t BSwap(const std::int64_t &x);

    std::string_view toHex(std::uint64_t x);
}

#endif

#include "Integers.h"
#include <immintrin.h>
#include <iostream>

std::uint32_t Math::Integers::BSwap(const std::uint32_t &x) {
    return __bswap_32(x);
}

std::uint16_t Math::Integers::BSwap(const std::uint16_t &x) {
    return __bswap_16(x);
}

std::int16_t Math::Integers::BSwap(const std::int16_t &x) {
    std::uint16_t val_u = *(std::uint16_t *) &x;  //Convert to unsigned
    val_u = BSwap(val_u);               //Convert to big endian
    return *(std::int16_t *) &val_u;         //Make it signed
}

std::uint64_t Math::Integers::BSwap(const std::uint64_t &x) {
    return __bswap_64(x);
}

constexpr std::uint64_t P01 = 10u;
constexpr std::uint64_t P02 = 100u;
constexpr std::uint64_t P03 = 1000u;
constexpr std::uint64_t P04 = 10000u;
constexpr std::uint64_t P05 = 100000u;
constexpr std::uint64_t P06 = 1000000u;
constexpr std::uint64_t P07 = 10000000u;
constexpr std::uint64_t P08 = 100000000u;
constexpr std::uint64_t P09 = 1000000000u;
constexpr std::uint64_t P10 = 10000000000u;
constexpr std::uint64_t P11 = 100000000000u;
constexpr std::uint64_t P12 = 1000000000000u;

static inline std::uint32_t digits10(const std::uint64_t &x) {
    if (x < P01) return 1u;
    if (x < P02) return 2u;
    if (x < P03) return 3u;

    if (x < P12) {
        if (x < P08) {
            if (x < P06) {
                if (x < P04) return 4u;
                return 5u + (x >= P05);
            }

            return 7u + (x >= P07);
        }

        if (x < P10)
            return 9u + (x >= P09);

        return 11u + (x >= P11);
    }

    return 12u + digits10(x / P12);
}

std::string Math::Integers::ToString(std::uint64_t x) {
    constexpr char digits[] = "0001020304050607080910111213141516171819"
                              "2021222324252627282930313233343536373839"
                              "4041424344454647484950515253545556575859"
                              "6061626364656667686970717273747576777879"
                              "8081828384858687888990919293949596979899";

    auto const length = digits10(x);
    std::string s(length, '*');
    auto nextIt = s.end() - 1;

    while (x >= 100) {
        auto const i = (x % 100) << 1u;
        x /= 100;
        *nextIt = digits[i + 1];
        nextIt--;
        *nextIt = digits[i];
        nextIt--;
    }

    //Handle last 1-2 digits
    if (x < 10) {
        *nextIt = '0' + static_cast<std::uint32_t>(x);
    } else {
        auto i = static_cast<std::uint32_t>(x) << 1u;
        *nextIt = digits[i + 1];
        nextIt--;
        *nextIt = digits[i];
    }

    return s;
}

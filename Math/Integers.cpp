#include "Integers.h"
#include <immintrin.h>

inline std::uint32_t Math::Integers::BSwap(const std::uint32_t &x) {
    return __bswap_32(x);
}

inline std::uint16_t Math::Integers::BSwap(const std::uint16_t &x) {
    return __bswap_16(x);
}

std::int16_t Math::Integers::BSwap(const std::int16_t &x) {
    std::uint16_t val_u = *(std::uint16_t *) &x;  //Convert to unsigned
    val_u = BSwap(val_u);               //Convert to big endian
    return *(std::int16_t *) &val_u;         //Make it signed
}

inline std::uint64_t Math::Integers::BSwap(const std::uint64_t &x) {
    return __bswap_64(x);
}

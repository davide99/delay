#include "Integers.h"
#include <immintrin.h>

uint32_t Math::Integers::BSwap(const uint32_t &x) {
    return __bswap_32(x);
}

uint16_t Math::Integers::BSwap(const uint16_t &x) {
    return __bswap_16(x);
}

int16_t Math::Integers::BSwap(const int16_t &x) {
    uint16_t val_u = *(uint16_t *) &x;  //Convert to unsigned
    val_u = BSwap(val_u);               //Convert to big endian
    return *(int16_t *) &val_u;         //Make it signed
}

uint64_t Math::Integers::BSwap(const uint64_t &x) {
    return __bswap_64(x);
}

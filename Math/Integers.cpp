#include "Integers.h"

uint32_t Math::Integers::little2Big(const uint32_t &x) {
    return (x >> 24u) | ((x >> 8u) & 0xFF00u) | ((x << 8u) & 0xFF0000u) | ((x << 24u) & 0xFF000000u);
}

uint16_t Math::Integers::little2Big(const uint16_t &x) {
    return ((uint16_t) (x >> 8u) & 0xFF00u) | (uint16_t) (x << 8u);
}

int16_t Math::Integers::little2Big(const int16_t &x) {
    uint16_t val_u = *(uint16_t *) &x;  //Convert to unsigned
    val_u = little2Big(val_u);          //Convert to big endian
    return *(int16_t *) &val_u;         //Make it signed
}

#include "Utils.h"
#include <unistd.h>
#include <cstdint>

bool Utils::fileExists(const std::string &fileName) {
    return access(fileName.c_str(), F_OK) == 0;
}

bool Utils::isBigEndian() {
    uint16_t n = 0x01u;
    auto *ptr = reinterpret_cast<uint8_t *>(&n);

    return ptr[0] == 0;
}

uint32_t Utils::swap32(const uint32_t &x) {
    uint32_t ret;

    ret = x >> 24u;
    ret |= (x >> 8u) & 0xFF00u;
    ret |= (x << 8u) & 0xFF0000u;
    ret |= (x << 24u) & 0xFF000000u;

    return ret;
}

uint16_t Utils::swap16(const uint16_t &x) {
    uint16_t ret;

    ret = x >> 8u;
    ret |= (uint16_t)(x << 8u) & 0xFF00u;

    return ret;
}

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

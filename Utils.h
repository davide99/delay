#ifndef FIN_CPP_UTILS_H
#define FIN_CPP_UTILS_H

#include <string>

namespace Utils {
    bool fileExists(const std::string& fileName);

    bool isBigEndian();

    uint32_t swap32(const uint32_t &x);

    uint16_t swap16(const uint16_t &x);
}

#endif

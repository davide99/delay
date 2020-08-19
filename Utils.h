#ifndef FIN_CPP_UTILS_H
#define FIN_CPP_UTILS_H

#include <string>

namespace Utils {
    bool fileExists(const std::string& fileName);

    bool isBigEndian();
}

#endif

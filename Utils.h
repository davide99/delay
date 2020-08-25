#ifndef FIN_CPP_UTILS_H
#define FIN_CPP_UTILS_H

#include <string>
#include <vector>

namespace Utils {
    bool fileExists(const std::string &fileName);

    bool isBigEndian();

    std::vector<std::string> listFiles(const std::string &path);
}

#endif

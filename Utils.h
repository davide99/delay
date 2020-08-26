#ifndef FIN_CPP_UTILS_H
#define FIN_CPP_UTILS_H

#include <string>
#include <vector>

namespace Utils {
    bool fileExists(const std::string &fileName);

    bool isBigEndian();

    bool endsWith(const std::string &str, const std::string &ending);

    std::vector<std::string> listFiles(const std::string &path, const std::string &extension = "");
}

#endif

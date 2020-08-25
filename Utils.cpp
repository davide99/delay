#include "Utils.h"
#include <unistd.h>
#include <cstdint>
#include <filesystem>

bool Utils::fileExists(const std::string &fileName) {
    return access(fileName.c_str(), F_OK) == 0;
}

bool Utils::isBigEndian() {
    uint16_t n = 0x0001u;
    auto *ptr = reinterpret_cast<uint8_t *>(&n);

    return ptr[0] == 0;
}

std::vector<std::string> Utils::listFiles(const std::string &path) {
    namespace fs = std::filesystem;
    std::vector<std::string> files;

    for (const auto &p : fs::directory_iterator(path))
        if (!p.is_directory())
            files.push_back(p.path().string());

    return files;
}

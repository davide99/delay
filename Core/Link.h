#ifndef CORE_LINK_H
#define CORE_LINK_H

#include <cstdint>
#include <array>
#include "Peak.h"
#include "../Utils.h"
#include "../Math/Integers.h"
#include <openssl/sha.h>
#include <string>

namespace Core {
    class Link {
    private:
        std::array<std::uint8_t, 20> hash;
        size_t window;
    public:
        Link(Peak address, Peak peak) {
            auto deltaTime = peak.getWindow() - address.getWindow();
            auto deltaFreq = peak.getFreqIndex() - address.getFreqIndex();
            auto addrFreq = address.getFreqIndex();

            std::string s = std::to_string(deltaTime) + std::to_string(deltaFreq) + std::to_string(addrFreq);
            const unsigned char str[s.length()] = s.c_str();
            SHA1(reinterpret_cast<const unsigned char *>(s.c_str()), s.size(), hash.data());
        }
    };
}


#endif

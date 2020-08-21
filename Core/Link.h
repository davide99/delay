#ifndef CORE_LINK_H
#define CORE_LINK_H

#include <cstdint>
#include <array>
#include "Peak.h"
#include "../Utils.h"
#include "../Math/Integers.h"
#include <string>
#include <vector>

namespace Core {
    class Link {
    private:
        std::size_t hash;
        std::size_t time;
    public:
        Link(Peak address, Peak peak) {
            std::uint64_t deltaTime = peak.getWindow() - address.getWindow();
            std::uint64_t deltaFreq = peak.getFreqIndex() - address.getFreqIndex();
            std::uint64_t addrFreq = address.getFreqIndex();

            std::vector<uint64_t> vec = {deltaTime, deltaFreq, addrFreq};
            this->hash = stupidHash(vec);

            this->time = address.getWindow();
        }

        const std::size_t &getHash(){
            return hash;
        }

        const std::size_t &getTime(){
            return time;
        }

    private:
        static std::size_t stupidHash(const std::vector<uint64_t> &vec) {
            std::size_t seed = vec.size();

            for (auto &val:vec)
                seed ^= 0x9e3779b9u + (seed << 6u) + (seed >> 2u);

            return seed;
        }
    };
}


#endif

#ifndef CORE_LINK_H
#define CORE_LINK_H

#include <cstdint>
#include "Peak.h"

namespace Core {
    class Link {
    private:
        std::uint64_t hash;
        std::size_t time;
    public:
        Link(Peak address, Peak peak);

        [[nodiscard]] const std::size_t &getHash() const;

        [[nodiscard]] const std::size_t &getTime() const;
    };
}


#endif

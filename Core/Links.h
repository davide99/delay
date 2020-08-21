#ifndef CORE_LINKS_H
#define CORE_LINKS_H

#include <vector>
#include "Link.h"
#include "Peak.h"

namespace Core {
    class Links : public std::vector<Link> {
    public:
        explicit Links(const std::vector<Peak> &a);
    };
}


#endif

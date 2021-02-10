#ifndef FIN_CPP_GENERICREADER_H
#define FIN_CPP_GENERICREADER_H

#include <cstdint>

namespace IO {
    class GenericReader {
    public:
        virtual const float *ptrAt(const std::size_t &pos) const = 0;
        [[nodiscard]] virtual const std::size_t &getNumberOfSamples() const = 0;
    };
}


#endif

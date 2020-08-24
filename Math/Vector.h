#ifndef MATH_VECTOR_H
#define MATH_VECTOR_H

#include <cstdint>
#include <algorithm>
#include <functional>

namespace Math::Vector {

    template<typename T>
    inline void mul(const T *v1, const T *v2, T *out, std::size_t len) {
        std::transform(v1, v1 + len, v2, out, std::multiplies<T>());
    }
}

#endif

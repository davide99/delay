#ifndef MATH_WINDOW_H
#define MATH_WINDOW_H

#include "../Consts.h"

namespace Math::Window {
    namespace {
        float window[Consts::WinSize];
        bool initialized = false;
    }

    float *get();
}

#endif

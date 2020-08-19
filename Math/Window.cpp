#include "Window.h"
#include <type_traits>
#include <cmath>

float *Math::Window::get() {
    if (!Math::Window::initialized)
        for (std::remove_const_t<decltype(Consts::WinSize)> i = 0; i < Consts::WinSize; i++)
            window[i] = (float) (0.5f * (1 - std::cos(2 * M_PI * i / (Consts::WinSize - 1))));

    return Math::Window::window;
}

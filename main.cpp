#include <iostream>
#include "IO/WavReader.h"

int main() {
    WavReader wavReader("../out.wav");

    for (auto const &value : wavReader.getData())
        std::cout << value << "\n";

    return 0;
}

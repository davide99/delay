#include <iostream>
#include "WavReader.h"

int main() {
    WavReader wavReader("../out.wav");

    std::cout << wavReader.getData().at(0);

    for (auto const &value : wavReader.getData())
        std::cout << value << "\n";

    return 0;
}

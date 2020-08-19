#include <iostream>
#include "IO/WavReader.h"
#include "Structures/MaxFixedHeap.h"
#include <functional>

using namespace Structures;

int main() {
    //IO::WavReader wavReader("../out.wav");

    //for (auto const &value : wavReader.getData())
    //    std::cout << value << "\n";

    MaxFixedHeap<float> fixedSizeHeap(4);

    for (int i = 0; i < 6; i++)
        fixedSizeHeap.push(i);

    for (auto &value:fixedSizeHeap)
        std::cout << value << std::endl;

    return 0;
}

#include <iostream>
#include "IO/WavReader.h"
#include "Math/Spectrogram.h"
#include <fstream>

int main() {
    IO::WavReader wavReader("../out.wav");
    Math::Spectrogram spectrogram(wavReader.getData());
    std::ofstream file("fft.txt");

    for (auto &value:spectrogram[0].getData())
        file << std::abs(value) << std::endl;

    file.close();

    return 0;
}

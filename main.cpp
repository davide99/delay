#include <iostream>
#include "IO/WavReader.h"
#include "Math/Spectrogram.h"
#include "Core/Peak.h"
#include <fstream>
#include <vector>
#include <algorithm>

using namespace Core;

int main() {
    IO::WavReader wavReader("../out.wav");
    Math::Spectrogram spectrogram(wavReader.getData());



    return 0;
}

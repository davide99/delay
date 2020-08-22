#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "IO/WavReader.h"
#include "Math/Spectrogram.h"
#include "Core/Fingerprint.h"
#include "Core/Peak.h"
#include "Core/Links.h"

void original() {
    IO::WavReader wavReader("../out.wav");
    Math::Spectrogram spectrogram(wavReader.getData());
    std::vector<Core::Peak> peaks = Core::Fingerprint::compute(spectrogram);
    Core::Links links = Core::Links(peaks);

    std::ofstream o("../links.txt");

    for (Core::Link link: links)
        o << link.getHash() << ";" << link.getTime() << std::endl;

    o.close();
}

void mic() {
    IO::WavReader wavReader("../mic.wav");
    Math::Spectrogram spectrogram(wavReader.getData());
    std::vector<Core::Peak> peaks = Core::Fingerprint::compute(spectrogram);
    Core::Links links = Core::Links(peaks);

    std::ofstream o("../links_mic.txt");

    for (Core::Link link: links)
        o << link.getHash() << ";" << link.getTime() << std::endl;

    o.close();
}

int main() {
    //original();
    //mic();

    std::stringstream s;
    s << "proca";
    s.seekp(-1, std::ios_base::end);
    s << "b";

    std::cout << s.str();

    return 0;
}

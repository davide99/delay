#include <vector>
#include <iostream>
#include <chrono>
#include "IO/WavReader.h"
#include "Math/Spectrogram.h"
#include "Core/Fingerprint.h"
#include "Core/Links.h"
#include "IO/DB.h"

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    IO::WavReader wavReader("../out.wav");
    Math::Spectrogram spectrogram(wavReader.getData());
    std::vector<Core::Peak> peaks = Core::Fingerprint::compute(spectrogram);
    Core::Links links = Core::Links(peaks);

    IO::DB db;
    db.drop();
    db.create();
    db.insertSong(wavReader.getFileName(), links);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << duration << std::endl;

    /*IO::WavReader wavMic("../mic.wav");
    Math::Spectrogram specMic(wavMic.getData());
    std::vector<Core::Peak> peaksMic = Core::Fingerprint::compute(specMic);
    Core::Links linksMic = Core::Links(peaksMic);

    std::uint64_t id;
    db.searchIdGivenLinks(id, linksMic);

    std::cout << id;*/

    return 0;
}

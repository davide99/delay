#include <vector>
#include <iostream>
#include <chrono>
#include "IO/WavReader.h"
#include "Math/Spectrogram.h"
#include "Core/Fingerprint.h"
#include "Core/Links.h"
#include "IO/DB.h"
#include "Utils.h"

void addWav(const std::string &fileName, IO::DB &db) {
    auto start = std::chrono::high_resolution_clock::now();

    IO::WavReader wavReader(fileName);
    Math::Spectrogram spectrogram(wavReader.getData());
    std::vector<Core::Peak> peaks = Core::Fingerprint::compute(spectrogram);
    Core::Links links = Core::Links(peaks);

    db.insertSong(fileName, links);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << duration << std::endl;
}

int main() {
    std::vector<std::string> fileList = Utils::listFiles(".");

    IO::DB db;
    db.drop();
    db.create();

    for (const auto &file:fileList)
        addWav(file, db);


    /*IO::WavReader wavMic("../mic.wav");
    Math::Spectrogram specMic(wavMic.getData());
    std::vector<Core::Peak> peaksMic = Core::Fingerprint::compute(specMic);
    Core::Links linksMic = Core::Links(peaksMic);

    std::uint64_t id;
    db.searchIdGivenLinks(id, linksMic);

    std::cout << id;*/

    return 0;
}

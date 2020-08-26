#include <vector>
#include <iostream>
#include <chrono>
#include "Utils/Utils.h"
#include "Utils/Wrapper.h"

int main(int argc, char **argv) {
    if (argc != 2)
        std::cerr << "Remember to pass the path of the WAV directory" << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::string> fileList = Utils::listFiles(std::string(argv[1]), "wav");
    IO::DB db;

    for (const auto &fileName:fileList)
        Utils::insertSong(fileName, db);

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

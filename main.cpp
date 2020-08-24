#include <vector>
#include <iostream>
#include "IO/WavReader.h"
#include "Math/Spectrogram.h"
#include "Core/Fingerprint.h"
#include "Core/Peak.h"
#include "Core/Links.h"
#include "IO/DB.h"

int main() {
    IO::WavReader wavReader("../out.wav");
    Math::Spectrogram spectrogram(wavReader.getData());
    std::vector<Core::Peak> peaks = Core::Fingerprint::compute(spectrogram);
    Core::Links links = Core::Links(peaks);

    IO::DB db;
    db.drop();
    db.create();
    db.insertSong(wavReader.getFileName(), links);

    IO::WavReader wavMic("../mic.wav");
    Math::Spectrogram specMic(wavMic.getData());
    std::vector<Core::Peak> peaksMic = Core::Fingerprint::compute(specMic);
    Core::Links linksMic = Core::Links(peaksMic);

    std::uint64_t id;
    db.searchIdGivenLinks(id, linksMic);

    std::cout << id;

    return 0;
}

#ifndef UTILS_WRAPPER_H
#define UTILS_WRAPPER_H

#include <string>
#include "../IO/DB.h"
#include "../IO/WavReader.h"
#include "../Math/Spectrogram.h"
#include "../Core/Fingerprint.h"

namespace Utils {
    void insertSong(const std::string &fileName, IO::DB &db) {
        IO::WavReader wavReader(fileName);
        Math::Spectrogram spectrogram(wavReader.getData());
        std::vector<Core::Peak> peaks = Core::Fingerprint::compute(spectrogram);
        Core::Links links = Core::Links(peaks);

        db.insertSong(fileName, links);
    }
};


#endif

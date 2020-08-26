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

    std::string search(const std::string &fileName, IO::DB &db) {
        IO::WavReader wavMic(fileName);
        Math::Spectrogram specMic(wavMic.getData());
        std::vector<Core::Peak> peaksMic = Core::Fingerprint::compute(specMic);
        Core::Links linksMic = Core::Links(peaksMic);

        std::uint64_t id;
        if (db.searchIdGivenLinks(id, linksMic))
            return db.getSongNameById(id);
        else
            return "";
    }
};


#endif

#ifndef UTILS_WRAPPER_H
#define UTILS_WRAPPER_H

#include <string>
#include "../IO/DB.h"
#include "../IO/WavReader.h"
#include "../Math/Spectrogram.h"
#include "../Core/Fingerprint.h"
#include "../Consts.h"

/*
 * Just a wrapper around the two main functions
 */
namespace Utils {
    /**
     * Insert a song in the database
     * @param fileName of the song
     * @param db initialized db object
     */
    void insertTrack(const std::string &fileName, IO::DB &db, const unsigned int &id) {
        IO::WavReader wavReader(fileName);
        Math::Spectrogram spectrogram(wavReader);
        std::vector<Core::Peak> peaks = Core::Fingerprint::compute(spectrogram);
        Core::Links links = Core::Links(peaks);

        db.insertTrack(id, links);
    }

    /**
     * Try to find a match for a recording
     * @param fileName of the recording
     * @param db initialized db object
     * @return the name of the sonf if found, an empty string otherwise
     */
    float findDelta(IO::DB &db) {
        int64_t a = db.findDelay();
        std::cout << "aa:" << a << std::endl;
        float windowDuration = ((float) Consts::Window::Size) / (float) Consts::Audio::SampleRate;
        return (float) db.findDelay() * windowDuration;
    }

    void saveToCSV(IO::DB &db, const std::string &fileName) {
        float windowDuration = ((float) Consts::Window::StepSize) / ((float) Consts::Audio::SampleRate);
        db.saveCommonToCSV(fileName, windowDuration);
    }
};


#endif

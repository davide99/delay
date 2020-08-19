#ifndef WAVREADER_H
#define WAVREADER_H

#include <string>
#include <vector>
#include <cstdint>

class WavReader {
private:
    std::vector<int16_t> data;
public:
    explicit WavReader(const std::string &fileName);

    const std::vector<int16_t> &getData();
};


#endif

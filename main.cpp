#include <iostream>
#include <chrono>
#include "Utils/Utils.h"
#include "Utils/Wrapper.h"
#include "Math/Integers.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "Wrong number of parameters, please use: " << argv[0] << " track1 track2" << std::endl;
        return 1;
    }

    auto track1 = Utils::trim(std::string(argv[1]));
    auto track2 = Utils::trim(std::string(argv[2]));

    IO::DB db;

    auto start = std::chrono::high_resolution_clock::now();

    std::cout << "Analyzing track1 " << std::endl;
    Utils::insertTrack(track1, db, 1);
    std::cout << "Analyzing track2 " << std::endl;
    Utils::insertTrack(track2, db, 2);

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now() - start).count() / 2;
    std::cout << "Mean time for each track: " << duration << "ms" << std::endl;

    auto delay = Utils::findDelta(db);
    std::cout << delay << std::endl;

    return 0;
}

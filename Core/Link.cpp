#include "Link.h"
#include "../Utils.h"
#include "../Math/Integers.h"
#include "../xxHash/xxh3.h"

Core::Link::Link(Peak address, Peak peak) {
    std::uint64_t deltaTime = peak.getWindow() - address.getWindow();
    std::uint64_t deltaFreq = peak.getFreqIndex() - address.getFreqIndex();
    std::uint64_t addrFreq = address.getFreqIndex();

    XXH3_state_t state;
    XXH3_64bits_reset(&state);

    if (Utils::isBigEndian()) {
        deltaTime = Math::Integers::BSwap(deltaTime);
        deltaFreq = Math::Integers::BSwap(deltaFreq);
        addrFreq = Math::Integers::BSwap(addrFreq);
    }

    XXH3_64bits_update(&state, &deltaTime, sizeof(deltaTime));
    XXH3_64bits_update(&state, &deltaFreq, sizeof(deltaFreq));
    XXH3_64bits_update(&state, &addrFreq, sizeof(addrFreq));

    this->hash = XXH3_64bits_digest(&state);
    this->time = address.getWindow();
}

const std::size_t &Core::Link::getHash() const {
    return this->hash;
}

const std::size_t &Core::Link::getTime() const {
    return this->time;
}


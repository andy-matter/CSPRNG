
#include "CSPRNG.h"


CSPRNG::CSPRNG(void) {
    _seeded = false;
}


CSPRNG::~CSPRNG(void) {
    _shake.clear();
}



ErrorCode CSPRNG::reseed(const void* seed, size_t seedLen) {
    if (seed == nullptr || seedLen == 0) {
        Log::Alarm("CSPRNG", "reseed failed: Invalid parameters");
        return ErrorCode::INVALID_PARAM;
    }

    _shake.reset();                    // Clear sponge
    _shake.update(seed, seedLen);      // Absorb new seed
    _seeded = true;
    Log::Trace("CSPRNG", "Re-Seeding done");
    return ErrorCode::OK;
}


ErrorCode CSPRNG::addSeed(const void* seed, size_t seedLen) {
    if (seed == nullptr || seedLen == 0) {
        Log::Alarm("CSPRNG", "addSeed failed: Invalid parameters");
        return ErrorCode::INVALID_PARAM;
    }

    _shake.update(seed, seedLen);      // Absorb new seed
    _seeded = true;
    Log::Trace("CSPRNG", "Add-Seed done");
    return ErrorCode::OK;
}



ErrorCode CSPRNG::randomArray(uint8_t &out, size_t len) {
    if (!_seeded) {
        Log::Alarm("CSPRNG", "RNG not seeded");
        return ErrorCode::NOT_INITIALIZED;
    }

    if (len == 0) {
        Log::Alarm("CSPRNG", "requested RNG output length is 0");
        return ErrorCode::INVALID_PARAM;
    }

    _shake.extend(&out, len);
    Log::Trace("CSPRNG", std::format("Generated {} random byte(s)", len));
    return ErrorCode::OK;
}


ErrorCode CSPRNG::randomByte(uint8_t& value) {
    value = 0;
    return randomArray(value, 1);
}


ErrorCode CSPRNG::randomLong(long& value) {
    value = 0;
    return randomArray(reinterpret_cast<uint8_t&>(value), sizeof(value));
}
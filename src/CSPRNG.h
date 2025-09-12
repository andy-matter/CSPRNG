#pragma once

#include <cstddef>
#include <cstdint>
#include "Core_SHAKE.h"
#include "ErrorCodes.h"
#include "Logger.h"


class CSPRNG {
public:

    CSPRNG(void);
    ~CSPRNG(void);

    /**
     * @brief Reseeds the CSPRNG with new seed material
     * @param seed Pointer to the seed data
     * @param seedLen Length of the seed data in bytes
     */
    ErrorCode reseed(const void* seed, size_t seedLen);

    /**
     * @brief Adds additional seed material to the CSPRNG state
     * @param seed Pointer to the seed data
     * @param seedLen Length of the seed data in bytes
     */
    ErrorCode addSeed(const void* seed, size_t seedLen);


    /**
     * @param out Reference to the buffer where random bytes will be written
     * @param len Number of random bytes to generate
     */
    ErrorCode randomArray(uint8_t &out, size_t len);

    /**
     * @param value Reference to a variable where the random byte will be stored
     */
    ErrorCode randomByte(uint8_t& value);

    /**
     * @param value Reference to a variable where the random long will be stored
     */
    ErrorCode randomLong(long& value);
    
    
private:
    Core_SHAKE256 _shake;
    bool _seeded = false;
};
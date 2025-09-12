#include "HardwareSerial.h"
#include "CSPRNG.h"

// Create a global CSPRNG object
CSPRNG rng;


// Custom log handler to redirect logs to Serial
void SerialLogHandler(int level, const std::string_view module, const std::string_view msg) {
    const char* out = std::format("{}:  [{}] {}", LOG_LEVEL_STRINGS[level], module, msg).c_str();
     Serial.println(out);  // Print log message over UART
}

// Example seed generator (replace with real hardware RNG on target platform)
void generateSeed(uint8_t *out, uint8_t outLen) {
    for (uint32_t i = 0; i < outLen; ++i) {
        out[i] = i;  // For demo only: predictable values (NOT secure!)
    }
}

// Helper function to print array values in HEX format
void PrintArray(uint8_t Arr[], uint32_t size) {
    for (size_t i = 0; i < size; i++) {
        Serial.print(Arr[i], HEX);
        Serial.print(", ");
    }
}


int main(void) {
    Serial.begin(115200);   // Start the serial port at 115200 baud
    Log::addLogger(SerialLogHandler);   // Register our Serial logger for debug output

    uint8_t seed[64] = {};     // Seed buffer (64 bytes)
    uint8_t randArr[32] = {};  // Output buffer (32 random bytes)

    generateSeed(seed, sizeof(seed));   // Fill seed buffer (replace with real entropy source)

    rng.reseed(seed, sizeof(seed));     // Initialize/reseed the CSPRNG with the seed
    rng.randomArray(randArr, sizeof(randArr));  // Generate random bytes into randArr

    PrintArray(randArr, sizeof(randArr));  // Print random array to Serial
    while(1) {}  // Keep running (embedded main loop)
}
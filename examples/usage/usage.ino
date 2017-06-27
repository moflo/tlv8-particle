// Example usage for TLV8 library by @moflome.

#include "TLV8.h"

// Initialize objects from the lib
TLV8Class tlv8;

void setup() {
    Particle.publish("TLV8 Setup");

    // Initialize TLV8
    struct tlv_map PairTagTLV8;
    memset(&PairTagTLV8, 0, sizeof(tlv_map));  

    const uint8_t len = 10;

    unsigned char buffer[len+1] = "\xff\x08testtest";

    tlv8.decode( buffer, len, &PairTagTLV8 );

    Particle.publish("TLV8 Object Count: ", PairTagTLV8.count );


}

void loop() {
}

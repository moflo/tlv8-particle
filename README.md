# TLV8

A Particle library for TLV encoding, for use with Apple's HomeKit.

## Background

This Particle.io library for encodng and decoding of TLV 8-bit structures per the open HomeKit specification.


## Usage

Connect Photon hardware, add the TLV8 library to your project and follow this simple example:

```
#include <tlv8.h>

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
```

See the [examples](examples) folder for more details.

## Documentation

More information online at GitHub [https://github.com/moflo/tlv8-particle](https://github.com/moflo/tlv8-particle)


## LICENSE
Copyright (c) 2017 @moflome.

EthernetBonjour is free software: you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation, either version 3 of
the License, or (at your option) any later version.

EthernetBonjour is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with EthernetBonjour. If not, see
<http://www.gnu.org/licenses/>.

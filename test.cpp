// Basic c++ test bench for testing Particle C code
/*
   g++ test.cpp tlv8.cpp -Wall -ggdb -std=c++0x -I. -O3 -fpermissive
   gcc2minix < a.out >test
   chmod +x test   # may not be necessary depending on your umask
   ./test

   Use online HEXDump tools to debug output: https://hexed.it

*/

#include "src/TLV8.h"

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

using namespace std;



void print_hex_memory(void *mem, int count) {
  int i;
  unsigned char *p = (unsigned char *)mem;
  for (i=0; i < count; i++) {
    printf("0x%02x ", p[i]);
    if ((i%16==0) && i)
      printf("\n");
  }
  printf("\n");
}

void assertNotEqual(uint8_t mem1, uint8_t mem2, const char * description, int * error_count ) {
    
    if (mem1 != mem2) {
        cout << "Error - " << description << ", got : " << (unsigned)mem1 << endl;
        (*error_count)++;
    }
}

int main()
{
    cout << "Starting Test.cpp ...\n\n" << endl;
    
    try {

        int error_count = 0;
        
        {
            cout << "Decode - Single string test ..." << endl;
            
            const uint8_t len = 10;

            unsigned char buffer[len+1] = "\xff\x08testtest";

            print_hex_memory( buffer, len );

            TLV8Class TLV8 = TLV8Class();

            struct tlv_map PairTagTLV8;
            memset(&PairTagTLV8, 0, sizeof(tlv_map));

            TLV8.decode( buffer, len, &PairTagTLV8 );

            cout << PairTagTLV8.object[0].data << endl;
            
            assertNotEqual(PairTagTLV8.count, 1, "count not 1", &error_count);
            
            assertNotEqual(PairTagTLV8.object[0].size, 8, "object size is not 8", &error_count);
            assertNotEqual(PairTagTLV8.object[0].type, '\xff', "object type is not FF", &error_count);
            assertNotEqual(PairTagTLV8.object[0].data[0], 't', "object data is not testtest", &error_count);
            
        }
        {
            
            cout << "Decode - Double string test ..." << endl;
            
            const uint8_t len = 13;
            
            unsigned char buffer[len+2] = "\xff\x04@@@@\x02\x05%%%%%";
            
            print_hex_memory( buffer, len );
            
            TLV8Class TLV8 = TLV8Class();
            
            struct tlv_map PairTagTLV8;
            memset(&PairTagTLV8, 0, sizeof(tlv_map));
            
            TLV8.decode( buffer, len, &PairTagTLV8 );
            
            cout << PairTagTLV8.object[0].data << endl;
            
            assertNotEqual(PairTagTLV8.count, 2, "count not 2", &error_count);
            
            assertNotEqual(PairTagTLV8.object[0].size, 4, "object size is not 4", &error_count);
            assertNotEqual(PairTagTLV8.object[0].type, '\xff', "object type is not FF", &error_count);
            assertNotEqual(PairTagTLV8.object[0].data[0], '@', "object data is not @", &error_count);
            
            assertNotEqual(PairTagTLV8.object[1].size, 5, "object size is not 5", &error_count);
            assertNotEqual(PairTagTLV8.object[1].type, '\x02', "object type is not 0x02", &error_count);
            assertNotEqual(PairTagTLV8.object[1].data[0], '%', "object data is not @", &error_count);
        }
        {
            
            cout << "Decode - Apple test 12.1.12 (1)..." << endl;
            
            const uint8_t len = 10;
            
            unsigned char buffer[len+1] = "\x06\x01\x03\x01\x05hello";
            
            print_hex_memory( buffer, len );
            
            TLV8Class TLV8 = TLV8Class();
            
            struct tlv_map PairTagTLV8;
            memset(&PairTagTLV8, 0, sizeof(tlv_map));
            
            TLV8.decode( buffer, len, &PairTagTLV8 );
            
            cout << PairTagTLV8.object[0].data << endl;
            
            assertNotEqual(PairTagTLV8.count, 2, "count not 1", &error_count);
            
            assertNotEqual(PairTagTLV8.object[0].size, 1, "object size is not 8", &error_count);
            assertNotEqual(PairTagTLV8.object[0].type, '\x06', "object type is not FF", &error_count);
            assertNotEqual(PairTagTLV8.object[0].data[0], 0x03, "object data is not 0x03", &error_count);
            
            assertNotEqual(PairTagTLV8.object[1].size, 5, "object size is not 8", &error_count);
            assertNotEqual(PairTagTLV8.object[1].type, 0x01, "object type is not 0x01", &error_count);
            assertNotEqual(PairTagTLV8.object[1].data[0], 'h', "object data is not 'h'", &error_count);
            
            
        }
        {
            
            cout << "Decode - Apple test 12.1.12 (2)..." << endl;
            
            const uint8_t len = 3+10+7;
            
            unsigned char buffer[len+1] = "\x06\x01\x03\x09\x08@@@@@@@@\x01\x05hello";
            
            print_hex_memory( buffer, len );
            
            TLV8Class TLV8 = TLV8Class();
            
            struct tlv_map PairTagTLV8;
            memset(&PairTagTLV8, 0, sizeof(tlv_map));
            
            TLV8.decode( buffer, len, &PairTagTLV8 );
            
            cout << PairTagTLV8.object[0].data << endl;
            
            assertNotEqual(PairTagTLV8.count, 3, "count not 3", &error_count);
            
            assertNotEqual(PairTagTLV8.object[0].size, 1, "object size is not 8", &error_count);
            assertNotEqual(PairTagTLV8.object[0].type, 0x06, "object type is not 0x06", &error_count);
            assertNotEqual(PairTagTLV8.object[0].data[0], 0x03, "object data is not 0x03", &error_count);
            
            assertNotEqual(PairTagTLV8.object[1].size, 8, "object 1 size is not 8", &error_count);
            assertNotEqual(PairTagTLV8.object[1].type, 0x09, "object 1 type is not 0x09", &error_count);
            assertNotEqual(PairTagTLV8.object[1].data[0], '@', "object 1 data is not @", &error_count);
            
            assertNotEqual(PairTagTLV8.object[2].size, 5, "object 2 size is not 8", &error_count);
            assertNotEqual(PairTagTLV8.object[2].type, 0x01, "object 2 type is not 0x01", &error_count);
            assertNotEqual(PairTagTLV8.object[2].data[0], 'h', "object 2 data is not 'h'", &error_count);
            
            
        }
        {
            
            cout << "Decode - Apple test 12.1.12 (3)..." << endl;
            
            const uint16_t len = 3+257+7;
            
            unsigned char buffer[len+1] = "\x06\x01\x03\x09\xff@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\x01\x05hello";
            
            print_hex_memory( buffer, len );
            
            TLV8Class TLV8 = TLV8Class();
            
            struct tlv_map PairTagTLV8;
            memset(&PairTagTLV8, 0, sizeof(tlv_map));
            
            TLV8.decode( buffer, len, &PairTagTLV8 );
            
            cout << PairTagTLV8.object[0].data << endl;
            
            assertNotEqual(PairTagTLV8.count, 3, "count not 3", &error_count);
            
            assertNotEqual(PairTagTLV8.object[0].size, 1, "object size is not 8", &error_count);
            assertNotEqual(PairTagTLV8.object[0].type, 0x06, "object type is not 0x06", &error_count);
            assertNotEqual(PairTagTLV8.object[0].data[0], 0x03, "object data is not 0x03", &error_count);
            
            assertNotEqual(PairTagTLV8.object[1].size, 255, "object 1 size is not 255", &error_count);
            assertNotEqual(PairTagTLV8.object[1].type, 0x09, "object 1 type is not 0x09", &error_count);
            assertNotEqual(PairTagTLV8.object[1].data[0], '@', "object 1 data is not @", &error_count);
            
            assertNotEqual(PairTagTLV8.object[2].size, 5, "object 2 size is not 8", &error_count);
            assertNotEqual(PairTagTLV8.object[2].type, 0x01, "object 2 type is not 0x01", &error_count);
            assertNotEqual(PairTagTLV8.object[2].data[0], 'h', "object 2 data is not 'h'", &error_count);
            
            
        }
        {
            
            cout << "Decode - Apple test 12.1.12 (3)..." << endl;
            
            const uint16_t len = 3+257+47+7;
            
            unsigned char buffer[len+1] = "\x06\x01\x03\x09\xff@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\x09\x2D@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\x01\x05hello";
            
            print_hex_memory( buffer, len );
            
            TLV8Class TLV8 = TLV8Class();
            
            struct tlv_map PairTagTLV8;
            memset(&PairTagTLV8, 0, sizeof(tlv_map));
            
            TLV8.decode( buffer, len, &PairTagTLV8 );
            
            cout << PairTagTLV8.object[0].data << endl;
            
            assertNotEqual(PairTagTLV8.count, 3, "count not 3", &error_count);
            
            assertNotEqual(PairTagTLV8.object[0].size, 1, "object size is not 8", &error_count);
            assertNotEqual(PairTagTLV8.object[0].type, 0x06, "object type is not 0x06", &error_count);
            assertNotEqual(PairTagTLV8.object[0].data[0], 0x03, "object data is not 0x03", &error_count);
            
            assertNotEqual(PairTagTLV8.object[1].size, 300, "object 1 size is not 255", &error_count);
            assertNotEqual(PairTagTLV8.object[1].type, 0x09, "object 1 type is not 0x09", &error_count);
            assertNotEqual(PairTagTLV8.object[1].data[0], '@', "object 1 data is not @", &error_count);
            
            assertNotEqual(PairTagTLV8.object[2].size, 5, "object 2 size is not 8", &error_count);
            assertNotEqual(PairTagTLV8.object[2].type, 0x01, "object 2 type is not 0x01", &error_count);
            assertNotEqual(PairTagTLV8.object[2].data[0], 'h', "object 2 data is not 'h'", &error_count);
            
            
        }
        {
            cout << "Encode - Single string test ..." << endl;
            
            const uint8_t len = 10;
            
            unsigned char buffer[len+1] = "\xff\x08testtest";
            
            print_hex_memory( buffer, len );
            
            TLV8Class TLV8 = TLV8Class();
            
            struct tlv_map PairTagTLV8;
            memset(&PairTagTLV8, 0, sizeof(tlv_map));
            
            TLV8.decode( buffer, len, &PairTagTLV8 );

            uint8_t *PairTagBuffer = NULL;
            uint32_t length = 0;
            
            TLV8.encode(&PairTagTLV8, &PairTagBuffer, &length);
            
            assertNotEqual(len, length, "size not equal to length", &error_count);

            for (int i = 0; i < length; i++) {
                char summary[32];
                sprintf(summary, "buffer char not equal at pos %d",i);
                assertNotEqual(buffer[i], PairTagBuffer[i], summary, &error_count);
                
            }
                
            assertNotEqual(PairTagBuffer[0], 0xff, "encode byte is not 0xff", &error_count);
            
        }
        {
            cout << "Encode - Double string test ..." << endl;
            
            const uint8_t len = 13;
            
            unsigned char buffer[len+2] = "\xff\x04@@@@\x02\x05%%%%%";
            
            print_hex_memory( buffer, len );
            
            TLV8Class TLV8 = TLV8Class();
            
            struct tlv_map PairTagTLV8;
            memset(&PairTagTLV8, 0, sizeof(tlv_map));
            
            TLV8.decode( buffer, len, &PairTagTLV8 );
            
            uint8_t *PairTagBuffer = NULL;
            uint32_t length = 0;
            
            TLV8.encode(&PairTagTLV8, &PairTagBuffer, &length);
            
            assertNotEqual(len, length, "size not equal to length", &error_count);
            
            for (int i = 0; i < length; i++) {
                char summary[32];
                sprintf(summary, "buffer char not equal at pos %d",i);
                assertNotEqual(buffer[i], PairTagBuffer[i], summary, &error_count);
                
            }
            
            assertNotEqual(PairTagBuffer[0], 0xff, "encode byte is not 0xff", &error_count);
            
        }
        {
            
            cout << "Encode - Apple test 12.1.12 (3)..." << endl;
            
            const uint16_t len = 3+257+47+7;
            
            unsigned char buffer[len+1] = "\x06\x01\x03\x09\xff@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\x09\x2D@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\x01\x05hello";
            
            print_hex_memory( buffer, len );
            
            TLV8Class TLV8 = TLV8Class();
            
            struct tlv_map PairTagTLV8;
            memset(&PairTagTLV8, 0, sizeof(tlv_map));
            
            TLV8.decode( buffer, len, &PairTagTLV8 );
            
            uint8_t *PairTagBuffer = NULL;
            uint32_t length = 0;
            
            TLV8.encode(&PairTagTLV8, &PairTagBuffer, &length);
            
            assertNotEqual(len, length, "encode decode length not equal", &error_count);
            
            assertNotEqual(PairTagTLV8.count, 0x03, "Encoded size not 0x03", &error_count);
            
            assertNotEqual(PairTagBuffer[0], 0xff, "encode byte is not 0xff", &error_count);
            
            
        }
        if (false) {
            cout << "Insert - insertion test ..." << endl;
            
            TLV8Class TLV8 = TLV8Class();
            
            struct tlv_map PairTagTLV8;
            memset(&PairTagTLV8, 0, sizeof(tlv_map));
            
            unsigned char buffer[9] = "deadbeef";
            
            struct tlv tlv1 = TLV8.TLVFromBuffer(buffer, 0x01, 8);
            
            TLV8.insert(&PairTagTLV8, tlv1);

            assertNotEqual(PairTagTLV8.count, 1, "size not equal to 1", &error_count);
            assertNotEqual(PairTagTLV8.object[0].type, 0x01, "object @ 0 type not equal to 0x01", &error_count);
            assertNotEqual(PairTagTLV8.object[0].size, 8, "object @ 0 size not equal to 1", &error_count);
            for (int i = 0; i < 8; i++) {
                char summary[64];
                sprintf(summary, "object @ 0 data char not equal at pos %d",i);
                assertNotEqual(PairTagTLV8.object[0].data[i], buffer[i], summary, &error_count);
                
            }

            uint8_t *PairTagBuffer = NULL;
            uint32_t length = 0;
            
            TLV8.encode(&PairTagTLV8, &PairTagBuffer, &length);
            
            assertNotEqual(length, 10, "size not equal to 3", &error_count);
            
        }
        {
            cout << "TLV8 - tlv data test ..." << endl;
            
            tlv_t tlvTest = tlv(0x11, 0x2);
            
            assertNotEqual(tlvTest.type, 0x11, "type not equal", &error_count);
            assertNotEqual(tlvTest.size, 0x01, "size not equal", &error_count);
            assertNotEqual(tlvTest.data[0], 0x2, "data not equal", &error_count);
            
        }
        {
            cout << "TLV8 - tlv alloc test ..." << endl;
            
            const char string[9] = "DEADBEEF";
            
            tlv_t tlvTest = tlv(0x0A, (uint8_t *)string, 8);
            
            assertNotEqual(tlvTest.type, 0x0A, "type not equal", &error_count);
            assertNotEqual(tlvTest.size, 0x08, "size not equal", &error_count);
            assertNotEqual(tlvTest.data[0], 'D', "data not equal", &error_count);
            assertNotEqual(tlvTest.data[1], 'E', "data not equal", &error_count);
            assertNotEqual(tlvTest.data[2], 'A', "data not equal", &error_count);
            assertNotEqual(tlvTest.data[3], 'D', "data not equal", &error_count);
            
        }
        {
            cout << "TLV8 - tlv_map creation test" << endl;
            
            tlv_map_t response;
            uint8_t key[17] = "DEADBEEFDEADBEEF";
            uint8_t salt[17] = "DEADBEEFDEADBEEF";
            
            response.count = 2;
            response.object[0] = tlv(0x11, 0x2);
            response.object[1] = tlv(0xDA, key, 16);
            response.object[2] = tlv(0x0A, salt, 16);
            
            assertNotEqual(response.count, 0x03, "count not equal", &error_count);
            
            assertNotEqual(response.object[0].type, 0x11, "type not equal", &error_count);
            assertNotEqual(response.object[0].size, 0x01, "size not equal", &error_count);
            assertNotEqual(response.object[0].data[0], 0x2, "data not equal", &error_count);
            
            assertNotEqual(response.object[1].type, 0xDA, "type not equal", &error_count);
            assertNotEqual(response.object[1].size, 0x10, "size not equal", &error_count);
            assertNotEqual(response.object[1].data[0], 'D', "data not equal", &error_count);
            
            assertNotEqual(response.object[2].type, 0x0A, "type not equal", &error_count);
            assertNotEqual(response.object[2].size, 0x10, "size not equal", &error_count);
            assertNotEqual(response.object[2].data[0], 'D', "data not equal", &error_count);
            
        }
        {
            cout << "TLV8 - tlv_map initialization test ..." << endl;
            
            tlv_map tlvMap = tlv_map();
            
            tlv_t tlvTest = tlv(0x11, 0x2);
            tlvMap.insert( tlvTest );
            
            assertNotEqual(tlvMap.count, 0x01, "count not equal", &error_count);
            
            assertNotEqual(tlvMap.object[0].type, 0x11, "type not equal", &error_count);
            assertNotEqual(tlvMap.object[0].size, 0x01, "size not equal", &error_count);
            assertNotEqual(tlvMap.object[0].data[0], 0x2, "data not equal", &error_count);
            
        }
        {
            cout << "TLV8 - tlv_map initialization option test ..." << endl;
            
            
            tlv_t tlv1 = tlv(0x11, 0x2);
            tlv_t tlv2 = tlv(0x22, 0x4);

            tlv_map tlvMap = tlv_map(tlv1, tlv2);

            assertNotEqual(tlvMap.count, 0x02, "count not equal", &error_count);
            
            assertNotEqual(tlvMap.object[0].type, 0x11, "type not equal", &error_count);
            assertNotEqual(tlvMap.object[0].size, 0x01, "size not equal", &error_count);
            assertNotEqual(tlvMap.object[0].data[0], 0x2, "data not equal", &error_count);

            assertNotEqual(tlvMap.object[1].type, 0x22, "type not equal", &error_count);
            assertNotEqual(tlvMap.object[1].size, 0x01, "size not equal", &error_count);
            assertNotEqual(tlvMap.object[1].data[0], 0x4, "data not equal", &error_count);

        }
        {
            cout << "TLV8 - tlv_map initialization long key test ..." << endl;
            
            tlv_map_t response = tlv_map();
            
            uint8_t salt[] = {
                0x59, 0x6f, 0x29, 0x06, 0x1b, 0xf3, 0xc6, 0x59, 0x92, 0x3d, 0x91, 0x12, 0x27, 0x54,
                0x09, 0xdd
            };
            
            uint32_t salt_len = sizeof(salt);
            
            uint8_t key[] = {
                0xa2, 0x22, 0x63, 0xf0, 0xd9, 0x67, 0xd2, 0xc7, 0x7c, 0xe6, 0xdb, 0x25, 0xbb, 0x79,
                0x12, 0xcd, 0x4e, 0xa7, 0xb1, 0xed, 0xb0, 0x76, 0x91, 0xff, 0x3f, 0x65, 0x9b, 0x89,
                0x25, 0x2d, 0x84, 0x12, 0xc7, 0xd2, 0x55, 0x4d, 0xd5, 0x80, 0xfe, 0x50, 0xc0, 0x0f,
                0xb4, 0x6e, 0x7f, 0x91, 0x75, 0x56, 0x8a, 0x75, 0xf0, 0xa4, 0xe1, 0x90, 0x54, 0xa7,
                0x8f, 0xe1, 0xd5, 0xf5, 0xa7, 0x3c, 0x93, 0x1c, 0xbd, 0x1e, 0x80, 0x7d, 0x5c, 0x42,
                0x23, 0x1a, 0xbc, 0xdd, 0x1a, 0xd6, 0xf6, 0x9b, 0xdc, 0x0c, 0xa3, 0x06, 0x0d, 0xfb,
                0x21, 0xa2, 0xac, 0x9f, 0xca, 0xdc, 0x91, 0x2d, 0x1f, 0xb4, 0x13, 0xd7, 0x95, 0xec,
                0x5b, 0x60, 0x5e, 0x38, 0x6f, 0x6c, 0xf2, 0x65, 0x60, 0x4f, 0xcc, 0xd4, 0xb6, 0x99,
                0xd1, 0xa8, 0x9b, 0x70, 0x6a, 0x78, 0x55, 0x2f, 0x2e, 0x6f, 0x08, 0x59, 0xbb, 0xae,
                0x8b, 0x19, 0xe2, 0xae, 0xd5, 0x08, 0x8c, 0x2d, 0x89, 0x6a, 0xe9, 0x75, 0x4b, 0xd8,
                0xbb, 0x38, 0x2b, 0xd7, 0xb6, 0x0e, 0xc8, 0xd0, 0xf0, 0xdd, 0xdb, 0x68, 0xf7, 0xd2,
                0x1e, 0x8b, 0xf0, 0x3d, 0x8a, 0x0d, 0x56, 0x43, 0x68, 0x33, 0x80, 0x5e, 0xa3, 0x67,
                0xf6, 0xbe, 0x86, 0xf2, 0xaa, 0x4b, 0xd3, 0x0f, 0x92, 0x48, 0x5a, 0x80, 0x82, 0xd6,
                0x76, 0x59, 0xef, 0x4d, 0xde, 0xd1, 0x65, 0x05, 0xfa, 0x3d, 0xa1, 0xb9, 0x08, 0x94,
                0xfe, 0xd8, 0x55, 0x73, 0x87, 0x80, 0xd4, 0x32, 0x1a, 0x85, 0x19, 0x53, 0x68, 0xa7,
                0x83, 0xa9, 0x09, 0xc9, 0xde, 0x8c, 0xb7, 0x90, 0x1a, 0xdd, 0xbf, 0x21, 0x40, 0x3a,
                0x49, 0xe3, 0xd6, 0x46, 0xf3, 0x62, 0x95, 0x5d, 0x78, 0x9c, 0xb3, 0x0b, 0x8d, 0xcf,
                0xc7, 0xd9, 0x67, 0xbd, 0x9e, 0xfa, 0xf4, 0x5b, 0x40, 0x8f, 0x23, 0x30, 0x18, 0x33,
                0xbc, 0xb0, 0x9c, 0x86, 0x1c, 0x06, 0xdc, 0xc0, 0x58, 0x35, 0x69, 0x9e, 0x92, 0x5c,
                0x9c, 0xfa, 0xb6, 0x52, 0x2a, 0xad, 0xb4, 0xb7, 0x19, 0x32, 0x19, 0x77, 0xcd, 0x4a,
                0x49, 0x29, 0xe1, 0xfe, 0xf2, 0x89, 0x95, 0xb3, 0x7c, 0xf3, 0x5e, 0xf9, 0xeb, 0xfe,
                0x44, 0x21, 0x98, 0x85, 0x3c, 0x9e, 0xa7, 0x8a, 0x39, 0xe9, 0xa5, 0x69, 0xce, 0x26,
                0x34, 0xe8, 0x07, 0x2d, 0x6d, 0x71, 0x9a, 0x9b, 0x29, 0x53, 0x9e, 0xcd, 0x68, 0xb2,
                0x1d, 0x3c, 0x86, 0xcb, 0xcf, 0xa1, 0x9a, 0x24, 0x99, 0xb4, 0x03, 0x8e, 0xb9, 0x68,
                0xc6, 0xa9, 0xc1, 0x0e, 0x42, 0xd6, 0x46, 0x41, 0xa2, 0x44, 0xd6, 0xf6, 0xe0, 0xe3,
                0xd9, 0xa8, 0x8b, 0x79, 0xae, 0x32, 0xf8, 0x99, 0x2b, 0xa2, 0x3b, 0x38, 0xc0, 0x29,
                0x49, 0x5f, 0x6d, 0xb8, 0x67, 0x1b, 0xfc, 0x4b, 0x90, 0x7d, 0x6e, 0x52, 0x20, 0xe7, 
                0x2f, 0xe8, 0xe1, 0x81, 0xcc, 0xf8
            };
            
            uint32_t key_len = sizeof(key);

            response.insert( tlv(0x06, 0x02) );
            response.insert( tlv(0x03, key, key_len) );
            response.insert( tlv(0x02, salt, salt_len) );
            
            assertNotEqual(response.count, 0x03, "count not equal", &error_count);
            
            assertNotEqual(response.object[0].type, 0x06, "object type not equal", &error_count);
            assertNotEqual(response.object[0].data[0], 0x02, "object data not equal", &error_count);

            assertNotEqual(response.object[1].type, 0x03, "object type not equal", &error_count);
            int data_0_equal = memcmp(response.object[1].data, key, key_len);
            assertNotEqual(data_0_equal, 0x00, "object data bytes not equal", &error_count);
            

            assertNotEqual(response.object[2].type, 0x02, "object type not equal", &error_count);
            int data_1_equal = memcmp(response.object[2].data, salt, salt_len);
            assertNotEqual(data_1_equal, 0x00, "object data bytes not equal", &error_count);

            
            // Test encoding
            TLV8Class TLV8 = TLV8Class();
            
            
            uint8_t *PairTagBuffer = NULL;
            uint32_t length = 0;
            
            TLV8.encode(&response, &PairTagBuffer, &length);

            
            uint8_t output[] = {
                0x06, 0x01, 0x02, 0x03, 0xFF, 0xA2, 0x22, 0x63, 0xF0, 0xD9, 0x67, 0xD2, 0xC7, 0x7C,
                0xE6, 0xDB, 0x25, 0xBB, 0x79, 0x12, 0xCD, 0x4E, 0xA7, 0xB1, 0xED, 0xB0, 0x76, 0x91,
                0xFF, 0x3F, 0x65, 0x9B, 0x89, 0x25, 0x2D, 0x84, 0x12, 0xC7, 0xD2, 0x55, 0x4D, 0xD5,
                0x80, 0xFE, 0x50, 0xC0, 0x0F, 0xB4, 0x6E, 0x7F, 0x91, 0x75, 0x56, 0x8A, 0x75, 0xF0,
                0xA4, 0xE1, 0x90, 0x54, 0xA7, 0x8F, 0xE1, 0xD5, 0xF5, 0xA7, 0x3C, 0x93, 0x1C, 0xBD,
                0x1E, 0x80, 0x7D, 0x5C, 0x42, 0x23, 0x1A, 0xBC, 0xDD, 0x1A, 0xD6, 0xF6, 0x9B, 0xDC,
                0x0C, 0xA3, 0x06, 0x0D, 0xFB, 0x21, 0xA2, 0xAC, 0x9F, 0xCA, 0xDC, 0x91, 0x2D, 0x1F,
                0xB4, 0x13, 0xD7, 0x95, 0xEC, 0x5B, 0x60, 0x5E, 0x38, 0x6F, 0x6C, 0xF2, 0x65, 0x60,
                0x4F, 0xCC, 0xD4, 0xB6, 0x99, 0xD1, 0xA8, 0x9B, 0x70, 0x6A, 0x78, 0x55, 0x2F, 0x2E,
                0x6F, 0x08, 0x59, 0xBB, 0xAE, 0x8B, 0x19, 0xE2, 0xAE, 0xD5, 0x08, 0x8C, 0x2D, 0x89,
                0x6A, 0xE9, 0x75, 0x4B, 0xD8, 0xBB, 0x38, 0x2B, 0xD7, 0xB6, 0x0E, 0xC8, 0xD0, 0xF0,
                0xDD, 0xDB, 0x68, 0xF7, 0xD2, 0x1E, 0x8B, 0xF0, 0x3D, 0x8A, 0x0D, 0x56, 0x43, 0x68,
                0x33, 0x80, 0x5E, 0xA3, 0x67, 0xF6, 0xBE, 0x86, 0xF2, 0xAA, 0x4B, 0xD3, 0x0F, 0x92,
                0x48, 0x5A, 0x80, 0x82, 0xD6, 0x76, 0x59, 0xEF, 0x4D, 0xDE, 0xD1, 0x65, 0x05, 0xFA,
                0x3D, 0xA1, 0xB9, 0x08, 0x94, 0xFE, 0xD8, 0x55, 0x73, 0x87, 0x80, 0xD4, 0x32, 0x1A,
                0x85, 0x19, 0x53, 0x68, 0xA7, 0x83, 0xA9, 0x09, 0xC9, 0xDE, 0x8C, 0xB7, 0x90, 0x1A,
                0xDD, 0xBF, 0x21, 0x40, 0x3A, 0x49, 0xE3, 0xD6, 0x46, 0xF3, 0x62, 0x95, 0x5D, 0x78,
                0x9C, 0xB3, 0x0B, 0x8D, 0xCF, 0xC7, 0xD9, 0x67, 0xBD, 0x9E, 0xFA, 0xF4, 0x5B, 0x40,
                0x8F, 0x23, 0x30, 0x18, 0x33, 0xBC, 0xB0, 0x9C, 0x03, 0x81, 0x86, 0x1C, 0x06, 0xDC,
                0xC0, 0x58, 0x35, 0x69, 0x9E, 0x92, 0x5C, 0x9C, 0xFA, 0xB6, 0x52, 0x2A, 0xAD, 0xB4,
                0xB7, 0x19, 0x32, 0x19, 0x77, 0xCD, 0x4A, 0x49, 0x29, 0xE1, 0xFE, 0xF2, 0x89, 0x95,
                0xB3, 0x7C, 0xF3, 0x5E, 0xF9, 0xEB, 0xFE, 0x44, 0x21, 0x98, 0x85, 0x3C, 0x9E, 0xA7,
                0x8A, 0x39, 0xE9, 0xA5, 0x69, 0xCE, 0x26, 0x34, 0xE8, 0x07, 0x2D, 0x6D, 0x71, 0x9A,
                0x9B, 0x29, 0x53, 0x9E, 0xCD, 0x68, 0xB2, 0x1D, 0x3C, 0x86, 0xCB, 0xCF, 0xA1, 0x9A,
                0x24, 0x99, 0xB4, 0x03, 0x8E, 0xB9, 0x68, 0xC6, 0xA9, 0xC1, 0x0E, 0x42, 0xD6, 0x46,
                0x41, 0xA2, 0x44, 0xD6, 0xF6, 0xE0, 0xE3, 0xD9, 0xA8, 0x8B, 0x79, 0xAE, 0x32, 0xF8, 
                0x99, 0x2B, 0xA2, 0x3B, 0x38, 0xC0, 0x29, 0x49, 0x5F, 0x6D, 0xB8, 0x67, 0x1B, 0xFC, 
                0x4B, 0x90, 0x7D, 0x6E, 0x52, 0x20, 0xE7, 0x2F, 0xE8, 0xE1, 0x81, 0xCC, 0xF8, 0x02, 
                0x10, 0x59, 0x6F, 0x29, 0x06, 0x1B, 0xF3, 0xC6, 0x59, 0x92, 0x3D, 0x91, 0x12, 0x27, 
                0x54, 0x09, 0xDD
            };
            uint32_t output_len = sizeof(output);

            assertNotEqual(length, output_len, "encoded bytes length not equal", &error_count);
            int buffer_equal = memcmp(PairTagBuffer, output, output_len);
            assertNotEqual(buffer_equal, 0x00, "encoded data bytes not equal", &error_count);
            if (buffer_equal != 0) {
                print_hex_memory( PairTagBuffer, length );
            }
            
        }

        
        cout << "\n\nError count == " << error_count << endl;
        
        return 1;

    }

    catch (...)
	{
		cout << "unknown exception occured" << endl;
		cout << "!!! TEST VECTORS FAILURE !!!" << endl;
	}

	cout << "end!!! TEST VECTORS FAILURE !!!" << endl;
	return -1;

}



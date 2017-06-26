// Basic c++ test bench for testing Particle C code
/*
   g++ test.cpp tlv8.cpp -Wall -ggdb -std=c++0x -I. -O3 -fpermissive
   gcc2minix < a.out >test
   chmod +x test   # may not be necessary depending on your umask
   ./test

   Use online HEXDump tools to debug output: https://hexed.it

*/

#include "src/tlv8.h"

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
            uint16_t length = 0;
            
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
            uint16_t length = 0;
            
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
            uint16_t length = 0;
            
            TLV8.encode(&PairTagTLV8, &PairTagBuffer, &length);
            
            assertNotEqual(len, length, "encode decode length not equal", &error_count);
            
            assertNotEqual(PairTagTLV8.count, 0x03, "Encoded size not 0x03", &error_count);
            
            assertNotEqual(PairTagBuffer[0], 0xff, "encode byte is not 0xff", &error_count);
            
            
        }
        {
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
            uint16_t length = 0;
            
            TLV8.encode(&PairTagTLV8, &PairTagBuffer, &length);
            
            assertNotEqual(length, 10, "size not equal to 3", &error_count);
            
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



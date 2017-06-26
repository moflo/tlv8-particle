
CC = gcc
CCC = g++
ASM = yasm

CCFLAGS = -Wall -I.
CCCFLAGS = -Wall -ggdb -std=c++0x -I. -O3 -fpermissive

#tells how to make an *.o object file from an *.c file
%.o: %.c
	$(CC) -c $(CCFLAGS) $< -o $@

#tells how to make an *.o object file from an *.cpp file
%.o: %.cpp
	$(CCC) -c $(CCCFLAGS) $< -o $@
	
	
# APPLICATION SECTION

#build the app

test: test.o src/tlv8.o
	$(CCC) test.o src/tlv8.o -o test

particle:
	rm -f *.o
	particle compile photon src/tlv8.*

clean::
	rm -f *.o
	rm -f src/*.o
	rm -f photon_firmware*

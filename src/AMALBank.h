///////////////////////////////////////////////////////////
// AMOS AMAL -> Load AMAL ABK Banks
// By Stephen Harvey-Brooks - Mequa Innovations
///////////////////////////////////////////////////////////

#ifndef AMAL_BANK_H
#define AMAL_BANK_H

#include "AMOS_System.h"
#include <iostream>
#include <string>

using namespace std;


// TODO - not working yet!
// Load AMOS .abk AMAL banks files directly:
class AMALBank
{
	// TODO:
	//unsigned int readUnsignedByte(DataInputStream d);
	unsigned int readUnsignedByte();

	// TODO:
	//int readWord(DataInputStream d);
	int readByte();

	// TODO:
	//int readWord(DataInputStream d);
	int readWord();

	// TODO:
	//int readLong(DataInputStream d);
	long readLong();

public:
	AMOS_System* AM;
	AMALBank(AMOS_System* AMi);

	int loadabk(string f);
};
#endif

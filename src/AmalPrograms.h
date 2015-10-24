// Translated AMAL scripts:

#ifndef AMAL_PROGRAMS_H
#define AMAL_PROGRAMS_H

#include "AMOS_System.h"

#include <string>
using namespace std;

class AmalPrograms
{
	// Here are your converted AMAL programs:
	void amal1(int CHAN);
	void amal2(int CHAN);
	void amal3(int CHAN);
	void amal4(int CHAN);
	void amal5(int CHAN);
	void amal6(int CHAN);
	void amal7(int CHAN);
	void amal8(int CHAN);
	void amal9(int CHAN);
	void amal10(int CHAN);
	void amal11(int CHAN);
	void amal12(int CHAN);

public:
	// This part initialises the class:
	AMOS_System* AM;
	bool forrepeat;
	AmalPrograms(AMOS_System* AMi);

	int runAmal(int program, int channel);
	int numPrograms();

	// Environment Generator:
	void environment();
};

#endif


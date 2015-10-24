///////////////////////////////////////////////////////////
// AMOS AMAL -> C++ Interpreter
// By Stephen Harvey-Brooks - Mequa Innovations
///////////////////////////////////////////////////////////

#ifndef AMAL_INTERPRETER_H
#define AMAL_INTERPRETER_H

#include "AMOS_System.h"
#include <string>

using namespace std;


// The following functions form the AMAL Interpreter:
class AMALInterpreter
{
public:
	AMOS_System* AM;

	AMALInterpreter(AMOS_System* AMi);
	void interpret();
	void FETCHARGUMENTS(int P1);

	// Debug:
	void DEBUG();
};

#endif


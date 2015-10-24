///////////////////////////////////////////////////////////
// AMOS AMAL -> Java/C++ Compiler                        //
// By Stephen Harvey-Brooks - Mequa Innovations          //
///////////////////////////////////////////////////////////

#ifndef AMAL_COMPILER_H
#define AMAL_COMPILER_H

#include "AMOS_System.h"
#include "PrintStream.h"
#include <string>
#include <string.h>

using namespace std;

class PrintStream;

class AMALCompiler
{
public:
	AMOS_System* AM;
	PrintStream* out;

	AMALCompiler(AMOS_System* AMi);

	// To access arrays/vectors:
	void setARG(int a, int b, int c);
	void setarg(int a, int b, string c);
	int getARGTYPE(int a, int b, int c);
	int getPROGPOINTER(int a);

	void FETCHARGUMENTS_C(bool cpp, int P1);
	void FETCHARGUMENTS_C2(int P1);
	void DEBUG();
	string getarg(int a, int b);

	void AmalCompileCPPHeader(int ch1, int ch2);
	//void AmalCompile(PrintStream out, int ch1, int ch2); // TODO
	void AmalCompile(int ch1, int ch2, bool cpp);
};

#endif


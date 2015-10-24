// Dummy Compiler class for Read Only and Precompiled AMAL programs which do not need an AMAL-to-Java compiler:

#include "AMALCompiler.h"

AMALCompiler::AMALCompiler(AMOS_System* AMi)
{
	AM = AMi;
	//out = AM->out;
}
void AMALCompiler::setARG(int a, int b, int c)
{
}
void AMALCompiler::setarg(int a, int b, string c)
{
}
int AMALCompiler::getARGTYPE(int a, int b, int c)
{
	return 0;
}
int AMALCompiler::getPROGPOINTER(int a)
{
	return 0;
}
void AMALCompiler::FETCHARGUMENTS_C(int P1)
{
}
void AMALCompiler::FETCHARGUMENTS_C2(int P1)
{
}
void AMALCompiler::DEBUG()
{
}
string AMALCompiler::getarg(int a, int b)
{
	return "";
}

// TODO - void AmalCompile(PrintStream out, int ch1, int ch2)
void AMALCompiler::AmalCompile(int ch1, int ch2)
{
}


#ifndef DUMPER_H
#define DUMPER_H

#include <string>

#include "Game.h"
#include "TheTokens.h"

class Dumper
{
public:

	Game* g;

	Dumper(Game* g_);

	string floattostring(double value); // was char*

	// For dumpoutput (below);
	int dumparg(double arg, int argtype, TheTokens* mytokens);
	int dumpoutput(vector <TheTokens>* multitokens);

	// For dumpoutputtofile (below):
	int dumpfilearg(FILE *fp, double arg, int argtype, TheTokens* mytokens);
	int olddumpoutputtofile(vector <TheTokens>* multitokens, string filename);

	// For dumpoutputtofile (below):
	string dumpstrarg(FILE *fp, double arg, int argtype, TheTokens* mytokens, string* tempargs);

	// For dumpoutputtofile (below):
	int dumpfileargn(FILE *fp, double arg, int argtype, TheTokens* mytokens, string* tempargs);
	int dumpoutputtofile(vector <TheTokens>* multitokens, string filename);
};

#endif


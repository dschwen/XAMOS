#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>

#include "TheTokens.h"
#include "ActiveObject.h"

using std::string;
using std::vector;

class Game
{
public:
	// Create dynamically allocatable array of tokens (brains):
	vector <TheTokens> mytokens;

	// Currently one myvalues per brain - will be customisable number of instances of each (including none).
	vector <ActiveObject*> ActiveObjects;

	// Note: (WAS) Using nasty global variables...
	// Command 1 = "print"
	// Set an array of strings. (only 10?)
	char** textinstruction; //char *textinstruction[25]; // 20
	char** textfunction; //char *textfunction[200]; // 100
	int numinstructions;
	int numfunctions;
};
#endif

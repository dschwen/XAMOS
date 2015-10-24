#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <vector>

#include "Game.h"
#include "ActiveObject.h"
#include "Mytype.h"
#include "TheTokens.h"
#include "TokeniserReturn.h"
#include "CommandWrapper.h"
#include "AMOS_System.h"

using std::vector;

class CommandWrapper;
class AMOS_System;

class Interpreter
{
public:
	Game* g;
	CommandWrapper* commandwrapper;

	// Added from jAMOS:
	AMOS_System* am;

	Interpreter(Game* g_, AMOS_System* am_);

	char* lower(string s, char* buffer);
	string floattostring(double value);

	// For the Interpreter:
	double getarg(double arg, int argtype, ActiveObject *myvalues, Mytype* mytemps);
	char* getarg2(double arg, int argtype, ActiveObject *myvalues, TheTokens* mytokens, Mytype* mytemps);
	int isnumber(double arg, int argtype, ActiveObject *myvalues, Mytype* mytemps);

	void setextravars(int nn);
	int initvalues(vector <TheTokens>* multitokens, int nn);
	int interpret(vector <TheTokens>* multitokens, int on);
};
#endif

#ifndef THETOKENS_H
#define THETOKENS_H

#include <vector>
#include <string>

#include "TokeniserReturn.h"

class TokeniserReturn;

using std::string;
using std::vector;

class TheTokens
{
public:

	vector <TokeniserReturn> myparameters;
	vector <string> myvarnames;
	vector <string> myarraynames;
	vector <string> mystrings;

	// Added for Procedures:
	vector <string> myprocedures;
	vector <string> myprocedurecalls;
	vector <int> myprocedurepositions;

	// Used for Procedure calls at run-time, to hold the initial position:
	vector <int> myprocedurestack;

	string name;

	//void addtokens(string s);

	TheTokens();
	TheTokens(string s);
};
#endif


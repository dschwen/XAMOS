#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

#include "Game.h"
#include "MultiExpressionReturn.h"

using std::string;
using std::vector;

class Parser
{
public:

	Game* g;
	int OPTIMISE;
	int AMOS; // = TRUE;

	// Moved:
	int numtemps; // = 0;

	Parser(Game* g_, int OPTIMISE_);

	// TODO - duplicate:
	// For the Parser:
	string floattostring(double value);
	double getarg(double arg, int argtype, ActiveObject *myvalues, Mytype* mytemps);
	char* getarg2(double arg, int argtype, ActiveObject *myvalues, TheTokens* mytokens, Mytype* mytemps);
	int isnumber(double arg, int argtype, ActiveObject *myvalues, Mytype* mytemps);

	int initinstructions();

	// The following are Java wrappers for C++ only:
	string substring(string str, int pos);
	string substring(string str, int pos1, int pos2);

	char* upper(string s, char* buffer);
	char* lower(string s, char* buffer);
	string uppers(string s);
	string lowers(string s);
	char lowerchar(char c);
	char *upper_o(char *st);
	char *lower_o(char *st);

	void inittokens(vector <TheTokens> *tokens, int n, string s);

	ExpressionReturn evaluateexpression(char *expression, TheTokens* mytokens); //, int *numtemps);
	MultiExpressionReturn* evaluatemultiexpressions(char* expression, TheTokens* mytokens); //, int *numtemps);
	TokeniserReturn* tokeniser(char* textline, char** textinstruction, int numinstructions, int numfunctions, TheTokens* mytokens); //, int *numtemps); 

	int optimisetemps(TheTokens* mytokens, int lastlines);
	vector <string>* addextravarnames(vector <string> *myvarnames);

	// New:
	vector<string> parsedim(string input);
	vector<string> splitstringbycommas(string input);

	int evaluateline(string textline, int tn);
	int evaluateinstructions(vector <string> textline);

	// New:
	int lexString(string str);
	int initvalues(vector<TheTokens>* multitokens, int nn);
};

#endif


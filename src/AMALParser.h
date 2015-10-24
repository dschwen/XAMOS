////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The following methods form the AMAL string parser and tokeniser, also known as the AMAL Lexer.
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef AMAL_PARSER_H
#define AMAL_PARSER_H

#include "AMOS_System.h"
#include <string>

using namespace std;

class AMALParser
{
public:
	AMOS_System* AM;

	AMALParser(AMOS_System* AMi);

	// Debug:
	void SETUP_AMAL();
	void SETUP_AMAL_DEBUG();

	void Tokenize();
	void REMOVE_UNUSED();
	void SCANINSTRUCTIONS();
	void SCANFORNEXTINSTRUCTION();
	void SIMPLEEXPRESSIONS();
	void OPERATORS();
	void SCANFUNCTIONS();
	int SEARCHCOMMA(string p1, string p2, int P3);
};
#endif


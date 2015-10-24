#ifndef AMAL_ENVGEN_H
#define AMAL_ENVGEN_H

#include "AMOS_System.h"
#include "Mytype.h"

#include <vector>
#include <string>

using namespace std;


class AMALEnvGen
{
public:
	AMOS_System* AM;
	vector<string> command;
	vector<string> javaCommand;
	vector<string> cppCommand;
	int commandlength;

	vector< vector<Mytype> > envScript; // v<v< Object type?


	AMALEnvGen(AMOS_System* AMi);
	int checkcommand(string inputline);
	Mytype parsearg(string input); // Object???
	void processline(string input);
	void processcode(string input);
	void dump();
	string outputCPP();
	string outputJava();
	int interpretEnvGen();
	void mymain();
};
#endif


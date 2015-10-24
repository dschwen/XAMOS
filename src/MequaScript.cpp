/*

    MequaScript

    (C) 2012 Mequa Innovations

 */

#include <string>
#include <vector>

// Added:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "MequaScript.h"
#include "Game.h"
#include "Parser.h"
#include "Dumper.h"
#include "Interpreter.h"
#include "AMOS_System.h"

using std::string;
using std::vector;


int MequaScript::debugtest(int argc, char *argv[])
{
	vector <string> textline;

	// File open:
	FILE *fp;
	char* fgetstr;
	char filstr[505]; //char* filstr = new char[505];
	filstr[0] = 0;

	// D:/
	if ((fp=fopen("test.meq", "r")) == NULL)
		exit(1);
	fgetstr=fgets(filstr, 500, fp);

	while(!feof(fp) && !(fgetstr == NULL))
	{
		// Kill any new lines:
		if (filstr[strlen(filstr)-1] == '\n')
			filstr[strlen(filstr)-1] = 0;
		// Copy the string to the vector:
		textline.push_back(string(filstr));
		fgetstr=fgets(filstr, 500, fp);
	}

	//TheTokens mytokens[100]; //= new TheTokens("")[10];

	// Added:
	AMOS_System* am = new AMOS_System();

	// Added:
	int OPTIMISE = 0;
	Game* g = new Game();
	Parser* parser = new Parser(g, OPTIMISE);
	Dumper* dumper = new Dumper(g);
	Interpreter* interpreter = new Interpreter(g, am);
	//Interpreter* interpreter = new Interpreter(g);

	parser->inittokens(&g->mytokens, 0, "Master");

	// Display raw code:
	printf("- The raw code:\n");
	for (unsigned int n=0; n<textline.size(); n++)
		printf("%s\n", textline[n].c_str());
	printf("\n\n");

	// Load the instruction and function names:
	parser->initinstructions();
	// Tokenise the instructions:
	parser->evaluateinstructions(textline);

	// Once tokenisation is complete - dump the output (only in this demo):
	dumper->dumpoutput(&g->mytokens);
	dumper->dumpoutputtofile(&g->mytokens, "dump.txt");

	// For each brain, initialise an object (in myvalues[n]), and set its brain number to the object number (only in this demo):
	for (unsigned int n=0; n<g->mytokens.size(); n++)
	{
		ActiveObject *temp = new ActiveObject();
		temp->ObjectBrain = n;
		g->ActiveObjects.push_back(temp);
	}

	// Now initialise the variables of each object:
	for (unsigned int n=0; n<g->mytokens.size(); n++)
		interpreter->initvalues(&g->mytokens, n);

	// Once tokenisation is complete - interpret and run the code for all the objects!
	printf("Now running the program:\n");

	//for (unsigned int nn=0; nn<2; nn++) // removed - try 2 iterations
	for (unsigned int n=0; n<g->ActiveObjects.size(); n++)
	{
		interpreter->interpret(&g->mytokens, n);
	}

	// Wait for keypress here:
	//system("PAUSE"); // removed for cross-platform compatibility

	return EXIT_SUCCESS;
}

int MequaScript::mymain(int argc, char *argv[])
{
	return debugtest(argc, argv);
}

/*
int main(int argc, char *argv[])
{
    MequaScript* mequascript = new MequaScript();
    return mequascript->mymain(argc, argv);
}
 */


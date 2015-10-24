#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <iostream>

#include "Dumper.h"

using namespace std;

Dumper::Dumper(Game* g_)
{
	g = g_;
}

// TODO: Duplicate:
string Dumper::floattostring(double value)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << value;
	return ss.str();
}

// For dumpoutput (below):
int Dumper::dumparg(double arg, int argtype, TheTokens* mytokens)
{
	if ((argtype) == 0)
		printf("%s", floattostring(arg).c_str());
	else if ((argtype) == 1)
		printf("%s", mytokens->myvarnames[(int)arg].c_str()); // Var names without numbers (normal)
	//printf("%s {%d}", mytokens->myvarnames[arg], arg); // Debug - var names with numbers
	else if ((argtype) == 3)
		printf("\"%s\"", mytokens->mystrings[(int)arg].c_str()); //  (%d) ... ,arg);
	else if ((argtype) == 5)
		printf("Temp[%s]", floattostring(arg).c_str());
	else //if (argtype == -1)
		printf("???");

	return 0;
}
int Dumper::dumpoutput(vector <TheTokens>* multitokens)
{
	TheTokens* mytokens;
	TokeniserReturn* ret; // = new TokeniserReturn();
	printf("-- The tokenised code:\n");

	for (unsigned int tn=0; tn<multitokens->size(); tn++)
	{
		mytokens = &((*multitokens)[tn]);
		printf("- Brain %s (%d):\n", mytokens->name.c_str(), tn);

		for (unsigned int l=0; l<(mytokens->myparameters.size()); l++)
		{
			ret = &mytokens->myparameters[l];
			printf("(%d) ", l);

			// Finally, evaluate the instruction itself:
			if ((ret->insttype) == 1) // Standard Instruction
			{
				//printf("Instruction[%d] (", ret->instflag);
				printf("%s", g->textinstruction[ret->instflag]);
				for (int n=0; n<ret->numargs; n++)
				{
					if (ret->argtypes[n] != -1)
					{
						if (n>0)
							printf(",");
						printf(" ");
						dumparg(ret->args[n], ret->argtypes[n], mytokens);
					}
				}
				//if (ret->numargs <= 0) printf("NOARG"); // Added in Java
				//printf(", "); dumparg(ret->arg2, ret->argtype2, mytokens); printf(", "); dumparg(ret->arg3, ret->argtype3, mytokens);
			}
			else if ((ret->insttype) == 2) // Let Temp[x] = a OPERATOR b
			{
				printf("Temp[%s] = ", floattostring(ret->args[0]).c_str());
				//printf("Arg: %d, Argtype: %d"), ret->args[1], ret->argtypes[1];
				dumparg(ret->args[1], ret->argtypes[1], mytokens);
				switch (ret->instflag)
				{
				case 0: printf("."); break;
				case 1: printf("Not "); break;
				case 2: printf(" * "); break;
				case 3: printf(" / "); break;
				case 4: printf(" mod "); break;
				case 5: printf(" + "); break;
				case 6: printf(" - "); break;
				case 7: printf(" < "); break;
				case 8: printf(" > "); break;
				case 9: printf(" <= "); break;
				case 10: printf(" >= "); break;
				case 11: printf(" == "); break;
				case 12: printf(" != "); break;
				case 13: printf(" and "); break;
				case 14: printf(" or "); break;
				}
				dumparg(ret->args[2], ret->argtypes[2], mytokens);
			}
			else if ((ret->insttype) == 3) // Let Temp[x] = Function(a)
			{
				printf("Temp[%s] = %s(", floattostring(ret->args[0]).c_str(), g->textfunction[ret->instflag]);
				for (int n=1; n<ret->numargs; n++)
				{
					dumparg(ret->args[n], ret->argtypes[n], mytokens);
					if (n<(ret->numargs-1))
						printf(", ");
				}
				printf(")");
			}
			else if ((ret->insttype) == 4) // Let Temp[x] = a (is this/should this be redundant?)
			{
				printf("Temp[%s] = ", floattostring(ret->args[0]).c_str());
				dumparg(ret->args[1], ret->argtypes[1], mytokens); // start from arg[1] - print all...
			}
			else if (((ret->insttype) >= 5) && ((ret->insttype) <= 11)) // Var[instflag] = arg;
			{
				printf("%s ", mytokens->myvarnames[ret->instflag].c_str());
				//printf("%s {%d} ", mytokens->myvarnames[ret->instflag], ret->instflag);
				switch (ret->insttype)
				{
				case 5: printf("="); break;
				case 6: printf("+="); break;
				case 7: printf("-="); break;
				case 8: printf("/="); break;
				case 9: printf("*="); break;
				case 10: printf("++"); break;
				case 11: printf("--"); break;
				}
				if (ret->insttype <= 9)
					printf(" ");
				switch (ret->argtypes[0])
				{
				case 0: printf("%s", floattostring(ret->args[0]).c_str()); break; // Constants
				case 1: printf("%s", mytokens->myvarnames[(int)ret->args[0]].c_str()); break; // Variables
				case 3: printf("\"%s\"", mytokens->mystrings[(int)ret->args[0]].c_str()); break; // String constants
				case 5: printf("Temp[%s]", floattostring(ret->args[0]).c_str()); break;// Temps
				default: printf("ARGERROR! %d", ret->argtypes[0]); break; // Added in Java
				}
			}
			else if (((ret->insttype) >= 15) && ((ret->insttype) <= 21)) // brain.var = arg;
			{
				printf("%s.%s ", mytokens->myvarnames[ret->instflag].c_str(), floattostring(ret->args[0]).c_str());
				//printf("%s {%d} ", mytokens->myvarnames[ret->instflag], ret->instflag);
				switch (ret->insttype)
				{
				case 15: printf("="); break;
				case 16: printf("+="); break;
				case 17: printf("-="); break;
				case 18: printf("/="); break;
				case 19: printf("*="); break;
				case 20: printf("++"); break;
				case 21: printf("--"); break;
				}
				if (ret->insttype <= 19)
					printf(" ");
				switch (ret->argtypes[1])
				{
				case 0: printf("%s", floattostring(ret->args[1]).c_str()); break; // Constants
				case 1: printf("%s", mytokens->myvarnames[(int)ret->args[1]].c_str()); break; // Variables
				case 3: printf("\"%s\"", mytokens->mystrings[(int)ret->args[1]].c_str()); break; // String constants
				case 5: printf("Temp[%s]", floattostring(ret->args[1]).c_str()); break;// Temps
				default: break;
				}
			}
			else if ((ret->insttype) == 50) // Function as Instruction
			{
				printf("%s", g->textfunction[ret->instflag]);
				for (int n=0; n<ret->numargs; n++)
				{
					if (ret->argtypes[n] != -1)
					{
						if (n>0)
							printf(",");
						printf(" ");
						dumparg(ret->args[n], ret->argtypes[n], mytokens);
					}
				}
				//if (ret->numargs <= 0) printf("NOARG"); // Added in Java
			}
			else
			{
				cout << "No instruction recognised!";
			}
			cout << endl; //printf(";\n");
		}

		// Display the variables:
		cout << endl << "Variables (" << mytokens->myvarnames.size() << "): ";
		for (unsigned int n=0; n<mytokens->myvarnames.size(); n++)
		{
			cout << mytokens->myvarnames[n];
			if (n<mytokens->myvarnames.size()-1)
				cout << ", ";
		}
		cout << endl << endl << endl;
	}
	return 1;
}

// For dumpoutputtofile (below):
int Dumper::dumpfilearg(FILE *fp, double arg, int argtype, TheTokens* mytokens)
{
	if ((argtype) == 0)
		fprintf(fp, "%s", floattostring(arg).c_str());
	else if ((argtype) == 1)
		//fprintf(fp, "%s", mytokens->myvarnames[(int)arg].c_str()); // Var names without numbers (normal)
		fprintf(fp, "%s {%g}", mytokens->myvarnames[(int)arg].c_str(), arg); // Debug - var names with numbers
	else if ((argtype) == 3)
		fprintf(fp, "\"%s\"", mytokens->mystrings[(int)arg].c_str()); //  (%d) ... ,arg);
	else if ((argtype) == 5)
		fprintf(fp, "Temp[%s]", floattostring(arg).c_str());
	//else if (argtype == -1)
	//    fprintf(fp, "???");
	return 0;
}
int Dumper::olddumpoutputtofile(vector <TheTokens>* multitokens, string filename)
{
	// Added - temp strings:
	//string tempargs[30]; // removed
	//int curtemp=0;

	FILE* fp;
	// Attempt to open the file:
	if ((fp = fopen(filename.c_str(), "w"))==NULL)
	{
		fprintf(fp, "Cannot open file!\n");
		return 0;
	}

	TheTokens* mytokens;
	TokeniserReturn* ret; // = new TokeniserReturn();

	fprintf(fp, "-- The tokenised code:\n");

	for (unsigned int tn=0; tn<multitokens->size(); tn++)
	{
		mytokens = &((*multitokens)[tn]);
		fprintf(fp, "- Brain %s (%d):\n", mytokens->name.c_str(), tn);

		for (unsigned int l=0; l<(mytokens->myparameters.size()); l++)
		{
			ret = &mytokens->myparameters[l];
			fprintf(fp, "(%d) ", l);

			// Finally, evaluate the instruction itself:
			if ((ret->insttype) == 1) // Standard Instruction
			{
				//fprintf(fp, "Instruction[%d] (", ret->instflag);
				fprintf(fp, "%s", g->textinstruction[ret->instflag]);
				for (int n=0; n<ret->numargs; n++)
				{
					if (ret->argtypes[n] != -1)
					{
						if (n>0)
							fprintf(fp, ",");
						fprintf(fp, " ");
						dumpfilearg(fp, ret->args[n], ret->argtypes[n], mytokens);
					}
				}
				//fprintf(fp, ", "); dumpfilearg(fp, ret->arg2, ret->argtype2, mytokens); fprintf(fp, ", "); dumpfilearg(fp, ret->arg3, ret->argtype3, mytokens);
			}
			else if ((ret->insttype) == 2) // Let Temp[x] = a OPERATOR b
			{
				fprintf(fp, "Temp[%s] = ", floattostring(ret->args[0]).c_str());
				//fprintf(fp, "Arg: %d, Argtype: %d"), ret->args[1], ret->argtypes[1];
				dumpfilearg(fp, ret->args[1], ret->argtypes[1], mytokens);
				switch (ret->instflag)
				{
				case 0: fprintf(fp, "."); break;
				case 1: fprintf(fp, "Not "); break;
				case 2: fprintf(fp, " * "); break;
				case 3: fprintf(fp, " / "); break;
				case 4: fprintf(fp, " mod "); break;
				case 5: fprintf(fp, " + "); break;
				case 6: fprintf(fp, " - "); break;
				case 7: fprintf(fp, " < "); break;
				case 8: fprintf(fp, " > "); break;
				case 9: fprintf(fp, " <= "); break;
				case 10: fprintf(fp, " >= "); break;
				case 11: fprintf(fp, " = "); break;
				case 12: fprintf(fp, " != "); break;
				case 13: fprintf(fp, " and "); break;
				case 14: fprintf(fp, " or "); break;
				}
				dumpfilearg(fp, ret->args[2], ret->argtypes[2], mytokens);
			}
			else if ((ret->insttype) == 3) // Let Temp[x] = Function(a)
			{
				fprintf(fp, "Temp[%s] = %s(", floattostring(ret->args[0]).c_str(), g->textfunction[ret->instflag]);
				for (int n=1; n<ret->numargs; n++)
				{
					dumpfilearg(fp, ret->args[n], ret->argtypes[n], mytokens);
					if (n<(ret->numargs-1))
						fprintf(fp, ", ");
				}
				fprintf(fp, ")");
			}
			else if ((ret->insttype) == 4) // Let Temp[x] = a (is this/should this be redundant?)
			{
				fprintf(fp, "Temp[%s] = ", floattostring(ret->args[0]).c_str());
				dumpfilearg(fp, ret->args[1], ret->argtypes[1], mytokens); // start from arg[1] - print all...
			}
			else if (((ret->insttype) >= 5) && ((ret->insttype) <= 11)) // Var[instflag] = arg;
			{
				fprintf(fp, "%s ", mytokens->myvarnames[ret->instflag].c_str());
				//fprintf(fp, "%s {%d} ", mytokens->myvarnames[ret->instflag], ret->instflag);
				switch (ret->insttype)
				{
				case 5: fprintf(fp, "="); break;
				case 6: fprintf(fp, "+="); break;
				case 7: fprintf(fp, "-="); break;
				case 8: fprintf(fp, "/="); break;
				case 9: fprintf(fp, "*="); break;
				case 10: fprintf(fp, "++"); break;
				case 11: fprintf(fp, "--"); break;
				}
				if (ret->insttype <= 9)
					fprintf(fp, " ");
				switch (ret->argtypes[0])
				{
				case 0: fprintf(fp, "%s", floattostring(ret->args[0]).c_str()); break; // Constants
				case 1: fprintf(fp, "%s", mytokens->myvarnames[(int)ret->args[0]].c_str()); break; // Variables
				case 3: fprintf(fp, "\"%s\"", mytokens->mystrings[(int)ret->args[0]].c_str()); break; // String constants
				case 5: fprintf(fp, "Temp[%s]", floattostring(ret->args[0]).c_str()); break;// Temps
				default: break;
				}
			}
			else if (((ret->insttype) >= 15) && ((ret->insttype) <= 21)) // brain.var = arg;
			{
				fprintf(fp, "%s.%s ", mytokens->myvarnames[ret->instflag].c_str(), floattostring(ret->args[0]).c_str());
				//fprintf(fp, "%s {%d} ", mytokens->myvarnames[ret->instflag], ret->instflag);
				switch (ret->insttype)
				{
				case 15: fprintf(fp, "="); break;
				case 16: fprintf(fp, "+="); break;
				case 17: fprintf(fp, "-="); break;
				case 18: fprintf(fp, "/="); break;
				case 19: fprintf(fp, "*="); break;
				case 20: fprintf(fp, "++"); break;
				case 21: fprintf(fp, "--"); break;
				}
				if (ret->insttype <= 19)
					fprintf(fp, " ");
				switch (ret->argtypes[1])
				{
				case 0: fprintf(fp, "%s", floattostring(ret->args[1]).c_str()); break; // Constants
				case 1: fprintf(fp, "%s", mytokens->myvarnames[(int)ret->args[1]].c_str()); break; // Variables
				case 3: fprintf(fp, "\"%s\"", mytokens->mystrings[(int)ret->args[1]].c_str()); break; // String constants
				case 5: fprintf(fp, "Temp[%s]", floattostring(ret->args[1]).c_str()); break;// Temps
				default: break;
				}
			}
			else if ((ret->insttype) == 50) // Function as Instruction
			{
				fprintf(fp, "%s", g->textfunction[ret->instflag]);
				for (int n=0; n<ret->numargs; n++)
				{
					if (ret->argtypes[n] != -1)
					{
						if (n>0)
							fprintf(fp, ",");
						fprintf(fp, " ");
						dumpfilearg(fp, ret->args[n], ret->argtypes[n], mytokens);
					}
				}
			}
			else
			{
				fprintf(fp, "No instruction recognised!");
			}
			fprintf(fp, "\n"); //fprintf(fp, ";\n");
		}

		// Display the variables:
		fprintf(fp, "\nVariables (%d): ", (int)mytokens->myvarnames.size());
		for (unsigned int n=0; n<mytokens->myvarnames.size(); n++)
		{
			fprintf(fp, "%s", mytokens->myvarnames[n].c_str());
			if (n<mytokens->myvarnames.size()-1)
				fprintf(fp, ", ");
		}
		fprintf(fp, "\n\n\n");
	}
	fclose(fp);
	return 1;
}

// For dumpoutputtofile (below):
string Dumper::dumpstrarg(FILE *fp, double arg, int argtype, TheTokens* mytokens, string* tempargs)
{
	if (argtype == 0)
		return floattostring(arg);
	else if (argtype == 1)
		return mytokens->myvarnames[(int)arg]; // Var names without numbers (normal)
	//fprintf(fp, "%s {%d}", mytokens->myvarnames[arg], arg); // Debug - var names with numbers
	else if (argtype == 3)
		return string("\"") + mytokens->mystrings[(int)arg] + "\""; //  (%d) ... ,arg);
	else if (argtype == 5)
		return tempargs[(int)arg];
	// Debug:
	//else if (argtype == -1)
	//    fprintf(fp, "???");
	return string("");
}
// For dumpoutputtofile (below):
int Dumper::dumpfileargn(FILE *fp, double arg, int argtype, TheTokens* mytokens, string* tempargs)
{
	if ((argtype) == 0)
		fprintf(fp, "%s", floattostring(arg).c_str());
	else if ((argtype) == 1)
		fprintf(fp, "%s", mytokens->myvarnames[(int)arg].c_str()); // Var names without numbers (normal)
	//fprintf(fp, "%s {%d}", mytokens->myvarnames[arg], arg); // Debug - var names with numbers
	else if ((argtype) == 3)
		fprintf(fp, "\"%s\"", mytokens->mystrings[(int)arg].c_str()); //  (%d) ... ,arg);
	else if (argtype == 5)
		fprintf(fp, "%s", tempargs[(int)arg].c_str());
	// Removed a long time ago:
	//else if ((argtype) == 5)
	//    fprintf(fp, "Temp[%s]", floattostring(arg).c_str());

	// Debug:
	//else if (argtype == -1)
	//    fprintf(fp, "???");

	return 0;
}
int Dumper::dumpoutputtofile(vector <TheTokens>* multitokens, string filename)
{
	// Added - temp strings:
	string tempargs[30];
	int indent = 0;
	int lastalways = 0;

	FILE* fp;
	// Attempt to open the file:
	if ((fp = fopen(filename.c_str(), "w"))==NULL)
	{
		fprintf(fp, "Cannot open file!\n");
		return 0;
	}

	TheTokens* mytokens;
	TokeniserReturn* ret; // = new TokeniserReturn();

	fprintf(fp, "-- The tokenised code:\n");

	for (unsigned int tn=0; tn<multitokens->size(); tn++)
	{
		mytokens = &((*multitokens)[tn]);
		fprintf(fp, "- Brain %s (%d):\n", mytokens->name.c_str(), tn);

		for (unsigned int l=0; l<(mytokens->myparameters.size()); l++)
		{
			ret = &(mytokens->myparameters[l]);
			//fprintf(fp, "(%d) ", l);

			// Finally, evaluate the instruction itself:
			if ((ret->insttype) == 1) // Standard Instruction
			{
				int numargstoshow = 0; // Added initialisation in Java
				//fprintf(fp, "Instruction[%d] (", ret->instflag);

				// If instruction is 'If', display only 1 arg (and add a blank line):
				if (ret->instflag == 6)
				{
					indent++;
					lastalways = 0;

					fprintf(fp, "\n");

					for (int o=0; o<indent && ret->instflag != 6; o++)
						fprintf(fp, "   ");

					fprintf(fp, "If "); //"When " //fprintf(fp, "%s", g->textinstruction[ret->instflag]);

					if (ret->argtypes[0] != -1)
						dumpfileargn(fp, ret->args[0], ret->argtypes[0], mytokens, tempargs);

					fprintf(fp, "\n");
				}
				else if (ret->instflag != 7 || ret->instflag != 11)
				{
					numargstoshow = ret->numargs;
					if ((lastalways==0) && (indent==0))
					{
						lastalways = 1;
						//fprintf(fp, "\nAlways\n"); // removed
					}
				}

				// In instruction is Endif or }, remove indent (and add a blank line):
				if (ret->instflag == 7 || ret->instflag == 11)
				{
					indent--;
					lastalways = 0;
					//fprintf(fp, "\n");
				}
				// Else, display the instruction and args
				else if (ret->instflag != 6)
				{
					for (int o=0; o<indent && ret->instflag != 6; o++)
						fprintf(fp, "   ");

					fprintf(fp, "%s", g->textinstruction[ret->instflag]);

					for (int n=0; n<numargstoshow; n++)
					{
						if (ret->argtypes[n] != -1)
						{
							if (n>0)
								fprintf(fp, ",");
							fprintf(fp, " ");
							dumpfileargn(fp, ret->args[n], ret->argtypes[n], mytokens, tempargs);
						}
					}
					fprintf(fp, "\n");
				}
				//fprintf(fp, ", "); dumpfilearg(fp, ret->arg2, ret->argtype2, mytokens); fprintf(fp, ", "); dumpfilearg(fp, ret->arg3, ret->argtype3, mytokens);
			}
			else if ((ret->insttype) == 2) // Let Temp[x] = a OPERATOR b
			{
				string op;
				tempargs[(int)ret->args[0]] = dumpstrarg(fp, ret->args[1], ret->argtypes[1], mytokens, tempargs);
				//if (ret->instflag != 1)
				//   tempargs[(int)ret->args[0]] = tempargs[(int)ret->args[0]]; // removed - redundant!
				switch (ret->instflag)
				{
				case 0: op = "."; break;
				case 1: op = "Not "; break;
				case 2: op = " * "; break;
				case 3: op = " / "; break;
				case 4: op = " mod "; break;
				case 5: op = " + "; break;
				case 6: op = " - "; break;
				case 7: op = " < "; break;
				case 8: op = " > "; break;
				case 9: op = " <= "; break;
				case 10: op = " >= "; break;
				case 11: op = " = "; break;
				case 12: op = " != "; break;
				case 13: op = " and "; break;
				case 14: op = " or "; break;
				}
				tempargs[(int)ret->args[0]] = tempargs[(int)ret->args[0]] + op + dumpstrarg(fp, ret->args[2], ret->argtypes[2], mytokens, tempargs);
			}
			else if ((ret->insttype) == 3) // Let Temp[x] = Function(a)
			{
				tempargs[(int)ret->args[0]] = string(g->textfunction[ret->instflag]) + "(";
				for (int n=1; n<ret->numargs; n++)
				{
					tempargs[(int)ret->args[0]] = tempargs[(int)ret->args[0]] + dumpstrarg(fp, ret->args[n], ret->argtypes[n], mytokens, tempargs);
					if (n<(ret->numargs-1))
						tempargs[(int)ret->args[0]] = tempargs[(int)ret->args[0]] + ", ";
				}
				tempargs[(int)ret->args[0]] = tempargs[(int)ret->args[0]] + ")";
			}
			else if ((ret->insttype) == 4) // Let Temp[x] = a (is this/should this be redundant?)
			{
				tempargs[(int)ret->args[0]] = string("(") + dumpstrarg(fp, ret->args[1], ret->argtypes[1], mytokens, tempargs) + ")";
			}
			else if (((ret->insttype) >= 5) && ((ret->insttype) <= 11)) // Var[instflag] = arg;
			{
				if (!lastalways && indent==0)
				{
					lastalways = 1;
					fprintf(fp, "\nAlways\n");
				}

				for (int o=0; o<indent ; o++)
					fprintf(fp, "   ");

				fprintf(fp, "%s ", mytokens->myvarnames[ret->instflag].c_str());
				//fprintf(fp, "%s {%d} ", mytokens->myvarnames[ret->instflag], ret->instflag);
				switch (ret->insttype)
				{
				case 5: fprintf(fp, "="); break;
				case 6: fprintf(fp, "+="); break;
				case 7: fprintf(fp, "-="); break;
				case 8: fprintf(fp, "/="); break;
				case 9: fprintf(fp, "*="); break;
				case 10: fprintf(fp, "++"); break;
				case 11: fprintf(fp, "--"); break;
				}
				if (ret->insttype <= 9)
					fprintf(fp, " ");
				switch (ret->argtypes[0])
				{
				case 0: fprintf(fp, "%s", floattostring(ret->args[0]).c_str()); break; // Constants
				case 1: fprintf(fp, "%s", mytokens->myvarnames[(int)ret->args[0]].c_str()); break; // Variables
				case 3: fprintf(fp, "\"%s\"", mytokens->mystrings[(int)ret->args[0]].c_str()); break; // String constants
				case 5: fprintf(fp, "%s", tempargs[(int)ret->args[0]].c_str()); break;
				//case 5: fprintf(fp, "Temp[%s]", floattostring(ret->args[0]).c_str()); break; // Temps
				default: break;
				}
				fprintf(fp, "\n");
			}
			else if (((ret->insttype) >= 15) && ((ret->insttype) <= 21)) // brain.var = arg;
			{
				if (!lastalways && indent==0)
				{
					lastalways = 1;
					//fprintf(fp, "\nAlways\n"); // removed
				}

				for (int o=0; o<indent; o++)
					fprintf(fp, "   ");

				fprintf(fp, "%s.%s ", mytokens->myvarnames[ret->instflag].c_str(), floattostring(ret->args[0]).c_str());
				//fprintf(fp, "%s {%d} ", mytokens->myvarnames[ret->instflag], ret->instflag);
				switch (ret->insttype)
				{
				case 15: fprintf(fp, "="); break;
				case 16: fprintf(fp, "+="); break;
				case 17: fprintf(fp, "-="); break;
				case 18: fprintf(fp, "/="); break;
				case 19: fprintf(fp, "*="); break;
				case 20: fprintf(fp, "++"); break;
				case 21: fprintf(fp, "--"); break;
				}
				if (ret->insttype <= 19)
					fprintf(fp, " ");
				switch (ret->argtypes[1])
				{
				case 0: fprintf(fp, "%s", floattostring(ret->args[1]).c_str()); break; // Constants
				case 1: fprintf(fp, "%s", mytokens->myvarnames[(int)ret->args[1]].c_str()); break; // Variables
				case 3: fprintf(fp, "\"%s\"", mytokens->mystrings[(int)ret->args[1]].c_str()); break; // String constants
				case 5: fprintf(fp, "%s", tempargs[(int)ret->args[1]].c_str()); break;
				//case 5: fprintf(fp, "Temp[%s]", floattostring(ret->args[1]).c_str()); break; // Temps
				default: break;
				}
				fprintf(fp, "\n");
			}
			else if ((ret->insttype) == 50) // Function as Instruction
			{
				if ((lastalways==0) && (indent==0))
				{
					lastalways = 1;
					//fprintf(fp, "\nAlways\n"); // removed
				}

				for (int o=0; o<indent; o++)
					fprintf(fp, "   ");

				fprintf(fp, "%s", g->textfunction[ret->instflag]);
				for (int n=0; n<ret->numargs; n++)
				{
					if (ret->argtypes[n] != -1)
					{
						if (n>0)
							fprintf(fp, ",");
						fprintf(fp, " ");
						dumpfileargn(fp, ret->args[n], ret->argtypes[n], mytokens, tempargs);
					}
				}
				fprintf(fp, "\n");
			}
			else
			{
				if ((lastalways==0) && (indent==0))
				{
					lastalways = 1;
					//fprintf(fp, "\nAlways\n"); //removed
				}

				for (int o=0; o<indent; o++)
					fprintf(fp, "   ");

				fprintf(fp, "No instruction recognised!");
			}
			//fprintf(fp, ";\n");
		}

		// Display the variables:
		fprintf(fp, "\nVariables (%d): ", (int)mytokens->myvarnames.size());
		for (unsigned int n=0; n<mytokens->myvarnames.size(); n++)
		{
			fprintf(fp, "%s", mytokens->myvarnames[n].c_str());
			if (n<mytokens->myvarnames.size()-1)
				fprintf(fp, ", ");
		}
		fprintf(fp, "\n\n\n");
	}

	fclose(fp);

	// From Java version - file write error checking not implemented in C++:
	//if (???)
	//{
	//   printf("Error writing file!"); // Added in Java
	//   return 0;
	//}

	return 1;
}

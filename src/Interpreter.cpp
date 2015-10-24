#include <stdio.h>
#include <string.h>
#include <sstream>

#include "Interpreter.h"
#include "Mytypearray.h"

using std::stringstream;


// For the Interpreter:
Interpreter::Interpreter(Game* g_, AMOS_System* am_)
{
	g = g_;
	am = am_;
	commandwrapper = new CommandWrapper(g, am);
}

/*Interpreter::Interpreter(Game* g_)
{
	g = g_;
	commandwrapper = new CommandWrapper(g);
}*/


// TODO - duplicate:
char* Interpreter::lower(string s, char* buffer)
{
	//char* st = (char*)s.c_str();
	for (unsigned int n=0; n<=s.size(); n++)
	{
		if ((s[n] >= 'A') && (s[n] <= 'Z'))
		{
			buffer[n] = s[n] + ('a' - 'A');
		}
		else
		{
			buffer[n] = s[n];
		}
	}

	return buffer;
}
string Interpreter::floattostring(double value)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << value;
	return ss.str();
}

// For the Interpreter:
double Interpreter::getarg(double arg, int argtype, ActiveObject *myvalues, Mytype* mytemps)
{
	switch(argtype)
	{
	case 0:
		return arg;
	case 1:
		// Var name (string): mytokens->myvarnames[arg]
		return myvalues->myvars[(int)arg].d;
	case 3:
		return 0; // string: mytokens->mystrings[arg] - fix types!
	case 5:
		return mytemps[(int)arg].d; // Make sure initialised!
	default:
		return 0;
	}
}
char* Interpreter::getarg2(double arg, int argtype, ActiveObject *myvalues, TheTokens* mytokens, Mytype* mytemps)
{
	switch(argtype)
	{
	case 0:
		return (char*)(floattostring(arg).c_str());
	case 1:
		// Var name (string): mytokens->myvarnames[arg]
		// Convert number if appropriate:
		if (myvalues->myvars[(int)arg].t == 0)
			return (char*)(floattostring(myvalues->myvars[(int)arg].d).c_str());
		else
			return (char*)((myvalues->myvars[(int)arg].s).c_str());
	case 3:
		return (char*)(mytokens->mystrings[(int)arg].c_str());
	case 5:
		return (char*)((mytemps[(int)arg].s).c_str()); // Make sure initialised!
	default:
		return NULL;
	}
}
// Was int in C++, changed to boolean in Java:
int Interpreter::isnumber(double arg, int argtype, ActiveObject *myvalues, Mytype* mytemps)
{
	switch(argtype)
	{
	case -1:
		return 1;
	case 0:
		return 1;
	case 1: // Variable name - to do:
		// Var name (string): mytokens->myvarnames[arg]
		return myvalues->myvars[(int)arg].t == 0;
	case 3:
		return 0;
	case 5:
		return (mytemps[(int)arg].t) == 0; // Make sure initialised!
	default:
		return 0;
	}
}


// Modified interpreter routine - note: if (nn>0) is removed!
void Interpreter::setextravars(int nn)
{
	//if (nn>0)
	//{
	//vector <Mytype> *myvars = &((*multivalues)[nn]->myvars);
	vector <Mytype> *myvars = &(g->ActiveObjects[nn]->myvars);
	//printf("Number of vars: %d\n", myvars->size()); //debug

	(*myvars)[0].s = "Test Object"; // Object Name
	(*myvars)[0].t = 1;
	(*myvars)[1].s = "Description Goes Here!"; // Object Description
	(*myvars)[1].t = 1;
	(*myvars)[2].d = 0; // Portable
	(*myvars)[2].t = 0;
	(*myvars)[3].d = 0; // Examine
	(*myvars)[3].t = 0;
	(*myvars)[4].d = 0; // Use
	(*myvars)[4].t = 0;
	(*myvars)[5].d = 0; // Use With
	(*myvars)[5].t = 0;
	(*myvars)[6].d = 0; // Take
	(*myvars)[6].t = 0;
	(*myvars)[7].d = 0; // In inventory
	(*myvars)[7].t = 0;

	// Removed - from 3Dlicious! - not implemented here:
	//setobjectvars(nn); // removed

	//}
}

int Interpreter::initvalues(vector <TheTokens>* multitokens, int nn)
{
	char* temptext = new char[100];
	char* temptext2 = new char[100];

	// Now initialise the variables for the object (size given in the brain/class):
	for (unsigned int n=0; n<((*multitokens)[g->ActiveObjects[nn]->ObjectBrain].myvarnames.size()); n++)
	{
		// Exception: Check if any used variable names correspond to brain/class names:
		// NOTE: In Java: temptext = ...
		lower((*multitokens)[g->ActiveObjects[nn]->ObjectBrain].myvarnames[n], temptext);
		unsigned int ob = 0;

		// Find the first object of the appropriate class/brain (returned in n):
		for (ob=0; ob<g->ActiveObjects.size() &&
		strcmp(temptext, lower((char*)(*multitokens)[g->ActiveObjects[ob]->ObjectBrain].name.c_str(), temptext2)); ob++);

		// Add the new variable:
		Mytype tempvar;
		if (ob<g->ActiveObjects.size())
			tempvar.d = (double)ob;
		else
			// Clear the variable:
			tempvar.d = 0;

		tempvar.t = 0;
		g->ActiveObjects[nn]->myvars.push_back(tempvar);
	}

	// Set the extra variables here:
	//setextravars(nn); // removed

	delete[] temptext;
	delete[] temptext2;
	return 0;
}


// The Interpreter!
int Interpreter::interpret(vector <TheTokens>* multitokens, int on)
{
	TokeniserReturn* ret;
	Mytype *realret = new Mytype();
	//int jumplevel; // removed - not used
	int iflevel, numjumps, limitjumps;
	ActiveObject* myvalues;
	TheTokens* mytokens;

	//// Initialise the array for nested jump-points:
	//int jumppoint[100]; // removed

	double ifexp[20];
	int iffinaljumppoint[20];

	// Only 50 temps? (Should be enough - was 100) - changed to 100!
	Mytype* mytemps = new Mytype[100];
	// Added for Java - initialise mytemps[] (not needed in C++ implementation)
	//for (int whichtemp=0; whichtemp<100; whichtemp++)
	//mytemps[whichtemp] = new Mytype();

	// Note: Move these to the class if concurrent brain interpretation is necessary (i.e. and Amal-style 'Pause')...

	// For the brain:
	//jumplevel = 0; // removed - not used
	iflevel = 0;

	// Debug - the number of jumps made and limit:
	// Reset this as appropriate:
	numjumps = 0;
	// Make this limit customisable (eventually):
	limitjumps = 100000000; // was 1000;

	myvalues = g->ActiveObjects[on];
	mytokens = &(*multitokens)[myvalues->ObjectBrain];

	// Allow multi-pausing:
	if (myvalues->paused > 0)
		myvalues->paused--;

	// TODO: Start from set position // using myvalues->currentpos instead of l

	for (; (myvalues->currentpos)<((int)mytokens->myparameters.size()) && (numjumps<limitjumps) && (myvalues->paused == 0); myvalues->currentpos++)
	{
		ret = &mytokens->myparameters[myvalues->currentpos];

		// Finally, evaluate the instruction itself:
		if ((ret->insttype) == 1) // Standard Instruction
		{
			// For executing system instructions:
			switch(ret->instflag)
			{
			case 1:
				// Else If
				// Include the !ifexp(...) in the new ifexp:

				// Similar to If:
				if (!((0 == ifexp[iflevel - 1]) && 0!=getarg(ret->args[0], ret->argtypes[0], myvalues, mytemps)))
				{
					// Skip to the endif if a successful If or Else If test has already been run,
					// otherwise, skip to the next Else If or Else...
					if (ifexp[iflevel - 1] != 0)
						myvalues->currentpos = iffinaljumppoint[iflevel - 1] - 1;
					else
						myvalues->currentpos = (int)ret->args[1] - 1;
				}
				else
				{
					ifexp[iflevel - 1] = 1;
				}
				break;
			case 2:
				// Else
				if (ifexp[iflevel - 1] != 0)
					myvalues->currentpos = (int)ret->args[1] - 1;
				//iflevel--; // Removed
				break;
			case 3:
				// End/Exit - move to end of code (ignore parameters):
				myvalues->currentpos = mytokens->myparameters.size();
				break;
			case 5:
				// Until
				// Jump to jump-point if argument is false:
				if (getarg(ret->args[0], ret->argtypes[0], myvalues, mytemps) == 0)
				{
					myvalues->currentpos = (int)ret->args[1] - 1; // -1 because of the loop
					// Increase the number of jumps made:
					numjumps++;
				}
				break;
			case 6:
				// If
				//printf("DEBUG: IF needs some work, jump point = %d", ((int)ret->args[3]));
				ifexp[iflevel] = getarg(ret->args[0], ret->argtypes[0], myvalues, mytemps);
				iffinaljumppoint[iflevel] = (int)ret->args[3];
				iflevel++;
				// Move to set jumppoint if argument is false:
				if (ifexp[iflevel - 1] == 0)
					myvalues->currentpos = (int)ret->args[1] - 1; // -1 because of the loop
				break;
			case 7: case 18:
				// Endif, End If
				iflevel--;
				break;
			case 8:
				// While
				// Move to set jumppoint if argument is false:
				if (!getarg(ret->args[0], ret->argtypes[0], myvalues, mytemps))
					//{
					myvalues->currentpos = (int)ret->args[1] - 1; // -1 because of the loop
				// Debug - increase the number of jumps made (removed)
				//numjumps++;
				//}
				break;
			case 9: case 15: case 16: case 17:
				// Wend, Loop, Endwhile, Forever
				// Jump to jump-point (where we evaluate the temps before the while):
				myvalues->currentpos = (int)ret->args[0] - 1; // -1 because of the loop
				// Debug - increase the number of jumps made:
				numjumps++;
				break;
			case 12:
				// Wait Vbl

				//if (ret->numargs > 0)
				//{
				//    printf("DEBUG: Wait Vbl %d here!\n", (int)(ret->args[0]));
				//    myvalues->paused = (int)(ret->args[0]);
				//}
				//else
				//{
				//    printf("DEBUG: Wait Vbl here!");
				myvalues->paused = 1;
				//}

				break;
			case 13:
				// Wait - TODO
				//printf("DEBUG: WAIT needs some work\n");

				if (ret->numargs > 0)
				{
					//printf("DEBUG: Wait %d here!\n", (int)(ret->args[0]));
					myvalues->paused = (int)(ret->args[0]);
				}
				else
				{
					//printf("DEBUG: Wait (1) here!");
					myvalues->paused = 1;
				}

				break;
			case 19:
				// Procedure:
				//printf("DEBUG - executing Procedure %s (%d), end position: %d\n", mytokens->myprocedures[(int)ret->args[0]].c_str(), (int)ret->args[0], (int)ret->args[1]);

				// Jump to the end position, 1 after the End Proc (+1 removed as it's added automatically):
				myvalues->currentpos = (int)ret->args[1]; // + 1;
				break;
			case 20:
				// End Proc
				//printf("DEBUG - executing End Proc\n");

				// First grab the return value, if it exists:
				if (ret->numargs > 0)
				{
					if (isnumber(ret->args[0], ret->argtypes[0], myvalues, mytemps))
					{
						myvalues->myparamfloat = getarg(ret->args[0], ret->argtypes[0], myvalues, mytemps);
						myvalues->myparamint = (int)(myvalues->myparamfloat);
						//myvalues->myparamint = (int)getarg(ret->args[0], ret->argtypes[0], myvalues, mytemps);
					}
					else
					{
						myvalues->myparamstring = getarg2(ret->args[0], ret->argtypes[0], myvalues, mytokens, mytemps);
					}
				}

				// Jump back to position on stack here:
				if (!mytokens->myprocedurestack.empty())
				{
					myvalues->currentpos = mytokens->myprocedurestack[mytokens->myprocedurestack.size() - 1];
					mytokens->myprocedurestack.pop_back();
				}
				else
				{
					printf("Error: Procedure stack is empty!");
				}

				break;
			case 21: case 22:
			{{
				// Proc (call Procedure):
				//printf("TODO - executing Proc %s (%d), jumppoint=%d\n", mytokens->myprocedures[(int)ret->args[0]].c_str(), (int)ret->args[0], (int)mytokens->myprocedurepositions[(int)ret->args[0]]);

				int procpos = mytokens->myprocedurepositions[(int)ret->args[0]];
				TokeniserReturn procedureret = mytokens->myparameters[procpos];

				// First grab any arguments (debug - removed):
				/*if (ret->numargs > 1)
               {
                   printf("TODO: Proc arguments: \n");
                   for (int arg=1; arg<ret->numargs; arg++)
                   {
                       if (isnumber(ret->args[arg], ret->argtypes[arg], myvalues, mytemps))
                       {
                           printf("%f", getarg(ret->args[arg], ret->argtypes[arg], myvalues, mytemps));
                       }
                       else
                       {
                           printf("\"");
                           printf("%s", getarg2(ret->args[arg], ret->argtypes[arg], myvalues, mytokens, mytemps));
                           printf("\"");
                       }

                       if ((arg+1)<(ret->numargs))
                           printf(", ");
                  }
                  printf("\n");
              }*/

				int procedureargs = (int)procedureret.args[2];
				if (procedureargs != ((ret->numargs) - 1))
					printf("Syntax error: Wrong number of arguments in procedure call!\n");

				//if (procedureargs > 0)
				//    printf("Debug: Procedure definition has %d arguments.\n", procedureargs);

				// Now pass the evaluated expressions to the procedure definition's defined variables:
				for (int varnum=0; (varnum<procedureargs) && (varnum<((ret->numargs) - 1)); varnum++)
				{
					int whichvar = (int)procedureret.args[3+varnum];
					if (isnumber(ret->args[varnum+1], ret->argtypes[varnum+1], myvalues, mytemps))
					{
						double arg = getarg(ret->args[varnum+1], ret->argtypes[varnum+1], myvalues, mytemps);
						// Set the variable here to the given number:
						myvalues->myvars[whichvar].set(arg);
					}
					else
					{
						string argstr = getarg2(ret->args[varnum+1], ret->argtypes[varnum+1], myvalues, mytokens, mytemps);
						// Set the variable here to the given string:
						myvalues->myvars[whichvar].set(argstr);
					}
				}

				// Add current position to stack here:
				mytokens->myprocedurestack.push_back(myvalues->currentpos);

				// Branch to position of procedure here:
				myvalues->currentpos = procpos;

				break;
			}}
			case 23:
			{
				// Dim (to dimension arrays):

				//int arraynum = (int)ret->args[0]; // debug
				int numargs = (int)ret->args[1];
				vector<int> dimensions;

				// Debug:
				//string arrayname = mytokens->myarraynames[arraynum];
				//printf("DEBUG: Dim called here!\n");
				//printf("Array name: #%s# (%d)\n", arrayname.c_str(), arraynum);
				//printf("Number of dimensions: %d\n", numargs);

				for (int c=0; c<numargs; c++)
				{
					int whicharg = c+2;
					if (isnumber(ret->args[whicharg], ret->argtypes[whicharg], myvalues, mytemps))
					{
						double arg = getarg(ret->args[whicharg], ret->argtypes[whicharg], myvalues, mytemps);
						dimensions.push_back((int)arg);
						// Debug:
						//printf("%s\n", floattostring(arg).c_str());
					}
					else
					{
						printf("Syntax error: Array dimension must be a number!\n");
						string argstr = getarg2(ret->args[whicharg], ret->argtypes[whicharg], myvalues, mytokens, mytemps);
						// Debug:
						printf("%s\n", argstr.c_str());
					}
				}

				// Now dimension arraynum with dimensions - should be initial declaration here (TEST - TODO):
				// TODO - test if it is correct number!!!
				Mytypearray newarray(dimensions); //Mytypearray* newarray = new Mytypearray(dimensions);

				// Add the array here:
				myvalues->myarrays.push_back(newarray);

				break;
			}
			default:
				// case 14: - Do (not executed)
				// case 4: - Repeat (not executed)
				break;
			}

			//printf("%s ", textinstruction[ret->instflag]);
			//dumparg(ret->arg, ret->argtype, mytokens);
			//printf("\n");
		}
		else if ((ret->insttype) == 2) // Let Temp[x] = a OPERATOR b
		{
			if (isnumber(ret->args[1], ret->argtypes[1], myvalues, mytemps)
					&& isnumber(ret->args[2], ret->argtypes[2], myvalues, mytemps))
			{
				// Get args 1 and 2, do operation...
				double arg1 = getarg(ret->args[1], ret->argtypes[1], myvalues, mytemps);
				double arg2 = getarg(ret->args[2], ret->argtypes[2], myvalues, mytemps);
				mytemps[(int)ret->args[0]].t = 0;

				switch (ret->instflag)
				{
				case 0: // dot (.) - to do
					if (g->ActiveObjects[(int)arg1]->myvars[(int)arg2].t == 0)
					{
						mytemps[(int)ret->args[0]].d = g->ActiveObjects[(int)arg1]->myvars[(int)arg2].d;
					}
					else
					{
						mytemps[(int)ret->args[0]].s = g->ActiveObjects[(int)arg1]->myvars[(int)arg2].s;
						mytemps[(int)ret->args[0]].t = 1;
					}
					break;
				case 1:
					mytemps[(int)ret->args[0]].d = (arg2 == 0) ? 1 : 0; //!arg2; // arg1 or arg2?
					break;
				case 2:
					mytemps[(int)ret->args[0]].d = arg1 * arg2;
					break;
				case 3:
					mytemps[(int)ret->args[0]].d = arg1 / arg2;
					break;
				case 4:
					mytemps[(int)ret->args[0]].d = ((int)arg1) % ((int)arg2); // Better conversion to int?
							break;
				case 5:
					mytemps[(int)ret->args[0]].d = arg1 + arg2;
					break;
				case 6:
					mytemps[(int)ret->args[0]].d = arg1 - arg2;
					break;
				case 7:
					mytemps[(int)ret->args[0]].d = (arg1 < arg2) ? 1 : 0; //arg1 < arg2;
					break;
				case 8:
					mytemps[(int)ret->args[0]].d = (arg1 > arg2) ? 1 : 0; //arg1 > arg2;
					break;
				case 9:
					mytemps[(int)ret->args[0]].d = (arg1 <= arg2) ? 1 : 0; //arg1 <= arg2;
					break;
				case 10:
					mytemps[(int)ret->args[0]].d = (arg1 >= arg2) ? 1 : 0; //arg1 >= arg2;
					break;
				case 11:
					mytemps[(int)ret->args[0]].d = (arg1 == arg2) ? 1 : 0; //arg1 == arg2;
					break;
				case 12:
					mytemps[(int)ret->args[0]].d = (arg1 != arg2) ? 1 : 0; //arg1 != arg2;
					break;
				case 13:
					mytemps[(int)ret->args[0]].d = ((int)arg1) & ((int)arg2); // Changed - was: // ((arg1 != 0) && (arg2 != 0)) ? 1 : 0;
					break;
				case 14:
					mytemps[(int)ret->args[0]].d = ((int)arg1) | ((int)arg2); // Changed - was: // ((arg1 != 0) || (arg2 != 0)) ? 1 : 0;
					break;
				}
			}
			else
			{
				string arg1 = getarg2(ret->args[1], ret->argtypes[1], myvalues, mytokens, mytemps);
				string arg2;

				if (isnumber(ret->args[2], ret->argtypes[2], myvalues, mytemps))
					arg2 = floattostring(getarg(ret->args[2], ret->argtypes[2], myvalues, mytemps));
				else
					arg2 = getarg2(ret->args[2], ret->argtypes[2], myvalues, mytokens, mytemps);

				//printf("-%s- -%d-\n", arg2.c_str(), ret->argtypes[2]);
				switch (ret->instflag)
				{
				case 5: // was 1
					mytemps[(int)ret->args[0]].s = arg1 + arg2;
					mytemps[(int)ret->args[0]].t = 1;
					break;
				case 11: // was 5
					mytemps[(int)ret->args[0]].d = (arg1 == arg2) ? 1 : 0; //arg1 == arg2;
					mytemps[(int)ret->args[0]].t = 0;
					break;
				case 12:
					mytemps[(int)ret->args[0]].d = (arg1 != arg2) ? 1 : 0; //arg1 != arg2;
					mytemps[(int)ret->args[0]].t = 0;
					break;
				default:
					printf("DAMN! Cannot use that operator with a string! %s %d %s\n", arg1.c_str(), ret->instflag, arg2.c_str());
					mytemps[(int)ret->args[0]].t = 0;
					break;
				}
			}
		}
		else if ((ret->insttype) == 3) // Let Temp[x] = Function(a)
		{
			// Temp - as for below...
			// Evaluate func(arg) here - return answer instead of arg...
			realret->erase();
			realret = commandwrapper->runfunction(ret, mytokens, myvalues, 1, realret, mytemps);
			mytemps[(int)ret->args[0]].t = realret->t;
			if (realret->t == 0)
				mytemps[(int)ret->args[0]].d = realret->d;
			else
				mytemps[(int)ret->args[0]].s = realret->s; //?
		}
		else if ((ret->insttype) == 4) // Let Temp[x] = a - should be redundant.
		{
			if (isnumber(ret->args[0], ret->argtypes[0], myvalues, mytemps)) //&& isnumber(ret->args[1], ret->argtypes[1], myvalues))
			{
				// Get arg
				double arg = getarg(ret->args[1], ret->argtypes[1], myvalues, mytemps);
				mytemps[(int)ret->args[0]].d = arg;
				mytemps[(int)ret->args[0]].t = 0;
			}
			else
			{
				char* arg = getarg2(ret->args[1], ret->argtypes[1], myvalues, mytokens, mytemps);
				mytemps[(int)ret->args[0]].s = arg;
				mytemps[(int)ret->args[0]].t = 1;
			}
		}
		else if (((ret->insttype) >= 5) && ((ret->insttype) <= 11)) // Var[instflag] = arg;
		{
			if (isnumber(ret->args[0], ret->argtypes[0], myvalues, mytemps)) //&& isnumber(ret->args[1], ret->argtypes[1], myvalues))
			{
				// Set variables to arg:
				double arg = getarg(ret->args[0], ret->argtypes[0], myvalues, mytemps);
				// Variable name: mytokens->myvarnames[ret->instflag]

				// Set the variable now:
				switch (ret->insttype)
				{
				case 5: // =
					myvalues->myvars[ret->instflag].set(arg);
					break;
				case 6: // +=
					myvalues->myvars[ret->instflag].d += arg;
					break;
				case 7: // -=
					myvalues->myvars[ret->instflag].d -= arg;
					break;
				case 8: // /=
					myvalues->myvars[ret->instflag].d /= arg;
					break;
				case 9: // *=
					myvalues->myvars[ret->instflag].d *= arg;
					break;
				case 10: // ++
					myvalues->myvars[ret->instflag].d ++;
					break;
				case 11: // --
					myvalues->myvars[ret->instflag].d --;
					break;
				default:
					break;
				}
				myvalues->myvars[ret->instflag].t = 0;
			}
			else
			{
				char* arg = getarg2(ret->args[0], ret->argtypes[0], myvalues, mytokens, mytemps);

				// Set the variable now:
				switch (ret->insttype)
				{
				case 5: // =
					myvalues->myvars[ret->instflag].s = arg;
					break;
				case 6: // +=
					myvalues->myvars[ret->instflag].s += arg;
					break;
				}
				myvalues->myvars[ret->instflag].t = 1;
			}
		}
		else if (((ret->insttype) >= 25) && ((ret->insttype) <= 31)) // Array(expressions) = arg;
		{
			// Variable name: mytokens->myarraynames[ret.instflag]
			//printf("TODO: Assign array here! %s(", mytokens->myarraynames[ret->instflag].c_str());
			//for (int arg=1; arg<ret->numargs; arg++)
			//{
			//    printf("%f", getarg(ret->args[arg], ret->argtypes[arg], myvalues, mytemps));
			//    if ((arg+1) < (ret->numargs)) printf(", ");
			//}
			//printf(")=");

			// Get the ArrayList/vector of dimensional arguments:
			//vector<int> multidemargs(ret->numargs - 1);
			//for (int arg=1; arg<ret->numargs; arg++)
			//	multidemargs.push_back((int) getarg(ret->args[arg], ret->argtypes[arg], myvalues, mytemps))

			// Using array instead of vector for speed:
			int* multidemargs = new int[ret->numargs];
			multidemargs[0] = ret->numargs-1;
			for (int arg=1; arg<ret->numargs; arg++)
				multidemargs[arg] = ((int)getarg(ret->args[arg], ret->argtypes[arg], myvalues, mytemps));
			

			if (isnumber(ret->args[0], ret->argtypes[0], myvalues, mytemps)) //&& isnumber(ret->args[1], ret->argtypes[1], myvalues))
			{
				// Set variables to arg:
				double arg = getarg(ret->args[0], ret->argtypes[0], myvalues, mytemps);
				//printf("Debug: Set array index to %f\n", arg); // debug

				// Set the variable now:
				switch (ret->insttype)
				{
				case 25: // =
					myvalues->myarrays[ret->instflag].get(multidemargs)->d = arg;
					break;
				case 26: // +=
					myvalues->myarrays[ret->instflag].get(multidemargs)->d += arg;
					break;
				case 27: // -=
					myvalues->myarrays[ret->instflag].get(multidemargs)->d -= arg;
					break;
				case 28: // /=
					myvalues->myarrays[ret->instflag].get(multidemargs)->d /= arg;
					break;
				case 29: // *=
					myvalues->myarrays[ret->instflag].get(multidemargs)->d *= arg;
					break;
				case 30: // ++
					myvalues->myarrays[ret->instflag].get(multidemargs)->d ++;
					break;
				case 31: // --
					myvalues->myarrays[ret->instflag].get(multidemargs)->d --;
					break;
				default:
					break;
				}
				myvalues->myarrays[ret->instflag].get(multidemargs)->t = 0;
			}
			else
			{
				string arg = getarg2(ret->args[0], ret->argtypes[0], myvalues, mytokens, mytemps);
				//printf("%s\n", arg.c_str()); // debug

				// Set the variable now:
				switch (ret->insttype)
				{
				case 25: // =
					myvalues->myarrays[ret->instflag].get(multidemargs)->s = arg;
					break;
				case 26: // +=
					myvalues->myarrays[ret->instflag].get(multidemargs)->s += arg;
					break;
				default:
					break;
				}
				myvalues->myarrays[ret->instflag].get(multidemargs)->t = 1;

				//printf("Debug: Set string array here! %s", arg.c_str());
			}

			// Needed for array type instead of vector:
			delete[] multidemargs;

		}
		else if (((ret->insttype) >= 15) && ((ret->insttype) <= 21)) // brain.var = arg;
		{
			if (isnumber(ret->args[1], ret->argtypes[1], myvalues, mytemps))
			{
				// Set variables to arg:
				double arg = getarg(ret->args[1], ret->argtypes[1], myvalues, mytemps);
				// Variable name: mytokens->myvarnames[ret->instflag]

				// Set the variable now:
				switch (ret->insttype)
				{
				// ret->instflag = array of local variable (i.e. 'main') containing BRAIN NUM...
				// ret->args[0] = array of referred variable
				case 15: // =
					g->ActiveObjects[(int)myvalues->myvars[ret->instflag].d]->myvars[(int)ret->args[0]].set(arg);
					break;
				case 16: // +=
					g->ActiveObjects[(int)myvalues->myvars[ret->instflag].d]->myvars[(int)ret->args[0]].d += arg;
					break;
				case 17: // -=
					g->ActiveObjects[(int)myvalues->myvars[ret->instflag].d]->myvars[(int)ret->args[0]].d -= arg;
					break;
				case 18: // /=
					g->ActiveObjects[(int)myvalues->myvars[ret->instflag].d]->myvars[(int)ret->args[0]].d /= arg;
					break;
				case 19: // *=
					g->ActiveObjects[(int)myvalues->myvars[ret->instflag].d]->myvars[(int)ret->args[0]].d *= arg;
					break;
				case 20: // ++
					g->ActiveObjects[(int)myvalues->myvars[ret->instflag].d]->myvars[(int)ret->args[0]].d ++;
					break;
				case 21: // --
					g->ActiveObjects[(int)myvalues->myvars[ret->instflag].d]->myvars[(int)ret->args[0]].d --;
					break;
				default:
					break;
				}
				g->ActiveObjects[(int)myvalues->myvars[ret->instflag].d]->myvars[(int)ret->args[0]].t = 0;
			}
			else
			{
				char* arg = getarg2(ret->args[1], ret->argtypes[1], myvalues, mytokens, mytemps);

				// Set the variable now:
				switch (ret->insttype)
				{
				case 15: // =
					g->ActiveObjects[(int)myvalues->myvars[ret->instflag].d]->myvars[(int)ret->args[0]].s = arg;
					break;
				case 16: // +=
					g->ActiveObjects[(int)myvalues->myvars[ret->instflag].d]->myvars[(int)ret->args[0]].s += arg;
					break;
				}
				g->ActiveObjects[(int)myvalues->myvars[ret->instflag].d]->myvars[(int)ret->args[0]].t = 1;
			}
		}
		else if (((ret->insttype) >= 35) && ((ret->insttype) <= 41)) // brain.array(expressions) = arg;
		{
			printf("TO DO: Assign brain.array(expression) = arg ...\n");
		}
		else if ((ret->insttype) == 50) // Function as Instruction
		{
			// Evaluate func(arg) here:
			realret->erase();
			commandwrapper->runfunction(ret, mytokens, myvalues, 0, realret, mytemps);
		}
		else
		{
			printf("Error: No instruction recognised.\n"); // debug
		}
	}

	// Error messages:
	// If allowed number of jumps exceeded:
	if (numjumps >= limitjumps)
	{
		printf("Error: Too many jumps or infinite loop - exceeded limit of %d\n", limitjumps);
		myvalues->paused = 1; // Added for consistency
	}

	//printf("\nEnd of script\n"); // debug // removed

	// Note: The following need to be deleted below in C++, not in Java:

	delete[] mytemps;
	delete realret;

	return 0;
}



/*if (tt > 0) - in wend - instead of current while - this caused a mysterious crash...
{
   while (((mytokens->myparameters[tt-1]->insttype) >= 2) && ((mytokens->myparameters[tt-1]->insttype) <= 4))
   {
   if ( tt>0 )
      tt--;
   else
       break;
   }
}*/

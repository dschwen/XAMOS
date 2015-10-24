#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>

#include "Parser.h"

using namespace std;


Parser::Parser(Game* g_, int OPTIMISE_)
{
	g = g_;
	OPTIMISE = OPTIMISE_;
	numtemps = 0;

	// Move this:
	AMOS = true;
}


// TODO - duplicate:
// For the Parser:
string Parser::floattostring(double value)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << value;
	return ss.str();
}
double Parser::getarg(double arg, int argtype, ActiveObject *myvalues, Mytype* mytemps)
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
char* Parser::getarg2(double arg, int argtype, ActiveObject *myvalues, TheTokens* mytokens, Mytype* mytemps)
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
int Parser::isnumber(double arg, int argtype, ActiveObject *myvalues, Mytype* mytemps)
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


int Parser::initinstructions()
{
	g->textinstruction = (char**)malloc(sizeof(char*) * 100);
	g->textfunction = (char**)malloc(sizeof(char*) * 200);

	// Later on, read from a text file...
	g->textinstruction[0]=(char*)""; // Added - dummy first index
	g->textinstruction[1]=(char*)"Else If";
	g->textinstruction[2]=(char*)"Else";
	g->textinstruction[3]=(char*)"Exit";
	g->textinstruction[4]=(char*)"Repeat";
	g->textinstruction[5]=(char*)"Until";
	g->textinstruction[6]=(char*)"If";
	g->textinstruction[7]=(char*)"Endif"; // "End If" // problem!!!
	g->textinstruction[8]=(char*)"While";
	g->textinstruction[9]=(char*)"Wend";
	g->textinstruction[10]=(char*)"{";
	g->textinstruction[11]=(char*)"}";

	g->textinstruction[12]=(char*)"Wait Vbl";
	g->textinstruction[13]=(char*)"Wait";
	g->textinstruction[14]=(char*)"Do";
	g->textinstruction[15]=(char*)"Loop";
	g->textinstruction[16]=(char*)"Endwhile"; // as for Wend
	g->textinstruction[17]=(char*)"Forever"; // following Repeat - as for Loop
	g->textinstruction[18]=(char*)"End If"; // as for Endif
	g->textinstruction[19]=(char*)"Procedure"; // Tested elsewhere
	g->textinstruction[20]=(char*)"End Proc"; // Tested elsewhere
	g->textinstruction[21]=(char*)"Proc"; // Tested elsewhere
	g->textinstruction[22]=(char*)"Proc$"; // Tested elsewhere - reserved for procedure calls without Proc...
	g->textinstruction[23]=(char*)"Dim"; // Tested elsewhere

	g->numinstructions = 23; // 18; // 11;


	g->textfunction[0]=(char*)""; // Added - dummy first index
	g->textfunction[1]=(char*)"Double";
	g->textfunction[2]=(char*)"Print";
	g->textfunction[3]=(char*)"Say";
	g->textfunction[4]=(char*)"Instr";
	g->textfunction[5]=(char*)"Substring";


	// Added from jAMOS:
	g->textfunction[6]=(char*)"Screen Open";
	g->textfunction[7]=(char*)"Screen Display";
	g->textfunction[8]=(char*)"Screen Offset";
	g->textfunction[9]=(char*)"Screen Close";
	g->textfunction[10]=(char*)"Screen Clone";
	g->textfunction[11]=(char*)"Screen";
	g->textfunction[12]=(char*)"Double Buffer";
	g->textfunction[13]=(char*)"Dual Playfield";
	g->textfunction[14]=(char*)"Dual Priority";
	g->textfunction[15]=(char*)"Load Iff";
	g->textfunction[16]=(char*)"Load";
	g->textfunction[17]=(char*)"Erase";
	g->textfunction[18]=(char*)"Hide On";
	g->textfunction[19]=(char*)"Update Every";
	g->textfunction[20]=(char*)"Flash Off";
	g->textfunction[21]=(char*)"Flash";
	g->textfunction[22]=(char*)"Set Rainbow";
	g->textfunction[23]=(char*)"Rainbow Del";
	g->textfunction[24]=(char*)"Rainbow";
	g->textfunction[25]=(char*)"Bob Off";
	g->textfunction[26]=(char*)"Bob";
	g->textfunction[27]=(char*)"Set Bob";
	g->textfunction[28]=(char*)"Sprite Off";
	g->textfunction[29]=(char*)"Sprite";
	g->textfunction[30]=(char*)"Set Sprite Buffer";
	g->textfunction[31]=(char*)"Set Reg";
	g->textfunction[32]=(char*)"Unpack";
	g->textfunction[33]=(char*)"Channel to Sprite";
	g->textfunction[34]=(char*)"Channel to Bob";
	g->textfunction[35]=(char*)"Channel to Screen Offset";
	g->textfunction[36]=(char*)"Channel to Screen Size";
	g->textfunction[37]=(char*)"Channel to Rainbow";
	g->textfunction[38]=(char*)"Channel to Screen Display";
	g->textfunction[39]=(char*)"Bell";
	g->textfunction[40]=(char*)"X Mouse";
	g->textfunction[41]=(char*)"Y Mouse";
	g->textfunction[42]=(char*)"Mouse Key";
	g->textfunction[43]=(char*)"X Screen";
	g->textfunction[44]=(char*)"Y Screen";
	g->textfunction[45]=(char*)"X Hard";
	g->textfunction[46]=(char*)"Y Hard";
	g->textfunction[47]=(char*)"Joy";
	g->textfunction[48]=(char*)"Jleft";
	g->textfunction[49]=(char*)"Jright";
	g->textfunction[50]=(char*)"Jup";
	g->textfunction[51]=(char*)"Jdown";
	g->textfunction[52]=(char*)"Fire";
	g->textfunction[53]=(char*)"X Sprite";
	g->textfunction[54]=(char*)"Y Sprite";
	g->textfunction[55]=(char*)"I Sprite";
	g->textfunction[56]=(char*)"X Bob";
	g->textfunction[57]=(char*)"Y Bob";
	g->textfunction[58]=(char*)"I Bob";
	g->textfunction[59]=(char*)"Paste Bob";
	g->textfunction[60]=(char*)"Plot";
	g->textfunction[61]=(char*)"Ink";
	g->textfunction[62]=(char*)"Draw";
	g->textfunction[63]=(char*)"Bar";
	g->textfunction[64]=(char*)"Box";
	g->textfunction[65]=(char*)"Circle";
	g->textfunction[66]=(char*)"Ellipse";
	g->textfunction[67]=(char*)"Rnd";
	g->textfunction[68]=(char*)"Hrev";
	g->textfunction[69]=(char*)"Vrev";
	g->textfunction[70]=(char*)"Rev";
	g->textfunction[71]=(char*)"Rain";
	g->textfunction[72]=(char*)"Degree";
	g->textfunction[73]=(char*)"Radian";
	g->textfunction[74]=(char*)"Sin";
	g->textfunction[75]=(char*)"Cos";
	g->textfunction[76]=(char*)"Tan";
	g->textfunction[77]=(char*)"Asin";
	g->textfunction[78]=(char*)"Acos";
	g->textfunction[79]=(char*)"Atan";
	g->textfunction[80]=(char*)"Pi#";
	g->textfunction[81]=(char*)"Left$";
	g->textfunction[82]=(char*)"Right$";
	g->textfunction[83]=(char*)"Mid$";
	g->textfunction[84]=(char*)"Len";
	g->textfunction[85]=(char*)"Upper$";
	g->textfunction[86]=(char*)"Lower$";
	g->textfunction[87]=(char*)"String$";
	g->textfunction[88]=(char*)"Repeat$";
	g->textfunction[89]=(char*)"Space$";
	g->textfunction[90]=(char*)"Flip$";
	g->textfunction[91]=(char*)"Val";
	g->textfunction[92]=(char*)"Str$";
	g->textfunction[93]=(char*)"Asc";
	g->textfunction[94]=(char*)"Chr$";
	g->textfunction[95]=(char*)"Boom";
	g->textfunction[96]=(char*)"Shoot";
	g->textfunction[97]=(char*)"Param$"; // Special function
	g->textfunction[98]=(char*)"Param#"; // Special function
	g->textfunction[99]=(char*)"Param"; // Special function
	g->textfunction[100]=(char*)"GetArrayValue"; // Special function
	g->textfunction[101]=(char*)"Bob Col";
	g->textfunction[102]=(char*)"Sprite Col";
	g->textfunction[103]=(char*)"Spritebob Col";
	g->textfunction[104]=(char*)"BobSprite Col";
	g->textfunction[105]=(char*)"Col";
	g->textfunction[106]=(char*)"Text";
	g->textfunction[107]=(char*)"Text Length";
	g->textfunction[108]=(char*)"Paste Icon";
	g->textfunction[109]=(char*)"Hot Spot";
	g->textfunction[110]=(char*)"Paper";
	g->numfunctions = 110;


	// From 3Dlicious! (another project)
	/*
	g->textfunction[6]=(char*)"Take";
	g->textfunction[7]=(char*)"Rotate";
	g->textfunction[8]=(char*)"Move";
	g->textfunction[9]=(char*)"SetNode";
	g->textfunction[10]=(char*)"SelectUseWith";
	g->textfunction[11]=(char*)"UseWithMe"; // Swapped with UseWith
	g->textfunction[12]=(char*)"SetOtherNode";
	g->textfunction[13]=(char*)"Kill";
	g->textfunction[14]=(char*)"CreateInventoryObject";
	g->textfunction[15]=(char*)"CreateActiveObject";
	g->textfunction[16]=(char*)"UseWith"; // changed - was UsedWith
	g->textfunction[17]=(char*)"Scale";
	g->textfunction[18]=(char*)"Sound";
	g->textfunction[19]=(char*)"Drop";*/

	// TODO: Special functions (temporary numbers given - fix this!)
	//g->textfunction[20]=(char*)"Param$"; // Special function
	//g->textfunction[21]=(char*)"Param#"; // Special function
	//g->textfunction[22]=(char*)"Param"; // Special function

	// TODO: Special functions (jAMOS numbers given - fix this!)
	//g->textfunction[97]=(char*)"Param$"; // Special function
	//g->textfunction[98]=(char*)"Param#"; // Special function
	//g->textfunction[99]=(char*)"Param"; // Special function

	// Special function:
	//g->textfunction[100]=(char*)"GetArrayValue";

	//g->numfunctions = 22; // 19; // 100; // (in jAMOS!)


	// Not included yet from EnvGen: (in jAMOS!)
	//"if screen", "if not screen", "if bank", "if not bank", "if reg"

	return 0;
}


/////////////////////////////////////////////////////////////
// The following are Java wrappers for C++ only:
// Java-style substring:
string Parser::substring(string str, int pos)
{
	return str.substr(pos, str.length() - pos);
}
string Parser::substring(string str, int pos1, int pos2)
{
	return str.substr(pos1, pos2 - pos1);
}
/////////////////////////////////////////////////////////////


char* Parser::upper(string s, char* buffer)
{
	//char* st = (char*)s.c_str();
	for (unsigned int n=0; n<=s.size(); n++)
	{
		if ((s[n] >= 'a') && (s[n] <= 'z'))
		{
			buffer[n] = s[n] + ('A' - 'a');
		}
		else
		{
			buffer[n] = s[n];
		}
	}
	return buffer;
}

char* Parser::lower(string s, char* buffer)
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

string Parser::uppers(string s)
{
	string s2 = "";
	for (unsigned int n=0; n<s.size(); n++)
	{
		if ((s[n] >= 'a') && (s[n] <= 'z'))
		{
			s2 += (s[n] + ('A' - 'a'));
		}
		else
		{
			s2 += s[n];
		}
	}
	return s2;
}
string Parser::lowers(string s)
{
	string s2 = "";
	for (unsigned int n=0; n<s.size(); n++)
	{
		if ((s[n] >= 'A') && (s[n] <= 'Z'))
		{
			s2 += (s[n] + ('a' - 'A'));
		}
		else
		{
			s2 += s[n];
		}
	}
	return s2;
}
char Parser::lowerchar(char c)
{
	if ((c >= 'A') && (c <= 'Z'))
		return c - ('A' - 'a');
	else
		return c;
}
char* Parser::upper_o(char *st)
{
	char *mystring = new char[strlen(st)]; //???
	for (unsigned int n=0; n<=strlen(st); n++)
		if ((st[n] >= 'a') && (st[n] <= 'z'))
			mystring[n] = st[n] - ('a' - 'A');
		else
			mystring[n] = st[n];
	return mystring;
}
char* Parser::lower_o(char *st)
{
	char *mystring = new char[strlen(st)]; //???
	for (unsigned int n=0; n<=strlen(st); n++)
		if ((st[n] >= 'A') && (st[n] <= 'Z'))
			mystring[n] = st[n] - ('A' - 'a');
		else
			mystring[n] = st[n];
	return mystring;
}



// Methods for the Parser follow:
void Parser::inittokens(vector <TheTokens> *tokens, int n, string s)
{
	TheTokens t;
	t.name = s;
	tokens->push_back(t);
}

// param 1 corrupted!
ExpressionReturn Parser::evaluateexpression(char *expression, TheTokens* mytokens) //, int *numtemps)
{
	char temptext1[200], temptext2[200];

	// Moved:
	char param1[100]; //char *param1 = new char[50]; // Flexible length? - Fix.
	char param2[100]; //char *param2 = new char[50]; // See above...

	ExpressionReturn expret; // Added
	ExpressionReturn expret2; // Added

	TokeniserReturn* ret = new TokeniserReturn();
	int exptype = -1; // expression type (see above function)
	double data = 0; // for param1
	//double data2 = 0; // for param2 // removed
	int optype = -1; // used for evaluating operators - operator type
	int operatorposition = 0; // used for evaluating operators - where in code?
	int bracketlevel = 0; // used for evaluating operators - ignoring parentheses...
	int bracketposition = 0; // used for functions - where does the new expression start?
	int instring = 0; // Check to see whether we are inside a string...
	int operatorlength = 0; // New addition...

	// Evaluate the expression (simple only here) - ignore parentheses/functions at this point.
	// To begin with - hunt for operators (+ - * /):

	// New: Operator precedence is evaluated in the opposite order.
	operatorposition = 0; //strlen(expression) - 1;
	//for (int nn=strlen(expression)-1; (nn >= 0); nn--)
	for (unsigned int nn=0; nn<strlen(expression); nn++)
	{
		char cant = lowerchar(expression[nn]);

		// First switch - check for strings and parentheses:
		switch(cant)
		{
		case '(':
			if (instring == 0)
				bracketlevel++;
			break;
		case ')':
			if (instring == 0)
				bracketlevel--;
			break;
		case '"':
			instring = 1 - instring;
			break;
		}

		// Main switch - scan for operators:
		if ((instring == 0) && (bracketlevel == 0)) switch (cant)
		{
		case '.':
			// dot - check if not floating-point number, i.e. 9.nnn
			if (nn>0)
				if (optype <= 0 && (expression[nn-1] < '0' || expression[nn-1] > '9'))
				{
					optype = 0;
					operatorposition = nn;
					operatorlength = 1;
				}
			break;
		case '!':
			// for != (same as <>)
			if (optype <= 12)
			{
				if (expression[nn+1] == '=')
				{
					optype = 12;
					operatorlength = 2;
					operatorposition = nn;
					nn++;
				}
			}

			// for !
			if (optype <= 1)
			{
				optype = 1;
				operatorposition = nn;
				operatorlength = 1;
			}
			break;
		case 'n':
			if ((strlen(expression)-nn) > 4) //???
			{
				if ((optype <= 1) && lowerchar(expression[nn+1])=='o' && lowerchar(expression[nn+2])=='t'
						&& (expression[nn+3]==' ' || expression[nn+3]=='(') )
				{
					optype = 1;
					operatorposition = nn;
					operatorlength = 3;
					nn += 2; // will be 3 after n++...
				}
			}
			break;
		case '*':
			if (optype <= 4)
			{
				optype = 2;
				operatorposition = nn;
				operatorlength = 1;
			}
			break;
		case '/':
			if (optype <= 4)
			{
				optype = 3;
				operatorposition = nn;
				operatorlength = 1;
			}
			break;
		case '%':
			if (optype <= 4)
			{
				optype = 4;
				operatorposition = nn;
				operatorlength = 1;
			}
			break;
		case 'm':
			if ((nn>0) && ((strlen(expression)-nn) > 4))
			{
				if ((optype <= 4) && (expression[nn-1]==' ' || expression[nn-1]==')')
						&& lowerchar(expression[nn+1])=='o' && lowerchar(expression[nn+2])=='d'
								&& (expression[nn+3]==' ' || expression[nn+3]=='(') )
				{
					optype = 4;
					operatorposition = nn;
					operatorlength = 3;
					nn += 2; // will be 3 after n++...
				}
			}
			break;
		case '+':
			if (optype <= 6)
			{
				optype = 5;
				operatorposition = nn;
				operatorlength = 1;
			}
			break;
		case '-':
			if (optype <= 6)
			{
				optype = 6;
				operatorposition = nn;
				operatorlength = 1;
			}
			break;
		case '<':
			// for <> (same as !=)
			if (optype <= 12)
			{
				if (expression[nn+1] == '>')
				{
					optype = 12;
					operatorlength = 2;
					operatorposition = nn;
					nn++;
				}
			}

			// for < or <=
			if (optype <= 10)
			{
				// for <=
				if (expression[nn+1] == '=')
				{
					optype = 9;
					operatorlength = 2;
					operatorposition = nn;
					nn++;
				}
				else
				{
					// for <
					optype = 7;
					operatorposition = nn;
					operatorlength = 1;
				}
			}
			break;
		case '>':
			// for > or >=
			if (optype <= 10)
			{
				// for >=
				if (expression[nn+1] == '=')
				{
					optype = 10;
					operatorlength = 2;
					operatorposition = nn;
					nn++;
				}
				else
				{
					// for >
					optype = 8;
					operatorposition = nn;
					operatorlength = 1;
				}
			}
			break;
		case '=':
			if (optype <= 12)
			{
				optype = 11;
				operatorposition = nn;
				// for == (same as = here)...
						if (expression[nn+1] == '=')
						{
							operatorlength = 2;
							nn++;
						}
						else
							operatorlength = 1;
			}
			break;
		case '&':
			if (optype <= 13)
			{
				optype = 13;
				operatorposition = nn;
				// for && (same as & here)...
						if (expression[nn+1] == '&')
						{
							operatorlength = 2;
							nn++;
						}
						else
							operatorlength = 1;
			}
			break;
		case 'a':
			if ((nn>0) && ((strlen(expression)-nn) > 4))
			{
				if ((optype <= 13) && (expression[nn-1]==' ' || expression[nn-1]==')')
						&& lowerchar(expression[nn+1])=='n' && lowerchar(expression[nn+2])=='d'
								&& (expression[nn+3]==' ' || expression[nn+3]=='(') )
				{
					optype = 13;
					operatorposition = nn;
					operatorlength = 3;
					nn += 2; // will be 3 after n++...
				}
			}
			break;
		case '|':
			if (optype <= 14)
			{
				optype = 14;
				operatorposition = nn;
				// for || (same as | here)...
						if (expression[nn+1] == '|')
						{
							operatorlength = 2;
							nn++;
						}
						else
							operatorlength = 1;
			}
			break;
		case 'o':
			if ((nn>0) && ((strlen(expression)-nn) > 3))
			{
				if ((optype <= 14) && (expression[nn-1]==' ' || expression[nn-1]==')')
						&& lowerchar(expression[nn+1])=='r'
								&& (expression[nn+2]==' ' || expression[nn+2]=='(') )
				{
					optype = 14;
					operatorposition = nn;
					operatorlength = 2;
					nn += 1; // will be 2 after n++...
				}
			}
			break;
		}
	}

	param1[0] = (char)0; param2[0] = (char)0; // Is this needed?

	if (optype == -1) // No operator recognised.
	{
		// Transfer expression into param1 - minus leading spaces:
		unsigned int nn=0; unsigned int nnn=0;
		for (nnn=0; (nnn < strlen(expression)) && expression[nnn]==' '; nnn++);
		for (nn=nnn; (nn < strlen(expression)); nn++)
			param1[nn-nnn] = expression[nn];
		param1[nn-nnn] = (char)0;

		// Remove trailing spaces:
		for (int nnnn=nn-nnn-1; nnnn>=0 && param1[nnnn]==' '; nnnn--)
			param1[nnnn] = (char)0;

		// Make param2 null:
		param2[0] = (char)0; // Is this needed?
	}
	else //if (optype != -1) // Operator recognised: + - * / (so far)
	{
		// Grab the first part of the expression string - param1 - minus leading spaces:
		int nn=0; int nnn=0;
		for (nnn=0; (nnn < operatorposition) && expression[nnn]==' '; nnn++);
		for (nn=nnn; (nn < operatorposition); nn++)
			param1[nn-nnn] = expression[nn];
		param1[nn-nnn] = (char)0;

		// Remove trailing spaces:
		for (int nnnn=nn-nnn-1; nnnn>=0 && param1[nnnn]==' '; nnnn--)
			param1[nnnn] = (char)0;

		// Grab the second part of the expression string - param2 - minus leading spaces:
		nn=0; nnn=operatorposition + operatorlength;
		// Operator length = 1 - fix this for longer operators...
		for (; (nnn < (int)strlen(expression)) && expression[nnn]==' '; nnn++); // removed nnn=nnn;
		for (nn=nnn; (nn < (int)strlen(expression)); nn++)
			param2[nn-nnn] = expression[nn];
		param2[nn-nnn] = (char)0;

		// Remove trailing spaces:
		for (int nnnn=nn-nnn-1; nnnn>=0 && param2[nnnn]==' '; nnnn--)
			param2[nnnn] = (char)0;

		// New - if using dot operator (optype == 0), make the second one into a string:
		if (optype == 0)
		{
			string t = "";
			t = t + ((char*)"\"") + (char*)param2 + ((char*)"\"");
			strcpy(param2, t.c_str());
		}

		// Create a new instruction - insttype = 2 (operator/set temp)
		// Evaluate the expressions
		expret = evaluateexpression((char*)string(param1).c_str(), mytokens); //, numtemps); // Recursive.
		expret2 = evaluateexpression((char*)string(param2).c_str(), mytokens); //, numtemps); // Recursive.


		ret = new TokeniserReturn(); // In Java - now defined earlier!

		ret->insttype = 2; // Evaluate operator / set temp
		ret->instflag = optype; // Operator number: + - * / (1, 2, 3, 4)
		// Create new array:
		//ret->args[4]; ret->argtypes[4]; //?
		//ret->args = new int[4]; ret->argtypes = new int[4];
		ret->numargs = 3;
		ret->argtypes[1] = expret.exptype; ret->args[1] = expret.expdata;
		ret->argtypes[2] = expret2.exptype; ret->args[2] = expret2.expdata;
		//ret->argtype = expret.exptype;
		//ret->arg = expret.expdata;
		//ret->argtype2 = expret2.exptype;
		//ret->arg2 = expret2.expdata;

		// Get the new temp value:
		int tempvalue = numtemps;
		ret->argtypes[0] = 0; ret->args[0] = tempvalue;
		//ret->argtype3 = 0; // Constant - Is this necessary?
		//ret->arg3 = tempvalue; // Put into new line - show which temp to set!

		// Shallow copy (???)
		mytokens->myparameters.push_back(*ret);

		// Now put the appropriate temp into the original instruction line:
		data = tempvalue;
		numtemps++; //*numtemps = *numtemps + 1; //*numtemps++; // Zeroed between instructions
		exptype = 5; // Temp (not operator, 4)
	}

	//debug
	//printf("%s, ", param1);
	//printf("%s\n", param2);

	// Now parse param1 and param2 (as appropriate) to determine if constant numbers or not
	int param1type = 0; // 0=constant number, 1=not
	if (param1[0] == (char)0) // if (param1.length() == 0)
		param1type = -1;
	for (unsigned int nn=0; (nn<strlen(param1)) && (param1type == 0); nn++)
	{
		int p = (int)param1[nn];
		if (!((p >= (int)'0') && (p <= (int)'9')) && (p!=(int)0) && (p!=(int)'.'))
		{
			param1type = 1;
		}
	}
	int param2type = 0; // 0=constant number, 1=not
	if (param2[0] == (char)0)
		param2type = -1;
	for (unsigned int nn=operatorposition + operatorlength + 1; (nn < strlen(expression)) && (param2type == 0); nn++) // Added: +1
	{
		int p = 0;
		if (strlen(param2) > (nn - (operatorposition+1)))
			p = (int)param2[nn - (operatorposition+1)];
		if (!((p >= (int)'0') && (p <= (int)'9')) || (p==(int)0) || (p!=(int)'.'))
			param2type = 1;
	}

	// Constant numbers!
	if ((exptype != 4) && (exptype != 5) && (param1type == 0) && (param2type == -1))
	{
		exptype = 0; // Is this needed? - redundant...
		char *end;
		data = strtod(param1, &end);
	}
	// Test for strings:
	else if ((strlen(param1) > 0) && (param1[0]=='\"') && (param1[strlen(param1)-1]=='\"'))
	{
		param1type = 3;
		if (exptype != 5)
		{
			// Now parse newexp1 recursively - returning the below temp.
			data = mytokens->mystrings.size();
			//char* temp = new char[strlen(param1)-2]; //?
			//for (int n=0; n<(strlen(param1)-2); n++)
			//    temp[n] = param1[n+1];
			//temp[strlen(param1)-2] = (char)0;
			//mytokens->mystrings.push_back(string(temp)); //[data] = temp;
			mytokens->mystrings.push_back(string(param1).substr(1, strlen(param1)-2));
			exptype = 3; // Strings!
		}
	}
	else if (exptype != 5) // NOT for operators (2 parameters) - for param1 only:
	{
		// Now parse them - if they are not constants (0) - and find out if they are:
		// 1=Variable names, 2=Functions - Func(newexpression), 3=Strings ("'..'").
		// (To determine param1type and param2type)

		// Test for functions (opening brackets AND closing brackets):
		if (strlen(param1)>0) // added in Java
		{
			if (param1[strlen(param1)-1]==')')
			{
				for (unsigned int nn=0; (nn<(strlen(param1)-1)) && (exptype != 2); nn++)
				{
					if (param1[nn] == '(')
						exptype = 2;
					else
						bracketposition++;
				}
				if (exptype != 2)
					exptype = -1; // error - debug?
			}
		}
	}

	// For functions - get the new expressions: (Do only if not operator)
	// Find the appropriate function number here too...
	if (exptype == 2) // Function found
	{
		char functionname[100]; //char *functionname = new char[bracketposition];
		for (int nn=0; nn<bracketposition; nn++)
			functionname[nn] = param1[nn];
		functionname[bracketposition] = (char)0;

		char newexp1[1000]; // 1000? //50?
		for (unsigned int nn=bracketposition+1; (nn<strlen(param1)-1); nn++)
			newexp1[nn-bracketposition-1] = param1[nn];

		// This part is unusual!
		newexp1[strlen(param1)-bracketposition-2] = (char)0; // Note: -2, NOT -1!

		// Create a new instruction - insttype = 3|4 (Run function + set temp | just set temp)
		// Evaluate the expression - expand this for multiple parameters...!!!!!!!!!!!!!!!!!!!!!

		ret->insttype = 3; // Run function / set temp (1 arg only so far)
		ret->instflag = 0; // Function number

		// Evaluate the expressions here:
		MultiExpressionReturn* exprets = evaluatemultiexpressions(newexp1, mytokens); //, numtemps);
		ret->numargs = exprets->numexpressions + 1; // +1 added - don't forget temp number also!
		for (int n=0; n<exprets->numexpressions; n++)
		{
			// Note: [n+1], as [0] is for temp value. Function number is in instflag...
			ret->argtypes[n+1] = exprets->exp[n].exptype;
			ret->args[n+1] = exprets->exp[n].expdata;
		}

		// Create new array (removed):
		//ret->numargs = 3;
		//ret->argtypes[1] = expret.exptype; ret->args[1] = expret.expdata;

		// If simple parentheses - change insttype!!!
		if (param1[0] == '(')
		{
			ret->insttype = 4; // Simple parentheses - simply set temp to expression
		}
		else
		{
			// Check with function list:
			for (int nn=1; (nn<=g->numfunctions) && ((ret->insttype) == 3); nn++)
			{
				if (0 == strncmp(lower(g->textfunction[nn], temptext1), lower(functionname, temptext2), 1000)) // Zero/false = match
				{
					ret->instflag = nn; // Get the function number!
				}
			}

			// True = no match:
			if (ret->instflag == 0)
			{
				// Check for defined arrays here:
				int foundarray = 0; // FALSE
				for (unsigned int nn=0; (nn<mytokens->myarraynames.size()) && ((ret->insttype) == 3); nn++)
				{
					if (0 == strncmp(lower(mytokens->myarraynames[nn], temptext1), lower(functionname, temptext2), 1000)) // Zero/false = match
					{
						//printf("DEBUG: Get array value here! %s\n", mytokens->myarraynames[nn].c_str());
						foundarray = 1; // TRUE
						ret->instflag = 100; // Special function - get array value!
						// Cludge = add the array identifier to the END of the expression list:
						ret->numargs++;
						ret->argtypes[ret->numargs - 1] = 0;
						ret->args[ret->numargs - 1] = nn; // Array identifier
					}
				}

				// This appears to be deprecated...
				if (!foundarray)
				{
					// If the two strings don't match - treat as a pair of parentheses:
					ret->insttype = 4; // Simple parentheses - simply set temp to expression
					/// To replace the low-level stuff below - slower, but might reduce crashes (when using char[] not char*)
					// Note: Java adds string param1n = "" here...
					for (int blark=0; blark<bracketposition; blark++)
						for (unsigned int sht=0; sht<(strlen(param1)-1); sht++)
							param1[sht]=param1[sht+1]; // shuffle chars...
					//param1 += bracketposition; // Clever low-level stuff. (removed as now using char[] nor char*)...

					//printf("Debug: Apparently simply treat as a pair of parentheses?\n");
				}
			}
		}

		// Get the new temp value:
		int tempvalue = numtemps;
		ret->args[0] = tempvalue; ret->argtypes[0] = 0; // Constant - is this necessary?
		//ret->arg3 = tempvalue; // Put into new line - show which temp to set!
		//ret->argtype3 = 0; // Constant - Is this necessary?

		// Shallow copy (???)
		mytokens->myparameters.push_back(*ret);

		// Now put the appropriate temp into the original instruction line:
		data = tempvalue;
		numtemps++; //*numtemps = *numtemps + 1; //*numtemps++; // Zeroed between instructions.
		exptype = 5; // Temp (not function, 2)
	}

	// Variables at last...
	if ((param1type == 1) && (param2type == -1) && (exptype != 5)
			&& (exptype != 2) && (optype == -1))
	{
		// Now parse newexp1 recursively - returning the below temp.
		int tempvalue = mytokens->myvarnames.size();
		data = tempvalue;
		char tempstring[1000]; // 200
		//char *tempstring = new char[strlen(param1)];
		for (unsigned int n=0; n<strlen(param1); n++)
			tempstring[n] = param1[n];
		tempstring[strlen(param1)] = (char)0;

		// Check with variable list:
		int varmatch=0;
		for (unsigned int nn=0; (nn<(mytokens->myvarnames.size())); nn++)
		{
			if (0 == strncmp(lower(mytokens->myvarnames[nn], temptext1), lower(tempstring, temptext2), 1000)) // Zero/false = match
			{
				data = nn; // Get the function number!
				varmatch = 1;
			}
		}

		if (0 == varmatch)
		{
			mytokens->myvarnames.push_back(tempstring); //mytokens->myvarnames[data] = tempstring;
			//strcpy(mytokens->myvarnames[data], tempstring); //mytokens->myvarnames[data] = tempstring;
			data = mytokens->myvarnames.size()-1;
			//printf("Add variable!\n"); //debug
		}
		//else
		//{
		//// NEW - Update to latest case:
		//mytokens->myvarnames[data] = new char[100]; //strlen(tempstring)];
		//strcpy(mytokens->myvarnames[data], tempstring); //mytokens->myvarnames[data] = tempstring;
		//}
		exptype = 1; // Variables!
	}

	ExpressionReturn* expdata = new ExpressionReturn();

	expdata->exptype = exptype;
	expdata->expdata = data;

	return *expdata;
}
MultiExpressionReturn* Parser::evaluatemultiexpressions(char *expressions, TheTokens* mytokens) //, int *numtemps)
{
	MultiExpressionReturn* multi = new MultiExpressionReturn;
	multi->numexpressions = 0;
	//multi.exp[0];

	char expr[300];
	int nn=0, s=0, bracketlevel=0, instring=0, foundcomma=0, explen=0;
	int firstbracket=-1, lastbracket=-1, numcharsinzerobracketlevel=0;

	// First, remove any trailing spaces:
	if (strlen(expressions)>0)
		while (expressions[0]==' ')
			strcpy(expressions, string(expressions).substr(1).c_str());
	// Low-level stuff removed for Java: expressions++;

	explen = strlen(expressions);
	for (;;) //while (true)
	{
		for (; nn<explen; nn++) // nn=nn
		{
			char c = expressions[nn];
			foundcomma = 0;
			switch (c)
			{
			case ',':
			if (bracketlevel==0 && instring==0)
			{
				expr[s] = (char)0;
				multi->exp[multi->numexpressions] = evaluateexpression(expr, mytokens); //, numtemps);
				multi->numexpressions++;
				s = 0;
				foundcomma = 1;
			}
			break;
			case '(':
				bracketlevel++;
				if (firstbracket == -1)
					firstbracket=nn;
				break;
			case ')':
				bracketlevel--;
				lastbracket = nn;
				break;
			case '"':
				instring = 1 - instring;
				if (bracketlevel == 0)
					numcharsinzerobracketlevel++;
				break;
			default:
				if (bracketlevel == 0)
					numcharsinzerobracketlevel++;
				break;
			}

			if (foundcomma == 0)
			{
				//string expr2 = "";
				//expr2 += string(expr).substr(0,s);
				//expr2 += expressions[nn];
				//expr2 += string(expr).substr(s+1, string(expr).length()-s-2);
				//strcpy(expr, (char*)(expr2.c_str()));
				expr[s] = expressions[nn]; // TODO - use this or above 5 lines (broken) ???
				s++;
			}
		}

		// Used for calling functions as instructions with parentheses: print("hello", "world");
		if (foundcomma == 0 && firstbracket>=0 && numcharsinzerobracketlevel==0 && bracketlevel==0)
		{
			//expr[s] = (char)0; printf("--%d--%s\n", numcharsinzerobracketlevel, expr); //debug
			s = 0;
			nn = firstbracket + 1;
			explen = lastbracket;
			firstbracket = -1;
			lastbracket = -1;
		}
		else
		{
			break;
		}
	}

	// Finally, evaluate the last one:
	if (foundcomma == 0)
	{
		expr[s] = (char)0;
		multi->exp[multi->numexpressions] = evaluateexpression(expr, mytokens); //, numtemps);
		multi->numexpressions++;
	}

	return multi;
}
TokeniserReturn* Parser::tokeniser(char* textline, char** textinstruction,
		int numinstructions, int numfunctions, TheTokens* mytokens) //, int *numtemps)
{
	char temptext1[300], temptext2[300]; // was [200] for both

	//printf("%s\n", textline); //debug

	// Instructions to numbers:
	//int instcode = 0; // not used

	// For parsing expressions:
	char expression[100];

	// Is the line recognised as containing a valid instruction?
	int instrecognised=false;

	// First get the length:
	int linelength = strlen(textline);

	// Added to ensure return:
	TokeniserReturn* ret = new TokeniserReturn();

	// For the list of instructions:
	for (int n=1; (n<= (numinstructions + numfunctions)) && (instrecognised==false); n++)
	{
		instrecognised = false;

		char *testinstruction;
		if (n <= numinstructions)
			testinstruction = g->textinstruction[n];
		else
			testinstruction = g->textfunction[n - numinstructions];

		// For the instruction - 1 char at a time - first get the length:
		int instlength = strlen(testinstruction);

		//printf("DEBUG: Now testing for \"%s\" against \"%s\"", lower(testinstruction, temptext1), lower(string(textline).substr(0, instlength).c_str(), temptext2));

		// Then do the comparison:
		int compare=true;
		if (strncmp(lower(textline, temptext1), lower(testinstruction, temptext2), instlength))
			compare = false;

		// If an instruction is recognised:
		if (compare)
		{
			//printf("DEBUG: Instruction recognised! %s\n", testinstruction);
			// Now parse the expression:
			expression[0]=(char)0; // expression = "";
			int expposition=0; // Not needed in Java implementation

			for (int nn=instlength; nn<linelength; nn++)
			{
				//// Check for comments (//) - needs updating for strings etc.
				//if ((textline[nn] == '/') && (textline[nn+1] == '/'))
				//    nn = linelength;

				//if ((textline[nn] != ' ') && (textline[nn] != (char)0)) // Spaces removed later...
				if (textline[nn] != (char)0)
				{
					expression[expposition] = textline[nn];
					expposition++;
				}
				expression[expposition] = (char)0; // last character only?
			}

			// Create the return object:
			ret = new TokeniserReturn();
			if (n <= numinstructions)
			{
				ret->insttype = 1; // Instruction recognised
				ret->instflag = n; // Instruction number
			}
			else
			{
				ret->insttype = 50; // Call function as instruction
				ret->instflag = n - numinstructions;
			}

			// Evaluate the expressions here:
			MultiExpressionReturn* expret = evaluatemultiexpressions(expression, mytokens); //, numtemps);
			ret->numargs = expret->numexpressions;
			for (int nn=0; nn<expret->numexpressions; nn++)
			{
				ret->argtypes[nn] = expret->exp[nn].exptype;
				ret->args[nn] = expret->exp[nn].expdata;
			}

			//ExpressionReturn expret = evaluateexpression(expression, mytokens); //, numtemps);
			//ret->argtypes[0] = expret.exptype; //ret->argtype = expret.exptype; // Is this necessary???
			//ret->args[0] = expret.expdata; //ret->arg = expret.expdata; // Temporary value array index
			//ret->numargs = 1; // Fix this...

			// Shallow copy
			mytokens->myparameters.push_back(*ret);

			// Curently return only temps.
			return ret;
		}
	}

	// TODO: Check for procedure call without Proc:
	//if (instrecognised == false)
	//{
	//}

	// If not an instruction - check for: =, +=, -=, /-, *=
	int arrayfound = 0;
	if (instrecognised == false)
	{
		int foundequals=0;
		int equalsposition=0;
		int bracketdepth=0;
		int inastring=0 ; // FALSE
		int postype=0; // Possible type.

		for (int nn=0; (nn < linelength) && (foundequals == 0); nn++)
		{
			equalsposition = nn;
			postype=0;
			switch (textline[nn])
			{
			case '+': if (bracketdepth == 0 && !inastring) postype=6; break;
			case '-': if (bracketdepth == 0 && !inastring) postype=7; break;
			case '/': if (bracketdepth == 0 && !inastring) postype=8; break;
			case '*': if (bracketdepth == 0 && !inastring) postype=9; break;
			case '=': if (bracketdepth == 0 && !inastring) foundequals=5; break; // Standard var = ... // Why not postype = 5 - doesn't work...
			case '(': if (!inastring) { bracketdepth++; if (arrayfound == 0) arrayfound = nn; } break;
			case ')': if (!inastring) bracketdepth--; break;
			case '"': case '\'': inastring = !inastring; break;

			//case '[':
			//     foundequals=5; // FIX! - Array[n] = ... (TO DO) - need second 'equals position' too...
			//break;

			default: break;
			}
			if (postype)
			{
				switch (textline[nn+1])
				{
				case '=': if (bracketdepth == 0 && !inastring) foundequals = postype; break; // += etc. (TO DO)
				case '+': if (bracketdepth == 0 && !inastring) foundequals = 10; break;
				case '-': if (bracketdepth == 0 && !inastring) foundequals = 11; break;
				default:  foundequals = 1; break; // Not recognised!
				}
			}
		}

		if (foundequals >= 5)
		{
			// A variable is assigned.
			// Note: for += etc, equalsposition is at the '+' (later ++ or +=1 to the '=' position)

			// Check with variable list:
			char tempstring[200]; //char *tempstring = new char[equalsposition];
			int p = 0; // Final position of variable name
			for (p = equalsposition - 1; (p >= 0) && (textline[p] == ' '); p--);

			for (int n=0; n<=p; n++)
				tempstring[n] = textline[n];
			tempstring[p+1] = (char)0;

			string varname = "";
			string arrayexpressions = "";

			if (arrayfound > 0)
			{
				varname = string(tempstring).substr(0, arrayfound);
				arrayexpressions = string(tempstring).substr(arrayfound+1, string(tempstring).length() - arrayfound - 2);
			}
			else
			{
				varname = string(tempstring);
			}

			// As for variables in arguments:
			int varmatch=0;
			int data=0;
			if (arrayfound == 0)
			{
				//printf("Debug: Possible variable name: %s\n", varname.c_str());

				for (unsigned int nn=0; nn<(mytokens->myvarnames.size()) && (varmatch == 0); nn++)
				{
					if (!strncmp(lower(mytokens->myvarnames[nn], temptext1), lower(varname.c_str(), temptext2), 100)) // Zero/false = match
					{
						data = nn; // Get the function number!
						varmatch = 1;
						break;
					}
				}
			}
			else
			{
				//printf("Debug: Array name: %s, arguments: %s\n", varname.c_str(), arrayexpressions.c_str());

				for (unsigned int nn=0; nn<(mytokens->myarraynames.size()) && (varmatch == 0); nn++)
				{
					if (!strncmp(lower(mytokens->myarraynames[nn], temptext1), lower(varname.c_str(), temptext2), 100)) // Zero/false = match
					{
						data = nn; // Get the function number!
						varmatch = 1;
						break;
					}
				}
			}

			// Check if the 'variable name' contains a dot (.):
			// Fix for arrays!
			string part1 = lower(tempstring, temptext2);
			string part2;
			int test = part1.find(".", 0);
			int nn;
			if (test != (int)string::npos)
			{
				part2 = part1.substr(test+1, 100);
				part1 = part1.substr(0, test);

				// Remove spaces after part1:
				while (part1.substr(0, 1) == " ") part1 = part1.substr(1, 100);
				// Remove spaces before and after part2:
				while (part2.substr(0, 1) == " ") part2 = part2.substr(1, 100);
				while (part2.substr(part2.length()-1, 1) == " ") part2 = part2.substr(0, part2.length()-1);

				// For part1 - check to see if it is a current variable name. If not, add it.
				varmatch = 0;
				for (nn=0; nn<(int)(mytokens->myvarnames.size()) && (varmatch == 0); nn++)
					if (part1 == lower(mytokens->myvarnames[nn], temptext2))
						varmatch = 1;
				nn--;
				if (varmatch == 0)
				{
					nn = mytokens->myvarnames.size();
					mytokens->myvarnames.push_back(part1); //mytokens->myvarnames[nn] = part1;
				}
				data = nn;
			}
			// Is the variable name not already used?
			else if (varmatch == 0)
			{
				// For non-array variables:
				if (arrayfound == 0)
				{
					data = mytokens->myvarnames.size();
					mytokens->myvarnames.push_back(varname); //mytokens->myvarnames[data] = varname; // new char[100];
					//strcpy(mytokens->myvarnames[data], varname);
				}
				// For arrays:
				else
				{
					data = mytokens->myarraynames.size();
					mytokens->myarraynames.push_back(varname); //mytokens->myarraynames[data] = varname; // new char[100];
					//strcpy(mytokens->myarraynames[data], varname);
				}
			}
			//else //?
			//{
			//// Update to latest case:
			//mytokens->myvarnames[data] = new char[100];
			//strcpy(mytokens->myvarnames[data], tempstring);
			//}
			test = (test != (int)string::npos) ? 1 : 0;

			// Now parse the expression (as before - simplify?):
			expression[0]=(char)0;
			int expposition=0;

			// Move on for +=, etc:
			if (foundequals > 5)
				equalsposition++;

			// Add 10 to instruction number if used to assign brain.var= :
			if (test != 0)
				foundequals += 10;

			// Add 20 to instruction number if used to assign an array:
			if (arrayfound > 0)
				foundequals += 20;

			for (int nnn=equalsposition+1; nnn<linelength; nnn++)
			{
				// Check for comments (//) - needs updating for strings etc.
				if ((textline[nnn] == '/') && (textline[nnn+1] == '/'))
					nnn = linelength;

				//if ((textline[nnn] != ' ') && (textline[nnn] != (char)0)) // Spaces removed later...???
				if (textline[nnn] != (char)0)
				{
					expression[expposition] = textline[nnn];
					expposition++;
				}
				expression[expposition] = (char)0; // last character only?
			}

			// Add the additional expressions for array access if required:
			if (arrayfound > 0)
			{
				//expression += "," + arrayexpressions;
				strcat(expression, ",");
				strcat(expression, arrayexpressions.c_str());
			}

			// Evaluate the expressions here:
			MultiExpressionReturn* expret = evaluatemultiexpressions(expression, mytokens); //, numtemps);

			// Create the return type for the line:
			ret = new TokeniserReturn();
			ret->insttype = foundequals; // Variable assignment: = (5), += (6), -= (7), *= (8), /= (9)...
			ret->instflag = data; // Variable number

			// If not using a dot:
			if (test == 0)
			{
				for (int exp=0; exp<expret->numexpressions; exp++)
				{
					ret->argtypes[exp] = expret->exp[exp].exptype; //ret->argtype = expret->exptype;
					ret->args[exp] = expret->exp[exp].expdata; //ret->arg = expret->expdata;
				}
				ret->numargs = expret->numexpressions; // Added - fixes bug with optimisetemps...
			}
			else
			{
				// Add a string constant:
				mytokens->mystrings.push_back(string(part2));
				ret->argtypes[0] = 3;
				ret->args[0] = mytokens->mystrings.size()-1;

				// Added - allow for array access with a dot!
				for (int exp=0; exp<expret->numexpressions; exp++)
				{
					ret->argtypes[exp + 1] = expret->exp[exp].exptype; //ret->argtype = expret->exptype;
					ret->args[exp + 1] = expret->exp[exp].expdata; //ret->arg = expret->expdata;
				}
				ret->numargs = expret->numexpressions + 1;
			}

			// Shallow copy
			mytokens->myparameters.push_back(*ret);

			return ret;
		}
	}

	// Added to ensure return:
	//ret = new TokeniserReturn();
	return NULL; //return ret; // debug - modified in Java
}

// Optimise (remove temp[a]=temp[b] and update as appropriate) here...
int Parser::optimisetemps(TheTokens* mytokens, int lastlines)
{
	if ((int)(mytokens->myparameters.size()) >= (lastlines)) // or lastlines (?) - >= or > (???)
	{
		// Go thru all the new lines up to the last one:
		for (unsigned int n=(lastlines); n<(mytokens->myparameters.size()); n++)
		{
			// If line is temp[a]=x, then remove the line, shuffle up:
			//and substitute x below:
			if ((mytokens->myparameters[n].insttype) == 4) // Simple set temp
			{
				// The one argument (excluding temp #):
				double myarg = mytokens->myparameters[n].args[1];
				int myargtype = mytokens->myparameters[n].argtypes[1]; //argtype;
				//int mynumargs = mytokens->myparameters[n].numargs; // ADDED! //? //removed
				// Temp #:
				int mytemp = (int)mytokens->myparameters[n].args[0];
				// Shuffle up the lines:
				for (unsigned int nn=n; nn<(mytokens->myparameters.size() - 1); nn++)
					mytokens->myparameters[nn] = mytokens->myparameters[nn+1];

				// Remove last instance from vector:
				mytokens->myparameters.erase(mytokens->myparameters.begin()+mytokens->myparameters.size()-1,
						mytokens->myparameters.begin()+mytokens->myparameters.size());

				// Now scan all the following lines for temp #, and replace it with the above argument:
				for (unsigned int nn=n; nn<(mytokens->myparameters.size()); nn++)
				{
					//printf("line %d: Replace any occurance of temp[%d] with temp[%d]\n", nn, mytemp, myarg); //debug
					//if (((mytokens->myparameters[nn]->argtype) == 5) && ((mytokens->myparameters[nn]->arg) == mytemp))
					for (int argnum=0; argnum<(mytokens->myparameters[nn].numargs); argnum++) // for all args!
						if (((mytokens->myparameters[nn].argtypes[argnum]) == 5)
								&& ((mytokens->myparameters[nn].args[argnum]) == mytemp))
						{
							mytokens->myparameters[nn].argtypes[argnum] = myargtype;
							mytokens->myparameters[nn].args[argnum] = myarg;
							//mytokens->myparameters[nn]->numargs = mynumargs;
						}
				}
				n--; // Added - fixes bug with ((expression))...
			}
		}
	}
	return 0;
	//return mytokens; // modified in Java
}

vector <string>* Parser::addextravarnames(vector <string>* myvarnames)
{
	myvarnames->push_back(string("Name"));
	myvarnames->push_back(string("Description"));
	myvarnames->push_back(string("Portable"));
	myvarnames->push_back(string("Examine"));
	myvarnames->push_back(string("Use"));
	myvarnames->push_back(string("UseWith")); // Was originally UseWith, then UsedWith
	myvarnames->push_back(string("Take"));
	myvarnames->push_back(string("InInventory"));
	return myvarnames;
}


// Added to parse Dim statements:
vector<string> Parser::parsedim(string input)
{
	vector<string> individualstatements;
	vector<string> output;
	individualstatements.push_back("");
	int bracketlevel=0;
	int instrings=0; // false
	int whichstatement=0;

	// First it is necessary to split by commas - ignoring commas inside brackets and ""
	// Start at 4 for now - assume space after "Dim":
	for (unsigned int n=4; n<input.length(); n++)
	{
		char c = input[n];
		if (c == '(')
			bracketlevel++;
		else if (c == ')')
			bracketlevel--;
		else if (c == '"')
			instrings = !instrings;

		if ((c == ',') && (bracketlevel == 0) && (!instrings))
		{
			// Check for correct closing bracket here:
			if (individualstatements[whichstatement][(individualstatements[whichstatement]).length()-1] != ')')
			{
				printf("Syntax error - array dimensioned without closing bracket!\n");
			}
			whichstatement++;
			individualstatements.push_back("");
		}
		else
		{
			// Add the character if not a space outside of a string:
			if (instrings || (c != ' '))
			{
				individualstatements[whichstatement] += c;
			}
		}
	}

	// Add the final split individual dim statement:
	whichstatement++;

	// Now, split each "individual statement" into array name and multi-expression:
	for (int s=0; s<whichstatement; s++)
	{
		// Find the opening bracket, '('
		// (We know there is a closing bracket at the end due to the previous test)
		int openingbracket = individualstatements[s].find('(', 0);
		// TODO - syntax error checking here - for missing opening bracket.

		// Grab the array name:
		output.push_back(individualstatements[s].substr(0, openingbracket));

		// Grab the multi-expression to dimension the array:
		output.push_back(individualstatements[s].substr(openingbracket+1, individualstatements[s].length()-openingbracket-2));
	}

	return output;
}

// Added for Procedure arguments - split a string by commas, and remove excess spaces:
vector<string> Parser::splitstringbycommas(string input)
{
	vector<string> output;
	int index=0;
	int started=0;

	// First count the number of commas:
	unsigned int numargs = 1;
	for (unsigned int p=0; p<input.length(); p++)
		if (input[p] == ',')
			numargs++;

	// Create the output string array (now vector):
	//output = (string*)malloc(sizeof(string) * numargs);
	output.push_back(""); //output[0] = "";

	// Load the output into the array, ignoring initial spaces:
	for (unsigned int p=0; p<input.length(); p++)
	{
		if ((started || (input[p] != ' ')) && input[p] != ',')
		{
			output[index] += input[p];
			started = 1; // true
		}
		else if (input[p] == ',')
		{
			index++;
			output.push_back(""); //output[index] = "";
			started = 0; // false
		}
	}

	// Finally strip any trailing spaces:
	for (unsigned int i=0; i<numargs; i++)
	{
		while (output[i][output[i].length() - 1] == ' ')
			output[i] = output[i].substr(0, output[i].length() - 1);
	}

	// Debug: Print output:
	//printf("Initial string: %s\n", input.c_str());
	//printf("Output string array:\n");
	//for (unsigned int i=0; i<numargs; i++)
	//     printf("%s;\n", output[i].c_str());

	return output;
}


int Parser::evaluateline(string textline, int tn)
{
	//char* testline = new char[300];//[300];
	//char* testline2 = new char[300]; //[300];
	char* temptext = new char[1000];
	char* temptext2 = new char[1000];
	string testline = "";
	string testline2 = "";

	TheTokens* mytokens = &(g->mytokens[tn]);
	vector <TheTokens>* tokens = &(g->mytokens);
	// Instruction parser:
	// For each code line:
	TokeniserReturn* ret; // = new TokeniserReturn();
	//TokeniserReturn* ret2;

	//int numtemps = 0; // moved to global as Java lacks pointers!
	numtemps = 0;

	testline = textline;
	//strcpy(testline, textline.c_str());

	// Reset the temporary variable counter:
	//numtemps = 0;
	// Get the number of lines before evaluating the line:
	int lastlines = mytokens->myparameters.size();

	// New: Remove any initial spaces or tabs (indent):
	if (textline.length() > 0) // Added in Java
		while (testline[0]==' ' || testline[0]=='\t')
			for (unsigned int n=0; n<(testline.length()); n++)
				testline[n] = testline[n+1];
	//   testline = testline + 1; // low-level stuff - slower alternative above...

	// Check for comments (//) - and check if not inside strings:
	int instring = 0;
	for (unsigned int n=0; n<testline.length(); n++)
	{
		if (testline[n] == '"')
			instring = 1-instring;
		else if ((testline[n] == '/') && (testline[n+1] == '/') && (instring == 0))
		{
			testline = testline.substr(0, n);
			//testline[n] = (char)0; //linelength=n;
			break;
		}
	}

	// New: Remove any leading spaces, tabs, colons or semicolons (added - 13):
	int len = testline.length();
	if (len > 0)
		while (testline[len-1]==' ' || testline[len-1]=='\t'
				|| testline[len-1]==':' || testline[len-1]==';' || testline[len-1]==13 )
		{
			testline[len-1]=(char)0;
			len = testline.length();
			if (len == 0)
				break;
		}

	// Now check for colons or semicolons (: ;):
	instring = 0;
	for (unsigned int n=0; n<testline.length(); n++)
	{
		if (testline[n] == '"')
			instring = 1-instring;
		else if ((testline[n] == ':' || testline[n] == ';' || testline[n] == '{' || testline[n] == '}') && (instring == 0))
		{
			int o=0;
			// Cut the string before, and tokenise it:
			if (n>0)
			{
				// Check for spaces before the :;{} :
				for (int nn=n-1; nn>=0 && testline[nn]==' '; nn--)
					o++;
				testline2 = "";
				for (unsigned int nn=0; nn<(n-o); nn++)
					testline2 += testline[nn]; //testline2[nn] = testline[nn];

				//testline2[n-o] = (char)0;

				//printf("Debug: splitter detected! Line = \"%s\"\n", testline.c_str());
				//printf("New Line = \"%s\"\n", testline2.c_str());

				// Check for brain ..., end brain:
				if ((strncmp(lower(testline2.c_str(), temptext), "brain ", 6) == 0)
						|| (strncmp(lower(testline2.c_str(), temptext2), "adventure ", 10) == 0))
				{
					// Grab the brain name:
					string temp;
					//char* temp = new char[100];
					int count = 6;
					if (strncmp(lower(testline2.c_str(), temptext), "adventure ", 10) == 0)
						count = 10;

					for (; (count < (int)testline2.length()) && (testline2[count]==' '); count++);
					//int count2 = count;

					// New: Don't include any spaces or [ at end of line:
					int findend = testline2.length() - 1;
					for (; (findend > 0) && ((testline2[findend]==' ') || (testline2[findend]=='[') || (testline2[findend]==13)); findend--);

					for (; count <= findend; count++)
						temp.push_back(testline2[count]);
					//temp[count - count2] = (char)0;

					if (strcmp(lower(temp.c_str(), temptext), "master") == 0)
					{
						tn = 0;
						mytokens = &(*tokens)[tn]; //mytokens = &tokens[tn]; // Note: This line is removed in the Java version.
					}
					else
					{
						// Add another brain:
						tn = tokens->size(); printf("This shouldn't happen!\n");
						inittokens(tokens, tn, temp);
						//mytokens[tn] = new TheTokens(temp);
						mytokens = &(*tokens)[tn]; //mytokens = &tokens[tn]; // Note: This line is removed in the Java version.
						// Add extra variables here (removed in Java):
						//addextravarnames(&(mytokens->myvarnames)); // removed
					}
				}
				else if ((strncmp(lower(testline2.c_str(), temptext), "endbrain", 8) == 0)
						|| (strncmp(lower(testline2.c_str(), temptext2), "];", 2) == 0))
				{
					// never ran?
					// Remove the preceding "}" instruction if appropriate:
					if ((strncmp(lower(testline2.c_str(), temptext), "];", 2) == 0))
					{

						// Remove last instance from vector:
						mytokens->myparameters.erase(mytokens->myparameters.begin()+mytokens->myparameters.size()-1,
								mytokens->myparameters.begin()+mytokens->myparameters.size());
					}
					tn = 0;
					mytokens = &(*tokens)[tn]; //mytokens = &tokens[tn]; // Note: This line is removed in the Java version.
				}
				else
				{
					// Tokenise the line:
					tokeniser((char*)testline2.c_str(), g->textinstruction, g->numinstructions, g->numfunctions, mytokens); //, &numtemps);

					// Optimise (remove temp[a]=temp[b] and update as appropriate) here...
					if (OPTIMISE)
						optimisetemps(mytokens, lastlines); // modified in Java - different in C++
				}
			}

			// Now check for braces { } - fix this and combine with above...
			if (testline[n] == '{' || ((testline[n] == '}') && (testline[n + 1] != ';')))
			{
				// Create the return type for the line:
				ret = new TokeniserReturn();
				ret->insttype = 1; // Standard instructon
				ret->instflag = 10 + (testline[n] == '}'); // 10={, 11=}
				ret->argtypes[0] = -1; // 0 shows in dumparg, -1 doesn't. (??????)
				ret->args[0] = 0;
				ret->numargs = 1; // Added - fixes bug with optimisetemps...

				// Shallow copy
				mytokens->myparameters.push_back(*ret);
			}

			if ((n+1) < testline.length())
				testline = testline.substr(n+1, testline.length()-n-1);
			else
				testline = "";
			//testline = substring(testline, n+1);

			//testline += n+1; // testline = substring(testline, n+1); // low-level stuff - removed in Java
			// low-level space removal (removed in Java):

			while (testline[0] == ' ')
				testline = testline.substr(1, testline.length()-1); //testline++; // testline = substring(testline, 1);

			n = -1; // as 1 is added (?)
			// (bug note: infinite loop without removing trailing colons/semicolons above...)
		}
	}


	// Added: Check for Procedure..., End Proc:
	int procfound = 0; //FALSE;
	int dimfound = 0; //FALSE;
	if (strncmp(lower(testline.c_str(), temptext), "procedure ", 10) == 0)
	{
		// Added - scan for [] for passing arguments:
		int foundparameter = -1; int foundparameter2 = -1;
		for (unsigned int temp=10; temp<testline.length(); temp++)
		{
			if (testline[temp] == '[')
			{
				foundparameter = temp;
				break;
			}
		}
		if (foundparameter != -1)
		{
			for (int temp=(testline.length()-1); temp>foundparameter; temp--)
			{
				if (testline[temp] == ']')
				{
					foundparameter2 = temp;
					break;
				}
			}
			if (foundparameter2 == -1)
			{
				printf("Syntax error: Procedure ...[ without closing ']' !\n");
			}
		}

		// First grab the procedure's name:
		string procname = "";
		int count = 10;
		// Ignore initial spaces:
		for (; (count < (int)testline.length()) && (testline[count]==' '); count++);

		// Don't include any spaces or [ at end of line:
		// Added - ignore anything after [ inclusive if Proc is called with parameters [...]:
		int findend;
		if (foundparameter == -1)
			findend = testline.length() - 1;
		else
			findend = foundparameter - 1;

		for (; (findend > 0) && ((testline[findend]==' ') || (testline[findend]=='[')  || (testline[findend]==13)); findend--);           
			
		// Now grab the procedure's name:
		for (; count <= findend; count++)
			procname += testline[count];

		// Add the procedure name to the list of procedure strings:
		g->mytokens[tn].myprocedures.push_back(lower(procname.c_str(), temptext));
		
		// Add instruction here, as in tokeniser()
		TokeniserReturn ret; // = new TokeniserReturn();
		ret.insttype = 1; // Instruction recognised
		ret.instflag = 19; // Instruction number
		
		ret.numargs = 3;
		// Procedure number:
		ret.args[0] = g->mytokens[tn].myprocedures.size() - 1;
		ret.argtypes[0] = 0;
		// Used to store the End Proc position (later):
		ret.args[1] = 0;
		ret.argtypes[1] = 0;
		// Used to store the number of arguments in the procedure definition:
		ret.args[2] = 0;
		ret.argtypes[2] = 0;

		// Grab the procedure arguments string if enclosed in []:
		if ((foundparameter != -1) && (foundparameter2 != -1))
		{
			if ((foundparameter2-foundparameter-1) <= 0 )
			{
				printf("Syntax error: Procedure ...[] without defined arguments!\n");
			}
			else
			{
				string arguments = testline.substr(foundparameter + 1, foundparameter2 - foundparameter - 1);
				//printf("TO DO - argument support: Procedure %s[%s]\n", procname.c_str(), arguments.c_str()); //+", size="+(foundparameter2-foundparameter-1));

				// Split string by commas:
				vector<string> varnames = splitstringbycommas(arguments);

				//for (int i=0; i<varnames.length; i++)
				//	printf("%s;\n", varnames[i].c_str());

				// Add the required number of arguments to the procedure definition:
				ret.args[2] = varnames.size();
				ret.numargs += varnames.size();

				// Here process the variable names in the procedure definition:
				for (unsigned int i=0; i<varnames.size(); i++)
				{
					// Check to see if it is a current variable name.
					int varnum = -1;
					unsigned int nn;
					for (nn=0; nn<(unsigned int)(g->mytokens[tn].myvarnames.size()) && (varnum == -1); nn++)
						if (varnames[i] == string(lower(g->mytokens[tn].myvarnames[nn], temptext)))
							varnum = nn;

					// If not, add it.
					if (varnum == -1)
					{
						varnum = g->mytokens[tn].myvarnames.size();
						g->mytokens[tn].myvarnames.push_back(varnames[i]);
						//printf("DEBUG: Added new variable #%d#: %s;", varnum, varnames[i].c_str());
					}
					//else
					//{
					//	printf("DEBUG: Variable found #%d#: %s;", varnum, varnames[i].c_str());
					//}

					// Now add the variable index to the procedure's list of arguments, offset 3:
					ret.argtypes[i+3]=0;
					ret.args[i+3]=varnum;
				}
			}
		}

		// Add the procedure definition to the list of instructions here:
		g->mytokens[tn].myparameters.push_back(ret);
		
		// Add the procedure position to the list of procedure positions:
		int procedureposition = g->mytokens[tn].myparameters.size() - 1;
		g->mytokens[tn].myprocedurepositions.push_back(procedureposition);
		
		// Debug:
		//printf("Procedure #%s# (%d), position: %d\n", procname.c_str(), (int)ret.args[0], procedureposition);

		procfound = 1; //TRUE;
	}
	else if (strncmp(lower(testline, temptext), "end proc", 8) == 0)
	{
		// Added - scan for [] for returning an argument:
		int foundparameter = -1; int foundparameter2 = -1;
		for (unsigned int temp=8; temp<testline.length(); temp++)
		{
			if (testline[temp] == '[')
			{
				foundparameter = temp;
				break;
			}
		}
		if (foundparameter != -1)
		{
			for (int temp=(testline.length()-1); temp>foundparameter; temp--)
			{
				if (testline[temp] == ']')
				{
					foundparameter2 = temp;
					break;
				}
			}
			if (foundparameter2 == -1)
			{
				printf("Syntax error: End Proc[ without closing ']' !\n");
			}
		}

		// Add instruction here, as in tokeniser()
		TokeniserReturn ret; // = new TokeniserReturn();
		ret.insttype = 1; // Instruction recognised
		ret.instflag = 20; // Instruction number

		// Grab the expression string if enclosed in []:
		if ((foundparameter != -1) && (foundparameter2 != -1))
		{
			if ((foundparameter2-foundparameter-1) <= 0 )
			{
				printf("Syntax error: End Proc[] without argument!\n");
			}
			else
			{
				string expression = testline.substr(foundparameter + 1, foundparameter2 - foundparameter - 1);
				//printf("Debug: End Proc[%s], size=%d\n", expression.c_str(), (int)(foundparameter2 - foundparameter - 1));

				// Parse the expression here and add to the program:
				// Evaluate the expressions here:
				MultiExpressionReturn* expret = evaluatemultiexpressions((char*)expression.c_str(), &(g->mytokens[tn])); //, numtemps);
				if (expret->numexpressions > 1)
				{
					printf("Syntax error: Too many arguments for End Proc[]!\n");
				}
				ret.numargs = expret->numexpressions;
				for (int nn=0; nn<expret->numexpressions; nn++)
				{
					ret.argtypes[nn] = expret->exp[nn].exptype;
					ret.args[nn] = expret->exp[nn].expdata;
				}
			}
		}
		else
		{
			ret.numargs = 0;
		}

		g->mytokens[tn].myparameters.push_back(ret);

		// Now set the End Proc position in the previous Procedure call (no nested procedures allowed):
		int procnum = g->mytokens[tn].myprocedurepositions.size() - 1;
		int procpos = g->mytokens[tn].myprocedurepositions[procnum];
		int endprocpos = g->mytokens[tn].myparameters.size() - 1;
		g->mytokens[tn].myparameters[procpos].args[1] = endprocpos;

		// Debug:
		//printf("End Proc - position: %d\n", (int)(g->mytokens[tn].myparameters.size()-1));

		procfound = 1; //TRUE;
	}
	else if (strncmp(lower(testline, temptext), "proc ", 5) == 0)
	{
		// Added - scan for [] for passing arguments:
		int foundparameter = -1; int foundparameter2 = -1;
		for (unsigned int temp=5; temp<testline.length(); temp++)
		{
			if (testline[temp] == '[')
			{
				foundparameter = temp;
				break;
			}
		}
		if (foundparameter != -1)
		{
			for (int temp=(testline.length()-1); temp>foundparameter; temp--)
			{
				if (testline[temp] == ']')
				{
					foundparameter2 = temp;
					break;
				}
			}
			if (foundparameter2 == -1)
			{
				printf("Syntax error: Proc ...[ without closing ']' !\n");
			}
		}

		// Grab the procedure's name:
		string procname = "";
		int count = 5;
		// Ignore initial spaces:
		for (; (count < (int)testline.length()) && (testline[count]==' '); count++);

		// Don't include any spaces or [ at end of line:
		// Added - ignore anything after [ inclusive if Proc is called with parameters [...]:
		int findend;
		if (foundparameter == -1)
			findend = testline.length() - 1;
		else
			findend = foundparameter - 1;

		for (; (findend > 0) && ((testline[findend]==' ') || (testline[findend]=='[')  || (testline[findend]==13)); findend--);           

		// Now grab the procedure's name:
		for (; count <= findend; count++)
			procname += testline[count];

		// Add the procedure call name to the list of procedure call strings:
		g->mytokens[tn].myprocedurecalls.push_back(string(lower(procname, temptext)));

		// Add instruction here, as in tokeniser()
		TokeniserReturn ret; // = new TokeniserReturn();
		ret.insttype = 1; // Instruction recognised
		ret.instflag = 21; // Instruction number


		// Grab the expression string if enclosed in []:
		if ((foundparameter != -1) && (foundparameter2 != -1))
		{
			if ((foundparameter2-foundparameter-1) <= 0 )
			{
				printf("Syntax error: Proc ...[] without argument!\n");
				ret.numargs = 1;
			}
			else
			{
				string expression = testline.substr(foundparameter + 1, foundparameter2 - foundparameter - 1);
				//printf("Debug: Proc[%s], size=%d\n", expression.c_str(), (foundparameter2 - foundparameter - 1));
				
				// Parse the expression here and add to the program:
				// Evaluate the expressions here:
				MultiExpressionReturn* expret = evaluatemultiexpressions((char*)expression.c_str(), &(g->mytokens[tn])); //, numtemps);

				// Added: +1, since first argument is reserved for the procedure call number (later the actual procedure number):
				ret.numargs = expret->numexpressions + 1;
				for (int nn=0; nn<expret->numexpressions; nn++)
				{
					ret.argtypes[nn+1] = expret->exp[nn].exptype;
					ret.args[nn+1] = expret->exp[nn].expdata;
				}
			}
		}
		else
		{
			ret.numargs = 1;
		}

		// Initial argument: Procedure call number (NOT Procedure number at this stage!)
		ret.args[0] = g->mytokens[tn].myprocedurecalls.size() - 1;
		ret.argtypes[0] = 0;

		// Add the Proc call to the list of instructions in the program:
		g->mytokens[tn].myparameters.push_back(ret);

		// Debug:
		//printf("Proc #%s# (%d), position: %d\n", procname.c_str(), (int)ret.args[0], (int)(g->mytokens[tn].myparameters.size()-1));
			
		procfound = true;
	}
	// Now parse array declarations (Dim):
	else if (strncmp(lower(testline, temptext), "dim ", 4) == 0)
	{
		vector<string> arrays = parsedim(testline);

		// Each even string is the array name, the following string is the multi-expressions to dimension that array.
		// Create a new statement for each.

		for (unsigned int s=0; s<arrays.size()/2; s++)
		{
			// Add instruction here, as in tokeniser()
			TokeniserReturn ret; // = new TokeniserReturn();
			ret.insttype = 1; // Instruction recognised
			ret.instflag = 23; // Instruction number (Dim)

			string arrayname = arrays[s*2];
			string arraymultiexpression = arrays[(s*2)+1];

			// Add the array name to the list of array names (TODO: Check for array already dimensioned!):
			g->mytokens[tn].myarraynames.push_back(lower(arrayname.c_str(), temptext));

			// Parse the multi-expression here:
			MultiExpressionReturn* expret = evaluatemultiexpressions((char*)arraymultiexpression.c_str(), &(g->mytokens[tn]));

			// Added: +2, since first argument is reserved for the array number, second for numargs:
			ret.numargs = expret->numexpressions + 2;
			for (int nn=0; nn<expret->numexpressions; nn++)
			{
				ret.argtypes[nn+2] = expret->exp[nn].exptype;
				ret.args[nn+2] = expret->exp[nn].expdata;
			}

			// Initial argument: Array number:
			ret.args[0] = g->mytokens[tn].myarraynames.size() - 1;
			ret.argtypes[0] = 0;

			// Second argument: Number of arguments (=dimensions):
			ret.args[1] = expret->numexpressions;
			ret.argtypes[1] = 0;

			// Add the Dim (split to each definition) to the list of instructions in the program:
			g->mytokens[tn].myparameters.push_back(ret);
		}

		// Flag it to not pass the Dim instruction again:
		dimfound = 1; //TRUE;

		// Debug - print out each statement:
		/*for (unsigned int s=0; s<arrays.size()/2; s++)
		{
			string arrayname = arrays[s*2];
			string arraymultiexpression = arrays[(s*2)+1];

			printf("Array name: ");
			printf("#%s#", arrayname.c_str());
			printf(", array multi-expression: ");
			printf("#%s#\n", arraymultiexpression.c_str());
		}*/
	}



	// Check for brain ..., end brain:
	int test = strncmp(lower(testline.c_str(), temptext), "brain ", 6) == 0;
	test = test || strncmp(lower(testline.c_str(), temptext2), "adventure ", 10) == 0;

	//if ( (strncmp(lower(testline, temptext), "brain ", 6) == 0)
	//  || (strncmp(lower(testline, temptext2), "adventure ", 10) == 0) )

	if (test)
	{
		// Grab the brain name:
		string temp = "";

		int count = 6;
		if (strncmp(lower(testline.c_str(), temptext), "adventure ", 10) == 0)
			count = 10;

		for (; (count < (int)testline.length()) && (testline[count]==' '); count++);
		//int count2 = count;

		// New: Don't include any spaces or [ at end of line:
		int findend = testline.length() - 1;
		for (; (findend > 0) && ((testline[findend]==' ') || (testline[findend]=='[')  || (testline[findend]==13)); findend--);

		for (; count <= findend; count++)
			temp.push_back(testline[count]);

		if (strcmp(lower(temp.c_str(), temptext), "master") == 0)
		{
			tn = 0;
			mytokens = &(*tokens)[tn]; //mytokens = &tokens[tn]; // line removed for Java
		}
		else
		{
			// Add another brain:
			tn = tokens->size();
			inittokens(tokens, tn, temp);
			mytokens = &(*tokens)[tn]; //mytokens = &tokens[tn]; // line removed for Java
			// Add extra variables here (removed in Java):
			//addextravarnames(&(mytokens->myvarnames)); // removed
		}
	}
	//else if (strncmp(lower(testline, temptext), "endbrain", 8) == 0)
	else
	{
		//lower(testline2, temptext);
		test = strncmp(lowers(testline2).c_str(), "endbrain", 8) == 0;
		test = test || (strncmp(testline2.c_str(), "];", 2) == 0);
		//if ( (strncmp(lower(testline2, temptext), "endbrain", 8) == 0)
		//       || (strncmp(lower(testline2, temptext2), "];", 2) == 0) )

		if (test)
		{
			// Remove the preceding "}" instruction if appropriate:
			if ((strncmp(testline2.c_str(), "];", 2) == 0))
			{
				// Remove last instance from vector:
				mytokens->myparameters.erase(mytokens->myparameters.begin()+mytokens->myparameters.size()-1,
						mytokens->myparameters.begin()+mytokens->myparameters.size());
			}

			tn = 0;
			mytokens = &(*tokens)[tn]; //mytokens = &tokens[tn]; // line removed for Java
		}
		else if ((!procfound) && (!dimfound)) // added - don't process Procedure/End Proc/Proc or Dim here.
		{
			// Tokenise the line:
			tokeniser((char*)testline.c_str(), g->textinstruction, g->numinstructions, g->numfunctions, mytokens); //, &numtemps); // removed param 2 in Java
			// Optimise (remove temp[a]=temp[b] and update as appropriate) here... - removed a long time ago
                        //if (OPTIMISE)
			//optimisetemps(mytokens, lastlines); // modified in Java
		}
	}

	//delete[] testline;
	//delete[] testline2;

	delete[] temptext;
	delete[] temptext2;

	return tn;
}

int Parser::evaluateinstructions(vector <string> textline)//, vector <TheTokens> *tokens)
{
	//char* testline = new char[300];//[300];
	//char* testline2 = new char[300]; //[300];
	char* temptext = new char[300];
	char* temptext2 = new char[300];

	vector <TheTokens>* tokens = &(g->mytokens);

	// Instruction parser:
	// For each code line:
	TokeniserReturn* ret; // = new TokeniserReturn();
	TokeniserReturn* ret2;

	//int numtemps;

	// Initialise brain number:
	int tn = 0;
	TheTokens* mytokens; // = &(g->mytokens[tn]);
	for (unsigned int l=0; l<textline.size(); l++)
	{
		tn = evaluateline(textline[l], tn);
	}

	// Now add jump-points for while..wend, if..endif ...
	// Initiate the array for nested jump-points:
	int jumppoint[100];
	int jumppoint2[100];
	int jumplevel, tt; //, lastinsttype, lastinstflag; // removed - not used
	for (unsigned int tn=0; tn<tokens->size(); tn++)
	{
		mytokens = &(*tokens)[tn]; //mytokens = &tokens[tn]; // line removed in Java
		jumplevel = 0;
		//lastinsttype = 0; lastinstflag=0; // removed - not used
		for (unsigned int l=0; l<(mytokens->myparameters.size()); l++)
		{
			ret = &(mytokens->myparameters[l]); // removed for Java

			// Finally, evaluate the instruction itself:
			if ((ret->insttype) == 1) // Standard Instruction
			{
				switch(ret->instflag)
				{
				case 1:
					// Else If
					if (l>0)
					{
						ret->numargs = 3; // added
						ret->args[2] = 0; // added

						// Find the first temp line (if any) before the Else If:
						tt = l;
						while (tt > 0)
						{
							int ins = mytokens->myparameters[tt-1].insttype;
							if (tt>0 && (ins>=2 && ins<=4))
								tt--;
							else
								break;
						}

						// Check if the last instruction BEFORE ANY TEMPS is an endif, i.e. }:
						int test = 0;
						if ((mytokens->myparameters[tt-1].insttype == 1) && (mytokens->myparameters[tt-1].instflag == 7))
						{
							// If so, check the arg[2] of the If on jumplevel (NOT jumplevel-1) to see if it has braces:
							if (mytokens->myparameters[jumppoint[jumplevel]].args[2])
								test = 1;
						}

						if (test != 0)
						{
							// If braces:
							// Remove the "endif" or "}" before the Else If:
							mytokens->myparameters.erase(mytokens->myparameters.begin() + tt - 1);
							// Correct the jump-point for (e.g. If):
							mytokens->myparameters[jumppoint[jumplevel]].args[1] = tt - 1;
							// Correct the current line number (l):
							l--;
							// Increase the jumplevel:
							jumplevel++;
						}
						else
						{
							// If no braces:
							// Set the jump-point for (e.g. If) (arg 2) to the first Temp line (if any) before the Else If:
							mytokens->myparameters[jumppoint[jumplevel-1]].args[1] = tt;
							//mytokens->myparameters[jumppoint[jumplevel-1]].numargs = 2; // removed
						}
						jumppoint[jumplevel - 1] = l;
					}
					break;
				case 2:
					// Else
					//printf("DEBUG: Trying to process ELSE...\n"); // debug
					ret->numargs = 3; // added
					ret->args[2] = 0; // added
					if (l>0)
					{
						// Check if the last instruction is an endif, i.e. }:
						int test = 0;
						if ((mytokens->myparameters[l-1].insttype == 1) && (mytokens->myparameters[l-1].instflag == 7))
						{
							// If so, check the arg[2] of the If on jumplevel (NOT jumplevel-1) to see if it has braces:
							if (mytokens->myparameters[jumppoint[jumplevel]].args[2] != 0)
								test = 1;
						}

						if (test != 0)
						{
							// If braces:
							// Remove the "endif" or "}" before the Else:
							mytokens->myparameters.erase(mytokens->myparameters.begin() + l - 1);
							// Correct the jump-point for (e.g. If):
							mytokens->myparameters[jumppoint[jumplevel]].args[1] = l - 1;
							// Correct the current line number (l):
							l--;
							// Increase the jumplevel:
							jumplevel++;
						}
						else // recently added in Java
						{
							// As for Endif (if no braces):
							// Set the jump-point for (e.g. If) (arg 2) to the Else line:
							mytokens->myparameters[jumppoint[jumplevel-1]].args[1] = l;
							//mytokens->myparameters[jumppoint[jumplevel-1]].numargs = 2; // removed
						}
						jumppoint[jumplevel - 1] = l; // recently added in Java
					}
					break;
				case 4: case 14:
					// Repeat, Do
					jumppoint[jumplevel] = l;
					jumplevel++;
					break;
				case 5:
					// Until
					// Set the jump-point for until:
					ret->args[1] = jumppoint[jumplevel-1] + 1; // +1 optional. // was arg2
					ret->numargs = 2;

					// Drop the jump level:
					jumplevel--;
					break;
				case 6:
					// If
					//printf("DEBUG: Trying to process IF...\n"); // debug
					ret->numargs = 4; // added
					ret->args[2] = 0; // added
					ret->args[3] = 0; // added
					jumppoint[jumplevel] = l;
					jumppoint2[jumplevel] = l;
					jumplevel++;
					break;
				case 7: case 18:
					// End If, Endif
					// Set the jump-point for if (arg 2) to the endif:
					//Note: Was the line after the endif, l+1
					//printf("DEBUG: Trying to process ENDIF...\n"); // debug
					mytokens->myparameters[jumppoint[jumplevel-1]].args[1] = l; // was l+1 // was arg2
					mytokens->myparameters[jumppoint2[jumplevel-1]].args[3] = l; // was l+1 // was arg2
					//mytokens->myparameters[jumppoint[jumplevel-1]]->numargs = 2; // removed

					// Drop the jump level:
					jumplevel--;
					break;
				case 8:
					// While
					//printf("DEBUG: Trying to process WHILE...\n"); // debug
					jumppoint[jumplevel] = l;
					jumplevel++;
					break;
				case 9: case 15: case 16: case 17:
					// Wend, Loop, Endwhile, Forever
					//printf("DEBUG: Trying to process WEND...\n"); // debug
					// Set the jump-point for while (arg 2) to the line after the wend:
					mytokens->myparameters[jumppoint[jumplevel-1]].args[1] = l+1; // was arg2
					mytokens->myparameters[jumppoint[jumplevel-1]].numargs = 2;

					// Calculate the jumppoint for the wend - after line which is not insttype 2,3 or 4 (set temp):
					tt = jumppoint[jumplevel-1];
					while (tt > 0)
					{
						int ins = mytokens->myparameters[tt-1].insttype;
						if (tt>0 && (ins>=2 && ins<=4))
							tt--;
						else
							break;
					}

					// Set the jump-point for wend:
					ret->args[0] = tt; // was arg
					ret->numargs = 1;

					// Drop the jump level:
					jumplevel--;
					break;
				case 10:
					// {
					//printf("DEBUG: Trying to process {...\n"); // debug
					// (Possibly to do: For local variables within scope, set a property of the preceding instruction...)

					// If preceding line is If, set arg[2] to 1 (if with braces) - needed for Else and Else If.
					// Extended to Else and Else If also (1 and 2 as well as 6)
					if (l>0)
					{
						ret2 = &mytokens->myparameters[l-1];
						if ((ret2->insttype == 1) && ((ret2->instflag == 6) || (ret2->instflag == 1) || (ret2->instflag == 2)))
							ret2->args[2] = 1;
					}

					// Remove this line, and shift down instructions:
					for (unsigned int ll=l; ll<(mytokens->myparameters.size() - 1); ll++)
						mytokens->myparameters[ll] = mytokens->myparameters[ll + 1];
					// Remove last instance from vector:
					mytokens->myparameters.erase(mytokens->myparameters.begin()+mytokens->myparameters.size()-1,
							mytokens->myparameters.begin()+mytokens->myparameters.size());
					l--;
					break;
				case 11:
					// }
					//printf("DEBUG: Trying to process }...\n"); // debug
					if (jumplevel == 0) // Error!
					{
						printf("Error with '}'!");

						break;
					}
					jumplevel--;
					ret2 = &mytokens->myparameters[jumppoint[jumplevel]];
					if (ret2->insttype == 1)
						switch (ret2->instflag)
						{
						case 4:
							// Repeat
							// Next line (after temps) should be Until - test for error?

							// Remove this line, and shift down instructions:
							for (unsigned int ll=l; ll<(mytokens->myparameters.size() - 1); ll++)
								mytokens->myparameters[ll] = mytokens->myparameters[ll + 1];
							// Remove last instance from vector:
							mytokens->myparameters.erase(mytokens->myparameters.begin()+mytokens->myparameters.size()-1,
									mytokens->myparameters.begin()+mytokens->myparameters.size());
							l--;
							break;
						case 6: case 1: case 2:
							// After If or Else If or Else
							// Set to Endif
							ret->instflag = 7;
							jumplevel++;
							l--;
							break;
						case 8:
							// After While
							// Set to Wend
							ret->instflag = 9;
							jumplevel++;
							l--;
							break;
						}
					break;

					// Added - for Procedures:
						case 21: case 22:
							// TODO:
							// Do string matching of procedure call with defined procedures:
							TokeniserReturn* ret = &(mytokens->myparameters[l]);
							string procname = mytokens->myprocedurecalls[(int)ret->args[0]];

							// Compare the called procedure string with the list of procedure strings:
							int numprocedures = mytokens->myprocedures.size();
							int procedurenumber;
							for (procedurenumber = 0; procedurenumber<numprocedures; procedurenumber++)
								if (procname == mytokens->myprocedures[procedurenumber])
									break;

							// Now set the procedure call reference to the procedure number, or give an error if not found:
							if (procedurenumber >= numprocedures)
							{
								printf("ERROR: Procedure not found: %s\n", procname.c_str());
							}
							else
							{
								//printf("DEBUG: Procedure found: %s, call number=%d, actual number=%d\n", procname.c_str(), (int)ret->args[0], (int)procedurenumber);
								mytokens->myparameters[l].args[0] = procedurenumber; //ret->args[0] = procedurenumber;
								//mytokens->myparameters[l] = ret; // removed
							}

							break;
				}
			}
			else if ((ret->insttype) == 2) // Operator
			{
				if (ret->instflag == 0) // Dot
				{
					// First, get the class/brain name from the variable name in arg[1]:
					strcpy(temptext, lower(mytokens->myvarnames[(int)ret->args[1]], temptext2));
					unsigned int br = 0;
					// Find the appropriate class/brain (returned in br):
					for (br=0; br<tokens->size(); br++)
					{
						if (strcmp(temptext, lower((char*)(*tokens)[br].name.c_str(), temptext2)) == 0)
							break;
					}
					if (br<tokens->size())
					{
						// Get the referred variable name string from arg[2]:
						// To do - also do functions...
						strcpy(temptext, lower(mytokens->mystrings[(int)ret->args[2]], temptext2));
						unsigned int v;
						// Find the appropriate variable in the pointed brain:
						for (v=0; v<(*tokens)[br].myvarnames.size(); v++)
						{
							if (strcmp(temptext, lower((*tokens)[br].myvarnames[v], temptext2)) == 0)
								break;
						}

						if (v < (*tokens)[br].myvarnames.size())
						{
							ret->args[2] = v;
							ret->argtypes[2] = 0;
						}
						else
						{
							printf("Error - referred variable (%s) not found (q)! Brain = \"%s\"\n",
									(char*)temptext, (char*)(mytokens->name.c_str()));
							for (unsigned int v=0; v<(*tokens)[br].myvarnames.size(); v++)
								printf("  %d: \"%s\"\n", v, (*tokens)[br].myvarnames[v].c_str());

						}
					}
					else
					{
						cout << "Error - class/brain not found (q)! Brain = \"" << mytokens->myvarnames[(int)ret->args[1]] << "\" " << mytokens->myvarnames[ret->instflag].size() << endl;
						// Debug:
						for (unsigned int br=0; br<tokens->size(); br++)
							cout << "   Brain #" << br << " = \"" << (*tokens)[br].name << "\", length=" << (*tokens)[br].name.size() << endl;
					}
				}
			}
			else if (((ret->insttype) >= 15) && ((ret->insttype) <= 21))
			{
				// First, get the class/brain name from the variable name in ret->instflag:
				strcpy(temptext, lower(mytokens->myvarnames[ret->instflag], temptext2));
				unsigned int br = 0;
				// Find the appropriate class/brain (returned in n):
				for (br=0; br<tokens->size(); br++)
				{
					if (strcmp(temptext, lower((char*)(*tokens)[br].name.c_str(), temptext2)) == 0)
					{
						break;
					}
				}
				if (br<tokens->size())
				{
					// Get the referred variable name string from arg[0]:
					// To do - also do functions...
					strcpy(temptext, lower(mytokens->mystrings[(int)ret->args[0]], temptext2));
					unsigned int v;
					// Find the appropriate variable in the pointed brain:
					for (v=0; v<(*tokens)[br].myvarnames.size(); v++)
					{
						//printf("Comparing the string -%s- with -%s-...\n", temptext, lower((*tokens)[br].myvarnames[v], temptext2)); // debug
						if (strcmp(temptext, lower((*tokens)[br].myvarnames[v], temptext2)) == 0)
							break;
					}

					if (v < (*tokens)[br].myvarnames.size())
					{
						ret->args[0] = v;
						ret->argtypes[0] = 0;
					}
					else
					{
						printf("Error - referred variable (%s) not found (AT END)! Brain = \"%s\"\n",
								(char*)temptext, (char*)((*tokens)[br].name.c_str()));
						for (unsigned int v=0; v<(*tokens)[br].myvarnames.size(); v++)
							printf("  %d: \"%s\"\n", v, (*tokens)[br].myvarnames[v].c_str());
					}
				}
				else
				{
					cout << "Error - class/brain not found (AT END)! Brain = \"" << mytokens->myvarnames[ret->instflag] << "\" (" << mytokens->myvarnames[ret->instflag].size() << ")" << endl;

					// Debug:
					for (unsigned int br=0; br<tokens->size(); br++)
						  cout << "   Brain[" << br << "] = \"" << (*tokens)[br].name << "\" (" << (*tokens)[br].name.size() << ")" << endl;
				}
			}
			//else printf("Unknown instruction!"); // debug
		}
	}

	// Here in the Java version, temptext[] is freed automatically by Java's garbage collector.
	delete[] temptext;
	delete[] temptext2;

	return 0;
}



// New - TODO:
// Added to split a string:
int Parser::lexString(string str)
{
	// First destroy the current tokens:
	g->mytokens.clear();
	for (unsigned int n=0; n<g->ActiveObjects.size(); n++)
		delete g->ActiveObjects[n];

	g->ActiveObjects.clear();

	// Added for jAMOS - initialise the MequaScript Parser:
	inittokens(&(g->mytokens), 0, string("Master"));

	// Load the instruction and function names:
	initinstructions();

	// Split the input string:
	// Java version:
	// ArrayList<String> splitstring = new ArrayList<String>(Arrays.asList(str.split("\r?\n|\r")));

	vector<string> splitstring;

	char* split;
	string split2;
	split = strtok((char*)str.c_str(), "\n");
	while (split != NULL)
	{
		// For DOS/Windows format "\r\n" endline, remove the trailing \r:
		int len = strlen(split);
		if (split[len - 1] == '\r')
			split[len - 1] = (char)0;

		split2 = string(split);
		splitstring.push_back(split2);
		split = strtok(NULL, "\n");
	}

	// Evaluate the instructions:
	evaluateinstructions(splitstring);

	// Do this after tokenisation:
	// For each brain, initialise an object (in myvalues[n]), and set its brain number to the object number (make more OO later):
	for (unsigned int n=0; n<g->mytokens.size(); n++)
	{
		ActiveObject* temp = new ActiveObject();
		temp->ObjectBrain = n;
		g->ActiveObjects.push_back(temp);
	}

	// Now initialise the variables of each object:
	for (unsigned int n=0; n<g->mytokens.size(); n++)
		initvalues(&(g->mytokens), (int)n);

	return 0;
}

// TODO - duplicate from Interpreter:
int Parser::initvalues(vector <TheTokens>* multitokens, int nn)
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

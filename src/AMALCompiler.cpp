///////////////////////////////////////////////////////////
// AMOS AMAL -> Java/C++ Compiler                        //
// By Stephen Harvey-Brooks - Mequa Innovations          //
///////////////////////////////////////////////////////////

#include "AMALCompiler.h"

AMALCompiler::AMALCompiler(AMOS_System* AMi)
{
	AM = AMi;
	//out = AM->out; // From Java
	out = new PrintStream(); // Added to C++
}

// Added - for C++

// To access arrays/vectors:
void AMALCompiler::setARG(int a, int b, int c)
{
	AM->ARG[a][b] = c;
}
void AMALCompiler::setarg(int a, int b, string c)
{
	AM->arg[a][b] = c;
}
int AMALCompiler::getARGTYPE(int a, int b, int c)
{
	return AM->ARGTYPE[a][b][c];
}
int AMALCompiler::getPROGPOINTER(int a)
{
	return AM->PROGPOINTER[a];
}

void AMALCompiler::FETCHARGUMENTS_C(bool cpp, int P1)
{
		for ( int PARNUM=1; PARNUM <= P1; PARNUM++ )
		{
			switch ( getARGTYPE(AM->CHAN, getPROGPOINTER(AM->CHAN), PARNUM) )
			{
			case 0:
				// for constant values:
				setARG(AM->CHAN, PARNUM, AM->COMMAND[AM->CHAN][getPROGPOINTER(AM->CHAN)][PARNUM]);
				setarg(AM->CHAN, PARNUM, "");
				break;
			case 1:
				// for Global/External variables (RA-RZ, #0-25):
				if (cpp)
					setarg(AM->CHAN, PARNUM, "AM->myGLOBAL["+AM->stri(AM->COMMAND[AM->CHAN][getPROGPOINTER(AM->CHAN)][PARNUM])+"]");
				else
					setarg(AM->CHAN, PARNUM, "AM.myGLOBAL["+AM->stri(AM->COMMAND[AM->CHAN][getPROGPOINTER(AM->CHAN)][PARNUM])+"]");
				setARG(AM->CHAN, PARNUM, -1);
				break;
			case 2:
				// for Local/Internal variables (R0-R9):
				if (cpp)
					setarg(AM->CHAN, PARNUM, "AM->LOCAL[CHAN]["+(AM->stri(AM->COMMAND[AM->CHAN][getPROGPOINTER(AM->CHAN)][PARNUM]))+"]");
				else
					setarg(AM->CHAN, PARNUM, "AM.LOCAL[CHAN]["+(AM->stri(AM->COMMAND[AM->CHAN][getPROGPOINTER(AM->CHAN)][PARNUM]))+"]");
				setARG(AM->CHAN, PARNUM, -1);
				break;
			case 3:
				// for Special registers (X,Y,A)
				if (cpp)
					setarg(AM->CHAN, PARNUM, "AM->SPECIAL[CHAN]["+(AM->stri(AM->COMMAND[AM->CHAN][getPROGPOINTER(AM->CHAN)][PARNUM]))+"]");
				else
					setarg(AM->CHAN, PARNUM, "AM.SPECIAL[CHAN]["+(AM->stri(AM->COMMAND[AM->CHAN][getPROGPOINTER(AM->CHAN)][PARNUM]))+"]");
				setARG(AM->CHAN, PARNUM, -1);
				break;
			case 4:
				// for Temporary values:
				setarg(AM->CHAN, PARNUM, AM->temp[AM->CHAN][AM->COMMAND[AM->CHAN][getPROGPOINTER(AM->CHAN)][PARNUM]]);
				setARG(AM->CHAN, PARNUM, -1);
			}
		}
}

void AMALCompiler::FETCHARGUMENTS_C2(int P1)
{
		for ( int PARNUM=1; PARNUM <= P1; PARNUM++ )
		{
			switch ( getARGTYPE(AM->CHAN, getPROGPOINTER(AM->CHAN), PARNUM) )
			{
			case 0:
				// For constant values:
				setARG(AM->CHAN, PARNUM, AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][PARNUM]);
				setarg(AM->CHAN, PARNUM, "");
				break;
			case 1:
				// For Global/External variables (RA-RZ, #0-25):
				setARG(AM->CHAN, PARNUM, AM->myGLOBAL[AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][PARNUM]]);
				setarg(AM->CHAN, PARNUM, "");
				break;
			case 2:
				// For Local/Internal variables (R0-R9):
				setARG(AM->CHAN, PARNUM, AM->LOCAL[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][PARNUM]]);
				setarg(AM->CHAN, PARNUM, "");
				break;
			case 3:
				// For Special registers (X,Y,A)
				setARG(AM->CHAN, PARNUM, AM->SPECIAL[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][PARNUM]]);
				setarg(AM->CHAN, PARNUM, "");
				break;
			case 4:
				// For Temporary values:
				setarg(AM->CHAN, PARNUM, AM->temp[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][PARNUM]]);
				setARG(AM->CHAN, PARNUM, -1);
			}
		}
}

void AMALCompiler::DEBUG()
{
		out->println(string("(")+AM->stri(AM->PROGPOINTER[AM->CHAN])+")  "+AM->commandlist[AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][0]]);
		if ( (AM->NUMARGS[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])]) > 0 )
		{
			for ( int TT=1; TT <= AM->NUMARGS[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])]; TT++ )
			{
				out->print( string(AM->argtypename[AM->ARGTYPE[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][TT]]) + AM->stri(AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][TT]) );
				if ( TT<AM->NUMARGS[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])] )
					out->print(", ");
			}
		}
		out->println("");
		if ( AM->NUMSTRINGS[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])]>0 )
		{
			out->println("strings:");
			for ( int TT=0; TT <= AM->NUMSTRINGS[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])]-1; TT++ )
			{
				out->print(AM->strin[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][TT]);
				if ( TT < AM->NUMARGS[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])] )
					out->print(", ");
			}
		}
		out->println("");
		//A_WaitKey();
}

string AMALCompiler::getarg(int a, int b)
{
	// Removed in C++:
	//if ((AM->arg[a][b]) == NULL)
	//	return "" + AM->stri(AM->ARG[a][b]);

	if ((AM->arg[a][b]).length() > 0) // && ((AM->ARG[a][b]) == -1)
		return "" + AM->arg[a][b];
	else
		return "" + AM->stri(AM->ARG[a][b]);
}

void AMALCompiler::AmalCompileCPPHeader(int ch1, int ch2)
{
	// Turn on Synchro to avoid any problems.
	bool synchrostatus = AM->AmalSynchro;
	AM->AmalSynchro = true;

	string id1="	";

	// Define our new C++ class header file with includes and header guards:
	out->println("// Translated AMAL scripts:");
	out->println("");
	out->println("#ifndef AMAL_PROGRAMS_H");
	out->println("#define AMAL_PROGRAMS_H");
	out->println("");
	out->println("#include \"AMOS_System.h\"");
	out->println("");
	out->println("#include <string>");
	out->println("using namespace std;");
	out->println("");
	out->println("class AmalPrograms");
	out->println("{");

	out->println(id1+"// Here are your converted AMAL programs:");

	// Define our individual AMAL program methods here:
	for ( AM->CHAN = ch1; AM->CHAN <= ch2; AM->CHAN++ )
		if (AM->EXISTS[AM->CHAN])
			out->println(id1+"void amal"+AM->stri(AM->CHAN)+"(int CHAN);");

	// Define our public fields and methods here:
	out->println("public:");
	out->println(id1+"// This part initialises the class:");
	out->println(id1+"AMOS_System* AM;");
	out->println(id1+"bool forrepeat;");
	out->println(id1+"AmalPrograms(AMOS_System* AMi);");
	out->println("");
	out->println(id1+"int runAmal(int program, int channel);");
	out->println(id1+"int numPrograms();");
	out->println("");
	out->println(id1+"// Environment Generator:");
	out->println(id1+"void environment();");

	// End the class header definition here:
	out->println("};");
	out->println("");
	out->println("#endif");
	out->println("");

	//Fileout.Close;
	//TEMP = 0;

	// Re-instate the previous status of Synchro.
	AM->AmalSynchro = synchrostatus;
}

// TODO - void AmalCompile(PrintStream out, int ch1, int ch2)
// In Jamagic - was: AmalCompile(File Fout, int ch1, int ch2)
void AMALCompiler::AmalCompile(int ch1, int ch2, bool cpp)
{
		// Turn on Synchro to avoid any problems.
		bool synchrostatus = AM->AmalSynchro;
		AM->AmalSynchro = true;

		string id1="	";
		string id=id1+id1+id1;

		//Logtruestr="LOGICTRUE*";
		//Logtruestr="(-1)*";

		string Logtruestr="";
		//if((IsDefaultValue(ch1))) {
		//	ch1=0; // Was 1
		//	ch2=TOPCHANNEL;
		//} else {
		//	if ((IsDefaultValue(ch2))) {
		//		ch2=ch1;
		//	}
		//}

		//int start = 1;

		string amr;
		if (cpp)
			amr = "AM->";
		else
			amr = "AM.";

		if (cpp)
		{
			// Define the creation method for our new C++ class:
			out->println("// Translated AMAL scripts:");
			out->println("");
			out->println("#include \"AmalPrograms.h\"");
			out->println("");
			out->println("// This part initialises the class:");
			out->println("AmalPrograms::AmalPrograms(AMOS_System* AMi)");
			out->println("{");
			out->println(id1+"AM = AMi;");
			out->println(id1+"forrepeat = false;");
			out->println("}");
			out->println("");
		}
		else
		{
			// Define the creation method for our new Java class:
			out->println("// Translated AMAL scripts:");
			out->println("package jamal;");
			//out->println("import java.io.*;");
			out->println("public class AmalPrograms");
			out->println("{");
			out->println(id1+"// This part initialises the class:");
			out->println(id1+"AMOS_System AM;");
			//out->println(id1+"int tempX; int tempY; boolean forrepeat=false;");
			out->println(id1+"boolean forrepeat=false;");
			out->println(id1+"public AmalPrograms(AMOS_System AMi) {");
			out->println(id1+id1+"AM = AMi;");
			out->println(id1+"}");
		}

		if (cpp)
		{
			// Define the "run any" method for our C++ class:
			out->println("int AmalPrograms::runAmal(int program, int channel)");
			out->println("{");
			
			if (ch2 > 0)
			{
				out->println(id1+"switch (program)");
				out->println(id1+"{");
				// Add the reference points to each Amal program here:
				for ( AM->CHAN = ch1; AM->CHAN <= ch2; AM->CHAN++ )
					out->println(id1+"case "+AM->stri(AM->CHAN)+": amal"+AM->stri(AM->CHAN)+"(channel); return 0;");
				out->println(id1+"default: return -1;");
				out->println(id1+"}");
				out->println("}");
			}
			else
			{
				out->println(id1+"return -1;");
				out->println("}");
			}
		}
		else
		{
			// Define the "run any" method for our Java class:
			out->println(id1+"public int runAmal(int program, int channel) {");
			
			if (ch2 > 0)
			{
				out->println(id1+id1+"switch (program)");
				out->println(id1+id1+"{");
				// Add the reference points to each Amal program here:
				for ( AM->CHAN = ch1; AM->CHAN <= ch2; AM->CHAN++ )
					out->println(id1+id1+"case "+AM->stri(AM->CHAN)+": amal"+AM->stri(AM->CHAN)+"(channel); return 0;");
				out->println(id1+id1+"default: return -1;");
				out->println(id1+id1+"}");
				out->println(id1+"}");
			}
			else
			{
				out->println(id1+id1+"return -1;");
				out->println(id1+"}");
			}
		}

		// Finally define our "size of" method:
		if (cpp)
			out->println("int AMALPrograms::numPrograms() { return "+AM->stri(1+ch2-ch1)+"; }");
		else
			out->println(id1+"public int numPrograms() { return "+AM->stri(1+ch2-ch1)+"; }");



		// Translate, split and add the environment string:
		out->println("");
		string strout;
		if (cpp)
		{
			out->println("// Environment Generator:");
			strout = AM->envGen->outputCPP();
		}
		else
		{
			out->println(id1+"// Environment Generator:");
			strout = AM->envGen->outputJava();
		}

		//string[] stroutsplit = strout->split("\n");
		vector<string> stroutsplit;

		// Added (C++) - string split routine:
		char* split;
		string split2;
		split = strtok((char*)strout.c_str(), "\n");
		while (split != NULL)
		{
			// For DOS/Windows format "\r\n" endline, remove the trailing \r:
			int len = strlen(split);
			if (split[len - 1] == '\r')
				split[len - 1] = (char)0;

			split2 = string(split);
			stroutsplit.push_back(split2);
			split = strtok(NULL, "\n");
		}

		for (unsigned int a=0; a<stroutsplit.size(); a++)
			out->println(stroutsplit[a]);
		out->println("");


		if (ch2 > 0)
		{
			if (cpp)
			{
				out->println("// And here are your converted AMAL programs:");
				id=id1+id1;
			}
			else
			{
				out->println(id1+"// And here are your converted AMAL programs:");
			}
		}

		//cout << "Debug: ch1 == " << AM->stri(ch1) << ", ch2 == " << AM->stri(ch2) << endl;

		for ( AM->CHAN = ch1; AM->CHAN <= ch2; AM->CHAN++ ) if (AM->EXISTS[AM->CHAN])
		{
			//cout << "Debug: AM->CHAN == " << AM->CHAN << endl;
			if (AM->CHAN > ch1)
				out->println("");

			if (cpp)
			{
				out->println("void AmalPrograms::amal"+AM->stri(AM->CHAN)+"(int CHAN)");
				out->println("{");
			}
			else
			{
				out->println(id1+"void amal"+AM->stri(AM->CHAN)+"(int CHAN)");
				out->println(id1+"{");
			}
			
			if (AM->NUMLINES[AM->CHAN] > 0)
			{
				if (cpp)
				{
					out->println(id1+"while(AM->PROGNOTFINISHED[CHAN] && !AM->PAUSED) switch(AM->PROGPOINTER[CHAN])");
					out->println(id1+"{");
					out->println(id1+"case 0:");
				}
				else
				{
					out->println(id1+id1+"while(AM.PROGNOTFINISHED[CHAN] && !AM.PAUSED) switch(AM.PROGPOINTER[CHAN])");
					out->println(id1+id1+"{");
					out->println(id1+id1+"case 0:");
				}
			}

			AM->caseon=1;
			AM->JUMPED = 0;

			//System.out->println("Channel: "+AM->CHAN+", Numlines: "+AM->NUMLINES[AM->CHAN]);

			for ( AM->PROGPOINTER[AM->CHAN]=0; AM->PROGPOINTER[AM->CHAN]<AM->NUMLINES[AM->CHAN]; AM->PROGPOINTER[AM->CHAN]++ )
			{
				AM->JUMPED = 0;

				if ( AM->caseon==1 )
				{
					if (cpp)
					{
						if (AM->PROGPOINTER[AM->CHAN]>0)
						{
							out->println(id1+"case "+AM->stri(AM->PROGPOINTER[AM->CHAN])+":");
						}
					}
					else
					{
						if (AM->PROGPOINTER[AM->CHAN]>0)
						{
							out->println(id1+id1+"case "+AM->stri(AM->PROGPOINTER[AM->CHAN])+":");
						}
					}
				}
				else	
				{
					AM->caseon=1;
				}

				switch ( AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][0] )
				{
				case 0:
					// Pause
					//out->println(id+"// Pause");
					out->println(id+amr+"amalPause(CHAN, "+AM->stri(AM->PROGPOINTER[AM->CHAN]+1)+");");
					//out->println(id+"AM->PROGPOINTER[CHAN] = "+(AM->PROGPOINTER[AM->CHAN]+1)+";");
					//out->println(id+"AM->PAUSED = true;");
					AM->JUMPED = 1;
					break;
				case 1:
					// For

					// c=0 -> global(d)=b
					// c=1 -> local(d)=b
					FETCHARGUMENTS_C2(2);
					switch ( AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][3] )
					{
					case 0:
						// For RA-RZ (global):
						FETCHARGUMENTS_C(cpp, 2);
						out->println(id+"// For RA-RZ (global)");
						out->println(id+"if ( forrepeat ) {");
						out->println(id+id1+"forrepeat = false;");

						out->println(id+id1+"if ( "+amr+"amalGetGlobal("+AM->stri(AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][4])+") < "+getarg(AM->CHAN,1)+" ) {");
						// As for Pause:
						//out->println(id+id1+id1+"AM->PAUSED = true;");
						// Add 1 to the index:
						out->println(id+id1+id1+amr+"amalIncGlobal("+AM->stri(AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][4])+");");
						// Jump straight after the 'for' and pause:
						out->println(id+id1+id1+amr+"amalPause(CHAN, "+AM->stri(AM->PROGPOINTER[AM->CHAN]+1)+");");
						out->println(id+id1+"} else");
						// Index has reached target, so continue after the 'Next':
						out->println(id+id1+id1+amr+"amalJump(CHAN, "+AM->stri(AM->INSTRLINENUM[AM->CHAN][(AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][5])-1]+2)+");");
						out->println(id+id1+"break;");
						out->println(id+"} else");

						out->println(id+id1+amr+"amalSetGlobal("+AM->stri(AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][4])+", "+(getarg(AM->CHAN,2))+");");
						break;
					case 1:
						// For R0-R9 (local):
						FETCHARGUMENTS_C(cpp, 2);
						out->println(id+"// For R0-R9 (local)");
						out->println(id+"if (forrepeat) {");
						out->println(id+id1+"forrepeat = false;");

						out->println(id+id1+"if ( "+amr+"amalGetLocal(CHAN, "+AM->stri(AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][4])+") < "+getarg(AM->CHAN,1)+" ) {");
						// As for Pause:
						//out->println(id+id1+id1+"AM->PAUSED = true;");
						// Add 1 to the index:
						out->println(id+id1+id1+amr+"amalIncLocal(CHAN, "+AM->stri(AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][4])+");");
						// Jump straight after the 'for' and pause:
						out->println(id+id1+id1+amr+"amalPause(CHAN, "+AM->stri(AM->PROGPOINTER[AM->CHAN]+1)+");");
						out->println(id+id1+"} else");
						// Index has reached target, so continue after the 'Next':
						out->println(id+id1+id1+amr+"amalJump(CHAN, "+AM->stri(AM->INSTRLINENUM[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][5]-1]+2)+");");
						out->println(id+id1+"break;");
						out->println(id+"} else");
						out->println(id+id1+amr+"amalSetLocal(CHAN, "+AM->stri(AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][4])+", "+getarg(AM->CHAN,2)+");");
						break;
					default:
					break;
					}
					break;
				case 2:
					// Next
					out->println(id+"// Next");
					out->println(id+"forrepeat = true;"); // Fix this later
					// Jump to LINE number of matching 'for':
					out->println(id+amr+"amalJump(CHAN, "+AM->stri(AM->INSTRLINENUM[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][3]])+");");
					//out->println(id+"AM->PROGPOINTER[CHAN] = "+AM->stri(AM->INSTRLINENUM[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][3]])+";");
					AM->JUMPED = 1;
					break;
				case 3:
					// Let
					// b=0 -> global(c)=a
					// b=1 -> local(c)=a
					// b=2 -> special(c)=a

					//out->println(id+"// Let");
					FETCHARGUMENTS_C(cpp, 1);
					switch ( AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][2] )
					{
					case 0:
						//out->println(id+"AM->myGLOBAL["+AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][3]+"] = "+getarg(AM->CHAN,1)+";");
						out->println(id+amr+"amalSetGlobal("+AM->stri(AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][3])+", "+getarg(AM->CHAN,1)+");");
						break;
					case 1:
						//out->println(id+"AM->LOCAL[CHAN]["+AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][3]+"] = "+getarg(AM->CHAN,1)+";");
						out->println(id+amr+"amalSetLocal(CHAN, "+AM->stri(AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][3])+", "+getarg(AM->CHAN,1)+");");
						break;
					case 2:
						//out->println(id+"AM->SPECIAL[CHAN]["+AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][3]+"] = "+getarg(AM->CHAN,1)+";");
						//out->println(id+"AM->amalSetSpecial(CHAN, "+AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][3]+", "+getarg(AM->CHAN,1)+");");

						// Added: Switch the special register here to get X, Y or A:
						switch (AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][3])
						{
						case 0:
							out->println(id+amr+"amalSetX(CHAN, "+getarg(AM->CHAN,1)+");");
							break;
						case 1:
							out->println(id+amr+"amalSetY(CHAN, "+getarg(AM->CHAN,1)+");");
							break;
						case 2:
							out->println(id+amr+"amalSetA(CHAN, "+getarg(AM->CHAN,1)+");");
							break;
						default:
							// Is this needed? Included for completeness:
							out->println(id+amr+"amalSetSpecial(CHAN, "+AM->stri(AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][3])+", "+getarg(AM->CHAN,1)+");");
							break;
						}
					}
					break;
				case 4:
					// Jump (Goto)
					out->println(id+"// Jump (Goto) Label "+AM->stri(AM->LABELS[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][1]]));
					if ( AM->LABELS[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][1]]==0 )
						out->println(id+amr+"amalJump(CHAN, 0);");
					//out->println(id+"AM->PROGPOINTER[CHAN] = 0;");
					else
						out->println(id+amr+"amalJump(CHAN, "+AM->stri(AM->INSTRLINENUM[AM->CHAN][AM->LABELS[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][1]]-1]+1)+");");
					//out->println(id+"AM->PROGPOINTER[CHAN] = "+(AM->INSTRLINENUM[AM->CHAN][AM->LABELS[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][1]]-1]+1)+";");

					AM->JUMPED = 1; // This will add "break;" after as appropriate.
					break;
				case 5:
					// If ...
					//out->println(id+"// If ...");
					FETCHARGUMENTS_C(cpp, 1);
					//out->println(id+"// If test is true, run next line (Jump L/Direct L/eXit) else skip:");
					out->println(id+"// If test is true, then run the next instruction, else skip the next instruction:");
					out->println(id+"if ( "+amr+"isfalse("+(getarg(AM->CHAN,1))+") ) {");
					//out->println(id+"{");
					out->println(id+id1+amr+"amalJump(CHAN, "+AM->stri(AM->PROGPOINTER[AM->CHAN]+2)+");");
					out->println(id+id1+"break;");
					out->println(id+"}");

					break;
				case 6:
					// Move (initialise)
					//out->println(id+"// Move (initialise):");
					FETCHARGUMENTS_C(cpp, 3);
					out->println(id+amr+"amalMoveInit(CHAN, "+(getarg(AM->CHAN,1))+", "+(getarg(AM->CHAN,2))+", "+(getarg(AM->CHAN,3))+");");

					//out->println(id+"AM->SPECIAL[CHAN][3] = "+getarg(AM->CHAN,1)+";");
					//out->println(id+"AM->SPECIAL[CHAN][4] = "+getarg(AM->CHAN,2)+";");
					//out->println(id+"AM->SPECIAL[CHAN][5] = "+getarg(AM->CHAN,3)+";");
					//out->println(id+"if (AM->SPECIAL[CHAN][5]==0)	AM->SPECIAL[CHAN][5]=1;");// Fix this... ");
					////out->println(id+"// Counter: ");
					//out->println(id+"AM->SPECIAL[CHAN][6] = 1;");

					// Removed a while ago.
					//out->println(id+"// Record positions for X and Y...");
					//out->println(id+"AM->SPECIAL[CHAN][7] = AM->SPECIAL[CHAN][0];");
					//out->println(id+"AM->SPECIAL[CHAN][8] = AM->SPECIAL[CHAN][1];");
					break;
				case 7:
					// Move (run)
					//out->println(id+"// Move (run)");
					out->println(id+amr+"amalMoveRun(CHAN, "+AM->stri(AM->PROGPOINTER[AM->CHAN])+", "+(AM->stri(AM->PROGPOINTER[AM->CHAN] + 1))+");");

					// Interpolate the position:
					//out->println(id+"tempX = (((AM->SPECIAL[CHAN][6] - 1) * AM->SPECIAL[CHAN][3]) / AM->SPECIAL[CHAN][5]);");
					//out->println(id+"tempY = (((AM->SPECIAL[CHAN][6] - 1) * AM->SPECIAL[CHAN][4]) / AM->SPECIAL[CHAN][5]);");
					//out->println(id+"AM->SPECIAL[CHAN][0] += ((AM->SPECIAL[CHAN][6] * AM->SPECIAL[CHAN][3]) / AM->SPECIAL[CHAN][5]) - tempX;");
					//out->println(id+"AM->SPECIAL[CHAN][1] += ((AM->SPECIAL[CHAN][6] * AM->SPECIAL[CHAN][4]) / AM->SPECIAL[CHAN][5]) - tempY;");

					// As for Pause:
					//out->println(id+"AM->PAUSED = true;");

					//out->println(id+"if (AM->SPECIAL[CHAN][6]<AM->SPECIAL[CHAN][5])");
					//out->println(id+"{");
					//out->println(id+id1+"AM->SPECIAL[CHAN][6]++; // Increase the Counter... ");
					// Don't move to next instruction yet...
					//out->println(id+id1+"AM->PROGPOINTER[CHAN]="+AM->PROGPOINTER[AM->CHAN]+";");
					//out->println(id+"} else {");
					//out->println(id+id1+"AM->PROGPOINTER[CHAN]="+(AM->PROGPOINTER[AM->CHAN]+1)+"; // End of Move...");
					//out->println(id+"}");

					AM->JUMPED = 1;
					break;
				case 8:
					// Direct
					//out->println(id+"// Direct (Jump out of Autotest)");
					// As for Jump...
					//out->println(id+"AM->RUNNINGAUTOTEST[CHAN] = false; // Leave Autotest...");
					if ( AM->LABELS[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][1]]==0 )
						out->println(id+amr+"amalDirect(CHAN, 0);");
					//out->println(id+"AM->PROGPOINTER[CHAN] = 0;");
					else
						out->println(id+amr+"amalDirect(CHAN, "+AM->stri(AM->INSTRLINENUM[AM->CHAN][AM->LABELS[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][1]]-1]+1)+");");
					//out->println(id+"AM->PROGPOINTER[CHAN] = "+(AM->INSTRLINENUM[AM->CHAN][AM->LABELS[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][1]]-1]+1)+";");
					AM->JUMPED = 1;
					break;
				case 9:
					// End
					//out->println(id+"// End program");
					out->println(id+amr+"amalEnd(CHAN);");
					//// Skip to end of program:
					//out->println(id+"AM->PROGNOTFINISHED[CHAN] = false;");
					AM->JUMPED = 1;
					break;
				case 10:
					// eXit
					//out->println(id+"// eXit");
					out->println(id+amr+"amalExitAutotest(CHAN);"); // left for now
					//// Re-enter the main program again, at the original departure point:
					//out->println(id+"AM->RUNNINGAUTOTEST[CHAN] = false; // Leave Autotest...");
					//out->println(id+"if (AM->MAINPROGDEPPOINT[CHAN] >= 0)");
					//out->println(id+id1+"AM->PROGPOINTER[CHAN] = AM->MAINPROGDEPPOINT[CHAN];");
					//out->println(id+"else");
					//// Jump to end of Autotest:
					//out->println(id+id1+"AM->PROGPOINTER[CHAN] = AM->AUTOTESTEND[CHAN];");

					AM->JUMPED = 1;
					break;
				case 11:
					// On
					//out->println(id+"// On");
					out->println(id+amr+"amalOn(CHAN);");
					//// Re-enter the main program again, after the original departure point:
					//out->println(id+"AM->RUNNINGAUTOTEST[CHAN] = false; // Leave Autotest...");
					//out->println(id+"if (AM->MAINPROGDEPPOINT[CHAN] >= 0)");
					//out->println(id+id1+"AM->PROGPOINTER[CHAN] = AM->MAINPROGDEPPOINT[CHAN] + 1;");
					//out->println(id+"else");
					//// Jump to end of Autotest:
					//out->println(id+id1+"AM->PROGPOINTER[CHAN] = AM->INSTRLINENUM[CHAN][AM->COMMAND[CHAN][(AM->AUTOTESTSTART[CHAN])][1]-1]+2;"); // +1+1");

					AM->JUMPED = 1;
					break;
				case 12:
					// Wait
					//out->println(id+"// Wait");
					// As for Pause, but don't move to next instruction
					//out->println(id+"AM->PROGPOINTER[CHAN] = "+AM->PROGPOINTER[AM->CHAN]+";");
					//out->println(id+"AM->PAUSED = true;");
					out->println(id+amr+"amalWait(CHAN, "+AM->stri(AM->PROGPOINTER[AM->CHAN])+");");

					AM->JUMPED = 1;
					break;
				case 13:
					// Anim (initialisation)
					//out->println(id+"// Animate (Anim)");
					FETCHARGUMENTS_C(cpp, AM->NUMARGS[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])]);
					out->println(id+amr+"amalAnimInit(CHAN, "+AM->stri(AM->ARG[AM->CHAN][1])+");"); AM->ARG[AM->CHAN][1]=0;

					for ( int T=1; T<AM->NUMARGS[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])]; T+=2 )
					{
						out->println(id+amr+"amalAnimInitPair(CHAN, "+ AM->stri((T - 1) / 2)+", "+
								(getarg(AM->CHAN, T+1))+", "+(getarg(AM->CHAN, T+2))+");");
						//out->print(id+"AM->SPECIAL[CHAN]["+(T+13)+"] = "+getarg(AM->CHAN, T+1)+";  ");
						//out->println("AM->SPECIAL[CHAN]["+(T+14)+"] = "+getarg(AM->CHAN, T+2)+";");
					}
					break;
				case 15:
					// PLay
					//out->println(id+"// PLay");
					// TO DO....
					FETCHARGUMENTS_C(cpp, 1);
					out->println(id+amr+"amalPLay(CHAN, "+(getarg(AM->CHAN,1))+");");
					break;
				case 16:
					// Add +
					//out->println(id+"// Add +"); // removed for conciseness;
					// AM->temp(c)=a+b

					FETCHARGUMENTS_C(cpp, 2);
					AM->temp[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][3]] = "("+(getarg(AM->CHAN,1))+" + "+(getarg(AM->CHAN,2))+")";
					AM->caseon = 0;
					break;
				case 17:
					// Subtract -
					//out->println(id+"// Subtract -"); // removed for conciseness;
					// AM->temp(c)=a-b

					FETCHARGUMENTS_C(cpp, 2);
					AM->temp[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][3]] = "("+(getarg(AM->CHAN,1))+" - "+(getarg(AM->CHAN,2))+")";
					AM->caseon = 0;
					break;
				case 18:
					// Multiply *
					//out->println(id+"// Multiply *"); // removed for conciseness;
					// AM->temp(c)=a*b

					FETCHARGUMENTS_C(cpp, 2);
					AM->temp[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][3]] = "("+(getarg(AM->CHAN,1))+" * "+(getarg(AM->CHAN,2))+")";
					AM->caseon = 0;
					break;
				case 19:
					// Divide /
					//out->println(id+"// Divide /"); // removed for conciseness;
					// AM->temp(c)=a/b

					FETCHARGUMENTS_C(cpp, 2);
					AM->temp[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][3]] = "("+(getarg(AM->CHAN,1))+" / "+(getarg(AM->CHAN,2))+")";
					AM->caseon = 0;
					break;
				case 20:
					// Equals =
					// out->println(id+"// Equals ="); // removed for conciseness;
					// AM->temp(c)=a=b

					FETCHARGUMENTS_C(cpp, 2);
					AM->temp[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][3]] = Logtruestr+"("+(getarg(AM->CHAN,1))+" == "+(getarg(AM->CHAN,2))+")";
					AM->caseon = 0;
					break;
				case 21:
					// Greater than >
					//out->println(id+"// Greater than >"); // removed for conciseness;
					// AM->temp(c)=a>b

					FETCHARGUMENTS_C(cpp, 2);
					AM->temp[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][3]] = Logtruestr+"("+(getarg(AM->CHAN,1))+" > "+(getarg(AM->CHAN,2))+")";
					AM->caseon = 0;
					break;
				case 22:
					// Less than <
					//out->println(id+"// Less than <"); // removed for conciseness;
					// AM->temp(c)=a<b

					FETCHARGUMENTS_C(cpp, 2);
					AM->temp[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][3]] = Logtruestr+"("+(getarg(AM->CHAN,1))+" < "+(getarg(AM->CHAN,2))+")";
					AM->caseon = 0;
					break;
				case 23:
					// Not equal <>
					//out->println(id+"// Not equal <>"); // removed for conciseness;
					// AM->temp(c)=a<>b

					FETCHARGUMENTS_C(cpp, 2);
					AM->temp[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][3]] = Logtruestr+"("+(getarg(AM->CHAN,1))+" != "+(getarg(AM->CHAN,2))+")";
					AM->caseon = 0;
					break;
				case 24:
					// And &
					//out->println(id+"// Bitwise And &"); // removed for conciseness;
					// AM->temp(c)=a AND b

					FETCHARGUMENTS_C(cpp, 2);
					AM->temp[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][3]] = Logtruestr+"("+(getarg(AM->CHAN,1))+" & "+(getarg(AM->CHAN,2))+")";
					break;
				case 25:
					// Or |
					//out->println(id+"// Bitwise Or |"); // removed for conciseness;
					// AM->temp(c)=a OR b

					FETCHARGUMENTS_C(cpp, 2);
					AM->temp[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][3]] = Logtruestr+"("+(getarg(AM->CHAN,1))+" | "+(getarg(AM->CHAN,2))+")";
					break;
				case 26:
					// XMouse
					//out->println(id+"// XMouse"); // removed for conciseness;
					// AM->temp(a)=XMouse

					AM->temp[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][1]] = amr+">xMouse()";
					AM->caseon = 0;
					break;
				case 27:
					// YMouse
					//out->println(id+"// YMouse"); // removed for conciseness;
					// AM->temp(a)=YMouse

					AM->temp[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][1]] = amr+"yMouse()";
					AM->caseon = 0;
					break;
				case 28:
					// J0
					//out->println(id+"// J0"); // removed for conciseness;
					// AM->temp(a)=J0

					AM->temp[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][1]] = amr+"joy(0)";
					AM->caseon = 0;
					break;
				case 29:
					// J1
					//out->println(id+"// J1"); // removed for conciseness;
					// AM->temp(a)=J1

					AM->temp[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][1]] = amr+"joy(1)";
					AM->caseon = 0;
					break;
				case 30:
					// K1
					//out->println(id+"// K1"); // removed for conciseness;
					// AM->temp(a)=K1

					AM->temp[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][1]] = "(("+amr+"mousekey() & 1) != 0)";
					AM->caseon = 0;
					break;
				case 31:
					// K2
					//out->println(id+"// K2"); // removed for conciseness;
					// AM->temp(a)=K2

					AM->temp[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][1]] = "(("+amr+"mousekey() & 2) != 0)";
					AM->caseon = 0;
					break;
				case 32:
					// XScreen()
					//out->println(id+"// XScreen()"); // removed for conciseness;
					// AM->temp(c)=XScreen(a,b)

					//System.out->println("AtAM->tempting XScreen now!!!");
					FETCHARGUMENTS_C(cpp, 2);

					AM->temp[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][3]] = amr+"xscreen("+(getarg(AM->CHAN,1))+", "+(getarg(AM->CHAN,2))+")";
					AM->caseon = 0;
					break;
				case 33:
					// YScreen()
					//out->println(id+"// YScreen()"); // removed for conciseness;
					// AM->temp(c)=YScreen(a,b)

					FETCHARGUMENTS_C(cpp, 2);
					AM->temp[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][3]] = amr+"yscreen("+(getarg(AM->CHAN,1))+", "+(getarg(AM->CHAN,2))+")";
					AM->caseon = 0;
					break;
				case 34:
					// XHard()
					//out->println(id+"// XHard()"); // removed for conciseness;
					// AM->temp(c)=XHard(a,b)

					FETCHARGUMENTS_C(cpp, 2);
					AM->temp[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][3]] = amr+"xhard("+(getarg(AM->CHAN,1))+", "+(getarg(AM->CHAN,2))+")";
					AM->caseon = 0;
					break;
				case 35:
					// YHard()
					//out->println(id+"// YHard()"); // removed for conciseness;
					// AM->temp(c)=YHard(a,b)

					FETCHARGUMENTS_C(cpp, 2);
					AM->temp[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][3]] = amr+"yhard("+(getarg(AM->CHAN,1))+", "+(getarg(AM->CHAN,2))+")";
					AM->caseon = 0;
					break;
				case 36:
					// BobCol
					//out->println(id+"// BobCol"); // removed for conciseness;
					// AM->temp(d)=BobCol(a,b,c)

					FETCHARGUMENTS_C(cpp, 3);
					AM->temp[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][4]] = amr+"bobcol("+(getarg(AM->CHAN,1))+", "+(getarg(AM->CHAN,2))+", "+(getarg(AM->CHAN,3))+")";
					AM->caseon = 0;
					break;
				case 37:
					// SpriteCol
					//out->println(id+"// SpriteCol"); // removed for conciseness;
					// AM->temp(d)=SpriteCol(a,b,c)

					FETCHARGUMENTS_C(cpp, 3);
					AM->temp[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][4]] = amr+"spritecol("+(getarg(AM->CHAN,1))+", "+(getarg(AM->CHAN,2))+", "+(getarg(AM->CHAN,3))+")";
					AM->caseon = 0;
					break;
				case 38:
					// VUmeter
					//out->println(id+"// VUmeter"); // removed for conciseness;
					// AM->temp(b)=VUmeter(a)

					FETCHARGUMENTS_C(cpp, 1);
					AM->temp[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][2]] = amr+"vumeter("+(getarg(AM->CHAN,1))+")";
					AM->caseon = 0;
					break;
				case 39:
					// Col
					// out->println(id+"// Col"); // removed for conciseness;
					// AM->temp(b)=Col(a)

					FETCHARGUMENTS_C(cpp, 1);
					AM->temp[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][2]] = amr+"col("+(getarg(AM->CHAN,1))+")";
					AM->caseon = 0;
					break;
				case 40:
					// Zandom
					//out->println(id+"// Zandom"); // removed for conciseness;
					// AM->temp(b)=Zandom(a)

					FETCHARGUMENTS_C(cpp, 1);
					AM->temp[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][2]] = amr+"rnd("+(getarg(AM->CHAN,1))+")";
					AM->caseon = 0;
					break;
				case 41:
					// AUtotest(
					out->println(id+"// Start of Autotest block");
					// Argument 1 = instruction number for ')'

					// Record the start position of the Autotest

					out->println(id+amr+"amalInitAutotest(CHAN, "+AM->stri(AM->PROGPOINTER[AM->CHAN])+", "+AM->stri(AM->INSTRLINENUM[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][1]-1]+2) +");");

					///out->println(id+"AM->AUTOTESTSTART[CHAN]="+AM->stri(AM->PROGPOINTER[AM->CHAN])+";");
					//out->println(id+"AM->AUTOTESTEND[CHAN]="+ AM->stri( AM->INSTRLINENUM[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][1]-1]+2 ) + ";");
					//// Skip to end of Autotest:
					//out->println(id+"AM->PROGPOINTER[CHAN]="+ AM->stri( AM->INSTRLINENUM[AM->CHAN][AM->COMMAND[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][1]-1]+2 ) + ";");

					AM->JUMPED = 1;
					break;
				case 42:
					// ")" (End of Autotest)               	
					out->println(id+amr+"amalEndAutotest(CHAN);");
					out->println(id+"// End of Autotest block");
					out->println();

					//// Re-enter the main program again, at the original departure point:
					//out->println(id+"AM->RUNNINGAUTOTEST[CHAN] = false; // Leave Autotest...");
					//out->println(id+"if ( AM->MAINPROGDEPPOINT[CHAN]>=0 )");
					//out->println(id+id1+"AM->PROGPOINTER[CHAN] = AM->MAINPROGDEPPOINT[CHAN];");
					//out->println(id+"else");
					//// Jump to end of Autotest:
					//out->println(id+id1+"AM->PROGPOINTER[CHAN] = AM->AUTOTESTEND[CHAN];");

					AM->JUMPED = 1;
					break;
				}

				if (AM->JUMPED == 1)
				{
					if (cpp)
						out->println(id1+id1+"break;"); // Extra indent added
					else
						out->println(id1+id1+id1+"break;"); // Extra indent added
				}
			}

			if (AM->NUMLINES[AM->CHAN] > 0)
			{
				if (cpp)
				{
					if (AM->JUMPED != 1)
					{
						out->println(id+id1+amr+"amalEnd(CHAN);");
					}
					out->println(id1+"}");
					out->println(id1+"if ("+amr+"PROGPOINTER[CHAN] >= "+AM->stri(AM->NUMLINES[AM->CHAN])+")");
					out->println(id1+id1+amr+"amalEnd(CHAN);");
				}
				else
				{
					if (AM->JUMPED != 1)
					{
						out->println(id+id1+amr+"amalEnd(CHAN);");
					}
					out->println(id1+id1+"}");
					out->println(id1+id1+"if ("+amr+"PROGPOINTER[CHAN] >= "+AM->stri(AM->NUMLINES[AM->CHAN])+")");
					out->println(id1+id1+id1+amr+"amalEnd(CHAN);");
				}
			}

			if (cpp)
				out->println("}");
			else
				out->println(id1+"}");
			
			AM->PROGPOINTER[AM->CHAN]=0;
		}

		if (!cpp)
			out->println("}");

		//Fileout->Close;
		//TEMP = 0;

		// Re-instate the previous status of Synchro.
		AM->AmalSynchro = synchrostatus;
}


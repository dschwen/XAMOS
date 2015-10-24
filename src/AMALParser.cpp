////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The following methods form the AMAL string parser and tokeniser, also known as the AMAL Lexer.
//
// Caution: This module was written many years ago, and is not particularly well written. But it works!
// If you are offended by bad code, please look away now. Thank you!
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "AMALParser.h"
#include <sstream>

// Constructor method:
AMALParser::AMALParser(AMOS_System* AMi)
{
	AM = AMi;
}

// Debug:
void AMALParser::SETUP_AMAL()
{
	AM->LOGICTRUE=1; AM->CHAN=0; AM->TOPCHANNEL=0;

	// TYPEAM->CHANNEL(channel)=
	// 0: To Sprite (default)
	// 1: To Bob
	// 2: To Screen Display
	// 3: To Screen Offset
	// 4: To Screen Size
	// 5: To Rainbow
	// Set the channels (to default):
	for ( int NUM = 0; NUM <= 7; NUM++ )
	{
		AM->SETCHANNEL[NUM] = NUM;
		AM->TYPECHANNEL[NUM] = 0; // To Sprite.
	}

	// Set up the debug arrays:
	SETUP_AMAL_DEBUG();
}
void AMALParser::SETUP_AMAL_DEBUG()
{
	// Instructions:
	AM->commandlist[0]="Pause";
	AM->commandlist[1]="for";
	AM->commandlist[2]="Next";
	AM->commandlist[3]="Let";
	AM->commandlist[4]="Jump";
	AM->commandlist[5]="If";
	AM->commandlist[6]="Move (init)";
	AM->commandlist[7]="Move (run)";
	AM->commandlist[8]="Direct";
	AM->commandlist[9]="End";
	AM->commandlist[10]="eXit";
	AM->commandlist[11]="On";
	AM->commandlist[12]="Wait";
	AM->commandlist[13]="Anim";
	AM->commandlist[14]="..";
	AM->commandlist[15]="PLay";

	// Operators:
	AM->commandlist[16]="+ADD";
	AM->commandlist[17]="-SUBTRACT";
	AM->commandlist[18]="*MULTIPLY";
	AM->commandlist[19]="/DIVIDE";
	AM->commandlist[20]="=EQUAL";
	AM->commandlist[21]=">GREATER_THAN";
	AM->commandlist[22]="<LESS_THAN";
	AM->commandlist[23]="<>NOT_EQUAL";
	AM->commandlist[24]="&AND";
	AM->commandlist[25]="|OR";
	// ^ (Exponent)? XOR? NOT? (not: >=, <=, MOD)

	// Functions:
	AM->commandlist[26]="XMouse";
	AM->commandlist[27]="YMouse";
	AM->commandlist[28]="J0";
	AM->commandlist[29]="J1";
	AM->commandlist[30]="K1";
	AM->commandlist[31]="K2";
	AM->commandlist[32]="XScreen";
	AM->commandlist[33]="YScreen";
	AM->commandlist[34]="XHard";
	AM->commandlist[35]="YHard";
	AM->commandlist[36]="BobCol";
	AM->commandlist[37]="SpriteCol";
	AM->commandlist[38]="VUmeter";
	AM->commandlist[39]="Col";
	AM->commandlist[40]="Z";

	//
	AM->commandlist[41]="AUtotest(";
	AM->commandlist[42]="')' (End of Autotest)";

	AM->commandlist[45]="Label:"; // Not an instruction...

	// Argument Type Names:
	AM->argtypename[0]=""; // Constant numbers...
	AM->argtypename[1]="Glbl";
	AM->argtypename[2]="Locl";
	AM->argtypename[3]="Spec";
	AM->argtypename[4]="Temp";
}

void AMALParser::Tokenize()
{
		//cout << AM->_input << endl;

		// Remove any unused characters:
		REMOVE_UNUSED(); //REMOVE_UNUSED(AM->_input);
		//cout << AM->tokest << endl;

		// Scan and find the AMAL instructions:
		SCANINSTRUCTIONS(); //SCANINSTRUCTIONS(AM->_input);

		AM->NUMINSTRUCTIONS[AM->CHAN]=AM->NUMLINES[AM->CHAN];
		for ( AM->N = 0; AM->N<=AM->NUMINSTRUCTIONS[AM->CHAN]-1; AM->N++ )
		{
			AM->INSTRLINENUM[AM->CHAN][AM->N] = AM->N;
			AM->TEMPCOUNT[AM->N]=0;
		}

		//cout << "SCANINSTRUCTIONS() complete. AM->NUMLINES[" << AM->stri(AM->CHAN) << "]=" << AM->stri(AM->NUMLINES[AM->CHAN]) << endl;
		//cout << "AM->_TOTALNUMSTRINGS == " + AM->stri(AM->_TOTALNUMSTRINGS) << endl;
		//for (int a=0; a<AM->_TOTALNUMSTRINGS; a++) cout << AM->strin[AM->CHAN][AM->N][a] << endl;

		//cout << "Debug: The expression strings to parse:" << endl;
		//for (int n=0; n > (AM->NUMLINES[AM->CHAN]); n++)
		//{
		//	// FIXME: VERY STRANGE BUG HERE - accessing AM->strin[][][] changes behaviour later!
		//	for (int strn=0; strn<(AM->NUMSTRINGS[AM->CHAN][n]); strn++)
		//		cout << (AM->strin[AM->CHAN][n][strn]) << endl;
		//}

		// Evaluate the expressions in the instructions:
		do
		{
			AM->_TOTALNUMSTRINGS=0;
			AM->N=0;
			while( (AM->N) < (AM->NUMLINES[AM->CHAN]) )
			{
				AM->NN = 0;
				while(((AM->NUMSTRINGS[AM->CHAN][AM->N]) - (AM->NN)) > 0)
				{
					//cout << "DEBUG! Tokenise() strings left: " << AM->stri(AM->NUMSTRINGS[AM->CHAN][AM->N] - AM->NN) << endl;
					// Debug:
					//if ((AM->NUMSTRINGS[AM->CHAN][AM->N] - AM->NN) == 1)
					//	cout << "Last string: \"" << AM->strin[AM->CHAN][AM->N][0] << "\"" << endl;

					// Kludge (removed):
					//if (((AM->NUMSTRINGS[AM->CHAN][AM->N] - AM->NN) == 1) && (AM->strin[AM->CHAN][AM->N][0] == "" )) //null)
					//{
					//	cout << "Problem? " << AM->strin[AM->CHAN][AM->N][0] << endl;

					//	AM->NUMSTRINGS[AM->CHAN][AM->N]--;
					//}
					//else
					//{
					AM->_TOTALNUMSTRINGS++;

					// Only continue doing tests when AM->TEST is true...
					AM->TEST=true;
					//cout << "Starting:" << endl;
					SIMPLEEXPRESSIONS(); //cout << "SIMPLEEXPRESSIONS() complete." << endl;
					OPERATORS(); //cout << "OPERATORS() complete." << endl;
					SCANFUNCTIONS(); //cout << "SCANFUNCTIONS() complete." << endl;
					AM->NN++;
					//}
				}

				//cout << "Infinite loop error here on =XS(11, 22)" << endl;
				//cout << "AM->_TOTALNUMSTRINGS == " << am->stri(AM->_TOTALNUMSTRINGS) << endl;
				//for (int a=0; a<AM->_TOTALNUMSTRINGS; a++)
				//	cout << "#" << AM->strin[AM->CHAN][AM->N][a] << "#" << endl;

				//cout << "SCANFUNCTIONS() complete. N = " << am->stri(N) + ", AM->NUMLINES[AM->CHAN] = " + am->stri(AM->NUMLINES[AM->CHAN]) << endl;
				AM->N++;
			}
			//cout << "AM->_TOTALNUMSTRINGS == " << AM->stri(AM->_TOTALNUMSTRINGS) << endl;
			//for (int a=0; a<AM->_TOTALNUMSTRINGS; a++) cout << AM->strin[AM->CHAN][AM->N][a] << endl;


			// Debug:
			//if (AM->_TOTALNUMSTRINGS == 1)
			//	cout << "*Last string: \"" << AM->strin[AM->CHAN][AM->N][0] << "\"" << endl;

			// Kludge (removed):
			if (AM->_TOTALNUMSTRINGS == 1)
				if (AM->strin[AM->CHAN][AM->N][0] == "" ) //null)
				{
					//cout << "*Problem? " << AM->strin[AM->CHAN][AM->N][0] << endl;
					//AM->_TOTALNUMSTRINGS = 0;
				}

		}
		while ( AM->_TOTALNUMSTRINGS > 0 );

		// cout << "TOKENISE() almost complete." << endl;
}

void AMALParser::REMOVE_UNUSED() // (string AM->_input)
{
		// Remove any unused characters:
		AM->tokest=""; AM->ttt=""; AM->lastt2=""; //return;
		for ( AM->N = 1; AM->N <= (int)(AM->_input.length()); AM->N++ )
		{
			AM->lastt=AM->ttt;
			//AM->lastt2="";
			AM->ttt=AM->mid(AM->_input,AM->N,1);
			//if (AM->ttt == (")")) cout << "Crash time!" << endl;
			// If a used character is found:
			AM->T=0;
			if( AM->ttt == ("(") || AM->ttt == (")") || AM->ttt == (".") || AM->ttt == ("-") || AM->ttt == (",") || AM->ttt == ("=")
					|| AM->ttt == ("+") || AM->ttt == ("*") || AM->ttt == ("/") || AM->ttt == ("<") || AM->ttt == (">")
					|| AM->ttt == ("&") || AM->ttt == ("|") || AM->ttt == (":") || AM->ttt == ("$") || AM->ttt == ("%") )
				AM->T++;
			//// || AM->ttt == (";")
			//cout << "AM->ttt = " << AM->ttt << ", AM->T = " << AM->stri(AM->T) << endl;
			if ( //((AM->ttt == (AM->ttt.toUpperCase()) && (AM->ttt == (AM->ttt.toLowerCase()))) ||
					(((int)AM->ttt[0]>=65) && ((int)AM->ttt[0]<=90)) || (AM->T != 0) ||
					(((int)AM->ttt[0]>=48) && ((int)AM->ttt[0]<=57)) || (AM->T != 0) )
				//|| ((AM->ttt[0]>=48) && (AM->ttt[0]<=57)) || (AM->T != 0) )
			{
				// Check for PL:
				if ( AM->lastt2 == ("P") && AM->ttt == ("L") )
				{
					if ( !(AM->lastt == ("P")) )
					{
						//{int b=0; while(b<10000) { cout << "AM->lastt2 = " << AM->lastt2 << "!" << endl; b++;}}
						AM->ttt=";"+AM->ttt;
					}
					// Similarly, check for XM:
				}
				else if ( AM->lastt2 == ("X") && AM->ttt == ("M") )
				{
					if ( !(AM->lastt == ("X")) )
					{
						AM->ttt=";"+AM->ttt;
					}
					// Check for YM:
				}
				else if ( AM->lastt2 == ("Y") && AM->ttt == ("M") )
				{
					if ( !(AM->lastt == ("Y")) )
					{
						AM->ttt=";"+AM->ttt;
					}
				}
				AM->lastt2=AM->ttt;

				AM->tokest=AM->tokest+AM->ttt;
			} // else if (AM->ttt != null) cout << "yELP! " << am->stri((int)(AM->ttt[0])) << " " << AM->ttt << endl; // Debug
		}
		//cout << "" << AM->tokest << endl;
}

void AMALParser::SCANINSTRUCTIONS() // (string AM->_input)
{
		int T=0; int I; int I2=0; int I3=0; int EXTRASTRINGS=0;
		//int T2=0; int T3=0;
		AM->TEST=false; int FF=0;
		string test = "";
		AM->SCANFROM=1; AM->BRSTACK=1; AM->NEST=0;
		SCANFORNEXTINSTRUCTION();

		// N is the LINE number (from 0)
		AM->N=0; AM->NUMLINES[AM->CHAN]=0;
		while ( AM->FOUNDINSTRUCTION>=0 )
		{
			switch ( AM->FOUNDINSTRUCTION ) // Label (N: etc.)
			{
			case 0:
				// 'Pause'
				// cout << "Pause! AM->SCANFROM = " << AM->stri(AM->SCANFROM) << endl;
				AM->COMMAND[AM->CHAN][AM->N][0]=0; // 'Pause'
				AM->strin[AM->CHAN][AM->N][0]="";
				AM->NUMARGS[AM->CHAN][AM->N]=0; // Number of arguments (in initial form.)
				AM->NUMSTRINGS[AM->CHAN][AM->N]=0; // Number of remaining strings...
				AM->TOPARGNUM[AM->N]=0;

				AM->SCANFROM += 1;
				SCANFORNEXTINSTRUCTION();
				AM->N++;

				break;
			case 1:
				// 'For'
				AM->COMMAND[AM->CHAN][AM->N][0]=1; // 'For'
				T=(int)AM->mid(AM->tokest,AM->SCANFROM+2,1)[0];
				if ( T > 57 )
				{
					AM->COMMAND[AM->CHAN][AM->N][3]=0; // Global/External register
					AM->COMMAND[AM->CHAN][AM->N][4]=T - 65; // Register number
				}
				else
				{
					AM->COMMAND[AM->CHAN][AM->N][3]=1; // Local/Internal register
					AM->COMMAND[AM->CHAN][AM->N][4]=T - 48; // Register number
				}
				AM->ARGTYPE[AM->CHAN][AM->N][3]=0; AM->ARGTYPE[AM->CHAN][AM->N][4]=0;

				I=AM->instr(AM->tokest,"T",AM->SCANFROM+4); // Search for 'To'
				// if I=0 : Bell : Stop : End if

				// Initial Value
				AM->strin[AM->CHAN][AM->N][1]=AM->mid(AM->tokest,AM->SCANFROM+4,I-AM->SCANFROM-4);
				AM->STRINGARGNUM[AM->N][1]=2;

				// Final Value
				AM->SCANFROM=I+2;
				SCANFORNEXTINSTRUCTION();
				AM->strin[AM->CHAN][AM->N][0]=AM->mid(AM->tokest,I+1,AM->SCANFROM-I-1); // TO END...
				AM->STRINGARGNUM[AM->N][0]=1;

				// NEW: Arg 5 = Instruction number of corresponding Next
				AM->COMMAND[AM->CHAN][AM->N][5]=0; AM->COMMAND[AM->CHAN][AM->N][5]=0;

				AM->NUMARGS[AM->CHAN][AM->N]=2; // Number of arguments (in initial form.)
				AM->NUMSTRINGS[AM->CHAN][AM->N]=2; // Number of remaining strings...
				AM->TOPARGNUM[AM->N]=5; // was 4 !!!

				// Initialize other argument values (strings to start with):
				AM->COMMAND[AM->CHAN][AM->N][1]=0; AM->COMMAND[AM->CHAN][AM->N][2]=0;
				AM->ARGTYPE[AM->CHAN][AM->N][1]=0; AM->ARGTYPE[AM->CHAN][AM->N][2]=0;

				AM->NEST++;

				// Since this is before new instructions are added,
				// later Instruction Number = Current Line number (N)...
				AM->NESTINSTRNUM[AM->NEST] = AM->N;

				AM->N++;

				break;
			case 2:
				// 'Next'
				AM->COMMAND[AM->CHAN][AM->N][0]=2; // 'Next'
				T=(int)AM->mid(AM->tokest,AM->SCANFROM+2,1)[0];
				if ( T>57 )
				{
					AM->COMMAND[AM->CHAN][AM->N][1]=0; // Global/External register
					AM->COMMAND[AM->CHAN][AM->N][2]=T-65; // Register number
				}
				else
				{
					AM->COMMAND[AM->CHAN][AM->N][1]=1; // Local/Internal register
					AM->COMMAND[AM->CHAN][AM->N][2]=T-48; // Register number
				}
				AM->ARGTYPE[AM->CHAN][AM->N][1]=0; AM->ARGTYPE[AM->CHAN][AM->N][2]=0;

				// Set Arg 3 to Instruction no. of for
				AM->COMMAND[AM->CHAN][AM->N][3]=AM->NESTINSTRNUM[AM->NEST]; AM->ARGTYPE[AM->CHAN][AM->N][3]=0;

				// NEW: Set arg 5 of for to Instruction no. of this Next:
				AM->COMMAND[AM->CHAN][(AM->NESTINSTRNUM[AM->NEST])][5] = AM->N;
				AM->ARGTYPE[AM->CHAN][(AM->NESTINSTRNUM[AM->NEST])][5] = 0;

				AM->NEST--;

				AM->strin[AM->CHAN][AM->N][0]="";
				AM->NUMARGS[AM->CHAN][AM->N]=3; // Number of arguments (in initial form.)
				AM->NUMSTRINGS[AM->CHAN][AM->N]=0; // Number of remaining strings...
				AM->TOPARGNUM[AM->N]=3;

				AM->SCANFROM+=3;
				SCANFORNEXTINSTRUCTION();
				AM->N++;

				break;
			case 3:
				// 'Let'
				test=AM->mid(AM->tokest,AM->SCANFROM+1,1);
				if ( test == ("R") ) // Standard registers...
				{
					AM->COMMAND[AM->CHAN][AM->N][0]=3; // 'Let'
					T=(int)AM->mid(AM->tokest,AM->SCANFROM+2,1)[0];
					if ( T>57 )
					{
						AM->COMMAND[AM->CHAN][AM->N][2]=0; // Global/External register
						AM->COMMAND[AM->CHAN][AM->N][3]=T-65; // Register number
					}
					else
					{
						AM->COMMAND[AM->CHAN][AM->N][2]=1; // Local/Internal register
						AM->COMMAND[AM->CHAN][AM->N][3]=T-48; // Register number
					}
					AM->ARGTYPE[AM->CHAN][AM->N][2]=0; AM->ARGTYPE[AM->CHAN][AM->N][3]=0;

					// Expression...
					AM->SCANFROM+=4;
					I=AM->SCANFROM;
					SCANFORNEXTINSTRUCTION();
					AM->strin[AM->CHAN][AM->N][0]=AM->mid(AM->tokest,I,AM->SCANFROM-I); // TO END...
					AM->STRINGARGNUM[AM->N][0]=1;
					AM->NUMARGS[AM->CHAN][AM->N]=2; // Number of arguments (in initial form.)
					AM->NUMSTRINGS[AM->CHAN][AM->N]=1; // Number of remaining strings...
					AM->TOPARGNUM[AM->N]=3;

					// Initialize other argument values (strings to start with):
					AM->COMMAND[AM->CHAN][AM->N][1]=0; AM->ARGTYPE[AM->CHAN][AM->N][1]=0;

					AM->N++;
				}
				else
				{
					// Special' registers...
					AM->COMMAND[AM->CHAN][AM->N][0]=3; // 'Let'
					T=(int)(test[0]);
					AM->COMMAND[AM->CHAN][AM->N][2]=2; // SPECIAL register
					//   X
					if ( T==88 ) { AM->COMMAND[AM->CHAN][AM->N][3]=0;
					// Y
					} else if ( T==89 ) { AM->COMMAND[AM->CHAN][AM->N][3]=1;
					// A
					} else if ( T==65 ) { AM->COMMAND[AM->CHAN][AM->N][3]=2;
					}
					AM->ARGTYPE[AM->CHAN][AM->N][2]=0; AM->ARGTYPE[AM->CHAN][AM->N][3]=0;

					// Expression...

					AM->SCANFROM+=3;
					I=AM->SCANFROM;
					SCANFORNEXTINSTRUCTION();
					AM->strin[AM->CHAN][AM->N][0]=AM->mid(AM->tokest,I,AM->SCANFROM-I); // TO END...
					AM->STRINGARGNUM[AM->N][0]=1;
					AM->NUMARGS[AM->CHAN][AM->N]=2; // Number of arguments (in initial form.)
					AM->NUMSTRINGS[AM->CHAN][AM->N]=1; // Number of remaining strings...
					AM->TOPARGNUM[AM->N]=3;

					// Initialize other argument values (strings to start with):
					AM->COMMAND[AM->CHAN][AM->N][1]=0; AM->ARGTYPE[AM->CHAN][AM->N][1]=0;

					AM->N++;
				}

				break;
			case 4:
				// 'Jump'
				//cout << "Jump! AM->CHAN=" << AM->stri(AM->CHAN) << ", instruction number N = " << AM->stri(AM->N) << endl;
				AM->COMMAND[AM->CHAN][AM->N][0]=4; // 'Jump'
				AM->COMMAND[AM->CHAN][AM->N][1]=(int)(AM->mid(AM->tokest,AM->SCANFROM+1,1)[0]) - 65; // Which label...
				AM->ARGTYPE[AM->CHAN][AM->N][1]=0;

				AM->strin[AM->CHAN][AM->N][0]="";
				AM->NUMARGS[AM->CHAN][AM->N]=1; // Number of arguments (in initial form.)
				AM->NUMSTRINGS[AM->CHAN][AM->N]=0; // Number of remaining strings...
				AM->TOPARGNUM[AM->N]=1;

				AM->SCANFROM+=2;
				SCANFORNEXTINSTRUCTION();
				AM->N++;

				break;
			case 5:
				// 'If'
				AM->COMMAND[AM->CHAN][AM->N][0]=5; // 'If'

				AM->SCANFROM++;
				I=AM->SCANFROM;
				SCANFORNEXTINSTRUCTION();

				AM->strin[AM->CHAN][AM->N][0]=AM->mid(AM->tokest,I,AM->SCANFROM-I); // Expression, TO END...
				AM->STRINGARGNUM[AM->N][0]=1;
				AM->NUMARGS[AM->CHAN][AM->N]=0; // Number of arguments (in initial form.)
				AM->NUMSTRINGS[AM->CHAN][AM->N]=1; // Number of remaining strings...
				AM->TOPARGNUM[AM->N]=1;

				// Initialize other argument values (strings to start with):
				AM->COMMAND[AM->CHAN][AM->N][1]=0; AM->ARGTYPE[AM->CHAN][AM->N][1]=0;

				AM->N++;

				break;
			case 6:
				// 'Move'
				AM->COMMAND[AM->CHAN][AM->N][0]=6; // 'Move' (initialize). (Done in 2 parts)

				// Search for comma (result in AM->RESULT)
				AM->RESULT = SEARCHCOMMA(AM->tokest,",",AM->SCANFROM);
				I=AM->RESULT;

				AM->strin[AM->CHAN][AM->N][0]=AM->mid(AM->tokest,AM->SCANFROM+1,I-AM->SCANFROM-1);
				AM->STRINGARGNUM[AM->N][0]=1;

				AM->RESULT = SEARCHCOMMA(AM->tokest,",",I+1);
				I2=AM->RESULT;
				//cout << "Doing Move! AM->SCANFROM = " << AM->stri(AM->SCANFROM) << "; I = " << AM->stri(I) << "; I2 = " << AM->stri(I2) << endl;

				AM->strin[AM->CHAN][AM->N][1]=AM->mid(AM->tokest,I+1,I2-I-1);
				AM->STRINGARGNUM[AM->N][1]=2;

				AM->SCANFROM=I2+1;
				SCANFORNEXTINSTRUCTION();
				// ''''I2=AM->RESULT : Rem ?

				AM->strin[AM->CHAN][AM->N][2]=AM->mid(AM->tokest,I2+1,AM->SCANFROM-I2-1); // TO END...
				AM->STRINGARGNUM[AM->N][2]=3;
				AM->NUMARGS[AM->CHAN][AM->N]=0; // Number of arguments (in initial form.)
				AM->NUMSTRINGS[AM->CHAN][AM->N]=3; // Number of remaining strings...
				AM->TOPARGNUM[AM->N]=3;

				// Initialize other argument values (strings to start with):
				AM->COMMAND[AM->CHAN][AM->N][1]=0; AM->COMMAND[AM->CHAN][AM->N][2]=0; AM->COMMAND[AM->CHAN][AM->N][3]=0;
				AM->ARGTYPE[AM->CHAN][AM->N][1]=0; AM->ARGTYPE[AM->CHAN][AM->N][2]=0; AM->ARGTYPE[AM->CHAN][AM->N][3]=0;

				AM->N++;

				AM->COMMAND[AM->CHAN][AM->N][0]=7; // 'Move' (main part, repeated)
				AM->strin[AM->CHAN][AM->N][0]="";
				AM->NUMARGS[AM->CHAN][AM->N]=0; // Number of arguments (in initial form.)
				AM->NUMSTRINGS[AM->CHAN][AM->N]=0; // Number of remaining strings...
				AM->TOPARGNUM[AM->N]=0;

				AM->N++;

				break;
			case 8:
				// 'Direct'
				AM->COMMAND[AM->CHAN][AM->N][0]=8; // 'Direct'
				AM->COMMAND[AM->CHAN][AM->N][1]=(int)(AM->mid(AM->tokest,AM->SCANFROM+1,1)[0]) - 65; // Which label...
				AM->ARGTYPE[AM->CHAN][AM->N][1]=0;

				AM->strin[AM->CHAN][AM->N][0]="";
				AM->NUMARGS[AM->CHAN][AM->N]=1; // Number of arguments (in initial form.)
				AM->NUMSTRINGS[AM->CHAN][AM->N]=0; // Number of remaining strings...
				AM->TOPARGNUM[AM->N]=1;

				AM->SCANFROM+=2;
				SCANFORNEXTINSTRUCTION();
				AM->N++;

				break;
			case 9:
				// 'End'
				AM->COMMAND[AM->CHAN][AM->N][0]=9; // 'End'
				AM->strin[AM->CHAN][AM->N][0]="";
				AM->NUMARGS[AM->CHAN][AM->N]=0; // Number of arguments (in initial form.)
				AM->NUMSTRINGS[AM->CHAN][AM->N]=0; // Number of remaining strings...
				AM->TOPARGNUM[AM->N]=0;

				AM->SCANFROM++;
				SCANFORNEXTINSTRUCTION();
				AM->N++;

				break;
			case 10:
				// 'eXit'
				AM->COMMAND[AM->CHAN][AM->N][0]=10; // 'eXit'
				AM->strin[AM->CHAN][AM->N][0]="";
				AM->NUMARGS[AM->CHAN][AM->N]=0; // Number of arguments (in initial form.)
				AM->NUMSTRINGS[AM->CHAN][AM->N]=0; // Number of remaining strings...
				AM->TOPARGNUM[AM->N]=0;

				AM->SCANFROM++;
				SCANFORNEXTINSTRUCTION();
				AM->N++;

				break;
			case 11:
				// 'On'
				AM->COMMAND[AM->CHAN][AM->N][0]=11; // 'On'
				AM->strin[AM->CHAN][AM->N][0]="";
				AM->NUMARGS[AM->CHAN][AM->N]=0; // Number of arguments (in initial form.)
				AM->NUMSTRINGS[AM->CHAN][AM->N]=0; // Number of remaining strings...
				AM->TOPARGNUM[AM->N]=0;

				AM->SCANFROM++;
				SCANFORNEXTINSTRUCTION();
				AM->N++;

				break;
			case 12:
				// 'Wait'
				AM->COMMAND[AM->CHAN][AM->N][0]=12; // 'Wait'
				AM->strin[AM->CHAN][AM->N][0]="";
				AM->NUMARGS[AM->CHAN][AM->N]=0; // Number of arguments (in initial form.)
				AM->NUMSTRINGS[AM->CHAN][AM->N]=0; // Number of remaining strings...
				AM->TOPARGNUM[AM->N]=0;

				AM->SCANFROM++;
				SCANFORNEXTINSTRUCTION();
				AM->N++;

				break;
			case 13:
				// 'Anim'
				AM->COMMAND[AM->CHAN][AM->N][0]=13; // 'Anim'

				AM->RESULT = SEARCHCOMMA(AM->tokest,",",AM->SCANFROM);
				I=AM->RESULT;

				AM->strin[AM->CHAN][AM->N][0]=AM->mid(AM->tokest,AM->SCANFROM+1,I-AM->SCANFROM-1); // Number
				AM->STRINGARGNUM[AM->N][0]=1;

				AM->RESULT = SEARCHCOMMA(AM->tokest,",",I+2);
				I2=AM->RESULT;

				AM->strin[AM->CHAN][AM->N][1]=AM->mid(AM->tokest,I+2,I2-I-2); // Anim n,(***,...)(
				AM->STRINGARGNUM[AM->N][1]=2;

				AM->RESULT = SEARCHCOMMA(AM->tokest,")",I2+1);
				I3=AM->RESULT;

				AM->strin[AM->CHAN][AM->N][2]=AM->mid(AM->tokest,I2+1,I3-I2-1); // Anim n,(...,***)(
				AM->STRINGARGNUM[AM->N][2]=3;

				// Initialize other argument values (strings to start with):
				AM->COMMAND[AM->CHAN][AM->N][1]=0; AM->COMMAND[AM->CHAN][AM->N][2]=0; AM->COMMAND[AM->CHAN][AM->N][3]=0;
				AM->ARGTYPE[AM->CHAN][AM->N][1]=0; AM->ARGTYPE[AM->CHAN][AM->N][2]=0; AM->ARGTYPE[AM->CHAN][AM->N][3]=0;

				EXTRASTRINGS=0;
				while ( AM->mid(AM->tokest,I3+1,1) == ("(") ) // More (image,delay) instructions...
				{
					EXTRASTRINGS += 2;

					AM->RESULT = SEARCHCOMMA(AM->tokest, ",", I3+2);
					I2=AM->RESULT;

					AM->strin[AM->CHAN][AM->N][(1+EXTRASTRINGS)] = AM->mid(AM->tokest,I3+2,I2-I3-2); // )(***,...)(
					AM->STRINGARGNUM[AM->N][(1+EXTRASTRINGS)] = 2 + EXTRASTRINGS;

					AM->RESULT = SEARCHCOMMA(AM->tokest, ")", I2+1);
					I3 = AM->RESULT;

					AM->strin[AM->CHAN][AM->N][(2+EXTRASTRINGS)]=AM->mid(AM->tokest,I2+1,I3-I2-1); // )(...,***)(
					AM->STRINGARGNUM[AM->N][(2+EXTRASTRINGS)]=3+EXTRASTRINGS;

					// Initialize other argument values (strings to start with):
					AM->COMMAND[AM->CHAN][AM->N][(2+EXTRASTRINGS)]=0; AM->COMMAND[AM->CHAN][AM->N][(3+EXTRASTRINGS)]=0;
					AM->ARGTYPE[AM->CHAN][AM->N][(2+EXTRASTRINGS)]=0; AM->ARGTYPE[AM->CHAN][AM->N][(3+EXTRASTRINGS)]=0;
				}

				AM->NUMARGS[AM->CHAN][AM->N]=0; // Number of arguments (in initial form.)
				AM->NUMSTRINGS[AM->CHAN][AM->N]=3 + EXTRASTRINGS; // Number of remaining strings...
				AM->TOPARGNUM[AM->N]=3 + EXTRASTRINGS;

				if ( I3==0 ) { } //A_Bell(); stop(); }
				AM->SCANFROM=I3+1;
				SCANFORNEXTINSTRUCTION();
				AM->N++;

				break;
			case 15:
				// 'PLay'
				AM->COMMAND[AM->CHAN][AM->N][0]=15; // 'PLay'
				AM->SCANFROM+=2; // was 3
				I=AM->SCANFROM; // was -1 at end
				SCANFORNEXTINSTRUCTION();

				// Next line was BUGGY - fixed above
				//AM->strin[AM->CHAN][AM->N][0]=AM->mid(AM->tokest,I); //,AM->SCANFROM-I); // TO END...
				AM->strin[AM->CHAN][AM->N][0]=AM->mid(AM->tokest, I, AM->SCANFROM-I); // TO END...

				AM->STRINGARGNUM[AM->N][0]=1;
				AM->NUMARGS[AM->CHAN][AM->N]=0; // Number of arguments (in initial form.)
				AM->NUMSTRINGS[AM->CHAN][AM->N]=1; // Number of remaining strings...
				AM->TOPARGNUM[AM->N]=1;

				// Initialize other argument values (strings to start with):
				AM->COMMAND[AM->CHAN][AM->N][1]=0; AM->ARGTYPE[AM->CHAN][AM->N][1]=0;

				AM->N++;

				break;
			case 41:
				// AUtotest(
				// NOTE: This is executed..
				AM->COMMAND[AM->CHAN][AM->N][0]=41; // 'AUtotest('
				AM->strin[AM->CHAN][AM->N][0]="";
				AM->NUMARGS[AM->CHAN][AM->N]=0; // Number of arguments (in initial form.)
				AM->NUMSTRINGS[AM->CHAN][AM->N]=0; // Number of remaining strings...
				AM->TOPARGNUM[AM->N]=0;

				AM->SCANFROM += 3;
				SCANFORNEXTINSTRUCTION();

				AM->NEST++;

				// Since this is before new instructions are added,
				// later Instruction Number = Current Line number (N)...
				AM->NESTINSTRNUM[AM->NEST] = AM->N;

				AM->N++;

				break;
			case 42:
				// ')' (End of Autotest)
				// NOTE: This is executed..
				AM->COMMAND[AM->CHAN][AM->N][0]=42; // 'End of Autotest'

				// AM->COMMAND(AM->CHAN,N,1)=AM->NESTINSTRNUM(AM->NEST)

				// Get the line number of the matching 'AUtotest('...
				FF=AM->NESTINSTRNUM[AM->NEST];
				// FF=AM->INSTRLINENUM(AM->CHAN,AM->NESTINSTRNUM(AM->NEST))
				// if FF<0 : FF=AM->NESTINSTRNUM(AM->NEST) : End if

				// Since this is before new instructions are added,
				// later Instruction Number = Current Line number (N)...
				AM->COMMAND[AM->CHAN][FF][1] = AM->N;
				AM->ARGTYPE[AM->CHAN][FF][1]=0;
				AM->NUMARGS[AM->CHAN][FF]++; AM->TOPARGNUM[FF]++;
				AM->NEST--;

				AM->strin[AM->CHAN][AM->N][0]="";
				AM->NUMARGS[AM->CHAN][AM->N]=0; // Number of arguments (in initial form.)
				AM->NUMSTRINGS[AM->CHAN][AM->N]=0; // Number of remaining strings...
				AM->TOPARGNUM[AM->N]=0;

				AM->SCANFROM += 1;
				SCANFORNEXTINSTRUCTION();
				AM->N++;

				break;
			case 45:
				// Label:
				AM->LABELS[AM->CHAN][(int)(AM->mid(AM->tokest,AM->SCANFROM,1)[0])-65] = AM->N;

				AM->SCANFROM += 2;
				SCANFORNEXTINSTRUCTION();
				// NOTE: No 'Inc N' here since a label is not executed...

				break;
			default:

				// Unrecognised instruction - Error.
				//A_Bell();

				break;
			}

		}
		AM->NUMLINES[AM->CHAN] = AM->N;
}

void AMALParser::SCANFORNEXTINSTRUCTION()
{
		AM->FOUNDINSTRUCTION=-1;
		string l1, l2, l3, lbef, lbef2; // What is the correct scope for these variables ???
		while (true)
		{
			l1=AM->mid(AM->tokest,AM->SCANFROM,1);
			l2=AM->mid(AM->tokest,AM->SCANFROM+1,1);
			l3=AM->mid(AM->tokest,AM->SCANFROM+2,1); // Test for 'eXit; Hit:' etc..
			lbef=AM->mid(AM->tokest,AM->SCANFROM-1,1);
			lbef2=AM->mid(AM->tokest,AM->SCANFROM-2,1); // New (added to avoid JR... (i.e. Jump [R I]f..) problem...)
			// From AMOS: Print L1$,L2$,LBEF$

			// New - Can't be an instruction if preceded by 'I'. Are there any other similar instances?
			if ( lbef == ("=") || lbef == ("+") || lbef == ("-") || lbef == ("*") || lbef == ("/") || lbef == ("<")
					|| lbef == (">") || lbef == ("|") || lbef == ("&") || lbef == (",") || lbef == (".") || lbef == ("I")
					|| ((lbef == ("R"))&&(!(lbef2 == ("J")))) ) // or LBEF$="("
				; // Can't be an instruction if preceded by such an operator.
			else if ( l1 == ("(") ) // Opening brackets....
				AM->BRSTACK++;
			else if ( l1 == (")") ) // Closing brackets
			{
				AM->BRSTACK--;
				if ( AM->BRSTACK==0 ) // ")" instruction for end of Autotest..
				{
					AM->BRSTACK=1;
					AM->FOUNDINSTRUCTION=42;
				}
			}
			else if ( l2 == (":") ) // Labels
				AM->FOUNDINSTRUCTION=45;
			else if ( l1 == ("P") && (!(l2 == ("L")) || (l3 == (":"))) ) // Pause
				AM->FOUNDINSTRUCTION=0;
			else if ( l1 == ("F") && l2 == ("R") ) // For (R...)
				AM->FOUNDINSTRUCTION=1;
			else if ( l1 == ("N") && l2 == ("R") ) // Next (R...)
				AM->FOUNDINSTRUCTION=2;
			else if ( l1 == ("L") ) // Let
				AM->FOUNDINSTRUCTION=3;
			else if ( l1 == ("J") && (!(l2 == ("0")) && !(l2 == ("1"))) ) // Jump
				AM->FOUNDINSTRUCTION=4;
			else if ( l1 == ("I") ) // If...Jump (or If...Direct or If...eXit)
				AM->FOUNDINSTRUCTION=5;
			else if ( l1 == ("M") && !(lbef == ("X")) && !(lbef == ("Y")) ) // Move
				AM->FOUNDINSTRUCTION=6;
			else if ( l1 == ("D") ) // Direct
				AM->FOUNDINSTRUCTION=8;
			else if ( l1 == ("E") ) // End
				AM->FOUNDINSTRUCTION=9;
			else if ( l1 == ("X") && ((!(l2 == ("H")) && !(l2 == ("M")) && !(l2 == ("S"))) || (l3 == (":"))) ) // eXit
				AM->FOUNDINSTRUCTION=10;
			else if ( l1 == ("O") ) // On
				AM->FOUNDINSTRUCTION=11;
			else if ( l1 == ("W") ) // Wait
				AM->FOUNDINSTRUCTION=12;
			else if ( l1 == ("A") && !(l2 == ("U")) ) // Anim
				AM->FOUNDINSTRUCTION=13;
			else if ( l1 == ("P") && l2 == ("L") ) // PLay
				AM->FOUNDINSTRUCTION=15;
			else if ( l1 == ("A") && l2 == ("U") ) // AUtotest(......)
				AM->FOUNDINSTRUCTION=41;
			//else
			//; // AM->FOUNDINSTRUCTION = -1;

			AM->SCANFROM++;
			if ( (AM->SCANFROM > (int)AM->tokest.length()) || (AM->FOUNDINSTRUCTION >= 0) )
				break;
		}

		// Fixed...
		if ( AM->FOUNDINSTRUCTION>=0 )
		{
			AM->SCANFROM--;
		}
}

void AMALParser::SIMPLEEXPRESSIONS()
{
		string v; int AC, VV;
		// For variables (AMAL Registers):
		AM->SLEN=AM->strin[AM->CHAN][AM->N][AM->NN].length();

		// Check for spaces at end, and remove if necessary:
		if ( AM->mid(AM->strin[AM->CHAN][AM->N][AM->NN], AM->SLEN, 1)== (" ") )
		{
			AM->strin[AM->CHAN][AM->N][AM->NN]=AM->left(AM->strin[AM->CHAN][AM->N][AM->NN], AM->SLEN - 1);
		}

		//cout << "SIMPLEEXPRESSIONS() running! AM->SLEN = " << AM->stri(AM->SLEN) << endl;

		switch ( AM->SLEN )
		{
		case 0:
			//cout << "Time to crash!" << endl;
			AM->TEST = false;
			break;
		case 1:
			// Expression length is 1
			v=AM->strin[AM->CHAN][AM->N][AM->NN];
			AC=(int)((unsigned char)v[0]);
			//cout << "DEBUG: 1 char expression. Testing for temp (>154). AC=" << AM->stri(AC) << endl;
			if ( AC==88 || AC==89 || AC==65 ) // X,Y or A
			{
				if ( AC==88 ) { AC=0; // X
				} else if ( AC==89 ) { AC=1; // Y
				} else if ( AC==65 ) { AC=2; // A
				}
				AM->NUMARGS[AM->CHAN][AM->N]++;
				AM->COMMAND[AM->CHAN][AM->N][(AM->STRINGARGNUM[AM->N][AM->NN])]=AC;
				AM->ARGTYPE[AM->CHAN][AM->N][(AM->STRINGARGNUM[AM->N][AM->NN])]=3; // Special AMAL Register
				AM->TEST=false;

				// Remove the string:
				if ( AM->NN<(AM->NUMSTRINGS[AM->CHAN][AM->N])-1 )
				{
					// Grab the last string:
					AM->strin[AM->CHAN][AM->N][AM->NN]=AM->strin[AM->CHAN][AM->N][(AM->NUMSTRINGS[AM->CHAN][AM->N])-1];
					AM->STRINGARGNUM[AM->N][AM->NN]=AM->STRINGARGNUM[AM->N][(AM->NUMSTRINGS[AM->CHAN][AM->N])-1];
					AM->NUMSTRINGS[AM->CHAN][AM->N]--;
					AM->NN--; // Check this string number again...
				}
				else
				{
					// At last string.
					AM->strin[AM->CHAN][AM->N][AM->NN]="";
					AM->NUMSTRINGS[AM->CHAN][AM->N]--;
				}
			}
			else // only- if temporary values have been added ??
			{
				if ( AC > 154 ) // Temporary value (added)...
				{
					//cout << "DEBUG: Temp value found!" << endl;
					AM->NUMARGS[AM->CHAN][AM->N]++;
					AM->COMMAND[AM->CHAN][AM->N][(AM->STRINGARGNUM[AM->N][AM->NN])]=AC-154;
					AM->ARGTYPE[AM->CHAN][AM->N][(AM->STRINGARGNUM[AM->N][AM->NN])]=4; // Temporary value...
					AM->TEST=false;

					// Remove the string:
					if ( AM->NN<AM->NUMSTRINGS[AM->CHAN][AM->N]-1 )
					{
						// Grab the last string:
						AM->strin[AM->CHAN][AM->N][AM->NN]=AM->strin[AM->CHAN][AM->N][(AM->NUMSTRINGS[AM->CHAN][AM->N])-1];
						AM->STRINGARGNUM[AM->N][AM->NN]=AM->STRINGARGNUM[AM->N][(AM->NUMSTRINGS[AM->CHAN][AM->N])-1];
						AM->NUMSTRINGS[AM->CHAN][AM->N]--;
						AM->NN--; // Check this string number again...
					}
					else
					{
						// At last string.
						AM->strin[AM->CHAN][AM->N][AM->NN]="";
						AM->NUMSTRINGS[AM->CHAN][AM->N]--;
					}
				}
			}
			break;
		case 2:
			// Expression length is 2
			v=AM->strin[AM->CHAN][AM->N][AM->NN];
			if ( AM->left(v,1)== ("R") )
			{
				VV=(int)(AM->mid(v,2,1)[0]);
				if ( VV>=65 && VV<=90 )
				{
					AM->NUMARGS[AM->CHAN][AM->N]++;
					AM->COMMAND[AM->CHAN][AM->N][(AM->STRINGARGNUM[AM->N][AM->NN])]=VV-65;
					AM->ARGTYPE[AM->CHAN][AM->N][(AM->STRINGARGNUM[AM->N][AM->NN])]=1; // Global/External AMAL Register..
					AM->TEST=false;

					// Remove the string:
					if ( AM->NN<AM->NUMSTRINGS[AM->CHAN][AM->N]-1 )
					{
						// Grab the last string:
						AM->strin[AM->CHAN][AM->N][AM->NN]=AM->strin[AM->CHAN][AM->N][(AM->NUMSTRINGS[AM->CHAN][AM->N])-1];
						AM->STRINGARGNUM[AM->N][AM->NN]=AM->STRINGARGNUM[AM->N][(AM->NUMSTRINGS[AM->CHAN][AM->N])-1];
						AM->NUMSTRINGS[AM->CHAN][AM->N]--;
						AM->NN--; // Check this string number again...
					}
					else
					{
						// At last string.
						AM->strin[AM->CHAN][AM->N][AM->NN]="";
						AM->NUMSTRINGS[AM->CHAN][AM->N]--;
					}
				}
				else if ( VV>=48 && VV<=57 )
				{
					AM->NUMARGS[AM->CHAN][AM->N]++;
					AM->COMMAND[AM->CHAN][AM->N][(AM->STRINGARGNUM[AM->N][AM->NN])]=VV - 48;
					AM->ARGTYPE[AM->CHAN][AM->N][(AM->STRINGARGNUM[AM->N][AM->NN])]=2; // Local/Internal AMAL Register..
					AM->TEST=false;

					// Remove the string:
					if ( AM->NN<AM->NUMSTRINGS[AM->CHAN][AM->N]-1 )
					{
						// Grab the last string:
						AM->strin[AM->CHAN][AM->N][AM->NN]=AM->strin[AM->CHAN][AM->N][(AM->NUMSTRINGS[AM->CHAN][AM->N])-1];
						AM->STRINGARGNUM[AM->N][AM->NN]=AM->STRINGARGNUM[AM->N][(AM->NUMSTRINGS[AM->CHAN][AM->N])-1];
						AM->NUMSTRINGS[AM->CHAN][AM->N]--;
						AM->NN--; // Check this string number again...
					}
					else
					{
						// At last string.
						AM->strin[AM->CHAN][AM->N][AM->NN]="";
						AM->NUMSTRINGS[AM->CHAN][AM->N]--;
					}
				}
				else
				{
					//stop(); // Illegal R. value...
				}
			}
		}

		// Now tested earlier:
		//if (AM->SLEN == 0)
		//	AM->TEST = false;

		if (AM->TEST == true)
		{
			bool NEWTEST = true;
			//cout << "DEBUG: Testing for constant numbers: " << AM->strin[AM->CHAN][AM->N][AM->NN] << endl;
			// For constant numbers:
			VV = 0;
			if ((AM->strin[AM->CHAN][AM->N][AM->NN]).length() == 0)
			{
			}
			else if ((AM->strin[AM->CHAN][AM->N][AM->NN])[0] == '$')
			{
				//cout << "The joy of HEX! 0x" << AM->strin[AM->CHAN][AM->N][AM->NN].substr(1, (AM->strin[AM->CHAN][AM->N][AM->NN]).length() - 1) << endl;

				if (((AM->strin[AM->CHAN][AM->N][AM->NN]).length() - 1) <= 1)
					VV = 0;
				else
					istringstream(AM->strin[AM->CHAN][AM->N][AM->NN].substr(1, (AM->strin[AM->CHAN][AM->N][AM->NN]).length() - 1)) >> hex >> VV;

				if (AM->hex(VV) != AM->strin[AM->CHAN][AM->N][AM->NN])
					NEWTEST = false;

				//cout << " = " + AM->stri(VV) << endl;
			}
			else if ((AM->strin[AM->CHAN][AM->N][AM->NN])[0] == '%')
			{
				// Added: Binary with %:
				if (((AM->strin[AM->CHAN][AM->N][AM->NN]).length() - 1) <= 1)
					VV = 0;
				else
					VV = AM->binstringtoint(AM->strin[AM->CHAN][AM->N][AM->NN].substr(1, (AM->strin[AM->CHAN][AM->N][AM->NN]).length() - 1));

				// To/from binary with %:
				if (AM->bin(VV) != AM->strin[AM->CHAN][AM->N][AM->NN])
					NEWTEST = false;
			}
			else
			{
				istringstream(AM->strin[AM->CHAN][AM->N][AM->NN]) >> dec >> VV;
				//istringstream(AM->strin[AM->CHAN][AM->N][AM->NN].substr(1, (AM->strin[AM->CHAN][AM->N][AM->NN]).length() - 1)) >> dec >> VV;

				// CPP - compare strings:
				if (AM->stri(VV) != AM->strin[AM->CHAN][AM->N][AM->NN])
					NEWTEST = false;
			}
			//VV = (int)(AM->strin[AM->CHAN][AM->N][AM->NN][0]);
			//cout << "DEBUG: Tested for constant numbers." << endl;
			

			v = "" + VV;
			//if ( VV==0 ) { v="0"; }
			//while ( AM->Left(v,1)== (" ") ) { v=AM->Right(v,v.length()-1); }

			// Debug:
			if (NEWTEST == false)
			{
				//cout << "DEBUG: Did not force constant number! Expression = " << AM->strin[AM->CHAN][AM->N][AM->NN] << ", Value = " << AM->stri(VV) << endl;
				//if (AM->TEST == false) cout << "WARNING! AM->TEST is false! Should be true!" << endl;
				// Debug - enable to disable expression parsing (crashes):
				//NEWTEST = true;
			}


			// if the string is a constant number:
			if ( NEWTEST ) // v == (AM->strin[AM->CHAN][AM->N][AM->NN]) )
			{
				//cout << "Constant number found! " << ("" + VV) << endl;
				AM->NUMARGS[AM->CHAN][AM->N]++;
				AM->COMMAND[AM->CHAN][AM->N][(AM->STRINGARGNUM[AM->N][AM->NN])] = VV;
				AM->ARGTYPE[AM->CHAN][AM->N][(AM->STRINGARGNUM[AM->N][AM->NN])] = 0; // A Constant Value
				//
				AM->TEST=false;

				// Remove the string:
				if ( AM->NN<AM->NUMSTRINGS[AM->CHAN][AM->N]-1 )
				{
					// Grab the last string:
					AM->strin[AM->CHAN][AM->N][AM->NN]=AM->strin[AM->CHAN][AM->N][(AM->NUMSTRINGS[AM->CHAN][AM->N])-1];
					AM->STRINGARGNUM[AM->N][AM->NN]=AM->STRINGARGNUM[AM->N][(AM->NUMSTRINGS[AM->CHAN][AM->N])-1];
					AM->NUMSTRINGS[AM->CHAN][AM->N]--;
					AM->NN--; // Check this string number again...
				}
				else
				{
					// At last string.
					AM->strin[AM->CHAN][AM->N][AM->NN]="";
					AM->NUMSTRINGS[AM->CHAN][AM->N]--;
				}
			}
		}
}

void AMALParser::OPERATORS()
{
		int OP1=0, OPTEST=0, OPTEST2=0;
		int M=0, MM=0, MMM=0, MMMM=0;
		int OPSCAN=1; // WHAT IS THE CORRECT SCOPE ???
		string optestchar = "";
		if ( AM->TEST==true )
		{
			//cout << "Debug: OPERATORS() running!" << endl;
			// Expression contains operators and/or functions...
			// Search for operators:

			// Search for first operator:
			OP1=0; OPTEST=0; OPTEST2=0;
			AM->BRSTACK=0;
			while ( OPSCAN<=AM->SLEN && OPTEST==0 )
			{
				optestchar=AM->mid(AM->strin[AM->CHAN][AM->N][AM->NN],OPSCAN,1);

				if ( AM->BRSTACK==0 )
				{
					switch ( (int)optestchar[0] ) { case '+': OPTEST=1;
					break; case '-': OPTEST=2;
					break; case '*': OPTEST=3;
					break; case '/': OPTEST=4;
					break; case '=': OPTEST=5;
					break; case '>': OPTEST=6;
					break; case '<': OPTEST=7;
					// Also for <> ...
					break; case '&': OPTEST=9;
					break; case '|': OPTEST=10;
					break;
					case '(':
						AM->BRSTACK++; OPSCAN++;
						break;
					case ')':
						AM->BRSTACK--; OPSCAN++;
						break;
					default:
						OPSCAN++;
					}
					//cout << "********** OPTEST=" << AM->stri(OPTEST) << endl;
				} else {
					switch ( (int)optestchar[0] ) {
					case '(': AM->BRSTACK++;
					break; case ')': AM->BRSTACK--;
					}
					OPSCAN++;
				}
			}

			if ( OPTEST>0 ) // An operator is found...
			{
				AM->TEST=false;

				if ( OPTEST==7 )
				{
					// Change <> to one digit:
					if ( AM->mid(AM->strin[AM->CHAN][AM->N][AM->NN],OPSCAN+1,1) == (">") )
					{
						OPTEST=8;
						//cout << "AM->Right(" << AM->strin[AM->CHAN][AM->N][AM->NN] << ", " << AM->stri(AM->strin[AM->CHAN][AM->N][AM->NN].length()-OPSCAN-1) << ")" << endl;
						AM->strin[AM->CHAN][AM->N][AM->NN]=AM->left(AM->strin[AM->CHAN][AM->N][AM->NN],OPSCAN)+AM->right(AM->strin[AM->CHAN][AM->N][AM->NN], (AM->strin[AM->CHAN][AM->N][AM->NN].length())-OPSCAN-1);
						AM->SLEN--; // Added - fix!
						//cout << "SUCCESS! " << AM->strin[AM->CHAN][AM->N][AM->NN] << endl;
					}
				}
				// Search for second operator (if any):
				// Result in OPSCAN (not OP2)
				OP1=OPSCAN;
				OPTEST2=0;
				OPSCAN+=2;
				while ( OPSCAN<=AM->SLEN && OPTEST2==0 )
				{
					//cout << "Stuck in this loop for 'Let X = X <> Y'! OPSCAN = "+AM->stri(OPSCAN)+"; AM->SLEN = "+AM->stri(AM->SLEN) << endl;

					optestchar=AM->mid(AM->strin[AM->CHAN][AM->N][AM->NN],OPSCAN,1);
					//cout << "FAIL? :"  << AM->mid(AM->strin[AM->CHAN][AM->N][AM->NN],OPSCAN,1) << ":" << endl;

					if (optestchar.length() > 0) { if (AM->BRSTACK==0)
					{
						switch ( (int)optestchar[0] ) {
						case '+': OPTEST2=1;
						break; case '-': OPTEST2=2;
						break; case '*': OPTEST2=3;
						break; case '/': OPTEST2=4;
						break; case '=': OPTEST2=5;
						break; case '>': OPTEST2=6;
						break; case '<': OPTEST2=7;
						// Also for <> ...
						break; case '&': OPTEST2=9;
						break; case '|': OPTEST2=10;
						break;
						case '(':
							AM->BRSTACK++; OPSCAN++;
							break;
						case ')':
							AM->BRSTACK--; OPSCAN++;
							break;
						default:
							OPSCAN++;
						}
						//cout << "********** OPTEST2=" << AM->stri(OPTEST2) << endl;
					} else {
						switch ( (int)optestchar[0] ) {
						case '(': AM->BRSTACK++;
						break; case ')': AM->BRSTACK--;
						}
						OPSCAN++;
					} }
				}

				if ( OPTEST2==7 )
				{
					// Change <> to one digit:
					if ( AM->mid(AM->strin[AM->CHAN][AM->N][AM->NN],OPSCAN+1,1) == (">") )
					{
						OPTEST2=8;
						AM->strin[AM->CHAN][AM->N][AM->NN]=AM->left(AM->strin[AM->CHAN][AM->N][AM->NN],OPSCAN)+AM->right(AM->strin[AM->CHAN][AM->N][AM->NN],AM->strin[AM->CHAN][AM->N][AM->NN].length()-OPSCAN-1);
						AM->SLEN--; // Added - fix!
					}
				}

				// Insert a Temp=Operator(a,b)... before line N:

				// MMM is Instruction, NOT Line, Number...
				// Find It:
				for ( MMM=0; MMM <= AM->NUMINSTRUCTIONS[AM->CHAN] - 1; MMM++ )
				{
					// 'Exit' works differently as 'break'??
					if ( AM->INSTRLINENUM[AM->CHAN][MMM]<=AM->N && (AM->INSTRLINENUM[AM->CHAN][MMM+1]>=AM->N || MMM==AM->NUMINSTRUCTIONS[AM->CHAN]-1) )
					{
						break;
					}
				}
				// 'MMM is Instruction, NOT Line, Number...
				// 'Find It:
				// 'Instruction number <= Line number
				// 'Thus start at Line number and work down...
				// MMM=N+1
				// Repeat
				//   Dec MMM
				//   If MMM<0 : Stop : End If
				// Until AM->INSTRLINENUM(AM->CHAN,MMM)=N

				// Then, move everything DOWN a line: (Insert a line)

				for ( M=AM->NUMLINES[AM->CHAN]-1; (M>=AM->NUMLINES[AM->CHAN]-1 && M<= AM->N)||(M<=AM->NUMLINES[AM->CHAN]-1 && M>= AM->N); M+=-1 )
				{
					for ( MM=0; MM <= AM->NUMSTRINGS[AM->CHAN][M]-1; MM++ ) // AM->TOPARGNUM(M)
					{
						if ( AM->NUMSTRINGS[AM->CHAN][M]>0 )
						{
							AM->strin[AM->CHAN][M+1][MM]=AM->strin[AM->CHAN][M][MM];
							AM->STRINGARGNUM[M+1][MM]=AM->STRINGARGNUM[M][MM];
						}
					}
					AM->COMMAND[AM->CHAN][M+1][0]=AM->COMMAND[AM->CHAN][M][0];
					for ( MM=1; MM <= AM->TOPARGNUM[M]; MM++ )
					{
						AM->COMMAND[AM->CHAN][M+1][MM]=AM->COMMAND[AM->CHAN][M][MM];
						AM->ARGTYPE[AM->CHAN][M+1][MM]=AM->ARGTYPE[AM->CHAN][M][MM];
					}
					AM->NUMSTRINGS[AM->CHAN][M+1]=AM->NUMSTRINGS[AM->CHAN][M];
					AM->NUMARGS[AM->CHAN][M+1]=AM->NUMARGS[AM->CHAN][M];
					AM->TOPARGNUM[M+1]=AM->TOPARGNUM[M];
				}

				AM->TEMPCOUNT[MMM]++;

				// Move the Starting LINE NUMBERS of following (NOT inclusive)
				// Amal INSTRUCTIONS
				// down by 1 (Add 1 to AM->INSTRLINENUM(AM->CHAN,MMMM) )...
				if ( MMM<AM->NUMINSTRUCTIONS[AM->CHAN]-1 )
				{
					for ( MMMM=MMM+1; MMMM <= AM->NUMINSTRUCTIONS[AM->CHAN]-1; MMMM++ )
					{
						AM->INSTRLINENUM[AM->CHAN][MMMM]++;
					}
				}

				AM->COMMAND[AM->CHAN][AM->N][0] = 15 + OPTEST; // Which Operator as instruction...
				AM->COMMAND[AM->CHAN][AM->N][3] = AM->TEMPCOUNT[MMM];
				AM->ARGTYPE[AM->CHAN][AM->N][3] = 0; // Always just a constant...

				AM->NUMARGS[AM->CHAN][AM->N] = 1;
				AM->NUMSTRINGS[AM->CHAN][AM->N] = 2;
				AM->TOPARGNUM[AM->N] = 3;
				AM->strin[AM->CHAN][AM->N][0] = AM->left(AM->strin[AM->CHAN][AM->N+1][AM->NN], OP1 - 1);
				AM->STRINGARGNUM[AM->N][0]=1;
				AM->strin[AM->CHAN][AM->N][1] = AM->mid(AM->strin[AM->CHAN][AM->N+1][AM->NN],OP1+1,OPSCAN-OP1-1);
				AM->STRINGARGNUM[AM->N][1]=2;

				// Initialize other argument values (strings to start with):
				AM->COMMAND[AM->CHAN][AM->N][1]=0; AM->COMMAND[AM->CHAN][AM->N][2]=0;
				AM->ARGTYPE[AM->CHAN][AM->N][1]=0; AM->ARGTYPE[AM->CHAN][AM->N][2]=0;

				AM->NUMLINES[AM->CHAN]++;
				AM->N++;
				// To end of string.
				AM->strin[AM->CHAN][AM->N][AM->NN]="" + AM->chr(154+AM->TEMPCOUNT[MMM]) + AM->mid(AM->strin[AM->CHAN][AM->N][AM->NN],OPSCAN);
				//AM->strin[AM->CHAN][AM->N][AM->NN]="" + ((char)(154+AM->TEMPCOUNT[MMM])) + AM->mid(AM->strin[AM->CHAN][AM->N][AM->NN],OPSCAN);
			}
		}
}

void AMALParser::SCANFUNCTIONS()
{
		AM->FOUNDFUNCTION=0;
		int M, MM, MMM, MMMM, OP1;
		string l1, l2;
		if ( AM->TEST==true )
		{
			//cout << "DEBUG: Scanning for functions..." << endl;
			// No operators, expression thus contains a function:

			// Scan for functions:
			l1=AM->mid(AM->strin[AM->CHAN][AM->N][AM->NN],1,1);
			l2=AM->mid(AM->strin[AM->CHAN][AM->N][AM->NN],1,2);

			if ( l2 == ("XM") )
				AM->FOUNDFUNCTION=26;
			else if ( l2 == ("YM") )
				AM->FOUNDFUNCTION=27;
			else if ( l2 == ("J0") )
				AM->FOUNDFUNCTION=28;
			else if ( l2 == ("J1") )
				AM->FOUNDFUNCTION=29;
			else if ( l2 == ("K1") )
				AM->FOUNDFUNCTION=30;
			else if ( l2 == ("K2") )
				AM->FOUNDFUNCTION=31;
			else if ( l2 == ("XS") )
				AM->FOUNDFUNCTION=32;
			else if ( l2 == ("YS") )
				AM->FOUNDFUNCTION=33;
			else if ( l2 == ("XH") )
				AM->FOUNDFUNCTION=34;
			else if ( l2 == ("YH") )
				AM->FOUNDFUNCTION=35;
			else if ( l2 == ("BC") )
				AM->FOUNDFUNCTION=36;
			else if ( l2 == ("SC") )
				AM->FOUNDFUNCTION=37;
			else if ( l2 == ("VU") )
				AM->FOUNDFUNCTION=38;
			else if ( l1 == ("C") )
				AM->FOUNDFUNCTION=39;
			else if ( l1 == ("Z") )
				AM->FOUNDFUNCTION=40;


			//cout << "Debug: l2 == \"" << l2 << "\", AM->FOUNDFUNCTION == " << AM->stri(AM->FOUNDFUNCTION) << endl;
			if ( AM->FOUNDFUNCTION>0 )
			{
				//cout << "Debug: AMAL Function found!" << endl;

				// Insert a Temp=Function(a,b)... before line N:

				// MMM is Instruction, NOT Line, Number...
				// Find It:
				for ( MMM=0; MMM <= AM->NUMINSTRUCTIONS[AM->CHAN]-1; MMM++ )
				{
					// 'Exit' works differently as 'Break'??
					if ( (AM->INSTRLINENUM[AM->CHAN][MMM] <= (AM->N)) && (((AM->INSTRLINENUM[AM->CHAN][MMM+1]) >= (AM->N)) || (MMM == (AM->NUMINSTRUCTIONS[AM->CHAN]-1))) )
					{
						break;
					}
				}

				// Then, move everything DOWN a line: (Insert a line)

				for ( M=AM->NUMLINES[AM->CHAN]-1; (M>=AM->NUMLINES[AM->CHAN]-1 && (M<=(AM->N)))||(M<=(AM->NUMLINES[AM->CHAN]-1) && (M>=(AM->N))); M+=-1 )
				{
					for ( MM=0; MM<=(AM->NUMSTRINGS[AM->CHAN][M]-1); MM++ ) // AM->TOPARGNUM(M)
					{
						if ((AM->NUMSTRINGS[AM->CHAN][M])>0 )
						{
							AM->strin[AM->CHAN][M+1][MM]=AM->strin[AM->CHAN][M][MM];
							AM->STRINGARGNUM[M+1][MM]=AM->STRINGARGNUM[M][MM];
						}
					}
					AM->COMMAND[AM->CHAN][M+1][0]=AM->COMMAND[AM->CHAN][M][0];
					for ( MM=1; MM <= AM->TOPARGNUM[M]; MM++ )
					{
						AM->COMMAND[AM->CHAN][M+1][MM]=AM->COMMAND[AM->CHAN][M][MM];
						AM->ARGTYPE[AM->CHAN][M+1][MM]=AM->ARGTYPE[AM->CHAN][M][MM];
					}
					AM->NUMSTRINGS[AM->CHAN][M+1]=AM->NUMSTRINGS[AM->CHAN][M];
					AM->NUMARGS[AM->CHAN][M+1]=AM->NUMARGS[AM->CHAN][M];
					AM->TOPARGNUM[M+1]=AM->TOPARGNUM[M];
				}

				AM->TEMPCOUNT[MMM]++;

				// Move the Starting LINE NUMBERS of following (NOT inclusive)
				// (given) Amal INSTRUCTIONS
				// down by 1 (Add 1 to AM->INSTRLINENUM(AM->CHAN,MMMM) )...
				if ( MMM<AM->NUMINSTRUCTIONS[AM->CHAN]-1 )
				{
					for ( MMMM=MMM+1; MMMM<=AM->NUMINSTRUCTIONS[AM->CHAN]-1; MMMM++ )
					{
						AM->INSTRLINENUM[AM->CHAN][MMMM]++;
					}
				}

				AM->COMMAND[AM->CHAN][AM->N][0]=AM->FOUNDFUNCTION; // Which Amal FUNCTION...


				if ( AM->FOUNDFUNCTION<=31 )
				{
					// Functions are 2 characters only
					if ( AM->strin[AM->CHAN][AM->N+1][AM->NN].length()!=2 ) { } //exit(1); } //A_Bell(); Stop; }
					AM->NUMSTRINGS[AM->CHAN][AM->N]=0;
					AM->NUMARGS[AM->CHAN][AM->N]=1;
					AM->TOPARGNUM[AM->N]=1;
					AM->COMMAND[AM->CHAN][AM->N][1]=AM->TEMPCOUNT[MMM];
					AM->ARGTYPE[AM->CHAN][AM->N][1]=0; // Always just a constant...
				}
				else
				{
					// Function has brackets:
					OP1=AM->instr(AM->strin[AM->CHAN][AM->N+1][AM->NN],"(");

					//cout << "Searching for opening bracket, found at " << AM->stri(OP1) << endl;

					// Added for Z (no brackets):
					if (AM->FOUNDFUNCTION == 40 && OP1==0)
					{
						cout << "Z without brackets to do!\n" << endl;
						AM->NUMSTRINGS[AM->CHAN][AM->N]=0;
						AM->NUMARGS[AM->CHAN][AM->N]=1;
						AM->TOPARGNUM[AM->N]=1;
						AM->COMMAND[AM->CHAN][AM->N][1]=AM->TEMPCOUNT[MMM];
						AM->ARGTYPE[AM->CHAN][AM->N][1]=-1; // flag! // Always just a constant...
					}
					else
					{
						AM->strin[AM->CHAN][AM->N][0]=AM->mid(AM->strin[AM->CHAN][AM->N+1][AM->NN],OP1+1,(AM->strin[AM->CHAN][AM->N+1][AM->NN]).length()-OP1-1);
						AM->NUMARGS[AM->CHAN][AM->N]=0;
						AM->TOPARGNUM[AM->N]=1; AM->NUMSTRINGS[AM->CHAN][AM->N]=1; AM->STRINGARGNUM[AM->N][0]=1;

						//cout << "AM->strin[AM->CHAN][AM->N][0] = " << AM->strin[AM->CHAN][AM->N][0] << ", AM->CHAN=" << AM->stri(AM->CHAN)+" << AM->N=" << AM->stri(AM->N) << endl;

						// Search for any commas:
						AM->RESULT = SEARCHCOMMA(AM->strin[AM->CHAN][AM->N][0],",",1);
						bool onemoretime = false;
						while ( AM->RESULT>0 || onemoretime)
						{
							//cout << "DEBUG: Z test!" << endl;
							// TODO!
							AM->strin[AM->CHAN][AM->N][(AM->NUMSTRINGS[AM->CHAN][AM->N])]=AM->strin[AM->CHAN][AM->N][((AM->NUMSTRINGS[AM->CHAN][AM->N])-1)].substr(AM->RESULT, (AM->strin[AM->CHAN][AM->N][((AM->NUMSTRINGS[AM->CHAN][AM->N])-1)].length()) - AM->RESULT);
							//cout << "DEBUG: Z test substr done!" << endl;

							AM->STRINGARGNUM[AM->N][(AM->NUMSTRINGS[AM->CHAN][AM->N])]=(AM->NUMSTRINGS[AM->CHAN][AM->N])+1;

							/*AM->strin[AM->CHAN][AM->N][(AM->NUMSTRINGS[AM->CHAN][AM->N])]=AM->mid(AM->strin[AM->CHAN][AM->N][((AM->NUMSTRINGS[AM->CHAN][AM->N])-1)],(AM->RESULT)+1);
							cout << "#" << AM->strin[AM->CHAN][AM->N][(AM->NUMSTRINGS[AM->CHAN][AM->N])] << "#" << endl;
							AM->STRINGARGNUM[AM->N][(AM->NUMSTRINGS[AM->CHAN][AM->N])]=(AM->NUMSTRINGS[AM->CHAN][AM->N])+1;*/

							//string remainder = AM->strin[AM->CHAN][AM->N][((AM->NUMSTRINGS[AM->CHAN][AM->N])-1)].substr(AM->RESULT, AM->strin[AM->CHAN][AM->N][((AM->NUMSTRINGS[AM->CHAN][AM->N])-1)].length() - AM->RESULT); //,(AM->RESULT)+1);

							//cout << "Args: #" << AM->strin[AM->CHAN][AM->N][(AM->NUMSTRINGS[AM->CHAN][AM->N])-1] << "#" << endl;
							AM->strin[AM->CHAN][AM->N][(AM->NUMSTRINGS[AM->CHAN][AM->N])-1]=AM->left(AM->strin[AM->CHAN][AM->N][((AM->NUMSTRINGS[AM->CHAN][AM->N])-1)],(AM->RESULT)-1);
							//cout << "First arg: #" << AM->strin[AM->CHAN][AM->N][(AM->NUMSTRINGS[AM->CHAN][AM->N])-1] << "#" << endl;
							//cout << "Remainder: #" << remainder << "#" << endl;
							AM->NUMSTRINGS[AM->CHAN][AM->N]++; AM->TOPARGNUM[AM->N]++;

							// Initialize other argument values (strings to start with):
							AM->COMMAND[AM->CHAN][AM->N][(AM->NUMSTRINGS[AM->CHAN][AM->N])]=0;
							AM->ARGTYPE[AM->CHAN][AM->N][(AM->NUMSTRINGS[AM->CHAN][AM->N])]=0;

							//int oldresult = AM->RESULT;

							// This line seems to fail! Returns zero OR infinite loop?
							//AM->RESULT = SEARCHCOMMA(AM->strin[AM->CHAN][AM->N][(AM->NUMSTRINGS[AM->CHAN][AM->N])-0],",",AM->RESULT);
							//cout << "comma 1: " << AM->stri(AM->RESULT) << endl;

							//AM->RESULT = SEARCHCOMMA(AM->strin[AM->CHAN][AM->N][(AM->NUMSTRINGS[AM->CHAN][AM->N])-1],",",AM->RESULT-1);
							//cout << "ADDED! The next arg: #" << AM->strin[AM->CHAN][AM->N][((AM->NUMSTRINGS[AM->CHAN][AM->N])-1)] << "#" << endl;


							AM->RESULT = SEARCHCOMMA(AM->strin[AM->CHAN][AM->N][(AM->NUMSTRINGS[AM->CHAN][AM->N])-1],",",AM->RESULT);

							//if (AM->RESULT == 0)
							//{
							//cout << "ADDED! The next bit: #" << AM->mid(AM->strin[AM->CHAN][AM->N][((AM->NUMSTRINGS[AM->CHAN][AM->N])-1)],(AM->RESULT)+1) << "#" << endl;
							//}

							// Added:
							//if (AM->RESULT == 0)
							//	AM->RESULT = SEARCHCOMMA(AM->strin[AM->CHAN][AM->N][(AM->NUMSTRINGS[AM->CHAN][AM->N])-1],")",oldresult);

							//cout << "comma 2: " << AM->stri(AM->RESULT) << endl;
							//cout << "Prepare to mess up!" << endl;
							/*if ((AM->RESULT == 0) && (onemoretime == false))
								onemoretime = true;
							else
								onemoretime = false;*/
						}

						// Add the Temp number last..
						AM->NUMARGS[AM->CHAN][AM->N]++; AM->TOPARGNUM[AM->N]++;
						AM->COMMAND[AM->CHAN][AM->N][(AM->TOPARGNUM[AM->N])]=AM->TEMPCOUNT[MMM];
						AM->ARGTYPE[AM->CHAN][AM->N][(AM->TOPARGNUM[AM->N])]=0; // Always just a constant...
					}
				}

				AM->NUMLINES[AM->CHAN]++;
				AM->N++;

				AM->strin[AM->CHAN][AM->N][AM->NN] = ""+AM->chr(154+AM->TEMPCOUNT[MMM]);
				//AM->strin[AM->CHAN][AM->N][AM->NN] = ""+((char)(154+AM->TEMPCOUNT[MMM]));
			}
			else
			{
				//A_Bell(); A_Boom();
			}
		}
}

int AMALParser::SEARCHCOMMA(string p1, string p2, int P3)
{
	// e.g. p1 is AM->tokest, p2 is ","
	// Search for p2 (e.g. comma), outside of any following brackets:
	AM->RESULT = AM->instr(p1, p2, P3);
	int OBR = AM->instr(p1, "(", P3);

	if ( (OBR>0) && (OBR<AM->RESULT) )
	{
		AM->BRSTACK = 1;
		while ( AM->BRSTACK > 0 && OBR < (int)(p1.length()) )
		{
			int OBR2 = AM->instr(p1, ")", OBR+1);
			OBR = AM->instr(p1, "(", OBR+1);
			// If next '(' before ')'
			if ((OBR>0) && (OBR<OBR2))
			{
				AM->BRSTACK++;
				// OBR = OBR;
			}
			else
			{
				AM->BRSTACK--;
				OBR = OBR2;
			}
		}
		if (OBR == 0)
		{
			AM->RESULT = 0;
		}
		else
		{
			AM->RESULT = AM->instr(p1, p2, OBR);
		}
	}
	return AM->RESULT;
}


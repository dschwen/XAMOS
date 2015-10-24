#include "AMOS_System.h"

// For tolower/toupper:
#include <algorithm>

// For atof:
#include <stdlib.h>

// For sin, cos, tan, asin, acos, atan:
#include <math.h>

// For seeding random numbers:
#include <time.h>

#define PI 3.14159265

#include <iostream>
#include <sstream>


// Constructor function:
AMOS_System::AMOS_System() //jAMOS mygamei)
{
	Mode=0; Fullscreen=0; ThreeDee=0; Scale=1; NumBobCols=0; LastBobTested=0; PenColor=0; PaperColor=0; currentScreen=0;
	_degree=false; MouseState=0; MouseClickState=0; Bobcolled=true; File=0; tim=0; Timer=0; CodeInput1=10; CodeInput2=-1;
	_ink=2; _paper=0; CHAN=0; TOPCHANNEL=0; oWorld=0; oCamera=0; KeyTimeLag=3; KeyDelaySpeed=30; RunningAdvancedScreenUpdate=false;
	thetm=0; UpdateSpeed=20; AutoUpdate=1; NumZones=0; MouseSprite=1; MouseDisplayed=true; MouseImageUsed=1;
	AmalSynchro = false;

	currentScreen=0; // added

	AM = this;
	//ma = mygamei; //TODO-CPP
	////wrapper = ma.wrapper;
	//wrapper = jAMOS.wrapper; //TODO-CPP // Needed for static type
		
	// Moved:
	OPTIMISE = false; // TODO - allow this to be set elsewhere?

	interpreterrunning = false;
	runningcompiled = false;
	pedantic = 1;

	// Not needed in C++ - vector is already initialised:
	//loadedimages = new vector<string>(); // loadedimages removed in CPP!
	//loadedspriteimages = new vector<string>();
	//currentspriteimages = new vector<string>();

	// Is this needed here?
	g = new Game();
	parser = new Parser(g, OPTIMISE);
	interpreter = new Interpreter(g, this);
	dumper = new Dumper(g);

	// Removed in C++ - from Java:
	// Added: Load audio clips:
	//ma.defineAudioClip("bell", "resources/bell.wav");
	//ma.defineAudioClip("boom", "resources/boom.wav");
	//ma.defineAudioClip("shoot", "resources/shoot.wav");
	//ma.defineAudioClip("java", "resources/java.wav");
	//ma.defineAudioClip("stripped", "resources/stripped.wav");

	// Set the random seed:
#if defined(__AROS_)
	srandom(time(NULL));
#else
	srand(time(NULL));
#endif

	// Initialise the arrays here...
	Init();
}

void AMOS_System::Init()
{
	// Removed in C++ - from Java:
	//randomgenerator = new Random();

	// XAMAL:
	amallexer = new AMALParser(this);
	amalinterpreter = new AMALInterpreter(this);
	amalcompiler = new AMALCompiler(this);
	amalbank = new AMALBank(this);
	envGen = new AMALEnvGen(this);

        AMAL_Init();
}

void AMOS_System::AMAL_Init()
{
	// For tokenizer:
	// TODO!
	//commandlist = new string[100]; // Initialise these string arrays!
	//NUMLINES=new int[100]; NUMINSTRUCTIONS=new int[100]; TEMPCOUNT=new int[100]; // int arrays
	//INSTRLINENUM = new int[100][100]; // int multi-array
	//EXISTS = new bool[8]; // New. // boolean array

	// Initialise size of vectors in C++:
	commandlist.clear(); NUMLINES.clear(); NUMINSTRUCTIONS.clear(); TEMPCOUNT.clear();

	for (int n=0; n<100; n++)
	{
		commandlist.push_back("");
		NUMLINES.push_back(0); NUMINSTRUCTIONS.push_back(0); TEMPCOUNT.push_back(0);
	}

	// Moved - done later:
	//EXISTS.clear();
	//for (int n=0; n<100; n++) // was 8
	//{
	//	EXISTS.push_back(0);
	//}

	// INSTRLINENUM is initialised slightly later.

	_input=""; // needs to be Global?
	N=0; NN=0;
	tokest="";
	SCANFROM=0; FOUNDINSTRUCTION=0; FOUNDFUNCTION=0;
	RESULT=0; TEST=false; SLEN=0; NEST=0;
	BRSTACK=0;

	// for AMAL compiler:
	caseon = 0;

	// for AMAL interpreter:

	// TODO! EXTREMELY memory inefficient in current implementation (over 12MB used)!

	//LOCAL=new int[100][100]; GLOBAL=new int[100]; SPECIAL=new int[100][100]; //TEMP=0; ARG=0;
	//PROGPOINTER=new int[100]; AUTOTESTSTART=new int[100]; AUTOTESTEND=new int[100];
	//RUNNINGAUTOTEST=new bool[100];
	//MAINPROGDEPPOINT=new int[100];
	//SETCHANNEL=new int[100]; TYPECHANNEL=new int[100]; EXISTS=new bool[100];
	//FROZEN=new bool[100]; PROGNOTFINISHED=new bool[100];
	//NUMSTRINGS=new int[100][100];
	//STRINGARGNUM = new int[100][100];
	//NUMARGS = new int[100][100];
	//ARGTYPE = new int[100][100][100];
	//strin = new string[100][100][100];
	//COMMAND = new int[100][100][100];
	//TOPARGNUM = new int[100];
	//NESTINSTRNUM = new int[100];
	//LABELS = new int[100][100];
	//ARG = new int[100][100];
	//arg = new string[100][100];
	//temp = new string[100][100];
	//TEMP = new int[100][100];
	//argtypename = new string[100];

	// For now - initialise C++ vectors in advance. Optimise later for memory usage and more AMAL channels.

	myGLOBAL.clear(); PROGPOINTER.clear(); AUTOTESTSTART.clear(); AUTOTESTEND.clear(); RUNNINGAUTOTEST.clear();
	MAINPROGDEPPOINT.clear(); SETCHANNEL.clear(); TYPECHANNEL.clear(); EXISTS.clear(); FROZEN.clear();
	PROGNOTFINISHED.clear(); TOPARGNUM.clear(); NESTINSTRNUM.clear(); argtypename.clear();

	for (int n=0; n<100; n++)
	{
		myGLOBAL.push_back(0);
		PROGPOINTER.push_back(0);
		AUTOTESTSTART.push_back(0);
		AUTOTESTEND.push_back(0);
		RUNNINGAUTOTEST.push_back(0);
		MAINPROGDEPPOINT.push_back(0);
		SETCHANNEL.push_back(0); TYPECHANNEL.push_back(0); EXISTS.push_back(0);
		FROZEN.push_back(0); PROGNOTFINISHED.push_back(0);
		TOPARGNUM.push_back(0);
		NESTINSTRNUM.push_back(0);
		argtypename.push_back("");
	}

	// TODO: ARGTYPE(!!!), strin(!!!), COMMAND(!!!)

	// First destroy 2-dimensional vectors here:
	for (unsigned int n=0; n<LOCAL.size(); n++) { LOCAL[n].clear(); } LOCAL.clear();
	for (unsigned int n=0; n<SPECIAL.size(); n++) { SPECIAL[n].clear(); } SPECIAL.clear();
	for (unsigned int n=0; n<NUMSTRINGS.size(); n++) { NUMSTRINGS[n].clear(); } NUMSTRINGS.clear();
	for (unsigned int n=0; n<STRINGARGNUM.size(); n++) { STRINGARGNUM[n].clear(); } STRINGARGNUM.clear();
	for (unsigned int n=0; n<NUMARGS.size(); n++) { NUMARGS[n].clear(); } NUMARGS.clear();
	for (unsigned int n=0; n<LABELS.size(); n++) { LABELS[n].clear(); } LABELS.clear();
	for (unsigned int n=0; n<ARG.size(); n++) { ARG[n].clear(); } ARG.clear();
	for (unsigned int n=0; n<arg.size(); n++) { arg[n].clear(); } arg.clear();
	for (unsigned int n=0; n<temp.size(); n++) { temp[n].clear(); } temp.clear();
	for (unsigned int n=0; n<TEMP.size(); n++) { TEMP[n].clear(); } TEMP.clear();
	for (unsigned int n=0; n<INSTRLINENUM.size(); n++) { INSTRLINENUM[n].clear(); } INSTRLINENUM.clear();

	// TODO - AMAL-specific - optimise for memory usage...
#if 1
	// Now build 2-dimensional vectors:
	for (int n=0; n<100; n++)
	{
		LOCAL.push_back(vector<int>());
		SPECIAL.push_back(vector<int>());
		NUMSTRINGS.push_back(vector<int>());
		STRINGARGNUM.push_back(vector<int>());
		NUMARGS.push_back(vector<int>());
		LABELS.push_back(vector<int>());
		ARG.push_back(vector<int>());
		arg.push_back(vector<string>());
		temp.push_back(vector<string>());
		TEMP.push_back(vector<int>());
		INSTRLINENUM.push_back(vector<int>());
		for (int nn=0; nn<100; nn++)
		{
			LOCAL[n].push_back(0);
			SPECIAL[n].push_back(0);
			NUMSTRINGS[n].push_back(0);
			STRINGARGNUM[n].push_back(0);
			NUMARGS[n].push_back(0);
			LABELS[n].push_back(0);
			ARG[n].push_back(0);
			arg[n].push_back("");
			temp[n].push_back("");
			TEMP[n].push_back(0);
			INSTRLINENUM[n].push_back(0);
		}
	}

	// First destroy 3-dimensional vectors here:
	for (unsigned int n=0; n<ARGTYPE.size(); n++) {
		for (unsigned int nn=0; nn<ARGTYPE[n].size(); nn++) ARGTYPE[n][nn].clear();
		ARGTYPE[n].clear();
	}
	ARGTYPE.clear();
	for (unsigned int n=0; n<strin.size(); n++) {
		for (unsigned int nn=0; nn<strin[n].size(); nn++) strin[n][nn].clear();
		strin[n].clear();
	}
	strin.clear();
	for (unsigned int n=0; n<COMMAND.size(); n++) {
		for (unsigned int nn=0; nn<COMMAND[n].size(); nn++) COMMAND[n][nn].clear();
		COMMAND[n].clear();
	}
	COMMAND.clear();

	// Now build 3-dimensional vectors (TODO - this is extremely memory inefficient!!!):
	for (int n=0; n<100; n++)
	{
		ARGTYPE.push_back(vector< vector<int> >());
		strin.push_back(vector< vector<string> >());
		COMMAND.push_back(vector< vector<int> >());
		for (int nn=0; nn<100; nn++)
		{
			ARGTYPE[n].push_back(vector<int>());
			strin[n].push_back(vector<string>());
			COMMAND[n].push_back(vector<int>());
			for (int nnn=0; nnn<100; nnn++)
			{
				ARGTYPE[n][nn].push_back(0);
				strin[n][nn].push_back("");
				COMMAND[n][nn].push_back(0);
			}
		}
	}
#endif

	PAUSED=0; /* FALSE */ CHAN=0; TOPCHANNEL=0;
	DEBUGMODE = 0; // debug the AMAL interpreter
	LOGICTRUE = -1; // for AMOS

	// New:
	//ScreenWidth = new int[100];
	//ScreenHeight = new int[100];
	//ScreenColors = new int[100];
	//ScreenRes = new int[100];
	//ScreenOffsetX = new int[100];
	//ScreenOffsetY = new int[100];
	//ScreenDisplayX = new int[100];
	//ScreenDisplayY = new int[100];
	//ScreenDisplayWidth=new int[100];
    	//ScreenDisplayHeight=new int[100];

	// TO DO - Cursor:
        //ScreenXCur = new int[100];
        //ScreenYCur = new int[100];
        // Perhaps clear/initialise these arrays here.

	ScreenWidth.clear(); ScreenHeight.clear(); ScreenColors.clear(); ScreenRes.clear();
	ScreenOffsetX.clear(); ScreenOffsetY.clear(); ScreenDisplayX.clear(); ScreenDisplayY.clear();
	ScreenDisplayWidth.clear(); ScreenDisplayHeight.clear(); ScreenXCur.clear(); ScreenYCur.clear();

	for (int n=0; n<100; n++)
	{
		ScreenWidth.push_back(0);
		ScreenHeight.push_back(0);
		ScreenColors.push_back(0);
		ScreenRes.push_back(0);
		ScreenOffsetX.push_back(0);
		ScreenOffsetY.push_back(0);
		ScreenDisplayX.push_back(0);
		ScreenDisplayY.push_back(0);
		ScreenDisplayWidth.push_back(0);
		ScreenDisplayHeight.push_back(0);

		ScreenXCur.push_back(0);
		ScreenYCur.push_back(0);
	}
        
        // New:
	//BobX=new int[2000];
	//BobY=new int[2000];
	//BobImage=new int[2000];

	BobX.clear(); BobY.clear(); BobImage.clear();
	SpriteX.clear(); SpriteY.clear(); SpriteImage.clear();

	for (int n=0; n<100; n++)
	{
		BobX.push_back(0);
		BobY.push_back(0);
		BobImage.push_back(0);
		SpriteX.push_back(0);
		SpriteY.push_back(0);
		SpriteImage.push_back(0);
	}


	for ( int T=0; T<= 25; T++ )
		myGLOBAL[T]=0; // Clear all globals

	//// TYPECHANNEL[channel]=
	// 0: To Sprite (default)
	// 1: To Bob
	// 2: To Screen Display
	// 3: To Screen Offset
	// 4: To Screen Size
	// 5: To Rainbow
	// Set the channels (to default):
	for (int NUM=0; NUM<100; NUM++)
	{
		SETCHANNEL[NUM]=NUM;
		TYPECHANNEL[NUM]=0;
		EXISTS[NUM]=0; //FALSE;
	}
	AmalSynchro = 0; //FALSE;
}


// AMOS functions follow...

// BASIC-style string functions:
string AMOS_System::left(string t1, int t2)
{
	if (t2 <=0 )
		return "";
	else if (t2 <= (int)t1.length())
		return t1.substr(0, t2);
	else if (t2<0)
		return "";
	else
		return  t1;
}
string AMOS_System::right(string t1,int t2)
{
	return mid(t1, 1 + (t1.length()) - t2, t2);
}
string AMOS_System::mid(string t1, int t2, int t3)
{
	if (t2 > ((int)t1.length()))
		return "";

	if ((t2 + t3) > ((int)t1.length()))
		t3 = t1.length() - t2 + 1;

	if ((t1.length() <= 0) || (t3 <= 0))
		return "";

	if (t2 <= 1)
		return t1.substr(0, t3);
	else
		return t1.substr(t2 - 1, t3);
}
string AMOS_System::mid(string t1, int t2)
{
	if (t2 > ((int)t1.length()))
		return "";

	if ((t1.length() <= 0) || (t2 <= 1))
		return t1;
	else
		return t1.substr(t2 - 1, t1.length() - t2 + 1);
}
int AMOS_System::instr(string t1, string t2, int t3)
{
	if (t3>1)
		return (t1.find(t2, t3-1)) + 1;
	else // If 'start of search position' is 0 (same as for 1).....
		return (t1.find(t2, 0)) + 1;
}
int AMOS_System::instr(string t1, string t2)
{
	return (t1.find(t2, 0)) + 1;
}

// Random number generator function:
int AMOS_System::rnd(int t1)
{
#if defined(__AROS_)
	if (RAND_MAX > 0xffff)
		return random() % (t1 + 1);
	else
		return ((random()<<15) + random()) % (t1 + 1);
#else
	if (RAND_MAX > 0xffff)
		return rand() % (t1 + 1);
	else
		return ((rand()<<15) + rand()) % (t1 + 1);
#endif
}
// These two are for AMAL's random number generator:
int AMOS_System::amalZnd(int t1)
{
	if (pedantic == 0)
		// Use standard AMOS random number generator:
		return rnd(t1); // return rand() % (t1+1);
	else
		// Return a bitwise AND with the result of "Znd" below:
		// TO DO: Convert to (pedantic) short type
		// to work with negative numbers (and need to verify).
		return (int)( ((short)t1) & amalZnd() );
}
int AMOS_System::amalZnd()
{
	// AMAL Z function without brackets (TO DO: Parser)
	// Return a random number in the range -32767 to 32768 (CHECK THIS)
#if defined(__AROS_)
	return (short)((random() % 65536) - 32767);
#else
	return (short)((rand() % 65536) - 32767);
#endif
}

// Input/output AMOS instructions required for AMAL:
int AMOS_System::xMouse()
{
	return wrapper->xmouse();
}
int AMOS_System::yMouse()
{
	return wrapper->ymouse();
}
int AMOS_System::joy(int t1)
{
	return wrapper->joy(t1);
}
int AMOS_System::mouseKey()
{
	return wrapper->mousekey(-1);
}
int AMOS_System::mouseKey(int t1)
{
	return wrapper->mousekey(t1);
}
void AMOS_System::waitKey()
{
}

// Added - more joystick controls:
int AMOS_System::jleft(int t1)
{
	return wrapper->joy(t1) & 1;
}
int AMOS_System::jright(int t1)
{
	return wrapper->joy(t1) & 2;
}
int AMOS_System::jup(int t1)
{
	return wrapper->joy(t1) & 4;
}
int AMOS_System::jdown(int t1)
{
	return wrapper->joy(t1) & 8;
}
int AMOS_System::fire(int t1)
{
	return wrapper->joy(t1) & 16;
}

// Screen, bob, sprite and collision AMOS functions for AMAL:
int AMOS_System::xScreen(int t1, int t2)
{
	return t2 + ScreenOffsetX[t1] - ScreenDisplayX[t1];
}
int AMOS_System::yScreen(int t1, int t2)
{
	return t2 + ScreenOffsetY[t1] - ScreenDisplayY[t1];
}
int AMOS_System::xHard(int t1, int t2)
{
	return t2 + ScreenDisplayX[t1] - ScreenOffsetX[t1];
}
int AMOS_System::yHard(int t1, int t2)
{
	return t2 + ScreenDisplayY[t1] - ScreenOffsetY[t1];
}
int AMOS_System::xScreen(int t1)
{
	return xScreen(currentScreen, t1);
}
int AMOS_System::yScreen(int t1)
{
	return yScreen(currentScreen, t1);
}
int AMOS_System::xHard(int t1)
{
	return xHard(currentScreen, t1);
}
int AMOS_System::yHard(int t1)
{
	return yHard(currentScreen, t1);
}

// Collision detection:
int AMOS_System::bobCol(int t1)
{
	return wrapper->bobCol(t1);
}
int AMOS_System::bobCol(int t1, int t2, int t3)
{
	return wrapper->bobCol(t1, t2, t3);	
}
int AMOS_System::spriteCol(int t1)
{
	return wrapper->spriteCol(t1);
}
int AMOS_System::spriteCol(int t1, int t2, int t3)
{
	return wrapper->spriteCol(t1, t2, t3);
}
int AMOS_System::spriteBobCol(int t1)
{
	return wrapper->spriteBobCol(t1);
}
int AMOS_System::spriteBobCol(int t1, int t2, int t3)
{
	return wrapper->spriteBobCol(t1, t2, t3);
}
int AMOS_System::bobSpriteCol(int t1)
{
	return wrapper->bobSpriteCol(t1);
}
int AMOS_System::bobSpriteCol(int t1, int t2, int t3)
{
	return wrapper->bobSpriteCol(t1, t2, t3);
}
int AMOS_System::col(int t1)
{
	return wrapper->col(t1);
}

int AMOS_System::vumeter(int t1)
{
	return 0;
}
int AMOS_System::xSprite(int t1)
{
	return (int)(wrapper->xsprite(t1));
}
int AMOS_System::ySprite(int t1)
{
	return (int)(wrapper->ysprite(t1));
}
int AMOS_System::iSprite(int t1)
{
	return (int)(wrapper->isprite(t1));
}
int AMOS_System::xBob(int t1)
{
	return (int)(wrapper->xbob(t1));
}
int AMOS_System::yBob(int t1)
{
	return (int)(wrapper->ybob(t1));
}
int AMOS_System::iBob(int t1)
{
	return (int)(wrapper->ibob(t1));
}
int AMOS_System::hrev(int a)
{
	return a | 0x8000;
}
int AMOS_System::vrev(int a)
{
	return a | 0x4000;
}
int AMOS_System::rev(int a)
{
	return a | 0xC000;
}

// AMOS Sprite and Bob instructions:
void AMOS_System::sprite(int a, double b, double c, int d)
{
	wrapper->sprite(a,b,c,d);
}
void AMOS_System::sprite(int a, double b, double c)
{
	wrapper->sprite(a,b,c);
}
void AMOS_System::bob(int a, double b, double c, int d)
{
	wrapper->bob(a,(int)b,(int)c,d);
}
void AMOS_System::bob(int a, double b, double c)
{
	wrapper->bob(a,(int)b,(int)c);
}

// AMOS Screen instructions:
void AMOS_System::screenOpen(int a, int b, int c, int d, int e)
{
	wrapper->screenOpen(a, b, c, d, e);
}
void AMOS_System::screenSize(int a, int b, int c)
{
	wrapper->screenSize(a, b, c);
}
void AMOS_System::screenDisplay(int a, int b, int c)
{
	wrapper->screenDisplay(a, b, c);
}
void AMOS_System::screenDisplay(int a, int b, int c, int d, int e)
{
	screenDisplay(a, b, c);
	screenSize(a, c, e);
}
void AMOS_System::screenOffset(int a, int b, int c)
{
	// Debug - to do:
	//screenSize(a, b, c);

	// Set the offset here (TO DO):
	ScreenOffsetX[a]=b;
	ScreenOffsetY[a]=c;

	// Re-display the screen (TO DO:)
	screenDisplay(a, ScreenDisplayX[a], ScreenDisplayY[a]);
}
void AMOS_System::screenClose()
{
	// Close all screens here.
}
void AMOS_System::screenClose(int a)
{
}
void AMOS_System::screenClone(int a)
{
}
void AMOS_System::screen(int a)
{
	// Set the current screen here:
	currentScreen = a;
}
void AMOS_System::doubleBuffer()
{
	// Ignored for now - implementation is not low-level enough
}
void AMOS_System::dualPlayfield(int a, int b)
{
}
void AMOS_System::dualPriority(int a, int b)
{
}

// Required for Java:
int AMOS_System::booltoint(bool b)
{
        if (b)
            return LOGICTRUE;
        else
            return 0;
}


// Added: for AMAL compiler:
    
// Here Move is implemented as two parts:
void AMOS_System::amalMoveInit(int CHAN, int a, int b, int c)
{
	// Move (Initialise):
	SPECIAL[CHAN][3] = a;
	SPECIAL[CHAN][4] = b;
	SPECIAL[CHAN][5] = c;
	if (SPECIAL[CHAN][5] == 0)
		SPECIAL[CHAN][5]=1;
	SPECIAL[CHAN][6]=1;
}
void AMOS_System::amalMoveRun(int CHAN, int movejumppoint, int movejumppoint2)
{
	int tempX;
	int tempY;

	// AMAL Move (run):
	tempX=(((SPECIAL[CHAN][6] - 1) * SPECIAL[CHAN][3]) / SPECIAL[CHAN][5]);
	tempY=(((SPECIAL[CHAN][6] - 1) * SPECIAL[CHAN][4]) / SPECIAL[CHAN][5]);

	SPECIAL[CHAN][0] += ((SPECIAL[CHAN][6] * SPECIAL[CHAN][3]) / SPECIAL[CHAN][5]) - tempX;
	SPECIAL[CHAN][1] += ((SPECIAL[CHAN][6] * SPECIAL[CHAN][4]) / SPECIAL[CHAN][5]) - tempY;
	PAUSED = true;

	if (SPECIAL[CHAN][6]<SPECIAL[CHAN][5])
	{
		SPECIAL[CHAN][6]++; // Increase the Counter.
		PROGPOINTER[CHAN]=movejumppoint;
	}
	else
	{
		PROGPOINTER[CHAN]=movejumppoint2; // End of Move, go to next jump point
	}
	// break; removed - need to use break inside compiled Java program!
}
// Not yet implemented - would need a variable number of input operators!
void AMOS_System::amalAnim(int CHAN, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k)
{
	amalAnimInit(CHAN, a);
}
void AMOS_System::amalAnim(int CHAN, int a, int b, int c, int d, int e, int f, int g, int h, int i)
{
	amalAnimInit(CHAN, a);
}
void AMOS_System::amalAnim(int CHAN, int a, int b, int c, int d, int e, int f, int g)
{
	amalAnimInit(CHAN, a);
}
void AMOS_System::amalAnim(int CHAN, int a, int b, int c, int d, int e)
{
	amalAnimInit(CHAN, a);
}
void AMOS_System::amalAnim(int CHAN, int a, int b, int c)
{
	amalAnimInit(CHAN, a);
}
// Part implemented here:
void AMOS_System::amalAnimInit(int CHAN, int a)
{
	// AMAL Anim (partial initialisation only):
	// TO DO - does CHAN work, or need channel variable from compiled program? Synchronise?
	// Current frame number (0 = no animation)
	SPECIAL[CHAN][10] = 1;
	// Number of frames (i.e. brackets)
	SPECIAL[CHAN][11] = +((NUMARGS[CHAN][(PROGPOINTER[CHAN])]-1)/2); //+"; // Number of frames");
	// Timer for current frame (VBLs)...
	SPECIAL[CHAN][12] = 1;
	// Copy the arguments into the special registers...
	SPECIAL[CHAN][13] = a;
}
// TO DO - need to test this works with compiler:
void AMOS_System::amalAnimInitPair(int CHAN, int offset, int a, int b)
{
	// Following SPECIAL[CHAN][13] = a; above:
	// Here offset is 0,1,2,3....
	SPECIAL[CHAN][(offset*2)+14] = a;
	SPECIAL[CHAN][(offset*2)+15] = b;  	
}
void AMOS_System::amalJump(int CHAN, int progpointer)
{
	PROGPOINTER[CHAN] = progpointer;
}
void AMOS_System::amalDirect(int CHAN, int progpointer)
{
	RUNNINGAUTOTEST[CHAN] = false; // Leave Autotest...
	PROGPOINTER[CHAN] = progpointer;
}
void AMOS_System::amalPause(int CHAN, int progpointer)
{
	PROGPOINTER[CHAN] = progpointer;
	PAUSED = true;
}
void AMOS_System::amalWait(int CHAN, int progpointer)
{
	PROGPOINTER[CHAN] = progpointer;
	PAUSED = true;
}
void AMOS_System::amalInitAutotest(int CHAN, int start, int end)
{
	AUTOTESTSTART[CHAN] = start;
	AUTOTESTEND[CHAN] = end;

	// Skip to end of Autotest:
	PROGPOINTER[CHAN] = end;
}
void AMOS_System::amalEndAutotest(int CHAN)
{
	// As for eXit:
	// Re-enter the main program again, at the original departure point:
	RUNNINGAUTOTEST[CHAN] = false; // Leave Autotest...
	if ( MAINPROGDEPPOINT[CHAN] >= 0 )
		PROGPOINTER[CHAN] = MAINPROGDEPPOINT[CHAN];
	else
	// Jump to end of Autotest:
		PROGPOINTER[CHAN] = AUTOTESTEND[CHAN];
}
void AMOS_System::amalExitAutotest(int CHAN)
{
	// Re-enter the main program again, at the original departure point:
	RUNNINGAUTOTEST[CHAN] = false; // Leave Autotest...
	if ( MAINPROGDEPPOINT[CHAN] >= 0 )
		PROGPOINTER[CHAN] = MAINPROGDEPPOINT[CHAN];
	else
	// Jump to end of Autotest:
		PROGPOINTER[CHAN] = AUTOTESTEND[CHAN];  
}
void AMOS_System::amalEnd(int CHAN)
{
	PROGNOTFINISHED[CHAN] = false;
}
// TO DO - Does this work? ("On") - run from AUtotest, should restart main program from Wait.
void AMOS_System::amal_On(int CHAN)
{
    	// On
        // Re-enter the main program again, after the original departure point:
        RUNNINGAUTOTEST[CHAN] = false; // Leave Autotest...");
        if (MAINPROGDEPPOINT[CHAN] >= 0)
        	PROGPOINTER[CHAN] = MAINPROGDEPPOINT[CHAN] + 1;
        else
        // Jump to end of Autotest:
        	PROGPOINTER[CHAN] = INSTRLINENUM[CHAN][COMMAND[CHAN][(AUTOTESTSTART[CHAN])][1]-1]+2; // +1+1");
}

// Access AMAL registers:
int AMOS_System::amalGetGlobal(int reg)
{
	return myGLOBAL[reg];
}
int AMOS_System::amalGetLocal(int CHAN, int reg)
{
	return LOCAL[CHAN][reg];
}
int AMOS_System::amalGetSpecial(int CHAN, int reg)
{
	return SPECIAL[CHAN][reg];
}
int AMOS_System::amalGetX(int CHAN)
{
	return SPECIAL[CHAN][0];
}
int AMOS_System::amalGetY(int CHAN)
{
	return SPECIAL[CHAN][1];
}
int AMOS_System::amalGetA(int CHAN)
{
	return SPECIAL[CHAN][2];
}

void AMOS_System::amalSetGlobal(int reg, int value)
{
	myGLOBAL[reg] = value;
}
void AMOS_System::amalSetLocal(int CHAN, int reg, int value)
{
	LOCAL[CHAN][reg] = value;
}

// These two are used for AMAL For loops:
void AMOS_System::amalIncGlobal(int reg)
{
	myGLOBAL[reg]++;
}
void AMOS_System::amalIncLocal(int CHAN, int reg)
{
	LOCAL[CHAN][reg]++;
}

void AMOS_System::amalSetSpecial(int CHAN, int reg, int value)
{
	SPECIAL[CHAN][reg] = value;
}
void AMOS_System::amalSetX(int CHAN, int value)
{
	SPECIAL[CHAN][0] = value;
}
void AMOS_System::amalSetY(int CHAN, int value)
{
	SPECIAL[CHAN][1] = value;
}
void AMOS_System::amalSetA(int CHAN, int value)
{
	SPECIAL[CHAN][2] = value;
}

// Added for int/bool expressions:
bool AMOS_System::istrue(bool value)
{
	return value;
}
bool AMOS_System::istrue(int value)
{
	return value != 0;
}
bool AMOS_System::isfalse(bool value)
{
	return !value;
}
bool AMOS_System::isfalse(int value)
{
	return value == 0;
}

// Compiled version (for now, with int - memory bank strings with int will be later):
void AMOS_System::amal(int p1, int p2)
{
	bool synchroStatus = AmalSynchro;
	AmalSynchro = 1; //TRUE;
	CHAN = p1;

	//bool isfunction = 0; //FALSE; // was used for the compiler on Jamagic

	// From Jamagic version:
	//if (isfunction) // (IsFunction(p2))
	//{
	//AMALFun[p1]=p2; // needs a re-write in Java!
	if ( CHAN>TOPCHANNEL )
	{
		TOPCHANNEL=CHAN;
	}
	NUMLINES[p1] = 1; // added (long ago).

	// We need to set the CHANNEL to the PROGRAM here. For now (n,n).

	// Initialize the interpreter:
	PROGPOINTER[p1]=0; RUNNINGAUTOTEST[p1]=0; AUTOTESTSTART[p1]=-1; MAINPROGDEPPOINT[p1]=-1;

	SPECIAL[p1][10]=0; // No Anim running at beginning...
	PROGNOTFINISHED[p1]=1; FROZEN[p1]=0; EXISTS[p1]=1;

	for ( int T=0; T<= 9; T++ ) { LOCAL[p1][T]=0; }

	AmalSynchro = synchroStatus;
}

// AMOS BASIC AMAL instructions:
void AMOS_System::amal(int p1, string p2)
{
	bool synchroStatus = AmalSynchro;
	AmalSynchro = 1; //TRUE;
	CHAN = p1;

	//bool isfunction = 0; //FALSE; // was used for the compiler on Jamagic

	_input=p2;

	if ( CHAN>TOPCHANNEL )
	{
		TOPCHANNEL=CHAN;
	}

	amallexer->Tokenize();

	//else // very old and removed long ago
	//{
	//	NUMLINES[P1] = 1;
	//}

	// Initialize the interpreter:
	PROGPOINTER[p1]=0; RUNNINGAUTOTEST[p1]=0; AUTOTESTSTART[p1]=-1; MAINPROGDEPPOINT[p1]=-1;

	SPECIAL[p1][10]=0; // No Anim running at beginning...
	PROGNOTFINISHED[p1]=1; FROZEN[p1]=0; EXISTS[p1]=1;

	for ( int T=0; T<= 9; T++ ) { LOCAL[p1][T]=0; }

	AmalSynchro = synchroStatus;
}

int AMOS_System::amreg(int t1)
{
	return myGLOBAL[t1];
}
int AMOS_System::amreg(int t1, int t2)
{
	return LOCAL[t1][t2];
}
void AMOS_System::setAmreg(int t1, int t2)
{
	myGLOBAL[t2] = t1;
}
void AMOS_System::setAmreg(int t1, int t2, int t3)
{
	LOCAL[t2][t3] = t1;
}
void AMOS_System::amalOn(int p1)
{
	FROZEN[p1] = 0; //FALSE;
}
void AMOS_System::amalOn()
{
	for (int p1 = 1; p1 <= TOPCHANNEL; p1++) // should start from 0
		FROZEN[p1] = 0; //FALSE;
}
void AMOS_System::amalFreeze(int p1)
{
	FROZEN[p1] = 1; //TRUE;
}
void AMOS_System::amalFreeze()
{
	for (int p1 = 1; p1 <= TOPCHANNEL; p1++) // should start from 0
		FROZEN[p1] = 1; //TRUE;
}
void AMOS_System::amalOff()
{
	for (int p1=1; p1 <= TOPCHANNEL; p1++) // should start from 0
	{
		PROGPOINTER[p1] = 0;
		NUMLINES[p1] = 0;
		EXISTS[p1] = 0; //FALSE;

		// Destroy AMAL program from memory here:
	}
	TOPCHANNEL = 0;
}
void AMOS_System::amalOff(int p1)
{
	// Need to check if out of range here.

	PROGPOINTER[p1] = 0;
	NUMLINES[p1] = 0;
	EXISTS[p1] = false;

	// Need to destroy AMAL program from memory here. (?)

	// Drop down the top channel here:
	if (p1 == TOPCHANNEL)
		if ( NUMLINES[P1]==0 && P1 >= 0 ) // while ( NUMLINES[P1]==0 && P1>=0 )
			TOPCHANNEL--;
}
void AMOS_System::channelToSprite(int p1, int p2)
{
	// Channel p1 To Sprite P2
	SETCHANNEL[p1] = p2;
	TYPECHANNEL[p1] = 0; // To Sprite.
}
void AMOS_System::channelToBob(int p1, int p2)
{
	// Channel p1 To Bob P2
	SETCHANNEL[p1] = p2;
	TYPECHANNEL[p1] = 1; // To Bob.
}
void AMOS_System::channelToScreenDisplay(int p1, int p2)
{
	// Channel p1 To Screen Display P2
	SETCHANNEL[p1] = p2;
	TYPECHANNEL[p1] = 2; // To Screen Display
}
void AMOS_System::channelToScreenOffset(int p1, int p2)
{
	// Channel p1 To Screen Offset P2
	SETCHANNEL[p1] = p2;
	TYPECHANNEL[p1] = 3; // To Screen Offset.
}
void AMOS_System::channelToScreenSize(int p1, int p2)
{
	// Channel p1 To Screen Size P2
	SETCHANNEL[p1] = p2;
	TYPECHANNEL[p1] = 4; // To Screen Size.
}
void AMOS_System::channelToRainbow(int p1, int p2)
{
	// Channel p1 To Rainbow P2
	SETCHANNEL[p1] = p2;
	TYPECHANNEL[p1] = 5; // To Rainbow.
}
void AMOS_System::synchroOff()
{
	AmalSynchro = 0; //FALSE;
}
void AMOS_System::synchroOn()
{
	AmalSynchro = 1; //TRUE;
}
void AMOS_System::synchro()
{
	AMAL_Do(runningcompiled);
}
void AMOS_System::AMAL_Do(bool isfunction)
{
    	if (!isfunction)
    		interpreterrunning = true; // needed if compiled?
    	
    	//cout << "Running AMAL_Do!" << endl;
    	
    	// if (TOPCHANNEL > 0) // old and removed
    	for ( CHAN=1; CHAN <= TOPCHANNEL; CHAN++ ) // Originally from 0, not from 1..
    	{
    		//cout << "CHAN = " << AM->stri(CHAN) << endl;
    		
    		bool objectremoved = 0; //FALSE;
    		//Say(""+AM->stri(CHAN)+" "+AM->stri(TOPCHANNEL)); // Wait(100);
    		
    		if (EXISTS[CHAN]) if ( (FROZEN[CHAN] == false))
    		{			
    			// Get values for special registers: 
    			if (DEBUGMODE == 0 )
    			{
    				// Debug - only print if typechannel > 0:
    				//if (TYPECHANNEL[CHAN]> 0)
    				//cout << "Debug: Fetching special registers. TYPECHANNEL[" << AM->stri(CHAN) << "] = " << AM->stri(TYPECHANNEL[CHAN]) << endl;

    				switch ( TYPECHANNEL[CHAN] )
    				{
    				case 0:
    					// Channel CHAN To Sprite SETCHANNEL[CHAN]
    					SPECIAL[CHAN][0]=xSprite(SETCHANNEL[CHAN]);
    					SPECIAL[CHAN][1]=ySprite(SETCHANNEL[CHAN]);
    					SPECIAL[CHAN][2]=iSprite(SETCHANNEL[CHAN]);
    				break;
    				case 1:
    					// Channel CHAN To Bob SETCHANNEL[CHAN]   
    					
    					// From Jamagic version - fix to detect deleted bobs:
    					//if (!IsObject(Bobs[SETCHANNEL[CHAN]]))
    					//{
    					//	amalOff(CHAN); objectremoved = true;
    					//	break;
					//}
    					
    					SPECIAL[CHAN][0]=(int)xBob(SETCHANNEL[CHAN]);
    					SPECIAL[CHAN][1]=(int)yBob(SETCHANNEL[CHAN]);
    					SPECIAL[CHAN][2]=(int)iBob(SETCHANNEL[CHAN]);
        			break;
    				case 2:
    					// Channel AMOS_Sys.CHAN To Screen Display AMOS_Sys.SETCHANNEL(AMOS_Sys.CHAN) 
    					
    					// FIX - is currentScreen correct here?
    					SPECIAL[CHAN][0]=(int)ScreenDisplayX[currentScreen]; // TO DO: Screen number is: (SETCHANNEL[CHAN])
    					SPECIAL[CHAN][1]=(int)ScreenDisplayY[currentScreen]; // TO DO: Screen number is: (SETCHANNEL[CHAN])
    					//cout << "Debug: Running Channel " << AM->stri(CHAN) << " to Screen Display (Screen) " << AM->stri(SETCHANNEL[CHAN]) << endl;
   					break;
    				case 3:
    					// Channel AMOS_Sys.CHAN To Screen Offset AMOS_Sys.SETCHANNEL(AMOS_Sys.CHAN) 
    					// TO DO:
    					SPECIAL[CHAN][0]=(int)xBob(SETCHANNEL[CHAN]);
    					SPECIAL[CHAN][1]=(int)yBob(SETCHANNEL[CHAN]);
        			break;
    				case 4:
    					// Channel AMOS_Sys.CHAN To Screen Size AMOS_Sys.SETCHANNEL(AMOS_Sys.CHAN) 
    					// TO DO:
    					SPECIAL[CHAN][0]=(int)xBob(SETCHANNEL[CHAN]);
    					SPECIAL[CHAN][1]=(int)yBob(SETCHANNEL[CHAN]);
        			break;
    				case 5:
    					// Channel AMOS_Sys.CHAN To Rainbow AMOS_Sys.SETCHANNEL(AMOS_Sys.CHAN) 
    					// TO DO:
    					SPECIAL[CHAN][0]=(int)xBob(SETCHANNEL[CHAN]);
    					SPECIAL[CHAN][1]=(int)yBob(SETCHANNEL[CHAN]);
    					SPECIAL[CHAN][2]=(int)iBob(SETCHANNEL[CHAN]);
    				break;
    				}

				//cout << "Debug: Successfully fetched special registers!" << endl;
    			}
    			
    			if (!objectremoved)
    			{
    				if (PROGNOTFINISHED[CHAN])
    				{
    					// Do the Autotest if applicable: 
    					if ( AUTOTESTSTART[CHAN]>=0 )
    					{
    						MAINPROGDEPPOINT[CHAN]=PROGPOINTER[CHAN]; // Record the position..
    						PROGPOINTER[CHAN]=AUTOTESTSTART[CHAN]+1; // Jump to the Autotest
    						RUNNINGAUTOTEST[CHAN]=1; //TRUE;
    					}
    					
    					// Now run the AMAL commands:
    					//boolean isfunction = false; // added - debug
    					if (isfunction) // if (isFunction(AMALFun[CHAN]))
    					{
    						//fun = AMALFun[CHAN];
    						//Forrepeat=0;					
    						//fun();
    						
    						// Now we run the compiled/translated AMAL programs:
    						translatedamalprograms->forrepeat = false; // needed?
    			    			translatedamalprograms->runAmal(CHAN, CHAN);
    					}
    					else
    					{
    						while ( PROGPOINTER[CHAN]<NUMLINES[CHAN] && PAUSED==false )
    						{
    							//THINGY++; //DEBUG!!
    							amalinterpreter->interpret();
    						
    							// Debug:
    							if ( DEBUGMODE != 0 )
    								amalinterpreter->DEBUG();
    						}
    						// Does this work ???
    						if ( PROGPOINTER[CHAN] < NUMLINES[CHAN] )
    							PROGNOTFINISHED[CHAN] = true; // was PROGFINISHED[CHAN] = false;
    					}
    					//A_Say(""+CHAN+" "+TYPECHANNEL[CHAN] ); // Wait(100);
    					
    					PAUSED=false;
    					if ( DEBUGMODE != 0 )
    						cout << "PAUSED..." << endl;
    				}
    				
    				// Run the AMAL Anim if applicable... 
    				if ( SPECIAL[CHAN][10]>0 )
    					AMAL_ANIM();
    				
				//cout << "Returning values from the special registers!" << endl;

    				// Return values from the special registers: 
    				if (DEBUGMODE == 0) switch (TYPECHANNEL[CHAN])
    				{
    				case 0:
    					// Channel CHAN To Sprite SETCHANNEL[CHAN]
    					sprite(SETCHANNEL[CHAN], SPECIAL[CHAN][0], SPECIAL[CHAN][1], SPECIAL[CHAN][2]);
    				break;
    				case 1:
    					//cout << "Trying to draw a bob" << endl;
    					// Channel CHAN To Bob SETCHANNEL[CHAN]
    					bob(SETCHANNEL[CHAN], SPECIAL[CHAN][0], SPECIAL[CHAN][1], SPECIAL[CHAN][2]);
        			break;
    				case 2:
    					// Channel CHAN To Screen Display SETCHANNEL[CHAN]
    					screenDisplay(SETCHANNEL[CHAN], SPECIAL[CHAN][0], SPECIAL[CHAN][1]);
    				break;
    				case 3:
    					// Channel CHAN To Screen Offset SETCHANNEL[CHAN]
    					screenOffset(SETCHANNEL[CHAN],SPECIAL[CHAN][0],SPECIAL[CHAN][1]);
    				break;
    				case 4:
    					// Channel CHAN To Screen Size SETCHANNEL[CHAN]
    					//ScreenDisplay(SETCHANNEL[CHAN],(int)null,(int)null, SPECIAL[CHAN][0], SPECIAL[CHAN][1]);
    					screenSize(SETCHANNEL[CHAN], SPECIAL[CHAN][0], SPECIAL[CHAN][1]);
        			break;
    				case 5:
    					// Channel CHAN To Rainbow SETCHANNEL[CHAN]
    					rainbow(SETCHANNEL[CHAN],SPECIAL[CHAN][0],SPECIAL[CHAN][1],SPECIAL[CHAN][2]);
    				}

				//cout << "Successfully returned values from the special registers!" << endl;
    			}
    		}
    	}

    	interpreterrunning = 0; //FALSE;
}

void AMOS_System::AMAL_ANIM()
{
	// Set the object image:
	SPECIAL[CHAN][2]=SPECIAL[CHAN][12+((SPECIAL[CHAN][10])*2)];

	// Increase the timer/counter for current frame:
	SPECIAL[CHAN][12]++;
	// If the counter is finished, move to the next frame:
	if ( (SPECIAL[CHAN][12])>(SPECIAL[CHAN][13+((SPECIAL[CHAN][10])*2)]) )
	{
		SPECIAL[CHAN][10]++;
		SPECIAL[CHAN][12]=1;
		// If past the number of frames:
		if ( (SPECIAL[CHAN][10])>(SPECIAL[CHAN][11]) )
		{
			switch ( SPECIAL[CHAN][13] )
			{
			case 0:
				// for infinite repeats:
				// Start from the beginning (first frame):
				SPECIAL[CHAN][10]=1;
				break;
			case 1:
				// Last time finished:
				// Stop running the animation.
				SPECIAL[CHAN][10]=0;
				break;
			default:
				// Repeat again, with count down:
				SPECIAL[CHAN][13]--;
				// Start from the beginning (first frame):
				SPECIAL[CHAN][10]=1;
			}
		}
	}
}

// To do - added channel number to run from an interpreted or compiled program:
int AMOS_System::amalPLay(int CHAN, int t1)
{
	return 0;
}



// Load image or IFF file (supports other formats instead for now):
void AMOS_System::loadIff(string a, int b)
{
	wrapper->loadIff(a, b);
}
void AMOS_System::loadIff(string a)
{
	wrapper->loadIff(a, currentScreen);
}


// Banks:
// Load a bank (folder of sprites for now)
// TO DO - faux packed pictures (with unpack).
void AMOS_System::load(string a, int b)
{
	wrapper->load(a, b);
}
// Added - scale:
void AMOS_System::load(string a, int b, int scale)
{
	wrapper->load(a, b, scale);
}
void AMOS_System::erase(int a)
{
	wrapper->erase(a);
}

// Hot Spot control:
void AMOS_System::hotspot(int a, int b, int c)
{
	while ((int)ImageHotSpotX.size() <= a)
		ImageHotSpotX.push_back(0);
	while ((int)ImageHotSpotY.size() <= a)
		ImageHotSpotY.push_back(0);

	ImageHotSpotX[a]=b;
	ImageHotSpotY[a]=c;
}
void AMOS_System::hotspot(int a, int b)
{
	while ((int)ImageHotSpotX.size() <= a)
		ImageHotSpotX.push_back(0);
	while ((int)ImageHotSpotY.size() <= a)
		ImageHotSpotY.push_back(0);

	// TODO - get image width and height here:
	int imagewidth=100;
	int imageheight=100;

	ImageHotSpotX[a] = ((b | 0xF0) / 0x10) * imagewidth / 2;
	ImageHotSpotY[a] = ((b | 0x0F) / 0x01) * imageheight / 2;
}


// Load a Sprite bank from AMOS Basic .abk files:
int AMOS_System::loadamosabk(string fileName, int bank)
{
	return wrapper->loadamosabk(fileName, bank, 1); // Added: scale=1
}

int AMOS_System::pastebob(int x, int y, int a)
{
	return wrapper->pastebob(x, y, a);
}
int AMOS_System::pasteicon(int x, int y, int a)
{
	return wrapper->pasteicon(x, y, a);
}

int AMOS_System::ink(int a)
{
	_ink = a;
	return 0;
}

int AMOS_System::pen(int a)
{
	_ink = a; // TODO - separate value for pen and ink!
	return 0;
}

int AMOS_System::paper(int a)
{
	_paper = a;
	return 0;
}

int AMOS_System::textlength(string a)
{
	return wrapper->textlength(a);
}
int AMOS_System::text(int x, int y, string a)
{
	return wrapper->text(x, y, a);
}

int AMOS_System::plot(int x, int y, int a)
{
	return wrapper->plot(x, y, a);
}
int AMOS_System::plot(int x, int y)
{
	return wrapper->plot(x, y);
}
int AMOS_System::draw(int x1, int y1, int x2, int y2)
{
	return wrapper->draw(x1, y1, x2, y2);
}
int AMOS_System::bar(int x1, int y1, int x2, int y2)
{
	return wrapper->bar(x1, y1, x2, y2);
}
int AMOS_System::box(int x1, int y1, int x2, int y2)
{
	return wrapper->box(x1, y1, x2, y2);
}
int AMOS_System::circle(int x1, int y1, int r1)
{
	return wrapper->circle(x1, y1, r1);
}
int AMOS_System::ellipse(int x1, int y1, int r1, int r2)
{
	return wrapper->ellipse(x1, y1, r1, r2);
}

// Added from Myqu:
void AMOS_System::_default()
{
	bobOff();
	rainbowDel();
	for (int n=0; n<=7; n++)
	{	
		ScreenClonePointer[n]=-1;
		//if (screens[n] != null)
		//{
		//	// Delete the screen here:
		//	screens[n] = null;
		//}
	}
	//screenOpen(0,320,200,3,lowres()); // create the default screen here
	// Erase the screen here
	//screens[0].SetBackgroundColor(A_PalTo24(1, AMOS_Sys.ScreenPalette[0,1]));
	//screens[0].EraseRect();
	_paper=1; //?

	MouseDisplayed = true;

	ink(3); bar(2,9,10,11);
	flash(3, "(DD0,2)(EE0,2)(FF2,2)(FF8,2)(FFC,2)(FFF,2)(AAF,2)(88C,2)(66A,2)(226,2)(004,2)(001,2)(000,2)(440,2)(880,2)(BB0,2)");
	ink(2);

	amalOff(); // FIX ME!
	AMAL_Init(); // FIX ME!
}

int AMOS_System::lowres() { return 0; }
int AMOS_System::hires() { return 32768; }
int AMOS_System::laced() { return 4; }

int AMOS_System::timer() { return Timer; }
void AMOS_System::setTimer(int t1) { Timer = t1; }


///////////////////////////////////////////////////////
// Maths Functions
void AMOS_System::degree() { _degree = 1; }
void AMOS_System::radian() { _degree = 0; }
double AMOS_System::_sin(double t1) { if (_degree) return sin(t1*PI / 180.0); else return sin(t1); }
double AMOS_System::_cos(double t1) { if (_degree) return cos(t1*PI / 180.0); else return cos(t1); }
double AMOS_System::_tan(double t1) { if (_degree) return tan(t1*PI / 180.0); else return tan(t1); }
double AMOS_System::_asin(double t1) { if (_degree) return asin(t1)*180.0 / PI; else return asin(t1); }
double AMOS_System::_acos(double t1) { if (_degree) return acos(t1)*180.0 / PI; else return acos(t1); }
double AMOS_System::_atan(double t1) { if (_degree) return atan(t1)*180.0 / PI; else return atan(t1); }
double AMOS_System::pi() { return PI; }
int AMOS_System::_true() { return -1; } // TODO
int AMOS_System::_false() { return 0; } // TODO
//bool AMOS_System::_true() { return 1; }
//bool AMOS_System::_false() { return 0; }

///////////////////////////////////////////////////////
// String Functions
int AMOS_System::len(string t1) { return t1.length(); }
string AMOS_System::upper(string t1) { string t2=t1; std::transform(t2.begin(), t2.end(), t2.begin(), ::toupper); return t2; }
string AMOS_System::lower(string t1) { string t2=t1; std::transform(t2.begin(), t2.end(), t2.begin(), ::tolower); return t2; }
string AMOS_System::_string(string t1, int t2) { string o=""; for (int t=0; t<t2; t++) o=o+t1; return o; }
string AMOS_System::repeat(string t1, int t2) { string o=""; for (int t=0; t<t2; t++) o=o+t1; return o; } // TODO
string AMOS_System::space(int t1) { string o=""; for (int t=0; t<t1; t++) o=o+" "; return o; }
string AMOS_System::flip(string i) { string o=""; for (unsigned int t=0; t<i.length(); t++) { o+=i[i.length()-t-1]; } return o; }
double AMOS_System::val(string i) { return atof(i.c_str()); }
//int AMOS_System::val(string i) { return atoi(i.c_str()); }
string AMOS_System::str(double i) { std::ostringstream s; s << i; return s.str(); }
string AMOS_System::stri(int i) { std::ostringstream s; s << i; return s.str(); } // Added
//string AMOS_System::str(int i) { std::ostringstream s; s << i; return s.str(); } // TODO - ambiguous!
int AMOS_System::asc(string a) { if (a.length()==0) return 0; return (int)a[0];}
int AMOS_System::asc(char a) { return (int)a; }
string AMOS_System::chr(int a) { char c[2]; c[0]=(char)a; c[1]=(char)0; return string(c); }

string AMOS_System::hex(int i) { std::ostringstream s; s << "$"; s << std::hex << i; return upper(s.str()); } // Added

// Added - for binary:
string AMOS_System::bin(int input)
{
	// Output string:
	string output = "";

	// Bit to test:
	unsigned int mybit = ((unsigned int)1) << 31;

	// Test each bit:
	for (int n=0; n<32; n++)
	{
		if ((mybit & input) == mybit)
			output += "1";
		else
			output += "0";

		mybit >>= 1;
	}

	// Remove trailing zeros:
	int pos;
	for (pos=0; (pos<31) && (output[pos]=='0'); pos++);
	output = "%"+output.substr(pos, output.length() - pos);

	return output;
}

int AMOS_System::binstringtoint(string input)
{
	// Return 0 for empty string:
	if (input.length() == 0)
		return 0;

	// Remove initial %:
	if (input[0] == '0')
		input = input.substr(1, input.length() - 1);

	// Get string length (less than 32):
	unsigned int mypos = input.length() - 1;
	if (mypos > 32)
		mypos = 32;
	
	unsigned int mybit = 1;
	unsigned int output = 0;

	for (int n=mypos; n>=0; n--)
	{
		if (input[n] == '1')
			output |= mybit;
		
		mybit <<= 1;
	}

	return (int)output;
}

///////////////////////////////////////////////////////
// AMOS Rainbows
void AMOS_System::rainbow(int t1, int t2, int t3, int t4)
{
	// TODO:
	// Avoid out-of-bounds (give error eventually):
	while ((int)RainbowOffset.size() <= t1)
	{
		RainbowOffset.push_back(0);
		RainbowPos.push_back(0);
		RainbowDisplayHeight.push_back(0);
		RainbowHeight.push_back(0);
	}
	RainbowOffset[t1]=t2;
	RainbowPos[t1]=t3;
	RainbowDisplayHeight[t1]=t4;
}
void AMOS_System::rain(int t1, int t2, int t3) // Which order??? ???? number t1, line t2 = colour t3......
{
	wrapper->rain(t1, t2, t3);
}
void AMOS_System::setRainbow(int t1, int t2, int t3, string t4, string t5, string t6)
{
	//cout << "DEBUG: Running setRainbow(...)" << endl;

	while ((int)RainbowOffset.size() <= t1)
	{
		RainbowOffset.push_back(0);
		RainbowPos.push_back(0);
		RainbowDisplayHeight.push_back(0);
		RainbowHeight.push_back(0);
	}
	RainbowOffset[t1]=0; RainbowPos[t1]=0; RainbowDisplayHeight[t1]=0;
	RainbowHeight[t1]=t3;

	int _red=0; int _green=0; int _blue=0;
	int _rednumberon=0; int _redcountdone=0;
	int _greennumberon=0; int _greencountdone=0;
	int _bluenumberon=0; int _bluecountdone=0;

	int t, tt;

	// Parse the red string:
	int Rnumber=0, Rstep=0, Rcount=0;
	if (t4.length() > 0)
	{
		t=t4.find(",", 0); tt=t4.find(",", t+1);
		Rnumber=atoi(t4.substr(1, t - 1).c_str());
		Rstep=atoi(t4.substr(t + 1, tt - t - 1).c_str());
		Rcount=atoi(t4.substr(tt + 1, t4.length() - tt - 2).c_str()); // was t4.length()-tt-1;
	}

	// Parse the green string:
	int Gnumber=0, Gstep=0, Gcount=0;
	if (t5.length() > 0)
	{
		t=t5.find(",", 0); tt=t5.find(",", t+1);
		Gnumber=atoi(t5.substr(1, t - 1).c_str());
		Gstep=atoi(t5.substr(t + 1, tt - t - 1).c_str());
		Gcount=atoi(t5.substr(tt + 1, t5.length() - tt - 2).c_str());
	}

	// Parse the blue string:
	int Bnumber=0, Bstep=0, Bcount=0;
	if (t6.length() > 0)
	{
		t=t6.find(",", 0); tt=t6.find(",", t+1);
		Bnumber=atoi(t6.substr(1, t - 1).c_str());
		Bstep=atoi(t6.substr(t + 1, tt - t - 1).c_str());
		Bcount=atoi(t6.substr(tt + 1, t6.length() - tt - 2).c_str());
	}

	//cout << "Red string: rnumber=" << stri(Rnumber) << ", Rstep=" << stri(Rstep) << ", Rcount=" << stri(Rcount) << endl; // debug
	//cout << "Green string: gnumber=" << stri(Gnumber) << ", Gstep=" << stri(Gstep) << ", Gcount=" << stri(Gcount) << endl; // debug
	//cout << "Blue string: bnumber=" << stri(Bnumber) << ", Bstep=" << stri(Bstep) << ", Bcount=" << stri(Bcount) << endl; // debug

	// Create SDL surface for rainbow here:
	wrapper->openrainbow(t1, t3);

	for (t=0; t<t3; t++)
	{
		wrapper->rain(t1, t, _red + _green*16 + _blue*256);

		if (_redcountdone >= Rcount) // Reset the cycle from here...
		{
			_rednumberon=0; _redcountdone=0; _red=0;
		}
		_rednumberon++;
		if (_rednumberon == Rnumber)
		{
			_red += Rstep; _red=_red % 16;
			_rednumberon=0;
			_redcountdone++; // Does this go here, or below?
		}
	
		if (_greencountdone >= Gcount) // Reset the cycle from here...
		{
			_greennumberon=0; _greencountdone=0; _green=0;
		}
		_greennumberon++;
		if (_greennumberon == Gnumber)
		{
			_green += Gstep; _green=_green % 16;
			_greennumberon=0;
			_greencountdone++; // Does this go here, or below?
		}

		if (_bluecountdone >= Bcount) // Reset the cycle from here...
		{	_bluenumberon=0; _bluecountdone=0; _blue=0;
		}
		_bluenumberon++;
		if (_bluenumberon == Bnumber)
		{
			_blue += Bstep; _blue=_blue % 16;
			_bluenumberon=0;
			_bluecountdone++; // Does this go here, or below?
		}
	}	
	//cout << "DEBUG: Ran setRainbow(...)" << endl;
}
// TODO:
void AMOS_System::rainbowDel()
{
}
void AMOS_System::rainbowDel(int a)
{
}

// Misc (to sort):
void AMOS_System::hide()
{
	hideOn();
}
void AMOS_System::hideOn()
{
}
void AMOS_System::hideOff()
{
}
void AMOS_System::updateEvery(int a)
{
}
void AMOS_System::flashOff()
{
}
void AMOS_System::flash(int a, string b)
{
}
void AMOS_System::bobOff(int a)
{
	wrapper->boboff(a);
}
void AMOS_System::bobOff()
{
	wrapper->boboff();
}
void AMOS_System::setBob(int a, int b, int c, int d)
{
}
void AMOS_System::spriteOff(int a)
{
	wrapper->spriteoff(a);
}
void AMOS_System::spriteOff()
{
	wrapper->spriteoff();
}
void AMOS_System::setSpriteBuffer(int a)
{
}

// May require extended syntax:
void AMOS_System::setReg(int a, int b)
{
}
void AMOS_System::unpack(int a, int b)
{
}

// To do - tests for Environment Generator:
bool AMOS_System::isScreen(int a)
{
	return 0;
}
bool AMOS_System::isNotScreen(int a)
{
	return !isScreen(a);
}
bool AMOS_System::isBank(int a)
{
	return 0;
}
bool AMOS_System::isNotBank(int a)
{
	return !isBank(a);
}
bool AMOS_System::isReg(int a, int b)
{
	return (a) != b;
}

// New:
void AMOS_System::bell()
{
	wrapper->bell();
}
void AMOS_System::bell(int pitch)
{
	// TODO:
	bell();
}
void AMOS_System::shoot()
{
	wrapper->shoot();
}
void AMOS_System::boom()
{
	wrapper->boom();
}


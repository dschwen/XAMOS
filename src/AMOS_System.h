#ifndef AMOS_SYSTEM_H
#define AMOS_SYSTEM_H

#include <vector>
#include <string>

#include "Mytype.h"
#include "Mytypearray.h"

using std::vector;
using std::string;


#include "Parser.h"
#include "Interpreter.h"
#include "Dumper.h"
#include "Game.h"
#include "GameEngineWrapper.h"
#include "XAMOS.h"

// XAMAL includes:
#include "AMALParser.h"
#include "AMALInterpreter.h"
#include "AMALCompiler.h"
#include "AMALBank.h"
#include "AMALEnvGen.h"
#include "AmalPrograms.h"


class GameEngineWrapper;
class Interpreter;
class XAMOS;

class AMALParser;
class AMALInterpreter;
class AMALCompiler;
class AMALBank;
class AMALEnvGen;

class AmalPrograms;

class AMOS_System
{
	// Added from MequaScript for jAMOS:
	bool OPTIMISE; // TODO: debug this

	bool runningcompiled;

	// New: Pedantic mode. (Make settable in editor)
	int pedantic;

public:
	// Moved to public:
	int Mode, Fullscreen, ThreeDee, Scale, NumBobCols, LastBobTested, PenColor, PaperColor, MouseState, MouseClickState;
	int File, tim, Timer, CodeInput1, CodeInput2, _ink, _paper;
	int oWorld, oCamera, KeyTimeLag, KeyDelaySpeed;
	int thetm, UpdateSpeed, AutoUpdate, NumZones, MouseSprite, MouseImageUsed;
	int DEBUGMODE;
	bool _degree, RunningAdvancedScreenUpdate, MouseDisplayed;
	int TT;
	int P1;

	// For collision detection:
	unsigned int Bobcolled, Bobteststart, Bobtestend, Bobtested, Coltype;

	// Added - moved to public:
   	int currentScreen;

	int CHAN;
	int TOPCHANNEL;
	int SCANFROM;
	int FOUNDINSTRUCTION;
	int FOUNDFUNCTION;
	int RESULT;
	int SLEN;
	int NEST;
	int BRSTACK;
	int LOGICTRUE;
	bool TEST;
	bool PAUSED;
	string tokest;
	string ttt;
	string lastt;
	string lastt2;


	int N;
	int NN;
	int _TOTALNUMSTRINGS;
	int T;
	bool AmalSynchro;

	int OLDPROGPOINTER;

	string _input;
	int JUMPED;
	int caseon;

	// Moved:
	bool interpreterrunning;

	// Added: Use to store loaded image names:
	//vector<string> loadedimages; // removed in C++!
	vector<string> loadedspriteimages;
	vector<string> currentspriteimages;
	vector<string> currenticonimages;

	vector<int> PROGPOINTER;
	vector<int> AUTOTESTSTART;
	vector<int> AUTOTESTEND;
	vector<int> MAINPROGDEPPOINT;
	vector< vector<int> > LOCAL;
	vector< vector<int> > SPECIAL;
	vector<int> myGLOBAL;
	vector<int> NUMINSTRUCTIONS;
	vector<int> NUMLINES;
	vector< vector<int> > INSTRLINENUM;
	vector<int> TEMPCOUNT;
	vector<int> SETCHANNEL;
	vector<int> TYPECHANNEL;

	vector<bool> RUNNINGAUTOTEST;
	vector<bool> PROGNOTFINISHED;
	vector<bool> FROZEN;
	vector<bool> EXISTS;

	vector<string> commandlist;
	vector<string> argtypename;
	vector< vector< vector<string> > > strin;
	vector< vector<string> > temp;
	vector<int> TOPARGNUM;
	vector< vector<int> > NUMSTRINGS;
	vector< vector<int> > STRINGARGNUM;
	vector< vector<int> > NUMARGS;
	vector< vector< vector<int> > > ARGTYPE;
	vector< vector <int> > LABELS;
	vector< vector <vector <int> > > COMMAND;
	vector<int> NESTINSTRNUM;

	vector< vector<int> > TEMP;

	vector<vector<int> > ARG;
	vector<vector<string> > arg; // Needs to be flexible/dynamic type

	// Moved to public:
	vector <int> BobX, BobY, BobImage, ImageHotSpotX, ImageHotSpotY, MouseImageHotSpotX, MouseImageHotSpotY;
	vector <int> ScreenWidth, ScreenHeight, ScreenColors, ScreenRes, ScreenOffsetX, ScreenOffsetY, ScreenDisplayX, ScreenDisplayY;
	vector <int> ScreenDisplayWidth, ScreenDisplayHeight, ScreenClonePointer, ScreenXCur, ScreenYCur;
	vector <int> RainbowHeight, RainbowOffset, RainbowPos, RainbowDisplayHeight, Palette, SpritePalette, IconPalette;
	vector <int> SpriteX, SpriteY, SpriteImage;


	// Added - from jAMOS:
	AMOS_System* AM;
	XAMOS* ma;
	GameEngineWrapper* wrapper;

	// XAMAL:
	AMALParser* amallexer;
	AMALInterpreter* amalinterpreter;
	AMALCompiler* amalcompiler;
	AMALBank* amalbank;
	AMALEnvGen* envGen;

	Game* g;
	Parser* parser;
	Interpreter* interpreter;
	Dumper* dumper;

	AmalPrograms* translatedamalprograms;

	// Constructor function:
	AMOS_System(); //jAMOS mygamei)

	void Init();
	void AMAL_Init();

	// AMOS functions follow...

	// BASIC-style string functions:
	string left(string t1, int t2);
	string right(string t1,int t2);
	string mid(string t1, int t2, int t3);
	string mid(string t1, int t2);
	int instr(string t1, string t2, int t3);
	int instr(string t1, string t2);

	// Random number generator function:
	int rnd(int t1);
	// These two are for AMAL's random number generator:
	int amalZnd(int t1);
	int amalZnd();

	// Input/output AMOS instructions required for AMAL:
	int xMouse();
	int yMouse();
	int joy(int t1);
	int mouseKey();
	int mouseKey(int t1);
	void waitKey();

	// Added - more joystick controls:
	int jleft(int t1);
	int jright(int t1);
	int jup(int t1);
	int jdown(int t1);
	int fire(int t1);

	// Screen, bob, sprite and collision AMOS functions for AMAL:
	int xScreen(int t1, int t2);
	int yScreen(int t1, int t2);
	int xHard(int t1, int t2);
	int yHard(int t1, int t2);
	int xScreen(int t1);
	int yScreen(int t1);
	int xHard(int t1);
	int yHard(int t1);

	// Collision detection:
	int bobCol(int t1);
	int bobCol(int t1, int t2, int t3);
	int spriteCol(int t1);
	int spriteCol(int t1, int t2, int t3);
	int spriteBobCol(int t1);
	int spriteBobCol(int t1, int t2, int t3);
	int bobSpriteCol(int t1);
	int bobSpriteCol(int t1, int t2, int t3);
	int col(int t1);

	int vumeter(int t1);
	int xSprite(int t1);
	int ySprite(int t1);
	int iSprite(int t1);
	int xBob(int t1);
	int yBob(int t1);
	int iBob(int t1);
	int hrev(int a);
	int vrev(int a);
	int rev(int a);

	// AMOS Sprite and Bob instructions:
	void sprite(int a, double b, double c, int d);
	void sprite(int a, double b, double c);
	void bob(int a, double b, double c, int d);
	void bob(int a, double b, double c);

	// AMOS Screen instructions:
	void screenOpen(int a, int b, int c, int d, int e);
	void screenSize(int a, int b, int c);
	void screenDisplay(int a, int b, int c);
	void screenDisplay(int a, int b, int c, int d, int e);
	void screenOffset(int a, int b, int c);
	void screenClose();
	void screenClose(int a);
	void screenClone(int a);
	void screen(int a);
	void doubleBuffer();
	void dualPlayfield(int a, int b);
	void dualPriority(int a, int b);

	// Required for Java:
	int booltoint(bool b);


	// Added: for AMAL compiler:
    
	// Here Move is implemented as two parts:
	void amalMoveInit(int CHAN, int a, int b, int c);
	void amalMoveRun(int CHAN, int movejumppoint, int movejumppoint2);
	// Not yet implemented - would need a variable number of input operators!
	void amalAnim(int CHAN, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k);
	void amalAnim(int CHAN, int a, int b, int c, int d, int e, int f, int g, int h, int i);
	void amalAnim(int CHAN, int a, int b, int c, int d, int e, int f, int g);
	void amalAnim(int CHAN, int a, int b, int c, int d, int e);
	void amalAnim(int CHAN, int a, int b, int c);
	// Part implemented here:
	void amalAnimInit(int CHAN, int a);
	// TO DO - need to test this works with compiler:
	void amalAnimInitPair(int CHAN, int offset, int a, int b);
	void amalJump(int CHAN, int progpointer);
	void amalDirect(int CHAN, int progpointer);
	void amalPause(int CHAN, int progpointer);
	void amalWait(int CHAN, int progpointer);
	void amalInitAutotest(int CHAN, int start, int end);
	void amalEndAutotest(int CHAN);
	void amalExitAutotest(int CHAN);
	void amalEnd(int CHAN);
	// TO DO - Does this work? ("On") - run from AUtotest, should restart main program from Wait.
	void amal_On(int CHAN);

	// Access AMAL registers:
	int amalGetGlobal(int reg);
	int amalGetLocal(int CHAN, int reg);
	int amalGetSpecial(int CHAN, int reg);
	int amalGetX(int CHAN);
	int amalGetY(int CHAN);
	int amalGetA(int CHAN);
	void amalSetGlobal(int reg, int value);
	void amalSetLocal(int CHAN, int reg, int value);

	// These two are used for AMAL For loops:
	void amalIncGlobal(int reg);
	void amalIncLocal(int CHAN, int reg);
	void amalSetSpecial(int CHAN, int reg, int value);
	void amalSetX(int CHAN, int value);
	void amalSetY(int CHAN, int value);
	void amalSetA(int CHAN, int value);

	// Added for int/bool expressions:
	bool istrue(bool value);
	bool istrue(int value);
	bool isfalse(bool value);
	bool isfalse(int value);

	// Compiled version (for now, with int - memory bank strings with int will be later):
	void amal(int p1, int p2);

	// AMOS BASIC AMAL instructions:
	void amal(int p1, string p2);
	int amreg(int t1);
	int amreg(int t1, int t2);
	void setAmreg(int t1, int t2);
	void setAmreg(int t1, int t2, int t3);
	void amalOn(int p1);
	void amalOn();
	void amalFreeze(int p1);
	void amalFreeze();
	void amalOff();
	void amalOff(int p1);
	void channelToSprite(int p1, int p2);
	void channelToBob(int p1, int p2);
	void channelToScreenDisplay(int p1, int p2);
	void channelToScreenOffset(int p1, int p2);
	void channelToScreenSize(int p1, int p2);
	void channelToRainbow(int p1, int p2);
	void synchroOff();
	void synchroOn();
	void synchro();
	void AMAL_Do(bool isfunction);
	void AMAL_ANIM();
	int amalPLay(int CHAN, int t1);


	// Load image or IFF file (supports other formats instead for now):
	void loadIff(string a, int b);
	void loadIff(string a);

	// Banks:
	// Load a bank (folder of sprites for now)
	// TO DO - faux packed pictures (with unpack).
	void load(string a, int b);
	void load(string a, int b, int scale);
	void erase(int a);

	// Hot Spot control:
	void hotspot(int a, int b, int c);
	void hotspot(int a, int b);

	// Load a Sprite bank from AMOS Basic .abk files:
	int loadamosabk(string fileName, int bank);

	// Drawing methods (moved/wrapped to GameEngineWrapper):
	int text(int x, int y, string a);
	int textlength(string a);
	int pastebob(int x, int y, int a);
	int pasteicon(int x, int y, int a);
	int ink(int a);
	int pen(int a);
	int paper(int a);
	int plot(int x, int y, int a);
	int plot(int x, int y);
	int draw(int x1, int y1, int x2, int y2);
	int bar(int x1, int y1, int x2, int y2);
	int box(int x1, int y1, int x2, int y2);
	int circle(int x1, int y1, int r1);
	int ellipse(int x1, int y1, int r1, int r2);

	// Added from Myqu:
	void _default();

	int lowres();
	int hires();
	int laced();
	int timer();
	void setTimer(int t1);

	///////////////////////////////////////////////////////
	// Maths Functions
	void degree();
	void radian();
	double _sin(double t1);
	double _cos(double t1);
	double _tan(double t1);
	double _asin(double t1);
	double _acos(double t1);
	double _atan(double t1);
	double pi();
	int _true();
	int _false();
	//bool _true();
	//bool _false();

	///////////////////////////////////////////////////////
	// String Functions
	int len(string t1);
	string upper(string t1);
	string lower(string t1);
	string _string(string t1, int t2); // NOTE: CHANGED!
	string repeat(string t1, int t2);
	string space(int t1);
	string flip(string i);
	double val(string i);
	//int val(string i);
	string str(double i);
	string stri(int i); // Added
	//string str(int i); //TODO: ambiguous!
	int asc(string a);
	int asc(char a);
	string chr(int a);

	string hex(int i);

	// Added - for binary:
	string bin(int input);
	int binstringtoint(string input);

	///////////////////////////////////////////////////////
	// AMOS Rainbows
	void rainbow(int t1, int t2, int t3, int t4);
	void rain(int t1, int t2, int t3); // Which order??? ???? number t1, line t2 = colour t3......
	void setRainbow(int t1, int t2, int t3, string t4, string t5, string t6);
	void rainbowDel();
	void rainbowDel(int a);

	// Misc (to sort):
	void hide();
	void hideOn();
	void hideOff();
	void updateEvery(int a);
	void flashOff();
	void flash(int a, string b);
	void bobOff(int a);
	void bobOff();
	void setBob(int a, int b, int c, int d);
	void spriteOff(int a);
	void spriteOff();
	void setSpriteBuffer(int a);

	// May require extended syntax:
	void setReg(int a, int b);
	void unpack(int a, int b);

	// To do - tests for Environment Generator:
	bool isScreen(int a);
	bool isNotScreen(int a);
	bool isBank(int a);
	bool isNotBank(int a);
	bool isReg(int a, int b);

	// New:
	void bell();
	void bell(int pitch);
	void shoot();
	void boom();
};
#endif


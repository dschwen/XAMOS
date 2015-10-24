/////////////////////////////////////////////////////////////////
// XAMOS - AMOS BASIC reimplemented!                           //
// (C) 2012 Mequa Innovations                                  //
/////////////////////////////////////////////////////////////////

#ifndef XAMOS_H
#define XAMOS_H

#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

#include "AMOS_System.h"
#include "GameEngineWrapper.h"
#include "Console.h"


class AMOS_System;
class GameEngineWrapper;
class Console;

using namespace std;


class XAMOS
{
	bool runonly;
	bool ntsc;
	int numprograms;

	AMOS_System* am;
	GameEngineWrapper* wrapper;
	XAMOS* mthis;
	Console* console;

public:
	int editingchannel; // = 1;
	bool viewingtranslatedcode; // = false;
	bool editingenvironment; // = false;
	bool editingamos; // = true;

	string amosCode;
	string environmentCode;
	vector<string> AMALCode;
	string inputstring;

	XAMOS();
	int mymain(int argc, char *args[]);
	string lower(string t1);
	string processargs(int argc, char *args[]);
	int initGame(int argc, char *args[]);
	int startGame(int argc, char *args[]);

	string stri(int i);
	string consolelauncher();

	void demoinit(vector<string> textline);
	void demodump();
	void dumprawcode(string textline);
	void dumprawcode_old(vector<string> textline);
	string loadfiletotext(string filename);
	vector<string> loadfiletotext_old(string filename);
	string defaultEnvGenString();
	vector<string> loadfile(bool usefile, string filename, vector<string> AMALCode);
};

#endif


/////////////////////////////////////////////////////////////////
// XAMAL - AMOS Animation Language reimplemented in C++!       //
// By Stephen Harvey-Brooks - (C) 2012 Mequa Innovations       //
/////////////////////////////////////////////////////////////////

#ifndef AMAL_DEBUGTEST_H
#define AMAL_DEBUGTEST_H

#include "AMOS_System.h"
#include <vector>
#include <string>

using namespace std;

class AMALDebugTest
{
public:
	AMOS_System* AM;
	AMALDebugTest();
	AMALDebugTest(AMOS_System* AMi);

	int mymain(int argc, char* args[]);

	//vector<string> loadfile(string filename, vector<string> AMALCode);
	vector<string> loadfile(string filename);
};

#endif


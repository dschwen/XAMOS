#ifndef ACTIVEOBJECT_H
#define ACTIVEOBJECT_H

#include <vector>
#include <string>

#include "Mytype.h"
#include "Mytypearray.h"

using std::vector;
using std::string;

class ActiveObject
{
public:

	vector <Mytype> myvars;
	vector <Mytypearray> myarrays;
	int ObjectBrain;

	// Added for Java - AMAL-style pause:
	int currentpos; // = 0;
	int paused; // = 0;

	// Moved Procedure Param returns here (was in AMOS_System.java):
	string myparamstring; // = "";
	double myparamfloat; // = 0.0;
	int myparamint; // = 0;
	int myparamtype; // = 0; // 0=int, 1=double, 2=string

	ActiveObject();
};
#endif

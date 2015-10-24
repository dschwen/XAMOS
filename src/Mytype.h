#ifndef MYTYPE_H
#define MYTYPE_H

#include <string>

using std::string;

class Mytype
{
public:

	int t;
	double d;
	string s;

	Mytype();

	void erase();
	void set(double a);
	void set(string a);
	void dump();
	void add(double b);
	void add(string b);

	Mytype* copy();

	friend void operator+=(Mytype a, double b);

	// Added:
	string floattostring(double value);
};
#endif

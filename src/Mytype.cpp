#include <stdio.h>
#include <sstream>

#include "Mytype.h"

using std::stringstream;


Mytype::Mytype()
{
	t=0;
	d=0;
}

void Mytype::erase()
{
	t=0;
	d=0;
}
void Mytype::set(double a)
{
	t=0;
	d=a;
}
void Mytype::set(string a)
{
	t=1;
	s=a;
}

// Used below:
string Mytype::floattostring(double value)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << value;
	return ss.str();
}
void Mytype::dump()
{
	if (t == 0)
		printf("%s\n", this->floattostring(d).c_str());
	else if (t == 1)
		printf("%s\n", s.c_str());
}

void Mytype::add(double b)
{
	if (t == 0)
		d += b;
	else if (t == 1)
		s += this->floattostring(b);
}
void Mytype::add(string b)
{
	if (t == 0)
	{
		t = 1;
		s = b;
	}
	else if (t == 1)
		s += b;
}

// Added to produce a duplicate object:
Mytype* Mytype::copy()
{
	Mytype* ret = new Mytype();
	ret->t = this->t;
	ret->d = this->d;
	ret->s = this->s;
	return ret;
}


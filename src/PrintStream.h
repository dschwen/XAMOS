#ifndef PRINTSTREAM_H
#define PRINTSTREAM_H

#include <string>

using std::string;

// TODO - move this to PrintStream.h or similar:
class PrintStream
{
public:
	PrintStream();
	void print(string a);
	void println(string a);
	void println();
};

#endif


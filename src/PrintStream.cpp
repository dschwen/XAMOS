#include "PrintStream.h"
#include <iostream>

using namespace std;

PrintStream::PrintStream()
{
}
void PrintStream::print(string a)
{
	cout << a;
}
void PrintStream::println(string a)
{
	cout << a << "\n";
}
void PrintStream::println()
{
	cout << "\n";
}


#ifndef TOKENISERRETURN_H
#define TOKENISERRETURN_H
class TokeniserReturn
{
public:

	// 0 = Error or no instruction - no arguments.
	// 1 = Standard instruction - 0, 1 or 2 [multiple] arguments) [type instflag].
	// 2 = Function call [type instflag] (not evaluated here) - 0, 1 or 2 [multiple] arguments).
	// (Note: temp[arg] set with result [arg2 the first argument], NOT type instflag [as below].
	// 3 = Operator - 2 arguments (1 for NOT or !), temp[instflag] set with result.
	// 4 = Set temporary variable instflag (should become redundant soon - when optimised)
	// 5 = Set variable, 1 argument (arg), variable array index = instflag
	// 6 = Set special variable, 1 argument (arg), particular variable = instflag...

	int insttype;
	// Used for referencing the instruction array for instructions, functions, temps...
	int instflag;
	// 2 parameters/arguments only at present:
	// For variables, string constants and temps - an array reference.

	int numargs; // USE THIS!
	double args[20]; // was *
	int argtypes[20]; // was *

	//int arg, arg2, arg3;
	//int argtype, argtype2, argtype3;

	// 0 = constant numbers, 1=variables, 3=string constants,
	// 5=tempvalue, -1=null (no [valid] expression)
	// Note: type 2 (functions) and type 4 (operators) become 5 (tempvalues)
};
#endif


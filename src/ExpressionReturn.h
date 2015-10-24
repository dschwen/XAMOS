#ifndef EXPRESSIONRETURN_H
#define EXPRESSIONRETURN_H
class ExpressionReturn
{
public:
	// 0 = constant numbers, 1=variables, 2=functions, 3=strings, 4=operators, 5=tempvalue, -1=null (no [valid] expression)
	int exptype;
	double expdata;
};
#endif

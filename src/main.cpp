#include "main.h"
#include "XAMOS.h"

//int main(int argc, char* args[])
//{
//	XAMOS* xamos = new XAMOS();
//	return xamos->main(argc, args);
//}

int main(int argc, char* args[])
{
	XAMOS* xamos = new XAMOS();
	return xamos->mymain(argc, args);
	return 0;
}


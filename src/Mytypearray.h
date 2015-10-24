#ifndef MYTYPEARRAY_H
#define MYTYPEARRAY_H

#include <vector>
#include <string>

#include "Mytype.h"

class Mytype;

using std::vector;
using std::string;

class Mytypearray
{
public:

	vector<Mytype*> arr;
	vector<int> dimensions;
	vector<int> dimensionsindex;
	int arrsize;

	Mytypearray(vector<int> newdimensions);
	void dimension(vector<int> newdimensions);
	//int getindexfrommulti(vector<int> multidimensions);
	int getindexfrommulti(int* multidimensions);

	//int set(vector<int> multidimensions, Mytype* val);
	int set(int* multidimensions, Mytype* val);
	int set(int num, Mytype* val);

	//Mytype* get(vector<int> multidimensions);
	Mytype* get(int* multidimensions);
	Mytype* get(int num);
};
#endif

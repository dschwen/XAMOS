#include <stdio.h>
#include "Mytypearray.h"


Mytypearray::Mytypearray(vector <int> newdimensions)
{
	this->dimension(newdimensions);
}

// For arrays:
void Mytypearray::dimension(vector<int> newdimensions)
{
	int size = 1;

	for (unsigned int n=0; n<newdimensions.size(); n++)
	{
		size *= newdimensions[n];

		// Create the dimensionsindex array to calculate later:
		dimensionsindex.push_back(0);
	}

	dimensions = newdimensions;

	arrsize = size;
	for (int temp=0; temp<size; temp++)
		arr.push_back(new Mytype());

	// Now calculate the dimensionsindex in reverse:
	size = 1;
	for (int n=newdimensions.size()-1; n>=0; n--)
	{
		dimensionsindex[n] = size;
		size *= newdimensions[n];
	}
}

// Get/set with multi-dimensional support:
int Mytypearray::getindexfrommulti(int* multidimensions)
{
	int num = 0;
	for (int n=0; n<multidimensions[0]; n++)
		num += dimensionsindex[n] * multidimensions[n+1];

	return num;
}
/*
int Mytypearray::getindexfrommulti(vector<int> multidimensions)
{
	int num = 0;
	for (unsigned int n=0; n<multidimensions.size(); n++)
		num += dimensionsindex[n] * multidimensions[n];

	return num;
}
*/

// Setter methods:
int Mytypearray::set(int* multidimensions, Mytype* val)
{
	return set(getindexfrommulti(multidimensions), val);
}
/*int Mytypearray::set(vector<int> multidimensions, Mytype* val)
{
	return set(getindexfrommulti(multidimensions), val);
}*/
int Mytypearray::set(int num, Mytype* val)
{
	if (num < arrsize)
	{
		//printf("Debug: Setting array index %d\n", num);
		arr[num] = val;
		return 0;
	}
	else
	{
		printf("Error: Array set index out of bounds!\n");
		return -1;
	}
}

// Getter methods:
Mytype* Mytypearray::get(int* multidimensions)
{
	return get(getindexfrommulti(multidimensions));
}
/*
Mytype* Mytypearray::get(vector<int> multidimensions)
{
	return get(getindexfrommulti(multidimensions));
}
*/
Mytype* Mytypearray::get(int num)
{
	if (num < arrsize)
	{
		//printf("Debug: Getting array index %d\n", num);
		return arr[num];
	}
	else
	{
		printf("Error: Array get index out of bounds!\n");
		return new Mytype(); //null;
	}
}

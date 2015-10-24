#include <string>

#include "ActiveObject.h"

ActiveObject::ActiveObject()
{
	this->currentpos=0;
	this->paused=0;

	this->myparamstring="";
	this->myparamfloat=0.0;
	this->myparamint=0;
	this->myparamtype=0; // 0=int, 1=double, 2=string
}

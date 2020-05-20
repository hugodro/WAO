/**************************************************
* File: dbObject.cc.
* Desc: Implementation of the basic db persistant object model.
* Module: AkraLog : WAO.
* Rev: 8 decembre 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/portableDefs.h>
#include "dbObject.h"


/**************************************************
* Implementation: ArrayDO.
**************************************************/

ArrayDO::ArrayDO(void)
{
    nbrInside= 0;
    arraySize= 32;
    values= new void *[arraySize];
}

ArrayDO::ArrayDO(unsigned int aSize)
{
    nbrInside= 0;
    arraySize= aSize;
    values= new void *[aSize];
}


ArrayDO::~ArrayDO(void)
{
    if (values != NULL) delete[] values;
}


void ArrayDO::addObject(void *anObject)
{
    if (nbrInside >= arraySize) {
	void **tmpValues= values;

	arraySize+= 32;
	values= new void *[arraySize];
	memcpy(values, tmpValues, (arraySize - 32) * sizeof(void *));
	delete[] tmpValues;
    }
    values[nbrInside++]= anObject;
}


void *ArrayDO::objectAt(unsigned int aPos)
{
    return ((aPos < nbrInside) ? values[aPos] : NULL);
}


unsigned int ArrayDO::count(void)
{
    return nbrInside;
}



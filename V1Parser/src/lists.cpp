/**************************************************
* File: lists.cc.
* Desc: Contains the definitions of the different lists used in the compilation process.
* Module: AkraLog : JavaComp.
* Rev: 4 juin 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

extern "C" {
#include <stdio.h>
#include <memory.h>
}
#include "lists.h"


/**************************************************
* Implementation: GenericList.
**************************************************/

GenericList::GenericList()
{
    init(32);
}


GenericList::GenericList(unsigned int initSize)
{
    init(initSize);
}


GenericList::~GenericList(void)
{
    delete[] elements;
}

void GenericList::init(unsigned int initSize)
{
    maxElements= initSize;
    elements= new void*[maxElements];
    memset(elements, 0, maxElements);
    nbrElements= 0;
}


unsigned int GenericList::count(void)
{
    return nbrElements;
}


boolean GenericList::addObject(void *object)
{
    if (nbrElements < maxElements) {
	elements[nbrElements++]= object;
     }
    else {
	maxElements*=  2;
	void **tmpElements= new void *[maxElements];
	memcpy(tmpElements, elements, sizeof(void *) * nbrElements);
	tmpElements[nbrElements++]= object;
	elements= tmpElements;
     }

    return true;	// ATTN: Should do a memory check and return conditional result.
}


boolean GenericList::removeObject(void *object)
{
    boolean result= false;
    for (unsigned int i= 0; i < nbrElements; i++) {
	if (elements[i] == object) {
	    result= true;
	    for (unsigned int j= i+1; j < nbrElements; j++, i++) {
		elements[i]= elements[j];
	    }
	    break;
	}
    }

    return result;
}


boolean GenericList::removeObjectAt(unsigned int position)
{
    boolean result= true;

    if (position < nbrElements) {
	elements[position]= NULL;
     }
    else result= false;

    return result;
}


boolean GenericList::removeLastObject(void)
{
    boolean result= true;

    if (nbrElements > 0) {
	nbrElements--;
	elements[nbrElements]= NULL;
     }
    else result= false;
    return result;
}


void *GenericList::voidObjectAt(unsigned int position)
{
    void *result= NULL;
    if (position < nbrElements) {
	result= elements[position];
     }

    return result;
}


void *GenericList::lastObject(void)
{
    void *result= NULL;
    if (nbrElements > 0) {
	result= elements[nbrElements-1];
     }

    return result;
}


void GenericList::removeAll(void)
{
    for (unsigned int i= 0; i < nbrElements; i++) elements[i]= NULL;
    nbrElements= 0;
}


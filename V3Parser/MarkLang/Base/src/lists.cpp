/**************************************************
* File: lists.cpp.
* Desc: Contains the definitions of the different lists used in the compilation process.
* Rev: 4 juin 1996 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/08/22 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: lists.cpp,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1.1.1  2000/09/01 07:33:30  hugo
* Initial Entry
*
**************************************************/

#include <memory>


#include "lists.h"


/**************************************************
* Implementation: xtnGenericList.
**************************************************/

xtnGenericList::xtnGenericList()
{
    init(32);
}


xtnGenericList::xtnGenericList(unsigned int initSize)
{
    init(initSize);
}


xtnGenericList::~xtnGenericList(void)
{
    delete[] elements;
}

void xtnGenericList::init(unsigned int initSize)
{
    maxElements= initSize;
    elements= new void*[maxElements];
    memset(elements, 0, maxElements);
    nbrElements= 0;
}


unsigned int xtnGenericList::count(void)
{
    return nbrElements;
}


bool xtnGenericList::addObject(void *object)
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


bool xtnGenericList::removeObject(void *object)
{
    bool result= false;
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


bool xtnGenericList::removeObjectAt(unsigned int position)
{
    bool result= true;

    if (position < nbrElements) {
	elements[position]= NULL;
     }
    else result= false;

    return result;
}


bool xtnGenericList::removeLastObject(void)
{
    bool result= true;

    if (nbrElements > 0) {
	nbrElements--;
	elements[nbrElements]= NULL;
     }
    else result= false;
    return result;
}


void *xtnGenericList::voidObjectAt(unsigned int position)
{
    void *result= NULL;
    if (position < nbrElements) {
	result= elements[position];
     }

    return result;
}


void *xtnGenericList::lastObject(void)
{
    void *result= NULL;
    if (nbrElements > 0) {
	result= elements[nbrElements-1];
     }

    return result;
}


void xtnGenericList::removeAll(void)
{
    for (unsigned int i= 0; i < nbrElements; i++) elements[i]= NULL;
    nbrElements= 0;
}


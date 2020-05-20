/**************************************************
* File: elementList.cc.
* Desc: Definition of the xtnCoreElementList class.
* Rev: 22 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/08/22 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: elementList.cpp,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1.1.1  2000/09/01 07:33:30  hugo
* Initial Entry
*
**************************************************/

#include "elementList.h"


/**************************************************
* Implementation: TypesList.
**************************************************/

bool xtnCoreElementList::addObject(xtnCoreElement *object)
{
    return xtnGenericList::addObject((void *)object);
}


xtnCoreElement *xtnCoreElementList::objectAt(unsigned int position)
{
    return (xtnCoreElement *)xtnGenericList::voidObjectAt(position);
}


/**************************************************
* Implementation: xtnCoreAttributeList.
**************************************************/

xtnCoreAttributeList::xtnCoreAttributeList(unsigned int initSize)
    : xtnGenericList(initSize)
{

}


bool xtnCoreAttributeList::addObject(xtnCoreAttribute *object)
{
    return xtnGenericList::addObject((void *)object);
}


xtnCoreAttribute *xtnCoreAttributeList::objectAt(unsigned int position)
{
    return (xtnCoreAttribute *)xtnGenericList::voidObjectAt(position);
}



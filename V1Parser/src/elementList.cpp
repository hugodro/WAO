/**************************************************
* File: elementList.cc.
* Desc: Definition of the SgmlElementList class.
* Module: WAO : SgmlParser.
* Rev: 22 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "elementList.h"


/**************************************************
* Implementation: TypesList.
**************************************************/

boolean SgmlElementList::addObject(SgmlElement *object)
{
    return GenericList::addObject((void *)object);
}


SgmlElement *SgmlElementList::objectAt(unsigned int position)
{
    return (SgmlElement *)GenericList::voidObjectAt(position);
}


/**************************************************
* Implementation: SgmlAttributeList.
**************************************************/

SgmlAttributeList::SgmlAttributeList(unsigned int initSize)
    : GenericList(initSize)
{

}


boolean SgmlAttributeList::addObject(SgmlAttribute *object)
{
    return GenericList::addObject((void *)object);
}


SgmlAttribute *SgmlAttributeList::objectAt(unsigned int position)
{
    return (SgmlAttribute *)GenericList::voidObjectAt(position);
}



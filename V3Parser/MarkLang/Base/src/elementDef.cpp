/**************************************************
* File: elementDef.cc.
* Desc: Implementation of the Core ML Element definition.
* Rev: 22 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/08/22 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: elementDef.cpp,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1.1.1  2000/09/01 07:33:30  hugo
* Initial Entry
*
**************************************************/

#include <ctype.h>
#include <string>
#include <stdlib.h>

#include <globDefs.h>

#include "elementDef.h"


/**************************************************
* Implementation: xtnCoreElementDef.
**************************************************/

xtnCoreElementDef::xtnCoreElementDef(char *aName)
{
    name= aName;
    attributes= NULL;
    arraySize= nbrAttributes= 0;
}


xtnCoreElementDef::~xtnCoreElementDef()
{
  if (arraySize > 0) {
	delete[] attributes;
  }
}


int xtnCoreElementDef::canIncludeElement(xtnCoreElementDef *aDef)
{
    // Response of an element inclusion request.
    return 0;
}


xtnCoreAttrDef *xtnCoreElementDef::getAttribute(char *aName)
{
  xtnCoreAttrDef *result= NULL;

  if (nbrAttributes > 0) {
    unsigned int i;

    for (i= 0; i < nbrAttributes; i++) {
      if (attributes[i]->isNamed(aName)) {
        result= attributes[i];
        break;
      }
    }
  }
  return result;
}


void xtnCoreElementDef::addAttribute(xtnCoreAttrDef *anAttr) {
  if (nbrAttributes == arraySize) {

    if (arraySize > 0) {
      xtnCoreAttrDef **tmpAttr;
      tmpAttr= attributes;
      arraySize= arraySize + 5;
      attributes= new xtnCoreAttrDef*[arraySize];
      for (unsigned int i= 0; i < nbrAttributes; i++)
        attributes[i]= tmpAttr[i];
      delete[] tmpAttr;
    }
    else {
      arraySize= 3;
      attributes= new xtnCoreAttrDef*[arraySize];
    }
  }
  attributes[nbrAttributes++]= anAttr;
}


/**************************************************
* Implementation: xtnCoreAttrDef.
**************************************************/

xtnCoreAttrDef::xtnCoreAttrDef(void)
{
    name= NULL;
    type= cdata;		// Default.
    utilFlag= implied;	// Default.
    next= NULL;
}


xtnCoreAttrDef::xtnCoreAttrDef(const char *aName, unsigned int aType, unsigned int aFlag)
{
    unsigned int tmpLng;

    name= new char[(tmpLng= strlen(aName)+1)];
    memcpy(name, aName, tmpLng);
    type= aType;
    utilFlag= aFlag;
    next= NULL;
}


xtnCoreAttrDef::~xtnCoreAttrDef(void)
{
// TODO.
}


void xtnCoreAttrDef::setDefinition(char *aName, unsigned int aType, unsigned int aFlag)
{
    unsigned int tmpLng;

    name= new char[(tmpLng= strlen(aName)+1)];
    memcpy(name, aName, tmpLng);

    type= aType;
    utilFlag= aFlag;
}


bool xtnCoreAttrDef::isNamed(char *aName)
{
    char *tmpChar= name;

    while (*tmpChar != '\0') {
	if (toupper(*tmpChar++) != toupper(*aName++)) {
	    return false;
	}
    }

    return true;
}


bool xtnCoreAttrDef::isAssignable(void)
{
    return (type != flag);
}


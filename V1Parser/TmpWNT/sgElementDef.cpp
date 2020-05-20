/**************************************************
* File: sgElementDef.cc.
* Desc: Implementation of the generic Sgml Element definition.
* Module: WAO : SgmlParser.
* Rev: 22 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/portableDefs.h>
#include <ctype.h>
#if defined(_WIN32)
#include <string.h>
#include <stdlib.h>
#endif
#include "sgElementDef.h"


/**************************************************
* Implementation: SgmlElementDef.
**************************************************/

SgmlElementDef::SgmlElementDef(char *aName, TagFlags firstFlag, TagFlags sndFlag)
{
    name= aName;
    startFlag= firstFlag;
    endFlag= sndFlag;
}


int SgmlElementDef::canIncludeElement(SgmlElementDef *aDef)
{
    // Response of an element inclusion request.
    return 0;
}


SgmlElementDef::TagFlags SgmlElementDef::startType(void)
{
    return startFlag;
}


SgmlElementDef::TagFlags SgmlElementDef::endType(void)
{
    return endFlag;
}


SgmlAttrDef *SgmlElementDef::getAttribute(char *aName)
{
    return NULL;	// By default, we don't handle attributes.
}


/**************************************************
* Implementation: SgmlAttrDef.
**************************************************/

SgmlAttrDef::SgmlAttrDef(void)
{
    name= NULL;
    type= cdata;		// Default.
    utilFlag= implied;	// Default.
}


SgmlAttrDef::SgmlAttrDef(char *aName, DataType aType, Flags aFlag)
{
    name= new char[strlen(aName)+1];
    strcpy(name, aName);
    type= aType;
    utilFlag= aFlag;
}


void SgmlAttrDef::setDefinition(char *aName, DataType aType, Flags aFlag)
{
    name= new char[strlen(aName)+1];
    strcpy(name, aName);
    type= aType;
    utilFlag= aFlag;
}


boolean SgmlAttrDef::isNamed(char *aName)
{
    char *tmpChar;

    while (*tmpChar != '\0') {
	if (toupper(*tmpChar++) != toupper(*aName++)) {
	    return false;
	}
    }

    return true;
}


boolean SgmlAttrDef::isAssignable(void)
{
    return (type != flag);
}


char *SgmlAttrDef::getName(void)
{
    return name;
}

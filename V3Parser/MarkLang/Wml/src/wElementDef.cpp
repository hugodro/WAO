/**************************************************
* File: wElementDef.cpp.
* Desc: Implementation of the WML Element definition.
* $Date: 2000/09/20 03:37:34 $
* Rev: 23 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/08/23 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: wElementDef.cpp,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
**************************************************/

#include <ctype.h>
#if defined(_WIN32)
#include <string>
#else
#include <string.h>
#endif

#include <globDefs.h>

#include "wElementDef.h"


xtnWmlElementDef::xtnWmlElementDef(char *aName)
  : xtnCoreElementDef(aName)
{
    attributes= 0;
    // ATTN-980323 [HD]: The following should generate an error on 'unknownTag'.
    tag= xtnWmlDTD::identifyTag(aName);
}


bool xtnWmlElementDef::canInclude(xtnWmlDTD::WmlTags aTag)
{
/* TODO-000123 [HD]: Implement the WML rules. */

    if ((tag == xtnWmlDTD::tPcdata) || (tag == xtnWmlDTD::tCdata)) return false;
    if (aTag == xtnWmlDTD::tComment) return true;
    switch(tag) {
	case xtnWmlDTD::tWml:		// Accept the out of bounds data.
		// TODO-000123 [HD: Review for the real set of rules.
	    return true;
	case xtnWmlDTD::tP:
	    return (aTag == xtnWmlDTD::tPcdata);
    }

    return false;
}


/**************************************************
* Implementation: xtnWmlAttrDef.
**************************************************/

xtnWmlAttrDef::xtnWmlAttrDef(void)
    : xtnXmlAttrDef()
{

}


xtnWmlAttrDef::xtnWmlAttrDef(char *aName, unsigned int aType, Flags aFlag)
    : xtnXmlAttrDef(aName, aType, aFlag)
{

    if (name != NULL) {
	unsigned int i;

	i= strlen(name);
	if (i > 0) {
	    i--;
	    for (; i != 0;) {
		name[i]= tolower(name[i]);
		i--;
	    }
	    name[0]= tolower(aName[0]);
	}
    }
}


void xtnWmlAttrDef::setDefinition(char *aName, unsigned int aType, Flags aFlag)
{
    xtnCoreAttrDef::setDefinition(aName, aType, aFlag);

    if (name != NULL) {
	unsigned int i;

	i= strlen(name);
	if (i > 0) {
	    i--;
	    for (; i != 0;) {
		name[i]= tolower(name[i]);
		i--;
	    }
	    name[0]= tolower(aName[0]);
	}
    }
}


bool xtnWmlAttrDef::isNamed(char *aName)
{
    if (name != NULL)
	return (strcmp(name, aName) == 0);
    else
	return 1;
}



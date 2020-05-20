/**************************************************
* File: wElementDef.cc.
* Desc: Implementation of the WML Element definition.
* Module: WAO : SgmlParser.
* Rev: 23 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <ctype.h>
#if defined(_WIN32)
#include <string.h>
#endif
#include "wElementDef.h"


WmlElementDef::WmlElementDef(char *aName)
    : SgmlElementDef(aName, SgmlElementDef::mandatory, SgmlElementDef::mandatory)
{
    nbrAttributes= 0;
    attributes= 0;
    // ATTN-980323 [HD]: The following should generate an error on 'unknownTag'.
    tag= WmlDTD::identifyTag(aName);
}


boolean WmlElementDef::canInclude(WmlDTD::WmlTags aTag)
{
/* TODO-000123 [HD]: Implement the WML rules. */

    if ((tag == WmlDTD::tPcdata) || (tag == WmlDTD::tCdata)) return false;
    if (aTag == WmlDTD::tComment) return true;
    switch(tag) {
	case WmlDTD::tWml:		// Accept the out of bounds data.
		// TODO-000123 [HD: Review for the real set of rules.
	    return (aTag == WmlDTD::tPcdata);
	    break;
    }

    return false;
}


SgmlAttrDef *WmlElementDef::getAttribute(char *aName)
{
    SgmlAttrDef *result= NULL;

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


WmlDTD::WmlTags WmlElementDef::getTag(void)
{
    return tag;
}


/**************************************************
* Implementation: WmlAttrDef.
**************************************************/

WmlAttrDef::WmlAttrDef(void)
    : SgmlAttrDef()
{

}


WmlAttrDef::WmlAttrDef(char *aName, DataType aType, Flags aFlag)
    : SgmlAttrDef(aName, aType, aFlag)
{
    unsigned int i;

    i= strlen(name);
    i--;
    for (; i != 0;) {
	name[i]= tolower(name[i]);
	i--;
    }
    name[0]= tolower(aName[0]);
}


void WmlAttrDef::setDefinition(char *aName, DataType aType, Flags aFlag)
{
    SgmlAttrDef::setDefinition(aName, aType, aFlag);
    unsigned int i;

    i= strlen(name);
    i--;
    for (; i != 0;) {
	name[i]= tolower(name[i]);
	i--;
    }
    name[0]= tolower(aName[0]);
}


boolean WmlAttrDef::isNamed(char *aName)
{
	if (name != NULL)
        return (strcmp(name, aName) == 0);
	else
	    return 1;
}



/**************************************************
* File: hdElementDef.cpp.
* Desc: Implementation of the HDML Element definition.
* $Date: 2000/09/20 03:37:34 $
* Rev: 2000/09/03 : REV 1 : Hugo DesRosiers : Creation.
* $Log: hdElementDef.cpp,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1  2000/09/05 07:13:40  hugo
* Initial entry of real parsing/generating HDML support.
*
**************************************************/

#include <ctype.h>
#if defined(_WIN32)
#include <string>
#endif

#include <globDefs.h>

#include "hdElementDef.h"


xtnHdmlElementDef::xtnHdmlElementDef(char *aName)
  : xtnCoreElementDef(aName)
{
    attributes= 0;
    // ATTN-980323 [HD]: The following should generate an error on 'unknownTag'.
    tag= xtnHdmlDTD::identifyTag(aName);
}


bool xtnHdmlElementDef::canInclude(xtnHdmlDTD::HdmlTags aTag)
{
/* TODO-000123 [HD]: Implement the HDML rules. */

    if ((tag == xtnHdmlDTD::tPcdata) || (tag == xtnHdmlDTD::tCdata)) return false;
    if (aTag == xtnHdmlDTD::tComment) return true;
    switch(tag) {
	case xtnHdmlDTD::tAction:
	    return (aTag == xtnHdmlDTD::tPcdata);

	case xtnHdmlDTD::tB:
	case xtnHdmlDTD::tBr:
	case xtnHdmlDTD::tCenter:
	case xtnHdmlDTD::tI:
	case xtnHdmlDTD::tLine:
	case xtnHdmlDTD::tRight:
	case xtnHdmlDTD::tTab:
	case xtnHdmlDTD::tWrap:
	    return (xtnHdmlDTD::isFromEntity(aTag, xtnHdmlDTD::eText));

	case xtnHdmlDTD::tCe:
	    return (aTag == xtnHdmlDTD::tPcdata);

	case xtnHdmlDTD::tChoice:
	    return ((aTag == xtnHdmlDTD::tAction) || (aTag == xtnHdmlDTD::tCe)
		    || (xtnHdmlDTD::isFromEntity(aTag, xtnHdmlDTD::eText)));

	case xtnHdmlDTD::tDeck:
	    return ((aTag == xtnHdmlDTD::tAction) || (xtnHdmlDTD::isFromEntity(aTag, xtnHdmlDTD::eCard)));

	case xtnHdmlDTD::tDisplay:
	case xtnHdmlDTD::tEntry:
	    return ((aTag == xtnHdmlDTD::tAction) || (xtnHdmlDTD::isFromEntity(aTag, xtnHdmlDTD::eText)));

	case xtnHdmlDTD::tImg:
	    return false;

	case xtnHdmlDTD::tNoDisplay:
	    return (aTag == xtnHdmlDTD::tAction);
    }

    return false;
}


/**************************************************
* Implementation: xtnHdmlAttrDef.
**************************************************/

xtnHdmlAttrDef::xtnHdmlAttrDef(void)
  : xtnCoreAttrDef()
{

}


xtnHdmlAttrDef::xtnHdmlAttrDef(char *aName, unsigned int aType, Flags aFlag)
    : xtnCoreAttrDef(aName, aType, aFlag)
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


void xtnHdmlAttrDef::setDefinition(char *aName, unsigned int aType, Flags aFlag)
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


bool xtnHdmlAttrDef::isNamed(char *aName)
{
    if (name != NULL)
	return (strcmp(name, aName) == 0);
    else
	return 1;
}



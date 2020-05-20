/**************************************************
* File: htElementDef.cc.
* Desc: Implementation of the HTML Element definition.
* Module: WAO : SgmlParser.
* Rev: 22 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <ctype.h>
#if defined(_WIN32)
#include <string.h>
#endif
#include "htElementDef.h"


HtmlElementDef::HtmlElementDef(char *aName, TagFlags firstFlag, TagFlags sndFlag)
    : SgmlElementDef(aName, firstFlag, sndFlag)
{
    nbrAttributes= 0;
    attributes= 0;
	// ATTN-980323 [HD]: The following should generate an error on 'unknownTag'.
    tag= HtmlDTD::identifyTag(aName);
}


boolean HtmlElementDef::canInclude(HtmlDTD::HtmlTags aTag)
{
    if ((tag == HtmlDTD::tPcdata) || (tag == HtmlDTD::tCdata)) return false;
    if (aTag == HtmlDTD::tComment) return true;
    switch(tag) {
	case HtmlDTD::tHtml:		// Accept the out of bounds data.
	    return (aTag == HtmlDTD::tPcdata);
	    break;
	case HtmlDTD::tHead:
	    return (HtmlDTD::isFromEntity(aTag, HtmlDTD::headContent) || HtmlDTD::isFromEntity(aTag, HtmlDTD::headMisc));
	    break;
	case HtmlDTD::tTitle:
	    return (aTag == HtmlDTD::tPcdata);
	    break;
	case HtmlDTD::tStyle:
	case HtmlDTD::tScript:
	    return (aTag == HtmlDTD::tPcdata);
	    break;
	case HtmlDTD::tBody:
	    return (HtmlDTD::isFromEntity(aTag, HtmlDTD::bodyContent));
	    break;
	case HtmlDTD::tH1: case HtmlDTD::tH2: case HtmlDTD::tH3:
	case HtmlDTD::tH4: case HtmlDTD::tH5: case HtmlDTD::tH6:
	    return (HtmlDTD::isFromEntity(aTag, HtmlDTD::text));
	    break;
	case HtmlDTD::tAddress:
	    return (HtmlDTD::isFromEntity(aTag, HtmlDTD::addressContent));
	    break;
	case HtmlDTD::tP:
	    return (HtmlDTD::isFromEntity(aTag, HtmlDTD::text));
	    break;
	case HtmlDTD::tUl:
	case HtmlDTD::tOl:
	    return (aTag == HtmlDTD::tLi);
	    break;
	case HtmlDTD::tLi:
	    return (HtmlDTD::isFromEntity(aTag, HtmlDTD::flow));
	    break;
	case HtmlDTD::tDl:
	    return ((aTag == HtmlDTD::tDt) || (aTag == HtmlDTD::tDd));
	    break;
	case HtmlDTD::tDt:
	    return (HtmlDTD::isFromEntity(aTag, HtmlDTD::text));
	    break;
	case HtmlDTD::tDd:
	    return (HtmlDTD::isFromEntity(aTag, HtmlDTD::flow));
	    break;
	case HtmlDTD::tDir:
	case HtmlDTD::tMenu:
	    return (aTag == HtmlDTD::tLi);
	    break;
	case HtmlDTD::tPre:
	    if (HtmlDTD::isFromEntity(aTag, HtmlDTD::preExclusion)) return false;
	    return (HtmlDTD::isFromEntity(aTag, HtmlDTD::text));
	    break;
	case HtmlDTD::tDiv:
	case HtmlDTD::tCenter:
	case HtmlDTD::tBlockquote:
	    return (HtmlDTD::isFromEntity(aTag, HtmlDTD::bodyContent));
	    break;
	case HtmlDTD::tForm:
	    if (aTag == HtmlDTD::tForm) return false;
	    return (HtmlDTD::isFromEntity(aTag, HtmlDTD::bodyContent));
	    break;
	case HtmlDTD::tTable:
	    return ((aTag == HtmlDTD::tCaption) || (aTag == HtmlDTD::tTr));
	    break;
	case HtmlDTD::tCaption:
	    return (HtmlDTD::isFromEntity(aTag, HtmlDTD::text));
	    break;
	case HtmlDTD::tTr:
	    return ((aTag == HtmlDTD:: tTh) || (aTag == HtmlDTD:: tTd));
	    break;
	case HtmlDTD::tTh:
	case HtmlDTD::tTd:
	    return (HtmlDTD::isFromEntity(aTag, HtmlDTD::bodyContent));
	    break;
	case HtmlDTD::tTt:		case HtmlDTD::tI:
	case HtmlDTD::tB:		case HtmlDTD::tU:
	case HtmlDTD::tStrike:	case HtmlDTD::tBig:
	case HtmlDTD::tSmall:	case HtmlDTD::tSub:
	case HtmlDTD::tSup:	case HtmlDTD::tEm:
	case HtmlDTD::tStrong:	case HtmlDTD::tDfn:
	case HtmlDTD::tCode:	case HtmlDTD::tSamp:	case HtmlDTD::tKbd:	case HtmlDTD::tVar:
	case HtmlDTD::tCite:
	    return (HtmlDTD::isFromEntity(aTag, HtmlDTD::text));
	    break;
	case HtmlDTD::tA:
	    if (aTag == HtmlDTD::tA) return false;	// Stop recursion.
	    if (aTag == HtmlDTD::tCenter) return true;	// ATTN: Non Html 3.2 conforment.
	    if (aTag == HtmlDTD::tSpan) return true;	// ATTN: Non Html 3.2 conforment.
	    return (HtmlDTD::isFromEntity(aTag, HtmlDTD::text));
	    break;
	case HtmlDTD::tApplet:
	    if (aTag == HtmlDTD::tParam) return true;
	    return (HtmlDTD::isFromEntity(aTag, HtmlDTD::text));
	    break;
	case HtmlDTD::tFont:
	    return (HtmlDTD::isFromEntity(aTag, HtmlDTD::text));
	    break;
	case HtmlDTD::tMap:
	    return (aTag == HtmlDTD::tArea);
	    break;
	case HtmlDTD::tSelect:
	    return (aTag == HtmlDTD::tOption);
	    break;
	case HtmlDTD::tOption:
	    return (aTag == HtmlDTD::tPcdata);
	    break;
	case HtmlDTD::tTextarea:
	    return (aTag == HtmlDTD::tPcdata);
	    break;
	case HtmlDTD::tSpan:
	    return (HtmlDTD::isFromEntity(aTag, HtmlDTD::text));
	    break;
    }

    return false;
}


SgmlAttrDef *HtmlElementDef::getAttribute(char *aName)
{
    SgmlAttrDef *result= NULL;

    if (nbrAttributes > 0) {
	unsigned int i;

	for (i= 0; i < nbrAttributes; i++) {
	    if (attributes[i].isNamed(aName)) {
		result= &attributes[i];
		break;
	    }
	}
    }
    return result;
}


HtmlDTD::HtmlTags HtmlElementDef::getTag(void)
{
    return tag;
}


/**************************************************
* Implementation: HtmlAttrDef.
**************************************************/

HtmlAttrDef::HtmlAttrDef(void)
    : SgmlAttrDef()
{

}


HtmlAttrDef::HtmlAttrDef(char *aName, DataType aType, Flags aFlag)
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


void HtmlAttrDef::setDefinition(char *aName, DataType aType, Flags aFlag)
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


boolean HtmlAttrDef::isNamed(char *aName)
{
    return (strcmp(name, aName) == 0);
}



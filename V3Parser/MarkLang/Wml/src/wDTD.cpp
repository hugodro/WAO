/**************************************************
* File: wDTD.cpp.
* Desc: Implementation of an optimized DtdDef for WML 1.1.
* $Date: 2000/09/20 03:37:34 $
* Rev: 19 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/08/23 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: wDTD.cpp,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
**************************************************/

// TMPTMP: DEBUG:
#include <iostream>
#if defined(_WIN32)
using std::cerr;
#endif

#if defined(_WIN32)
#include <string>
#endif

#include <coreml/xElementDef.h>

#include "wElements.h"
#include "wDoc.h"
#include "wElementDef.h"
#include "wDTD.h"


char *xtnWmlDTD::tagNames[xtnWmlDTD::numOfElements]= {
    "A", "ACCESS", "ANCHOR",
    "B", "BIG", "BR",
    "CARD",
    "DO",
    "EM",
    "FIELDSET",
    "GO",
    "HEAD",
    "I", "IMG", "INPUT",
    "META",
    "NOOP",
    "ONEVENT", "OPTGROUP", "OPTION",
    "P", "POSTFIELD", "PREV",
    "REFRESH",
    "SELECT", "SETVAR", "SMALL", "STRONG",
    "TABLE", "TD", "TEMPLATE", "TIMER", "TR",
    "U",
    "WML"
    , NULL, NULL		// tPcData and tCdata have no tag names.
};


xtnWmlElementDef *xtnWmlDTD::elementDef[xtnWmlDTD:: numOfElements] = { NULL };


xtnWmlDTD::WmlTags xtnWmlDTD::identifyTag(char *aName)
{
    unsigned int i;

    if (aName != NULL) {
	for (i= 0; i < numOfElements - 2; i++) {	// The last two elements (tPcData, tCdata) have no names.
	    if (strcmp(tagNames[i], aName) == 0) {
		return (WmlTags)i;
	    }
	}
    }
    return unknownTag;
}


xtnWmlElementDef *xtnWmlDTD::getElementDef(xtnWmlDTD::WmlTags aTag)
{
    return elementDef[aTag];
}


xtnWmlDTD::xtnWmlDTD()
{
    loadDefinitions();
}


xtnWmlDTD::~xtnWmlDTD()
{
// TODO.
}


xtnCoreDoc *xtnWmlDTD::createConformentDoc(char *aName)
{
    return new xtnWmlDoc(aName, this);
}


xtnWmlElement *xtnWmlDTD::instanciateType(WmlTags aType)
{
    switch(aType) {
	case tA:
	    return new xtnWAnchorMin();
	    break;

	case tAccess:
	    return new xtnWAccess();
	    break;

	case tAnchor:
	    return new xtnWAnchor();
	    break;

	case tB:
	    return new xtnWBold();
	    break;

	case tBig:
	    return new xtnWBig();
	    break;

	case tBr:
	    return new xtnWBreak();
	    break;

	case tCard:
	    return new xtnWCard();
	    break;

	case tDo:
	    return new xtnWDo();
	    break;

	case tEm:
	    return new xtnWEm();
	    break;

	case tFieldset:
	    return new xtnWFieldSet();
	    break;

	case tGo:
	    return new xtnWGo();
	    break;

	case tHead:
	    return new xtnWHead();
	    break;

	case tI:
	    return new xtnWItalic();
	    break;

	case tImg:
	    return new xtnWImg();
	    break;

	case tInput:
	    return new xtnWInput();
	    break;

	case tMeta:
	    return new xtnWMeta();
	    break;

	case tNoop:
	    return new xtnWNoop();
	    break;

	case tOnevent:
	    return new xtnWOnEvent();
	    break;

	case tOptgroup:
	    return new xtnWOptGroup();
	    break;

	case tOption:
	    return new xtnWOption();
	    break;

	case tP:
	    return new xtnWPara();
	    break;

	case tPostfield:
	    return new xtnWPostField();
	    break;

	case tPrev:
	    return new xtnWPrev();
	    break;

	case tRefresh:
	    return new xtnWRefresh();
	    break;

	case tSelect:
	    return new xtnWSelect();
	    break;

	case tSetvar:
	    return new xtnWSetVar();
	    break;

	case tSmall:
	    return new xtnWSmall();
	    break;

	case tStrong:
	    return new xtnWStrong();
	    break;

	case tTable:
	    return new xtnWTable();
	    break;

	case tTd:
	    return new xtnWTableData();
	    break;

	case tTemplate:
	    return new xtnWTemplate();
	    break;

	case tTimer:
	    return new xtnWTimer();
	    break;

	case tTr:
	    return new xtnWTableRow();
	    break;

	case tU:
	    return new xtnWUnderscore();
	    break;

	case tWml:
	    return new xtnWWml();
	    break;

	case tPcdata :
	    return new xtnWPcData();
	    break;
    }
    return NULL;
}


bool xtnWmlDTD::useVersion(char *versName)
{
// TODO-000823 [HD]: Pick up the correct version.
// By default, the version will be "-//W3C//DTD WML 1.1//EN".
    return true;
}


void xtnWmlDTD::loadDefinitions(void)
{
    xtnWmlAttrDef **coreAttributes;
    xtnWmlAttrDef **cardev;
    unsigned int tmpNbrAttrib;
    WmlTags tmpTag;

/* TODO-000123 [HD]: come up with a heap of xtnWmlAttrDef and xtnWmlElementDef, so that instances can
 *    be deleted without causing past-due reference pointers.  This is the case now with the attributes
 *    array in the elementDef, and it will be the case with the rule array in the entityDef.
*/

    name= new char[25];
    strcpy(name, "-//W3C//DTD WML 1.1//EN");

    coreAttributes= new xtnWmlAttrDef*[2];
    coreAttributes[0]= new xtnWmlAttrDef("id", xtnXmlAttrDef::id, xtnCoreAttrDef::implied);
    coreAttributes[1]= new xtnWmlAttrDef("class", xtnCoreAttrDef::cdata, xtnCoreAttrDef::implied);

    /*** Decks and Cards. ***/
    /* Rule: (head?, template?, card+). */
    tmpTag= tWml; tmpNbrAttrib= 9;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **)new xtnWmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new xtnWmlAttrDef("xml:lang", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= coreAttributes[0];
    elementDef[tmpTag]->attributes[2]= coreAttributes[1];

    cardev= new xtnWmlAttrDef*[3];
    cardev[0]= new xtnWmlAttrDef("onenterforward", xtnCoreAttrDef::cdata, xtnCoreAttrDef::implied);
    cardev[1]= new xtnWmlAttrDef("onenterbackward", xtnCoreAttrDef::cdata, xtnCoreAttrDef::implied);
    cardev[2]= new xtnWmlAttrDef("ontimer", xtnCoreAttrDef::cdata, xtnCoreAttrDef::implied);

    /* Rule: (onevent*, timer?, (do | p). */
    tmpTag= tCard; tmpNbrAttrib= 9;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **) new xtnWmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new xtnWmlAttrDef("title", xtnCoreAttrDef::cdata, xtnCoreAttrDef::implied);
        // Default: false.
    elementDef[tmpTag]->attributes[1]= new xtnWmlAttrDef("newcontext", xtnXmlAttrDef::dtBoolean, xtnCoreAttrDef::implied);
        // Default: true.
    elementDef[tmpTag]->attributes[2]= new xtnWmlAttrDef("ordered", xtnXmlAttrDef::dtBoolean, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[3]= new xtnWmlAttrDef("xml:lang", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[4]= cardev[0];
    elementDef[tmpTag]->attributes[5]= cardev[1];
    elementDef[tmpTag]->attributes[6]= cardev[2];
    elementDef[tmpTag]->attributes[7]= coreAttributes[0];
    elementDef[tmpTag]->attributes[8]= coreAttributes[1];

    /*** Event bindings. ***/
    /* Rule: (%task;). */
    tmpTag= tDo; tmpNbrAttrib= 7;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **) new xtnWmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new xtnWmlAttrDef("type", xtnCoreAttrDef::cdata, xtnCoreAttrDef::required);
    elementDef[tmpTag]->attributes[1]= new xtnWmlAttrDef("label", xtnCoreAttrDef::cdata, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[2]= new xtnWmlAttrDef("name", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
      // Default: false.
    elementDef[tmpTag]->attributes[3]= new xtnWmlAttrDef("optional", xtnXmlAttrDef::dtBoolean, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[4]= new xtnWmlAttrDef("xml:lang", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[5]= coreAttributes[0];
    elementDef[tmpTag]->attributes[6]= coreAttributes[1];

    /* Rule: (%task;). */
    tmpTag= tOnevent; tmpNbrAttrib= 3;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **) new xtnWmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new xtnWmlAttrDef("type", xtnCoreAttrDef::cdata, xtnCoreAttrDef::required);
    elementDef[tmpTag]->attributes[1]= coreAttributes[0];
    elementDef[tmpTag]->attributes[2]= coreAttributes[1];

    /*** Deck-level declarations. ***/
    /* Rule: (access | meta)+. */
    tmpTag= tHead; tmpNbrAttrib= 2;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **)coreAttributes;

    /* Rule: (%navelmts;). */
    tmpTag= tTemplate; tmpNbrAttrib= 5;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **) new xtnWmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= cardev[0];
    elementDef[tmpTag]->attributes[1]= cardev[1];
    elementDef[tmpTag]->attributes[2]= cardev[2];
    elementDef[tmpTag]->attributes[3]= coreAttributes[0];
    elementDef[tmpTag]->attributes[4]= coreAttributes[1];

    /* Rule: EMPTY. */
    tmpTag= tAccess; tmpNbrAttrib= 4;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **) new xtnWmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new xtnWmlAttrDef("domain", xtnCoreAttrDef::cdata, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= new xtnWmlAttrDef("path", xtnCoreAttrDef::cdata, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[2]= coreAttributes[0];
    elementDef[tmpTag]->attributes[3]= coreAttributes[1];

    /* Rule: EMPTY. */
    tmpTag= tMeta; tmpNbrAttrib= 7;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **) new xtnWmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new xtnWmlAttrDef("http-equiv", xtnCoreAttrDef::cdata, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= new xtnWmlAttrDef("name", xtnCoreAttrDef::cdata, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[2]= new xtnWmlAttrDef("forua", xtnXmlAttrDef::dtBoolean, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[3]= new xtnWmlAttrDef("content", xtnCoreAttrDef::cdata, xtnCoreAttrDef::required);
    elementDef[tmpTag]->attributes[4]= new xtnWmlAttrDef("scheme", xtnCoreAttrDef::cdata, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[5]= coreAttributes[0];
    elementDef[tmpTag]->attributes[6]= coreAttributes[1];

    /* Rule: (postfield | setvar)*. */
    tmpTag= tGo; tmpNbrAttrib= 6;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **) new xtnWmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new xtnWmlAttrDef("href", xtnCoreAttrDef::cdata, xtnCoreAttrDef::required);
    elementDef[tmpTag]->attributes[1]= new xtnWmlAttrDef("sendreferer", xtnXmlAttrDef::dtBoolean, xtnCoreAttrDef::implied);
    // Type: (post | get), default: get.
    elementDef[tmpTag]->attributes[2]= new xtnWmlAttrDef("method", xtnCoreAttrDef::custom, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[3]= new xtnWmlAttrDef("accept-charset", xtnCoreAttrDef::cdata, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[4]= coreAttributes[0];
    elementDef[tmpTag]->attributes[5]= coreAttributes[1];

    /* Rule: (setvar). */
    tmpTag= tPrev; tmpNbrAttrib= 2;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **)coreAttributes;

    /* Rule: (setvar). */
    tmpTag= tRefresh; tmpNbrAttrib= 2;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **)coreAttributes;

    /* Rule: EMPTY. */
    tmpTag= tNoop; tmpNbrAttrib= 2;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **)coreAttributes;

    /*** Postfield. ***/
    /* Rule: EMPTY. */
    tmpTag= tPostfield; tmpNbrAttrib= 4;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **) new xtnWmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new xtnWmlAttrDef("name", xtnCoreAttrDef::cdata, xtnCoreAttrDef::required);
    elementDef[tmpTag]->attributes[1]= new xtnWmlAttrDef("value", xtnCoreAttrDef::cdata, xtnCoreAttrDef::required);
    elementDef[tmpTag]->attributes[2]= coreAttributes[0];
    elementDef[tmpTag]->attributes[3]= coreAttributes[1];

    /*** Variables. ***/
    /* Rule: Empty. */
    tmpTag= tSetvar; tmpNbrAttrib= 4;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **) new xtnWmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new xtnWmlAttrDef("name", xtnCoreAttrDef::cdata, xtnCoreAttrDef::required);
    elementDef[tmpTag]->attributes[1]= new xtnWmlAttrDef("value", xtnCoreAttrDef::cdata, xtnCoreAttrDef::required);
    elementDef[tmpTag]->attributes[2]= coreAttributes[0];
    elementDef[tmpTag]->attributes[3]= coreAttributes[1];

    /*** Card Fields. ***/
    /* Rule: (optgroup | option)+. */
    tmpTag= tSelect; tmpNbrAttrib= 10;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **) new xtnWmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new xtnWmlAttrDef("title", xtnCoreAttrDef::cdata, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= new xtnWmlAttrDef("name", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[2]= new xtnWmlAttrDef("value", xtnCoreAttrDef::cdata, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[3]= new xtnWmlAttrDef("iname", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[4]= new xtnWmlAttrDef("ivalue", xtnCoreAttrDef::cdata, xtnCoreAttrDef::implied);
    // Default: false.
    elementDef[tmpTag]->attributes[5]= new xtnWmlAttrDef("multiple", xtnXmlAttrDef::dtBoolean, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[6]= new xtnWmlAttrDef("tabindex", xtnCoreAttrDef::number, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[7]= new xtnWmlAttrDef("xml:lang", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[8]= coreAttributes[0];
    elementDef[tmpTag]->attributes[9]= coreAttributes[1];

    /* Rule: (optgroup | option)+. */
    tmpTag= tOptgroup; tmpNbrAttrib= 4;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **) new xtnWmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new xtnWmlAttrDef("title", xtnCoreAttrDef::cdata, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= new xtnWmlAttrDef("xml:lang", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[2]= coreAttributes[0];
    elementDef[tmpTag]->attributes[3]= coreAttributes[1];

    /* Rule: (#PCDATA | onevent)*. */
    tmpTag= tOption; tmpNbrAttrib= 6;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **) new xtnWmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new xtnWmlAttrDef("value", xtnCoreAttrDef::cdata, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= new xtnWmlAttrDef("title", xtnCoreAttrDef::cdata, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[2]= new xtnWmlAttrDef("onpick", xtnCoreAttrDef::cdata, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[3]= new xtnWmlAttrDef("xml:lang", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[4]= coreAttributes[0];
    elementDef[tmpTag]->attributes[5]= coreAttributes[1];

    /* Rule: EMPTY. */
    tmpTag= tInput; tmpNbrAttrib= 12;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **) new xtnWmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new xtnWmlAttrDef("name", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::required);
    // Type: (text | password), default: text.
    elementDef[tmpTag]->attributes[1]= new xtnWmlAttrDef("type", xtnCoreAttrDef::custom, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[2]= new xtnWmlAttrDef("value", xtnCoreAttrDef::cdata, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[3]= new xtnWmlAttrDef("format", xtnCoreAttrDef::cdata, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[4]= new xtnWmlAttrDef("emptyok", xtnXmlAttrDef::dtBoolean, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[5]= new xtnWmlAttrDef("size", xtnCoreAttrDef::number, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[6]= new xtnWmlAttrDef("maxlength", xtnCoreAttrDef::number, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[7]= new xtnWmlAttrDef("tabindex", xtnCoreAttrDef::number, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[8]= new xtnWmlAttrDef("title", xtnCoreAttrDef::cdata, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[9]= new xtnWmlAttrDef("xml:lang", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[10]= coreAttributes[0];
    elementDef[tmpTag]->attributes[11]= coreAttributes[1];

    /* Rule: (%fields; | do)*. */
    tmpTag= tFieldset; tmpNbrAttrib= 4;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **) new xtnWmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new xtnWmlAttrDef("title", xtnCoreAttrDef::cdata, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= new xtnWmlAttrDef("xml:lang", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[2]= coreAttributes[0];
    elementDef[tmpTag]->attributes[3]= coreAttributes[1];

    /* Rule: EMPTY. */
    tmpTag= tTimer; tmpNbrAttrib= 4;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **) new xtnWmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new xtnWmlAttrDef("name", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= new xtnWmlAttrDef("value", xtnCoreAttrDef::cdata, xtnCoreAttrDef::required);
    elementDef[tmpTag]->attributes[2]= coreAttributes[0];
    elementDef[tmpTag]->attributes[3]= coreAttributes[1];


    /*** Images. ***/

    /* Rule: EMPTY. */
    tmpTag= tImg; tmpNbrAttrib= 11;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **) new xtnWmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new xtnWmlAttrDef("alt", xtnCoreAttrDef::cdata, xtnCoreAttrDef::required);
    elementDef[tmpTag]->attributes[1]= new xtnWmlAttrDef("src", xtnCoreAttrDef::cdata, xtnCoreAttrDef::required);
    elementDef[tmpTag]->attributes[2]= new xtnWmlAttrDef("localsrc", xtnCoreAttrDef::cdata, xtnCoreAttrDef::implied);
    // Default: 0.
    elementDef[tmpTag]->attributes[3]= new xtnWmlAttrDef("vspace", xtnCoreAttrDef::cdata, xtnCoreAttrDef::implied);
    // Default: 0.
    elementDef[tmpTag]->attributes[4]= new xtnWmlAttrDef("hspace", xtnCoreAttrDef::cdata, xtnCoreAttrDef::implied);
    // Type: (top | middle | bottom), Default: bottom.
    elementDef[tmpTag]->attributes[5]= new xtnWmlAttrDef("align", xtnCoreAttrDef::custom, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[6]= new xtnWmlAttrDef("height", xtnCoreAttrDef::cdata, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[7]= new xtnWmlAttrDef("width", xtnCoreAttrDef::cdata, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[8]= new xtnWmlAttrDef("xml:lang", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[9]= coreAttributes[0];
    elementDef[tmpTag]->attributes[10]= coreAttributes[1];


    /*** Anchor. ***/

    /* Rule: ( #PCDATA | br | img | go | prev | refresh )*. */
    tmpTag= tAnchor; tmpNbrAttrib= 4;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **) new xtnWmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new xtnWmlAttrDef("title", xtnCoreAttrDef::cdata, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= new xtnWmlAttrDef("xml:lang", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[2]= coreAttributes[0];
    elementDef[tmpTag]->attributes[3]= coreAttributes[1];

    /* Rule: ( #PCDATA | br | img). */
    tmpTag= tA; tmpNbrAttrib= 5;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **) new xtnWmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new xtnWmlAttrDef("href", xtnCoreAttrDef::cdata, xtnCoreAttrDef::required);
    elementDef[tmpTag]->attributes[1]= new xtnWmlAttrDef("title", xtnCoreAttrDef::cdata, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[2]= new xtnWmlAttrDef("xml:lang", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[3]= coreAttributes[0];
    elementDef[tmpTag]->attributes[4]= coreAttributes[1];


    /*** Tables. ***/

    /* Rule: (tr)+. */
    tmpTag= tTable; tmpNbrAttrib= 6;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **) new xtnWmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new xtnWmlAttrDef("title", xtnCoreAttrDef::cdata, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= new xtnWmlAttrDef("align", xtnCoreAttrDef::cdata, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[2]= new xtnWmlAttrDef("columns", xtnCoreAttrDef::number, xtnCoreAttrDef::required);
    elementDef[tmpTag]->attributes[3]= new xtnWmlAttrDef("xml:lang", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[4]= coreAttributes[0];
    elementDef[tmpTag]->attributes[5]= coreAttributes[1];

    /* Rule: (td)+. */
    tmpTag= tTr; tmpNbrAttrib= 2;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **)coreAttributes;

    /* Rule: ( %text; | %layout; | img | anchor | a )*. */
    tmpTag= tTd; tmpNbrAttrib= 3;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **) new xtnWmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new xtnWmlAttrDef("xml:lang", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= coreAttributes[0];
    elementDef[tmpTag]->attributes[2]= coreAttributes[1];


    /*** Text layout and line breaks. ***/

    /* Rule: (%flow;)*. */
    tmpTag= tEm; tmpNbrAttrib= 3;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **) new xtnWmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new xtnWmlAttrDef("xml:lang", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= coreAttributes[0];
    elementDef[tmpTag]->attributes[2]= coreAttributes[1];

    /* Rule: (%flow;)*. */
    tmpTag= tStrong; tmpNbrAttrib= 3;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **) new xtnWmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new xtnWmlAttrDef("xml:lang", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= coreAttributes[0];
    elementDef[tmpTag]->attributes[2]= coreAttributes[1];

    /* Rule: (%flow;)*. */
    tmpTag= tB; tmpNbrAttrib= 3;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **) new xtnWmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new xtnWmlAttrDef("xml:lang", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= coreAttributes[0];
    elementDef[tmpTag]->attributes[2]= coreAttributes[1];

    /* Rule: (%flow;)*. */
    tmpTag= tI; tmpNbrAttrib= 3;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **) new xtnWmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new xtnWmlAttrDef("xml:lang", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= coreAttributes[0];
    elementDef[tmpTag]->attributes[2]= coreAttributes[1];

    /* Rule: (%flow;)*. */
    tmpTag= tU; tmpNbrAttrib= 3;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **) new xtnWmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new xtnWmlAttrDef("xml:lang", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= coreAttributes[0];
    elementDef[tmpTag]->attributes[2]= coreAttributes[1];

    /* Rule: (%flow;)*. */
    tmpTag= tBig; tmpNbrAttrib= 3;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **) new xtnWmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new xtnWmlAttrDef("xml:lang", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= coreAttributes[0];
    elementDef[tmpTag]->attributes[2]= coreAttributes[1];

    /* Rule: (%flow;)*. */
    tmpTag= tSmall; tmpNbrAttrib= 3;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **) new xtnWmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new xtnWmlAttrDef("xml:lang", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= coreAttributes[0];
    elementDef[tmpTag]->attributes[2]= coreAttributes[1];

    /* Rule: (%fields; | do)*. */
    tmpTag= tP; tmpNbrAttrib= 5;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **) new xtnWmlAttrDef*[tmpNbrAttrib];
    // Type: (left | right | center), default: left.
    elementDef[tmpTag]->attributes[0]= new xtnWmlAttrDef("align", xtnCoreAttrDef::custom, xtnCoreAttrDef::implied);
    // Type: (wrap | nowrap).
    elementDef[tmpTag]->attributes[1]= new xtnWmlAttrDef("mode", xtnCoreAttrDef::custom, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[2]= new xtnWmlAttrDef("xml:lang", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[3]= coreAttributes[0];
    elementDef[tmpTag]->attributes[4]= coreAttributes[1];

    /* Rule: EMPTY. */
    tmpTag= tBr; tmpNbrAttrib= 3;
    elementDef[tmpTag]= new xtnWmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **) new xtnWmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new xtnWmlAttrDef("xml:lang", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= coreAttributes[0];
    elementDef[tmpTag]->attributes[2]= coreAttributes[1];
}


bool xtnWmlDTD::checkCategory(xtnWmlDTD::WmlTags aTag, xtnWmlDTD::EntityCategory aCategory)
{
    // TODO:
    switch(aTag) {
	default:
	    if (aCategory == eBody) return true;
	    return false;
    }
}


bool xtnWmlDTD::isFromEntity(WmlTags aTag, WmlEntity anEntity)
{
    // TODO:
    switch(anEntity) {
	default:
	    return false;
	    break;
    }
    return false;
}


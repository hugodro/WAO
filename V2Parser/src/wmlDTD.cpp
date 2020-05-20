/**************************************************
* File: wmlDTD.cc.
* Desc: Implementation of an optimized DtdDef for WML 1.1.
* Module: WAO : SgmlParser.
* Rev: 19 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#if defined(_WIN32)
#include <string.h>
#endif
#include "wElements.h"
#include "wmlDoc.h"
#include "wElementDef.h"
#include "wmlDTD.h"

char *WmlDTD::tagNames[WmlDTD::numOfElements]= {
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


WmlElementDef *WmlDTD::elementDef[WmlDTD:: numOfElements] = { NULL };


WmlDTD::WmlTags WmlDTD::identifyTag(char *aName)
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


WmlElementDef * WmlDTD::getElementDef(WmlDTD::WmlTags aTag)
{
    return elementDef[aTag];
}


WmlDTD::WmlDTD(void)
{
    loadDefinitions();
}


SgmlDoc *WmlDTD::createConformentDoc(char *aName)
{
    return new WmlDoc(aName, this);
}


WmlElement *WmlDTD::instanciateType(WmlTags aType)
{
    switch(aType) {
    case tA:
	return new WAnchorMin();
	break;

    case tAccess:
	return new WAccess();
	break;

    case tAnchor:
	return new WAnchor();
	break;

    case tB:
	return new WBold();
	break;

    case tBig:
	return new WBig();
	break;

    case tBr:
	return new WBreak();
	break;

    case tCard:
	return new WCard();
	break;

    case tDo:
	return new WDo();
	break;

    case tEm:
	return new WEm();
	break;

    case tFieldset:
	return new WFieldSet();
	break;

    case tGo:
	return new WGo();
	break;

    case tHead:
	return new WHead();
	break;

    case tI:
	return new WItalic();
	break;

    case tImg:
	return new WImg();
	break;

    case tInput:
	return new WInput();
	break;

    case tMeta:
	return new WMeta();
	break;

    case tNoop:
	return new WNoop();
	break;

    case tOnevent:
	return new WOnEvent();
	break;

    case tOptgroup:
	return new WOptGroup();
	break;

    case tOption:
	return new WOption();
	break;

    case tP:
	return new WPara();
	break;

    case tPostfield:
	return new WPostField();
	break;

    case tPrev:
	return new WPrev();
	break;

    case tRefresh:
	return new WRefresh();
	break;

    case tSelect:
	return new WSelect();
	break;

    case tSetvar:
	return new WSetVar();
	break;

    case tSmall:
	return new WSmall();
	break;

    case tStrong:
	return new WStrong();
	break;

    case tTable:
	return new WTable();
	break;

    case tTd:
	return new WTableData();
	break;

    case tTemplate:
	return new WTemplate();
	break;

    case tTimer:
	return new WTimer();
	break;

    case tTr:
	return new WTableRow();
	break;

    case tU:
	return new WUnderscore();
	break;

    case tWml:
	return new WWml();
	break;


    case tPcdata :
	return new WPcData();
	break;
    }
    return NULL;
}


boolean WmlDTD::useVersion(char *versName)
{
// ATTN: Pick up the correct version.
// By default, the version will be "-//W3C//DTD WML 1.1//EN".
    return true;
}


void WmlDTD::loadDefinitions(void)
{
    WmlAttrDef **coreAttributes;
    WmlAttrDef **cardev;
    unsigned int tmpNbrAttrib;
    WmlTags tmpTag;

/* TODO-000123 [HD]: come up with a heap of WmlAttrDef and WmlElementDef, so that instances can
 *    be deleted without causing past-due reference pointers.  This is the case now with the attributes
 *    array in the elementDef, and it will be the case with the rule array in the entityDef.
*/

    name= new char[25];
    strcpy(name, "-//W3C//DTD WML 1.1//EN");

    coreAttributes= new WmlAttrDef*[2];
    coreAttributes[0]= new WmlAttrDef("id", SgmlAttrDef::id, SgmlAttrDef::implied);
    coreAttributes[1]= new WmlAttrDef("class", SgmlAttrDef::cdata, SgmlAttrDef::implied);

    /*** Decks and Cards. ***/
    /* Rule: (head?, template?, card+). */
    tmpTag= tWml; tmpNbrAttrib= 9;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **)new WmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new WmlAttrDef("xml:lang", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= coreAttributes[0];
    elementDef[tmpTag]->attributes[2]= coreAttributes[1];

    cardev= new WmlAttrDef*[3];
    cardev[0]= new WmlAttrDef("onenterforward", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    cardev[1]= new WmlAttrDef("onenterbackward", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    cardev[2]= new WmlAttrDef("ontimer", SgmlAttrDef::cdata, SgmlAttrDef::implied);

    /* Rule: (onevent*, timer?, (do | p). */
    tmpTag= tCard; tmpNbrAttrib= 9;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **) new WmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new WmlAttrDef("title", SgmlAttrDef::cdata, SgmlAttrDef::implied);
        // Default: false.
    elementDef[tmpTag]->attributes[1]= new WmlAttrDef("newcontext", SgmlAttrDef::dtBoolean, SgmlAttrDef::implied);
        // Default: true.
    elementDef[tmpTag]->attributes[2]= new WmlAttrDef("ordered", SgmlAttrDef::dtBoolean, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[3]= new WmlAttrDef("xml:lang", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[4]= cardev[0];
    elementDef[tmpTag]->attributes[5]= cardev[1];
    elementDef[tmpTag]->attributes[6]= cardev[2];
    elementDef[tmpTag]->attributes[7]= coreAttributes[0];
    elementDef[tmpTag]->attributes[8]= coreAttributes[1];

    /*** Event bindings. ***/
    /* Rule: (%task;). */
    tmpTag= tDo; tmpNbrAttrib= 7;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **) new WmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new WmlAttrDef("type", SgmlAttrDef::cdata, SgmlAttrDef::required);
    elementDef[tmpTag]->attributes[1]= new WmlAttrDef("label", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[2]= new WmlAttrDef("name", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
      // Default: false.
    elementDef[tmpTag]->attributes[3]= new WmlAttrDef("optional", SgmlAttrDef::dtBoolean, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[4]= new WmlAttrDef("xml:lang", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[5]= coreAttributes[0];
    elementDef[tmpTag]->attributes[6]= coreAttributes[1];

    /* Rule: (%task;). */
    tmpTag= tOnevent; tmpNbrAttrib= 3;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **) new WmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new WmlAttrDef("type", SgmlAttrDef::cdata, SgmlAttrDef::required);
    elementDef[tmpTag]->attributes[1]= coreAttributes[0];
    elementDef[tmpTag]->attributes[2]= coreAttributes[1];

    /*** Deck-level declarations. ***/
    /* Rule: (access | meta)+. */
    tmpTag= tHead; tmpNbrAttrib= 2;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **)coreAttributes;

    /* Rule: (%navelmts;). */
    tmpTag= tTemplate; tmpNbrAttrib= 5;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **) new WmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= cardev[0];
    elementDef[tmpTag]->attributes[1]= cardev[1];
    elementDef[tmpTag]->attributes[2]= cardev[2];
    elementDef[tmpTag]->attributes[3]= coreAttributes[0];
    elementDef[tmpTag]->attributes[4]= coreAttributes[1];

    /* Rule: EMPTY. */
    tmpTag= tAccess; tmpNbrAttrib= 4;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **) new WmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new WmlAttrDef("domain", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= new WmlAttrDef("path", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[2]= coreAttributes[0];
    elementDef[tmpTag]->attributes[3]= coreAttributes[1];

    /* Rule: EMPTY. */
    tmpTag= tMeta; tmpNbrAttrib= 7;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **) new WmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new WmlAttrDef("http-equiv", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= new WmlAttrDef("name", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[2]= new WmlAttrDef("forua", SgmlAttrDef::dtBoolean, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[3]= new WmlAttrDef("content", SgmlAttrDef::cdata, SgmlAttrDef::required);
    elementDef[tmpTag]->attributes[4]= new WmlAttrDef("scheme", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[5]= coreAttributes[0];
    elementDef[tmpTag]->attributes[6]= coreAttributes[1];

    /* Rule: (postfield | setvar)*. */
    tmpTag= tGo; tmpNbrAttrib= 6;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **) new WmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new WmlAttrDef("href", SgmlAttrDef::cdata, SgmlAttrDef::required);
    elementDef[tmpTag]->attributes[1]= new WmlAttrDef("sendreferer", SgmlAttrDef::dtBoolean, SgmlAttrDef::implied);
    // Type: (post | get), default: get.
    elementDef[tmpTag]->attributes[2]= new WmlAttrDef("method", SgmlAttrDef::custom, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[3]= new WmlAttrDef("accept-charset", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[4]= coreAttributes[0];
    elementDef[tmpTag]->attributes[5]= coreAttributes[1];

    /* Rule: (setvar). */
    tmpTag= tPrev; tmpNbrAttrib= 2;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **)coreAttributes;

    /* Rule: (setvar). */
    tmpTag= tRefresh; tmpNbrAttrib= 2;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **)coreAttributes;

    /* Rule: EMPTY. */
    tmpTag= tNoop; tmpNbrAttrib= 2;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **)coreAttributes;

    /*** Postfield. ***/
    /* Rule: EMPTY. */
    tmpTag= tPostfield; tmpNbrAttrib= 4;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **) new WmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new WmlAttrDef("name", SgmlAttrDef::cdata, SgmlAttrDef::required);
    elementDef[tmpTag]->attributes[1]= new WmlAttrDef("value", SgmlAttrDef::cdata, SgmlAttrDef::required);
    elementDef[tmpTag]->attributes[2]= coreAttributes[0];
    elementDef[tmpTag]->attributes[3]= coreAttributes[1];

    /*** Variables. ***/
    /* Rule: Empty. */
    tmpTag= tSetvar; tmpNbrAttrib= 4;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **) new WmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new WmlAttrDef("name", SgmlAttrDef::cdata, SgmlAttrDef::required);
    elementDef[tmpTag]->attributes[1]= new WmlAttrDef("value", SgmlAttrDef::cdata, SgmlAttrDef::required);
    elementDef[tmpTag]->attributes[2]= coreAttributes[0];
    elementDef[tmpTag]->attributes[3]= coreAttributes[1];

    /*** Card Fields. ***/
    /* Rule: (optgroup | option)+. */
    tmpTag= tSelect; tmpNbrAttrib= 10;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **) new WmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new WmlAttrDef("title", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= new WmlAttrDef("name", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[2]= new WmlAttrDef("value", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[3]= new WmlAttrDef("iname", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[4]= new WmlAttrDef("ivalue", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    // Default: false.
    elementDef[tmpTag]->attributes[5]= new WmlAttrDef("multiple", SgmlAttrDef::dtBoolean, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[6]= new WmlAttrDef("tabindex", SgmlAttrDef::number, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[7]= new WmlAttrDef("xml:lang", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[8]= coreAttributes[0];
    elementDef[tmpTag]->attributes[9]= coreAttributes[1];

    /* Rule: (optgroup | option)+. */
    tmpTag= tOptgroup; tmpNbrAttrib= 4;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **) new WmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new WmlAttrDef("title", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= new WmlAttrDef("xml:lang", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[2]= coreAttributes[0];
    elementDef[tmpTag]->attributes[3]= coreAttributes[1];

    /* Rule: (#PCDATA | onevent)*. */
    tmpTag= tOption; tmpNbrAttrib= 6;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **) new WmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new WmlAttrDef("value", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= new WmlAttrDef("title", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[2]= new WmlAttrDef("onpick", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[3]= new WmlAttrDef("xml:lang", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[4]= coreAttributes[0];
    elementDef[tmpTag]->attributes[5]= coreAttributes[1];

    /* Rule: EMPTY. */
    tmpTag= tInput; tmpNbrAttrib= 12;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **) new WmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new WmlAttrDef("name", SgmlAttrDef::nmToken, SgmlAttrDef::required);
    // Type: (text | password), default: text.
    elementDef[tmpTag]->attributes[1]= new WmlAttrDef("type", SgmlAttrDef::custom, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[2]= new WmlAttrDef("value", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[3]= new WmlAttrDef("format", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[4]= new WmlAttrDef("emptyok", SgmlAttrDef::dtBoolean, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[5]= new WmlAttrDef("size", SgmlAttrDef::number, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[6]= new WmlAttrDef("maxlength", SgmlAttrDef::number, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[7]= new WmlAttrDef("tabindex", SgmlAttrDef::number, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[8]= new WmlAttrDef("title", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[9]= new WmlAttrDef("xml:lang", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[10]= coreAttributes[0];
    elementDef[tmpTag]->attributes[11]= coreAttributes[1];

    /* Rule: (%fields; | do)*. */
    tmpTag= tFieldset; tmpNbrAttrib= 4;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **) new WmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new WmlAttrDef("title", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= new WmlAttrDef("xml:lang", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[2]= coreAttributes[0];
    elementDef[tmpTag]->attributes[3]= coreAttributes[1];

    /* Rule: EMPTY. */
    tmpTag= tTimer; tmpNbrAttrib= 4;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **) new WmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new WmlAttrDef("name", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= new WmlAttrDef("value", SgmlAttrDef::cdata, SgmlAttrDef::required);
    elementDef[tmpTag]->attributes[2]= coreAttributes[0];
    elementDef[tmpTag]->attributes[3]= coreAttributes[1];


    /*** Images. ***/

    /* Rule: EMPTY. */
    tmpTag= tImg; tmpNbrAttrib= 11;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **) new WmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new WmlAttrDef("alt", SgmlAttrDef::cdata, SgmlAttrDef::required);
    elementDef[tmpTag]->attributes[1]= new WmlAttrDef("src", SgmlAttrDef::cdata, SgmlAttrDef::required);
    elementDef[tmpTag]->attributes[2]= new WmlAttrDef("localsrc", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    // Default: 0.
    elementDef[tmpTag]->attributes[3]= new WmlAttrDef("vspace", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    // Default: 0.
    elementDef[tmpTag]->attributes[4]= new WmlAttrDef("hspace", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    // Type: (top | middle | bottom), Default: bottom.
    elementDef[tmpTag]->attributes[5]= new WmlAttrDef("align", SgmlAttrDef::custom, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[6]= new WmlAttrDef("height", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[7]= new WmlAttrDef("width", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[8]= new WmlAttrDef("xml:lang", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[9]= coreAttributes[0];
    elementDef[tmpTag]->attributes[10]= coreAttributes[1];


    /*** Anchor. ***/

    /* Rule: ( #PCDATA | br | img | go | prev | refresh )*. */
    tmpTag= tAnchor; tmpNbrAttrib= 4;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **) new WmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new WmlAttrDef("title", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= new WmlAttrDef("xml:lang", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[2]= coreAttributes[0];
    elementDef[tmpTag]->attributes[3]= coreAttributes[1];

    /* Rule: ( #PCDATA | br | img). */
    tmpTag= tA; tmpNbrAttrib= 5;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **) new WmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new WmlAttrDef("href", SgmlAttrDef::cdata, SgmlAttrDef::required);
    elementDef[tmpTag]->attributes[1]= new WmlAttrDef("title", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[2]= new WmlAttrDef("xml:lang", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[3]= coreAttributes[0];
    elementDef[tmpTag]->attributes[4]= coreAttributes[1];


    /*** Tables. ***/

    /* Rule: (tr)+. */
    tmpTag= tTable; tmpNbrAttrib= 6;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **) new WmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new WmlAttrDef("title", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= new WmlAttrDef("align", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[2]= new WmlAttrDef("columns", SgmlAttrDef::number, SgmlAttrDef::required);
    elementDef[tmpTag]->attributes[3]= new WmlAttrDef("xml:lang", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[4]= coreAttributes[0];
    elementDef[tmpTag]->attributes[5]= coreAttributes[1];

    /* Rule: (td)+. */
    tmpTag= tTr; tmpNbrAttrib= 2;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **)coreAttributes;

    /* Rule: ( %text; | %layout; | img | anchor | a )*. */
    tmpTag= tTd; tmpNbrAttrib= 3;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **) new WmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new WmlAttrDef("xml:lang", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= coreAttributes[0];
    elementDef[tmpTag]->attributes[2]= coreAttributes[1];


    /*** Text layout and line breaks. ***/

    /* Rule: (%flow;)*. */
    tmpTag= tEm; tmpNbrAttrib= 3;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **) new WmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new WmlAttrDef("xml:lang", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= coreAttributes[0];
    elementDef[tmpTag]->attributes[2]= coreAttributes[1];

    /* Rule: (%flow;)*. */
    tmpTag= tStrong; tmpNbrAttrib= 3;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **) new WmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new WmlAttrDef("xml:lang", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= coreAttributes[0];
    elementDef[tmpTag]->attributes[2]= coreAttributes[1];

    /* Rule: (%flow;)*. */
    tmpTag= tB; tmpNbrAttrib= 3;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **) new WmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new WmlAttrDef("xml:lang", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= coreAttributes[0];
    elementDef[tmpTag]->attributes[2]= coreAttributes[1];

    /* Rule: (%flow;)*. */
    tmpTag= tI; tmpNbrAttrib= 3;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **) new WmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new WmlAttrDef("xml:lang", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= coreAttributes[0];
    elementDef[tmpTag]->attributes[2]= coreAttributes[1];

    /* Rule: (%flow;)*. */
    tmpTag= tU; tmpNbrAttrib= 3;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **) new WmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new WmlAttrDef("xml:lang", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= coreAttributes[0];
    elementDef[tmpTag]->attributes[2]= coreAttributes[1];

    /* Rule: (%flow;)*. */
    tmpTag= tBig; tmpNbrAttrib= 3;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **) new WmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new WmlAttrDef("xml:lang", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= coreAttributes[0];
    elementDef[tmpTag]->attributes[2]= coreAttributes[1];

    /* Rule: (%flow;)*. */
    tmpTag= tSmall; tmpNbrAttrib= 3;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **) new WmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new WmlAttrDef("xml:lang", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= coreAttributes[0];
    elementDef[tmpTag]->attributes[2]= coreAttributes[1];

    /* Rule: (%fields; | do)*. */
    tmpTag= tP; tmpNbrAttrib= 5;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **) new WmlAttrDef*[tmpNbrAttrib];
    // Type: (left | right | center), default: left.
    elementDef[tmpTag]->attributes[0]= new WmlAttrDef("align", SgmlAttrDef::custom, SgmlAttrDef::implied);
    // Type: (wrap | nowrap).
    elementDef[tmpTag]->attributes[1]= new WmlAttrDef("mode", SgmlAttrDef::custom, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[2]= new WmlAttrDef("xml:lang", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[3]= coreAttributes[0];
    elementDef[tmpTag]->attributes[4]= coreAttributes[1];

    /* Rule: EMPTY. */
    tmpTag= tBr; tmpNbrAttrib= 3;
    elementDef[tmpTag]= new WmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **) new WmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new WmlAttrDef("xml:lang", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= coreAttributes[0];
    elementDef[tmpTag]->attributes[2]= coreAttributes[1];
}


boolean WmlDTD::checkCategory(WmlDTD::WmlTags aTag, WmlDTD::EntityCategory aCategory)
{
    // TODO:
    switch(aTag) {
	default:
	    if (aCategory == eBody) return true;
	    return false;
    }
}


boolean WmlDTD::isFromEntity(WmlTags aTag, WmlEntity anEntity)
{
    switch(anEntity) {
	default:
	    return false;
	    break;
    }
    return false;
}


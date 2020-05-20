/**************************************************
* File: hdDTD.cc.
* Desc: Implementation of an optimized DtdDef for HDML 2.0.
* Module: WAO : SgmlParser.
* Rev: 29 mai 2000 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/09/02 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: hdDTD.cpp,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.2  2000/09/20 03:25:22  hugo
* Minor updates to the HDML rendering.
*
* Revision 1.1  2000/09/05 07:13:40  hugo
* Initial entry of real parsing/generating HDML support.
*
**************************************************/

#if defined(_WIN32)
#include <string>
#endif

#include <globDefs.h>

#include "allHdElements.h"
#include "hdDoc.h"
#include "hdElementDef.h"
#include "hdDTD.h"


char *xtnHdmlDTD::tagNames[xtnHdmlDTD::numOfElements]= {
    "ACTION"
    , "B"
    , "BR"
    , "CE"
    , "CENTER"
    , "CHOICE"
    , "DISPLAY"
    , "ENTRY"
    , "HDML"
    , "I"
    , "IMG"
    , "LINE"
    , "NODISPLAY"
    , "RIGHT"
    , "TAB"
    , "WRAP"
    , NULL, NULL
};


xtnHdmlElementDef *xtnHdmlDTD::elementDef[xtnHdmlDTD::numOfElements] = { NULL };


xtnHdmlDTD::HdmlTags xtnHdmlDTD::identifyTag(char *aName)
{
    unsigned int i;

    if (aName != NULL) {
	for (i= 0; i < numOfElements - 2; i++) {	// The last two elements (tPcData, tCdata) have no names.
	    if (strcmp(tagNames[i], aName) == 0) {
		return (HdmlTags)i;
	    }
	}
    }
    return unknownTag;
}


xtnHdmlElementDef * xtnHdmlDTD::getElementDef(xtnHdmlDTD::HdmlTags aTag)
{
    return elementDef[aTag];
}


xtnHdmlDTD::xtnHdmlDTD()
{
    loadDefinitions();
}


xtnHdmlDTD::~xtnHdmlDTD()
{
// TODO.
}


xtnCoreDoc *xtnHdmlDTD::createConformentDoc(char *aName)
{
    return new xtnHdmlDoc(aName, this);
}


xtnHdmlElement *xtnHdmlDTD::instanciateType(HdmlTags aType)
{
    switch(aType) {
      case tAction:
	return new xtnHdAction();
	break;
      case tB:
	return new xtnHdB();
	break;
      case tBr:
	return new xtnHdBr();
	break;
      case tCe:
	return new xtnHdCe();
	break;
      case tCenter:
	return new xtnHdCenter();
	break;
      case tChoice:
	return new xtnHdChoice();
	break;
      case tDeck:
	return new xtnHdDeck();
	break;
      case tDisplay:
	return new xtnHdDisplay();
	break;
      case tEntry:
	return new xtnHdEntry();
	break;
      case tI:
	return new xtnHdI();
	break;
      case tImg:
	return new xtnHdImg();
	break;
      case tLine:
	return new xtnHdLine();
	break;
      case tNoDisplay:
	return new xtnHdNoDisplay();
	break;
      case tRight:
	return new xtnHdRight();
	break;
      case tTab:
	return new xtnHdTab();
	break;
      case tWrap:
	return new xtnHdWrap();
	break;
      case tPcdata:
	return new xtnHdPcData();
	break;
    }
    return NULL;
}


bool xtnHdmlDTD::useVersion(char *versName)
{
// ATTN: Pick up the correct version.
// By default, the version will be "-//W3C//DTD HDML 2.0//EN".
    return true;
}


void xtnHdmlDTD::loadDefinitions(void)
{
    xtnHdmlAttrDef **coreAttributes;
    xtnHdmlAttrDef **cardev;
    unsigned int tmpNbrAttrib, i;
    HdmlTags tmpTag;

/* TODO-000123 [HD]: come up with a heap of xtnHdmlAttrDef and xtnHdmlElementDef, so that instances can
 *    be deleted without causing past-due reference pointers.  This is the case now with the attributes
 *    array in the elementDef, and it will be the case with the rule array in the entityDef.
*/

    /*** Deck. ***/
    /* Rule: deck-header { action }* { card }+ deck-footer
               deck-header ::= <HDML o-version ol(deck-options) >
	 deck-options ::= o-ttl | o-deckseq | o-public | o-accessdomain | o-accesspath | o-markable
	 deck-footer ::= </HDML>
 
	 o-version ::= version = value
	 o-ttl ::= ttl = {numeric}+
	 o-public ::= public = bool-value
	 o-accessdomain ::= accessdomain = url
	 o-accesspath ::= accesspath = path
	 o-markable ::= markable = bool-value
	 bool-value ::= true | false 
     */
    tmpTag= tDeck; tmpNbrAttrib= 7;
    elementDef[tmpTag]= new xtnHdmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **)new xtnHdmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new xtnHdmlAttrDef("version", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= new xtnHdmlAttrDef("ttl", xtnCoreAttrDef::number, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[2]= new xtnHdmlAttrDef("public", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[3]= new xtnHdmlAttrDef("accessdomain", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[4]= new xtnHdmlAttrDef("accesspath", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[5]= new xtnHdmlAttrDef("markable", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    // ATTN-000529 [HD]: The deskseq attribute is not defined in the document of HDML 2.0.
    elementDef[tmpTag]->attributes[6]= new xtnHdmlAttrDef("deskseq", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);


    /*** Cards. ***/
    /* Rule: card ::= display-card | nodisplay-card | choice-card | entry-card
           card-options ::= o-name | o-title | o-bookmark | o-markable
	   o-name ::= name = identifier
	   o-title ::= title = value-with-vars
	   o-bookmark ::= bookmark = destination
    */

    xtnHdmlAttrDef **cardOptions= new xtnHdmlAttrDef*[4];
    cardOptions[0]= new xtnHdmlAttrDef("name", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    cardOptions[1]= new xtnHdmlAttrDef("title", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    cardOptions[2]= new xtnHdmlAttrDef("bookmark", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    cardOptions[3]= new xtnHdmlAttrDef("markable", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);


    /* Rule: task-options ::=  o-task | o-dest | o-vars | o-receive | o-retvals | o-next | 
       o-cancel | o-sendreferer | o-friend | o-clear | o-confirm | 
       o-data | o-number | o-go | o-call
    */
    xtnHdmlAttrDef **taskOptions= new xtnHdmlAttrDef*[15];
    taskOptions[0]= new xtnHdmlAttrDef("task", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    taskOptions[1]= new xtnHdmlAttrDef("dest", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    taskOptions[2]= new xtnHdmlAttrDef("vars", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    taskOptions[3]= new xtnHdmlAttrDef("receive", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    taskOptions[4]= new xtnHdmlAttrDef("retvals", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    taskOptions[5]= new xtnHdmlAttrDef("next", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    taskOptions[6]= new xtnHdmlAttrDef("cancel", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    taskOptions[7]= new xtnHdmlAttrDef("sendreferer", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    taskOptions[8]= new xtnHdmlAttrDef("friend", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    taskOptions[9]= new xtnHdmlAttrDef("clear", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    // ATTN-000529 [HD]: The 'o-confirm' is not defined in the HDML 2.0 definition.
    taskOptions[10]= new xtnHdmlAttrDef("confirm", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    taskOptions[11]= new xtnHdmlAttrDef("data", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    taskOptions[12]= new xtnHdmlAttrDef("number", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    taskOptions[13]= new xtnHdmlAttrDef("go", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    taskOptions[14]= new xtnHdmlAttrDef("call", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);


    /* Rule: display-card ::= display-header display-content display-footer
                 display-header ::= <DISPLAY ol(display-options) >
	   display-options ::= card-options
	   display-content ::= { action }* formatted-text
	   display-footer ::= </DISPLAY>
    */
    tmpTag= tDisplay; tmpNbrAttrib= 4;
    elementDef[tmpTag]= new xtnHdmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **)new xtnHdmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= cardOptions[0];
    elementDef[tmpTag]->attributes[1]= cardOptions[1];
    elementDef[tmpTag]->attributes[2]= cardOptions[2];
    elementDef[tmpTag]->attributes[3]= cardOptions[3];


    /* Rule: nodisplay-card ::= nodisplay-header nodisplay-content nodisplay-footer
                  nodisplay-header ::= <NODISPLAY ol(nodisplay-options) >
	    nodisplay-options ::= card-options
	    nodisplay-content ::= { action }*
	    nodisplay-footer ::= </NODISPLAY>
    */

    tmpTag= tNoDisplay; tmpNbrAttrib= 4;
    elementDef[tmpTag]= new xtnHdmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **)new xtnHdmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= cardOptions[0];
    elementDef[tmpTag]->attributes[1]= cardOptions[1];
    elementDef[tmpTag]->attributes[2]= cardOptions[2];
    elementDef[tmpTag]->attributes[3]= cardOptions[3];

    /* Rule:  choice-card ::= choice-header display-content { entries } choice-footer
       choice-header ::= <CHOICE ol(choice-options) >
       choice-options ::= card-options | o-method | o-key | o-ikey | o-default | o-idefault
       o-method ::= method = method-type
       method-type ::= list | alpha
       entries ::= { choice-entry }+
       choice-footer ::= </CHOICE>
       o-key ::= key = identifier
       o-ikey ::= ikey = identifier
       o-default ::= default = value-with-vars
       o-idefault ::= idefault = value-with-vars 
    */
    tmpTag= tChoice; tmpNbrAttrib= 9;
    elementDef[tmpTag]= new xtnHdmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **)new xtnHdmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= cardOptions[0];
    elementDef[tmpTag]->attributes[1]= cardOptions[1];
    elementDef[tmpTag]->attributes[2]= cardOptions[2];
    elementDef[tmpTag]->attributes[3]= cardOptions[3];
    elementDef[tmpTag]->attributes[4]= new xtnHdmlAttrDef("method", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[5]= new xtnHdmlAttrDef("key", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[6]= new xtnHdmlAttrDef("ikey", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[7]= new xtnHdmlAttrDef("default", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[8]= new xtnHdmlAttrDef("idefault", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);


    /* Rule: choice-entry ::= choice-entry-header choice-entry-content choice-entry-footer
       choice-entry-header ::= <CE ol(choice-entry-options) >
       choice-entry-options ::= o-value | task-options
       choice-entry-content ::= formatted-line
       choice-entry-footer ::= { </CE> }
       o-value ::= value = value
    */
    tmpTag= tCe; tmpNbrAttrib= 16;
    elementDef[tmpTag]= new xtnHdmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **)new xtnHdmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new xtnHdmlAttrDef("value", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    for (i= 0; i < 15; i++)
	elementDef[tmpTag]->attributes[i+1]= taskOptions[i];


    /* Rule: entry-header ::= <ENTRY ol(entry-options) >
       entry-options ::= card-options | o-format | o-noecho | o-emptyok | o-key | o-default
       entry-footer ::= </ENTRY>
       o-format ::= format = value
       o-noecho ::= noecho = bool-value
       o-emptyok ::= emptyok = bool-value
   */

    tmpTag= tEntry; tmpNbrAttrib= 10;
    elementDef[tmpTag]= new xtnHdmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **)new xtnHdmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= cardOptions[0];
    elementDef[tmpTag]->attributes[1]= cardOptions[1];
    elementDef[tmpTag]->attributes[2]= cardOptions[2];
    elementDef[tmpTag]->attributes[3]= cardOptions[3];
    elementDef[tmpTag]->attributes[4]= new xtnHdmlAttrDef("format", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[5]= new xtnHdmlAttrDef("noecho", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[6]= new xtnHdmlAttrDef("emptyok", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[7]= new xtnHdmlAttrDef("key", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[8]= new xtnHdmlAttrDef("default", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    // NOTE-000903 [HD]: Added to conform with Waptop HDML usage.
    elementDef[tmpTag]->attributes[9]= new xtnHdmlAttrDef("label", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);


    /* Rule: image ::= <IMG ol(image-options) >
       image-options ::= o-alt | o-name | o-src
       o-alt ::= alt = value-with-vars
       o-name ::= name = value-with-vars
       o-src ::= src = destination
    */
    tmpTag= tImg; tmpNbrAttrib= 3;
    elementDef[tmpTag]= new xtnHdmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **)new xtnHdmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new xtnHdmlAttrDef("alt", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= new xtnHdmlAttrDef("name", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[2]= new xtnHdmlAttrDef("src", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);


    /* Rule: action ::= <ACTION ol(action-options) >
       action-options ::= o-label | o-type | o-image | task-options
       o-type ::= type = key
       key ::= soft1 | soft2 | soft3 | soft4 | soft5 | 
                 soft6 | soft7 | soft8 |
	   accept | prev | help
       o-label ::= label = value-with-vars
       o-image ::= image = url
    */
    tmpTag= tAction; tmpNbrAttrib= 18;
    elementDef[tmpTag]= new xtnHdmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (xtnCoreAttrDef **)new xtnHdmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new xtnHdmlAttrDef("label", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= new xtnHdmlAttrDef("type", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    elementDef[tmpTag]->attributes[2]= new xtnHdmlAttrDef("image", xtnCoreAttrDef::nmToken, xtnCoreAttrDef::implied);
    for (i= 0; i < 15; i++)
	elementDef[tmpTag]->attributes[i+3]= taskOptions[i];


    tmpTag= tB; tmpNbrAttrib= 0;
    elementDef[tmpTag]= new xtnHdmlElementDef(tagNames[tmpTag]);
    tmpTag= tBr; tmpNbrAttrib= 0;
    elementDef[tmpTag]= new xtnHdmlElementDef(tagNames[tmpTag]);
    tmpTag= tCenter; tmpNbrAttrib= 0;
    elementDef[tmpTag]= new xtnHdmlElementDef(tagNames[tmpTag]);
    tmpTag= tI; tmpNbrAttrib= 0;
    elementDef[tmpTag]= new xtnHdmlElementDef(tagNames[tmpTag]);
    tmpTag= tLine; tmpNbrAttrib= 0;
    elementDef[tmpTag]= new xtnHdmlElementDef(tagNames[tmpTag]);
    tmpTag= tRight; tmpNbrAttrib= 0;
    elementDef[tmpTag]= new xtnHdmlElementDef(tagNames[tmpTag]);
    tmpTag= tTab; tmpNbrAttrib= 0;
    elementDef[tmpTag]= new xtnHdmlElementDef(tagNames[tmpTag]);
    tmpTag= tWrap; tmpNbrAttrib= 0;
    elementDef[tmpTag]= new xtnHdmlElementDef(tagNames[tmpTag]);

}


bool xtnHdmlDTD::checkCategory(xtnHdmlDTD::HdmlTags aTag, xtnHdmlDTD::EntityCategory aCategory)
{
    // TODO:
    switch(aTag) {
	case tB:
	case tBr:
	case tCenter:
	case tI:
	case tLine:
	case tRight:
	case tTab:
	case tWrap:
	case tPcdata:
	    return (aCategory == ecText);
    }

    return false;
}


bool xtnHdmlDTD::isFromEntity(xtnHdmlDTD::HdmlTags aTag, xtnHdmlDTD::HdmlEntity anEntity)
{
    switch(anEntity) {
	case eCard:
	    return ((aTag == tDisplay) || (aTag == tChoice) || (aTag == tEntry) || (aTag == tNoDisplay));

	case eText:
	    return ((aTag == tB) || (aTag == tBr) || (aTag == tCenter)
		    || (aTag == tI) || (aTag == tLine) || (aTag == tRight)
		    || (aTag == tTab) || (aTag == tWrap) || (aTag == tPcdata));
	default:
	    return false;
	    break;
    }
    return false;
}




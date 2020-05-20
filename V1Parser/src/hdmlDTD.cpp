/**************************************************
* File: hdmlDTD.cc.
* Desc: Implementation of an optimized DtdDef for HDML 2.0.
* Module: WAO : SgmlParser.
* Rev: 29 mai 2000 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#if defined(_WIN32)
#include <string.h>
#endif
#include "wElements.h"
#include "hdmlDoc.h"
#include "wElementDef.h"
#include "hdmlDTD.h"


char *HdmlDTD::tagNames[HdmlDTD::numOfElements]= {
    "ACTION"
    , "B", "BR"
    , "CE", "CENTER", "CHOICE"
    , "HDML", "DISPLAY"
    , "ENTRY"
    , "I", "IMG"
    , "LINE", "NODISPLAY"
    , "RIGHT"
    , "TAB"
    , "WRAP"
    , NULL, NULL
};


HdmlElementDef *HdmlDTD::elementDef[HdmlDTD:: numOfElements] = { NULL };


HdmlDTD::HdmlTags HdmlDTD::identifyTag(char *aName)
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


HdmlElementDef * HdmlDTD::getElementDef(HdmlDTD::HdmlTags aTag)
{
    return elementDef[aTag];
}


HdmlDTD::HdmlDTD(void)
{
    loadDefinitions();
}


SgmlDoc *HdmlDTD::createConformentDoc(char *aName)
{
    return new HdmlDoc(aName, this);
}


HdmlElement *HdmlDTD::instanciateType(HdmlTags aType)
{
    switch(aType) {
      case tAction:
	return new HdAction();
	break;
      case tB:
	return new HdB();
	break;
      case tBr:
	return new HdBr();
	break;
      case tCe:
	return new HdCe();
	break;
      case tCenter:
	return new HdCenter();
	break;
      case tChoice:
	return new HdChoice();
	break;
      case tDeck:
	return new HdDeck();
	break;
      case tDisplay:
	return new HdDisplay();
	break;
      case tEntry:
	return new HdEntry();
	break;
      case tI:
	return new HdI();
	break;
      case tImg:
	return new HdImg();
	break;
      case tLine:
	return new HdLine();
	break;
      case tNoDisplay:
	return new HdNoDisplay();
	break;
      case tRight:
	return new HdRight();
	break;
      case tTab:
	return new HdTab();
	break;
      case tWrap:
	return new HdWrap();
	break;
      case tPcdata:
	return new HdPcdata();
	break;
    }
    return NULL;
}


boolean HdmlDTD::useVersion(char *versName)
{
// ATTN: Pick up the correct version.
// By default, the version will be "-//W3C//DTD HDML 2.0//EN".
    return true;
}


void HdmlDTD::loadDefinitions(void)
{
    HdmlAttrDef **coreAttributes;
    HdmlAttrDef **cardev;
    unsigned int tmpNbrAttrib;
    HdmlTags tmpTag;

/* TODO-000123 [HD]: come up with a heap of HdmlAttrDef and HdmlElementDef, so that instances can
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
	 o-public ::= public = boolean-value
	 o-accessdomain ::= accessdomain = url
	 o-accesspath ::= accesspath = path
	 o-markable ::= markable = boolean-value
	 boolean-value ::= true | false 
     */
    tmpTag= tDeck; tmpNbrAttrib= 7;
    elementDef[tmpTag]= new HdmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **)new HdmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new HdmlAttrDef("version", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= new HdmlAttrDef("ttl", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[2]= new HdmlAttrDef("public", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[3]= new HdmlAttrDef("accessdomain", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[4]= new HdmlAttrDef("accesspath", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[5]= new HdmlAttrDef("markable", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    // ATTN-000529 [HD]: The deskseq attribute is not defined in the document of HDML 2.0.
    elementDef[tmpTag]->attributes[6]= new HdmlAttrDef("deskseq", SgmlAttrDef::nmToken, SgmlAttrDef::implied);


    /*** Cards. ***/
    /* Rule: card ::= display-card | nodisplay-card | choice-card | entry-card
           card-options ::= o-name | o-title | o-bookmark | o-markable
	   o-name ::= name = identifier
	   o-title ::= title = value-with-vars
	   o-bookmark ::= bookmark = destination
    */

    cardOptions= new HdmlElementDef*[4];
    cardOptions[0]= new HdmlAttrDef("name", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    cardOptions[1]= new HdmlAttrDef("title", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    cardOptions[2]= new HdmlAttrDef("bookmark", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    cardOptions[3]= new HdmlAttrDef("markable", SgmlAttrDef::nmToken, SgmlAttrDef::implied);


    /* Rule: task-options ::=  o-task | o-dest | o-vars | o-receive | o-retvals | o-next | 
       o-cancel | o-sendreferer | o-friend | o-clear | o-confirm | 
       o-data | o-number | o-go | o-call
    */
    taskOptions= new HdmlElementDef*[15];
    taskOptions[0]= new HdmlAttrDef("task", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    taskOptions[1]= new HdmlAttrDef("dest", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    taskOptions[2]= new HdmlAttrDef("vars", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    taskOptions[3]= new HdmlAttrDef("receive", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    taskOptions[4]= new HdmlAttrDef("retvals", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    taskOptions[5]= new HdmlAttrDef("next", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    taskOptions[6]= new HdmlAttrDef("cancel", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    taskOptions[7]= new HdmlAttrDef("sendreferer", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    taskOptions[8]= new HdmlAttrDef("friend", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    taskOptions[9]= new HdmlAttrDef("clear", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    // ATTN-000529 [HD]: The 'o-confirm' is not defined in the HDML 2.0 definition.
    taskOptions[10]= new HdmlAttrDef("confirm", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    taskOptions[11]= new HdmlAttrDef("data", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    taskOptions[12]= new HdmlAttrDef("number", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    taskOptions[13]= new HdmlAttrDef("go", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    taskOptions[14]= new HdmlAttrDef("call", SgmlAttrDef::nmToken, SgmlAttrDef::implied);


    /* Rule: display-card ::= display-header display-content display-footer
                 display-header ::= <DISPLAY ol(display-options) >
	   display-options ::= card-options
	   display-content ::= { action }* formatted-text
	   display-footer ::= </DISPLAY>
    */
    tmpTag= tDisplay; tmpNbrAttrib= 4;
    elementDef[tmpTag]= new HdmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **)new HdmlAttrDef*[tmpNbrAttrib];
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
    elementDef[tmpTag]= new HdmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **)new HdmlAttrDef*[tmpNbrAttrib];
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
    elementDef[tmpTag]= new HdmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **)new HdmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= cardOptions[0];
    elementDef[tmpTag]->attributes[1]= cardOptions[1];
    elementDef[tmpTag]->attributes[2]= cardOptions[2];
    elementDef[tmpTag]->attributes[3]= cardOptions[3];
    elementDef[tmpTag]->attributes[4]= new HdmlAttrDef("method", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[5]= new HdmlAttrDef("key", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[6]= new HdmlAttrDef("ikey", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[7]= new HdmlAttrDef("default", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[8]= new HdmlAttrDef("idefault", SgmlAttrDef::nmToken, SgmlAttrDef::implied);


    /* Rule: choice-entry ::= choice-entry-header choice-entry-content choice-entry-footer
       choice-entry-header ::= <CE ol(choice-entry-options) >
       choice-entry-options ::= o-value | task-options
       choice-entry-content ::= formatted-line
       choice-entry-footer ::= { </CE> }
       o-value ::= value = value
    */
    tmpTag= tCe; tmpNbrAttrib= 16;
    elementDef[tmpTag]= new HdmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes= (SgmlAttrDef **)new HdmlAttrDef*[tmpNbrAttrib];
    elementDef[tmpTag]->attributes[0]= new HdmlAttrDef("value", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    for (unsigned int i= 0; i < 15; i++)
	elementDef[tmpTag]->attributes[i+1]= taskOptions[i];


    /* Rule: entry-header ::= <ENTRY ol(entry-options) >
       entry-options ::= card-options | o-format | o-noecho | o-emptyok | o-key | o-default
       entry-footer ::= </ENTRY>
       o-format ::= format = value
       o-noecho ::= noecho = boolean-value
       o-emptyok ::= emptyok = boolean-value
   */

    tmpTag= tCe; tmpNbrAttrib= 9;
    elementDef[tmpTag]= new HdmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes[0]= cardOptions[0];
    elementDef[tmpTag]->attributes[1]= cardOptions[1];
    elementDef[tmpTag]->attributes[2]= cardOptions[2];
    elementDef[tmpTag]->attributes[3]= cardOptions[3];
    elementDef[tmpTag]->attributes[4]= new HdmlAttrDef("format", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[5]= new HdmlAttrDef("noecho", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[6]= new HdmlAttrDef("emptyok", SgmlAttrDef::nmToken, SgmlAttrDef::implied);


    /* Rule: image ::= <IMG ol(image-options) >
       image-options ::= o-alt | o-name | o-src
       o-alt ::= alt = value-with-vars
       o-name ::= name = value-with-vars
       o-src ::= src = destination
    */
    tmpTag= tImg; tmpNbrAttrib= 3;
    elementDef[tmpTag]= new HdmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes[0]= new HdmlAttrDef("alt", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= new HdmlAttrDef("name", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[2]= new HdmlAttrDef("src", SgmlAttrDef::nmToken, SgmlAttrDef::implied);


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
    elementDef[tmpTag]= new HdmlElementDef(tagNames[tmpTag]);
    elementDef[tmpTag]->nbrAttributes= tmpNbrAttrib;
    elementDef[tmpTag]->attributes[0]= new HdmlAttrDef("label", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[1]= new HdmlAttrDef("type", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    elementDef[tmpTag]->attributes[2]= new HdmlAttrDef("image", SgmlAttrDef::nmToken, SgmlAttrDef::implied);
    for (unsigned int i= 0; i < 15; i++)
	elementDef[tmpTag]->attributes[i+1]= taskOptions[i];

}


boolean HdmlDTD::checkCategory(HdmlDTD::HdmlTags aTag, HdmlDTD::EntityCategory aCategory)
{
    // TODO:
    switch(aTag) {
	default:
	    if (aCategory == eBody) return true;
	    return false;
    }
}


boolean HdmlDTD::isFromEntity(HdmlTags aTag, HdmlEntity anEntity)
{
    switch(anEntity) {
	default:
	    return false;
	    break;
    }
    return false;
}




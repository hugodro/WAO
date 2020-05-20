/**************************************************
* File: renderWml.cpp.
* Desc: Implementation of the Wml-to-Wml (!) spit engine.
* Module: WAO : SgmlParser.
* Rev: 11 juillet 2000 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <fstream.h>
#include "wmlElement.h"
#include "elementList.h"
#include "wmlDoc.h"
#include "nonStdElements.h"
#include "topElements.h"
#include "sgElementDef.h"
#include "wmlDTD.h"
#include "renderWml.h"

char *WmlRenderer::tagNames[WmlDTD::numOfElements]= {
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


WmlRenderer::WmlRenderer(ostream *output)
{
    outStream= output;
}


WmlRenderer::~WmlRenderer(void)
{
    delete outStream;
}


void WmlRenderer::renderDoc(SgmlDoc *aDoc)
{
    WmlDoc *theDoc= (WmlDoc *)aDoc;		// Get rid of casting.
    WmlElement *rootElement;

    *outStream << "<!DOCTYPE WML PUBLIC \"" <<  theDoc->getDocType()->getName()  << "\">\n";

    rootElement= theDoc->getContainer();
    render(rootElement);

}


void WmlRenderer::renderStartOf(SgmlElement *anElement)
{
    WmlElement *theEle= ((WmlElement *)anElement);
    SgmlAttributeList *attributes;
    WmlDTD::WmlTags tag;

    tag= theEle->getTag();
    if (tag == WmlDTD::tComment) {
	*outStream << "<!--" << ((CommentElement *)theEle)->getData() << ">\n";
    }
    else if (tag == WmlDTD::tPcdata) {
	*outStream << ((HPcData *)theEle)->getData();
    }
    else {
	*outStream << "<" << tagNames[(unsigned int)tag];

	if ((attributes= theEle->getAttributes()) != NULL) {
	    WmlAttribute *attrib;
	    unsigned int i, attrCount= attributes->count();
	
	    for (i= 0; i < attrCount; i++) {
		attrib= (WmlAttribute *)attributes->objectAt(i);
		*outStream << " " << attrib->getName();
		if (attrib->getDefinition()->isAssignable()) {
		    *outStream << "="<< attrib->getValue();
		}
	    }
	}
	*outStream << ">";
	if ((tag == WmlDTD::tScript) || (tag == WmlDTD::tStyle) || (!WmlDTD::isFromEntity(tag, WmlDTD::text) && (tag != WmlDTD::tTitle))) {
	*outStream << "\n";
	}
    }
}

void WmlRenderer::renderEndOf(SgmlElement *anElement)
{
    WmlElement *theEle= ((WmlElement *)anElement);
    WmlDTD::WmlTags tag;

    tag= theEle->getTag();
    if ((tag != WmlDTD::tComment) && (tag != WmlDTD::tPcdata)) {
	if ((tag == WmlDTD::tWml) || (tag == WmlDTD::tHead) || (tag == WmlDTD::tBody)
			|| (theEle->getDefinition()->endType() == SgmlElementDef::mandatory)) {
	    *outStream << "</" << tagNames[(unsigned int)tag] << ">";
	    if ((tag == WmlDTD::tScript) || (tag == WmlDTD::tStyle) || !WmlDTD::isFromEntity(tag, WmlDTD::text)) {
	    *outStream << "\n";
	    }
	}
    }
}



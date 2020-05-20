/**************************************************
* File: renderHtml.cc.
* Desc: Implementation of the Html-to-Html (!) spit engine.
* Module: WAO : SgmlParser.
* Rev: 24 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <fstream.h>
#include "htmlElement.h"
#include "elementList.h"
#include "htmlDoc.h"
#include "nonStdElements.h"
#include "topElements.h"
#include "sgElementDef.h"
#include "htmlDTD.h"
#include "renderHtml.h"

char *HtmlRenderer::tagNames[HtmlDTD::numOfElements]= {
    "A", "ADDRESS", "APPLET", "AREA",
    "BASE", "BASEFONT", "BLOCKQUOTE", "BODY", "BR", "B", "BIG",
    "CAPTION", "CENTER", "CITE", "CODE",
    "DFN", "DIR", "DIV", "DL", "DD", "DT",
    "EM",
    "FONT", "FORM",
    "H1", "H2", "H3", "H4", "H5", "H6", "HEAD", "HR", "HTML",
    "I", "IMG", "INPUT", "ISINDEX",
    "KBD",
    "LINK", "LI", "LISTING",
    "MAP", "MENU", "META",
    "OPTION", "OL",
    "P", "PARAM", "PLAINTEXT", "PRE",
    "S", "SAMP", "SCRIPT", "SELECT", "SMALL", "SPAN", "STRIKE", "STRONG", "STYLE", "SUB", "SUP",
    "TABLE", "TD", "TEXTAREA", "TH", "TITLE", "TR", "TT",
    "U", "UL",
    "VAR",
    "XMP"
    , NULL, NULL		// Tags tPcData and tCData have no names.
};


HtmlRenderer::HtmlRenderer(ostream *output)
{
    outStream= output;
}


HtmlRenderer::~HtmlRenderer(void)
{
    delete outStream;
}


void HtmlRenderer::renderDoc(SgmlDoc *aDoc)
{
    HtmlDoc *theDoc= (HtmlDoc *)aDoc;		// Get rid of casting.
    HtmlElement *rootElement;

    *outStream << "<!DOCTYPE HTML PUBLIC \"" <<  theDoc->getDocType()->getName()  << "\">\n";

    rootElement= theDoc->getContainer();
    render(rootElement);

}


void HtmlRenderer::renderStartOf(SgmlElement *anElement)
{
    HtmlElement *theEle= ((HtmlElement *)anElement);
    SgmlAttributeList *attributes;
    HtmlDTD::HtmlTags tag;

    tag= theEle->getTag();
    if (tag == HtmlDTD::tComment) {
	*outStream << "<!--" << ((CommentElement *)theEle)->getData() << ">\n";
    }
    else if (tag == HtmlDTD::tPcdata) {
	*outStream << ((HPcData *)theEle)->getData();
    }
    else {
	*outStream << "<" << tagNames[(unsigned int)tag];

	if ((attributes= theEle->getAttributes()) != NULL) {
	    HtmlAttribute *attrib;
	    unsigned int i, attrCount= attributes->count();
	
	    for (i= 0; i < attrCount; i++) {
		attrib= (HtmlAttribute *)attributes->objectAt(i);
		*outStream << " " << attrib->getName();
		if (attrib->getDefinition()->isAssignable()) {
		    *outStream << "="<< attrib->getValue();
		}
	    }
	}
	*outStream << ">";
	if ((tag == HtmlDTD::tScript) || (tag == HtmlDTD::tStyle) || (!HtmlDTD::isFromEntity(tag, HtmlDTD::text) && (tag != HtmlDTD::tTitle))) {
	*outStream << "\n";
	}
    }
}

void HtmlRenderer::renderEndOf(SgmlElement *anElement)
{
    HtmlElement *theEle= ((HtmlElement *)anElement);
    HtmlDTD::HtmlTags tag;

    tag= theEle->getTag();
    if ((tag != HtmlDTD::tComment) && (tag != HtmlDTD::tPcdata)) {
	if ((tag == HtmlDTD::tHtml) || (tag == HtmlDTD::tHead) || (tag == HtmlDTD::tBody)
			|| (theEle->getDefinition()->endType() == SgmlElementDef::mandatory)) {
	    *outStream << "</" << tagNames[(unsigned int)tag] << ">";
	    if ((tag == HtmlDTD::tScript) || (tag == HtmlDTD::tStyle) || !HtmlDTD::isFromEntity(tag, HtmlDTD::text)) {
	    *outStream << "\n";
	    }
	}
    }
}



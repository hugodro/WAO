/**************************************************
* File: renderHtml.cc.
* Desc: Implementation of the Wml rendering engine..
* $Date: 2000/09/20 03:37:34 $
* Rev: 24 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/08/25 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: wRender.cpp,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
**************************************************/

#include <fstream>

#include <coreml/elementList.h>
#include <coreml/elementDef.h>

#include "wElement.h"
#include "wDoc.h"
#include "wDTD.h"
#include "allWElements.h"
#include "wRender.h"


char *xtnWmlRenderer::tagNames[xtnWmlDTD::numOfElements]= {
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
    , NULL, NULL		// Tags tPcData and tCData have no names.
};


xtnWmlRenderer::xtnWmlRenderer(std::ostream *output)
{
    outStream= output;
}


xtnWmlRenderer::~xtnWmlRenderer(void)
{
    delete outStream;
}


void xtnWmlRenderer::renderDoc(xtnCoreDoc *aDoc)
{
    xtnWmlDoc *theDoc= (xtnWmlDoc *)aDoc;		// Get rid of casting.
    xtnCoreElement *rootElement;

    *outStream << "<?xml version=\"1.0\"?>\n";
    *outStream << "<!DOCTYPE WML PUBLIC \"" <<  theDoc->getDocType()->getName()  << "\">\n";

    rootElement= theDoc->getHead();
    render(rootElement);

}


void xtnWmlRenderer::renderStartOf(xtnCoreElement *anElement)
{
    xtnWmlElement *theEle= ((xtnWmlElement *)anElement);
    xtnCoreAttributeList *attributes;
    xtnWmlDTD::WmlTags tag;

    tag= theEle->getTag();
    if (tag == xtnWmlDTD::tComment) {
	*outStream << "<!--" << ((xtnWComment *)theEle)->getData() << ">\n";
    }
    else if (tag == xtnWmlDTD::tPcdata) {
	*outStream << ((xtnWPcData *)theEle)->getData();
    }
    else {
	*outStream << "<" << tagNames[(unsigned int)tag];

	if ((attributes= theEle->getAttributes()) != NULL) {
	    xtnWmlAttribute *attrib;
	    unsigned int i, attrCount= attributes->count();
	
	    for (i= 0; i < attrCount; i++) {
		attrib= (xtnWmlAttribute *)attributes->objectAt(i);
		*outStream << " " << attrib->getName();
		if (attrib->getDefinition()->isAssignable()) {
		    *outStream << "="<< attrib->getValue();
		}
	    }
	}
 	if (theEle->getSubElements() != NULL) {
	    *outStream << ">";
	}
	else {
	    *outStream << "/>";
	}
    }
}


void xtnWmlRenderer::renderEndOf(xtnCoreElement *anElement)
{
    xtnWmlElement *theEle= ((xtnWmlElement *)anElement);
    xtnWmlDTD::WmlTags tag;

    tag= theEle->getTag();
    if ((tag != xtnWmlDTD::tComment) && (tag != xtnWmlDTD::tPcdata)) {
 	if (theEle->getSubElements() != NULL) {
	    *outStream << "</" << tagNames[(unsigned int)tag] << ">";
	}
    }
}



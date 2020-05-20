/**************************************************
* File: hdRender.cpp.
* Desc: Implementation of the Hdml rendering engine..
* $Date: 2000/09/20 03:37:34 $
* Rev: 2000/09/03 : REV 1 : Hugo DesRosiers : Creation.
* $Log: hdRender.cpp,v $
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

#include <fstream>

#include <coreml/elementList.h>
#include <coreml/sgElementDef.h>

#include "hdElement.h"
#include "hdDoc.h"
#include "hdDTD.h"
#include "allHdElements.h"
#include "hdRender.h"


char *xtnHdmlRenderer::tagNames[xtnHdmlDTD::numOfElements]= {
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
    , NULL, NULL		// Tags tPcData and tCData have no names.
};


xtnHdmlRenderer::xtnHdmlRenderer(ostream *output)
{
    outStream= output;
}


xtnHdmlRenderer::~xtnHdmlRenderer(void)
{
//    delete outStream;
}


void xtnHdmlRenderer::renderDoc(xtnCoreDoc *aDoc)
{
    xtnHdmlDoc *theDoc= (xtnHdmlDoc *)aDoc;		// Get rid of casting.
    xtnCoreElement *rootElement;

    rootElement= theDoc->getHead();
    render(rootElement);
}


void xtnHdmlRenderer::renderStartOf(xtnCoreElement *anElement)
{
    xtnHdmlElement *theEle= ((xtnHdmlElement *)anElement);
    xtnCoreAttributeList *attributes;
    xtnHdmlDTD::HdmlTags tag;

    tag= theEle->getTag();
    if (tag == xtnHdmlDTD::tComment) {
	*outStream << "<!--" << ((xtnHdComment *)theEle)->getData() << ">\n";
    }
    else if (tag == xtnHdmlDTD::tPcdata) {
	*outStream << ((xtnHdPcData *)theEle)->getData();
    }
    else {
	*outStream << "<" << tagNames[(unsigned int)tag];

	if ((attributes= theEle->getAttributes()) != NULL) {
	    xtnHdmlAttribute *attrib;
	    unsigned int i, attrCount= attributes->count();
	
	    for (i= 0; i < attrCount; i++) {
		attrib= (xtnHdmlAttribute *)attributes->objectAt(i);
		*outStream << " " << attrib->getName();
		if (attrib->getDefinition()->isAssignable()) {
		    *outStream << "="<< attrib->getValue();
		}
	    }
	}
	*outStream << ">";
    }
}


void xtnHdmlRenderer::renderEndOf(xtnCoreElement *anElement)
{
    xtnHdmlElement *theEle= ((xtnHdmlElement *)anElement);
    xtnHdmlDTD::HdmlTags tag;

    tag= theEle->getTag();
    if ((tag != xtnHdmlDTD::tComment) && (tag != xtnHdmlDTD::tPcdata)) {
	if ((tag == xtnHdmlDTD::tDeck) || (((xtnSgmlElementDef *)theEle->getDefinition())->endType() == xtnSgmlElementDef::mandatory)) {
	    *outStream << "</" << tagNames[(unsigned int)tag] << ">";
	}
    }
}



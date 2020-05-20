/**************************************************
* File: htRender.cpp.
* Desc: Implementation of the Html rendering engine..
* $Date$
* Rev: 2000/09/03 : REV 1 : Hugo DesRosiers : Creation.
* $Log$
**************************************************/


#include <coreml/elementList.h>
#include <coreml/sgElementDef.h>

#include "htElement.h"
#include "htDoc.h"
#include "htDTD.h"
#include "htElements.h"
#include "htRender.h"


xtnHtmlRenderer::xtnHtmlRenderer(std::ostream *output)
{
    outStream= output;
}


xtnHtmlRenderer::~xtnHtmlRenderer(void)
{
//    delete outStream;
}


void xtnHtmlRenderer::renderDoc(xtnCoreDoc *aDoc)
{
    xtnHtmlDoc *theDoc= (xtnHtmlDoc *)aDoc;		// Get rid of casting.
    xtnCoreElement *rootElement;

    *outStream << "<!DOCTYPE HTML PUBLIC \"" <<  theDoc->getDocType()->getName()  << "\">\n";

    rootElement= theDoc->getContainer();
    render(rootElement);
}


void xtnHtmlRenderer::renderStartOf(xtnCoreElement *anElement)
{
  xtnHtmlElement *theEle= ((xtnHtmlElement *)anElement);
  xtnCoreAttributeList *attributes;
  xtnHtmlDTD::HtmlTags tag;

  tag= theEle->getTag();
  if (tag == xtnHtmlDTD::tComment) {
    *outStream << "<!--" << ((xtnHtComment *)theEle)->getData() << "-->";
  }
  else if (tag == xtnHtmlDTD::tPcdata) {
    *outStream << ((xtnHPcData *)theEle)->getData();
  }
  else {
    *outStream << "<" << xtnHtmlDTD::nameTag(tag);
	if ((attributes= theEle->getAttributes()) != NULL) {
      xtnHtmlAttribute *attrib;
      unsigned int i, attrCount= attributes->count();
  
      for (i= 0; i < attrCount; i++) {
        attrib= (xtnHtmlAttribute *)attributes->objectAt(i);
        *outStream << " " << attrib->getName();
        if (attrib->getDefinition()->isAssignable()) {
            *outStream << "="<< attrib->getValue();
        }
      }
    }
    *outStream << ">";
    /* MOD-050203 [HD]: NO more beautification.
      if ((tag == xtnHtmlDTD::tScript) || (tag == xtnHtmlDTD::tStyle) || (!xtnHtmlDTD::isFromEntity(tag, xtnHtmlDTD::text) && (tag != xtnHtmlDTD::tTitle))) {
        *outStream << "\n";
      }
    */
  }
}


void xtnHtmlRenderer::renderEndOf(xtnCoreElement *anElement)
{
  xtnHtmlElement *theEle= ((xtnHtmlElement *)anElement);
  xtnHtmlDTD::HtmlTags tag;

  tag= theEle->getTag();
  if ((tag != xtnHtmlDTD::tComment) && (tag != xtnHtmlDTD::tPcdata)) {
	if ((tag == xtnHtmlDTD::tHtml) || (tag == xtnHtmlDTD::tHead) || (tag == xtnHtmlDTD::tBody)
        || (((xtnSgmlElementDef *)theEle->getDefinition())->endType() != xtnSgmlElementDef::illegal)) {
      *outStream << "</" << xtnHtmlDTD::nameTag(tag) << ">";
    /* MOD-050203 [HD]: NO more beautification.
      if ((tag == xtnHtmlDTD::tScript) || (tag == xtnHtmlDTD::tStyle) || !xtnHtmlDTD::isFromEntity(tag, xtnHtmlDTD::text)) {
	    *outStream << "\n";
      }
    */
	}
  }
}



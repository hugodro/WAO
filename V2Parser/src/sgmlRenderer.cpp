/**************************************************
* File: sgmlRenderer.cc.
* Desc: Implementation of the generic Sgml Renderer interface.
* Module: WAO : SgmlParser.
* Rev: 24 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#if defined(_WIN32)
#include <stdlib.h>
#endif
#include <akra/portableDefs.h>
#include "sgmlElement.h"
#include "elementList.h"
#include "sgmlRenderer.h"

void SgmlRenderer::renderDoc(SgmlDoc *aDoc)
{
    // ATTN-980324 [HD]: What to do ?
}


void SgmlRenderer::render(SgmlElement *anElement)
{
    SgmlElementList *subElements;

    renderStartOf(anElement);
    if ((subElements= anElement->getSubElements()) != NULL) {    // There is a list if it is not empty.
	renderElements(anElement, subElements);
    }
    renderEndOf(anElement);
}


void SgmlRenderer::renderStartOf(SgmlElement *anElement)
{
    // Must write the entry of the element, followed by the attributes.
}


void SgmlRenderer::renderElements(SgmlElement *anElement, SgmlElementList *subElements)
{
    unsigned int eleCount= subElements->count();
    unsigned int i;

    for (i= 0; i < eleCount; i++) {
	render(subElements->objectAt(i));
    }
}


void SgmlRenderer::renderEndOf(SgmlElement *anElement)
{
    // Must write the end of the element, if necessary.
}



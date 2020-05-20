/**************************************************
* File: renderer.cpp.
* Desc: Implementation of the Core ML Renderer interface.
* Rev: 24 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/08/22 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: renderer.cpp,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1.1.1  2000/09/01 07:33:30  hugo
* Initial Entry
*
**************************************************/

#if defined(_WIN32)
#include <stdlib.h>
#endif

#include <globDefs.h>

#include "element.h"
#include "elementList.h"
#include "renderer.h"


void xtnCoreRenderer::renderDoc(xtnCoreDoc *aDoc)
{
    // ATTN-980324 [HD]: What to do ?
}


void xtnCoreRenderer::render(xtnCoreElement *anElement)
{
    xtnCoreElementList *subElements;

    renderStartOf(anElement);
    if ((subElements= anElement->getSubElements()) != NULL) {    // There is a list if it is not empty.
	renderElements(anElement, subElements);
    }
    renderEndOf(anElement);
}


void xtnCoreRenderer::renderStartOf(xtnCoreElement *anElement)
{
    // Must write the entry of the element, followed by the attributes.
}


void xtnCoreRenderer::renderElements(xtnCoreElement *anElement, xtnCoreElementList *subElements)
{
    unsigned int eleCount= subElements->count();
    unsigned int i;

    for (i= 0; i < eleCount; i++) {
	render(subElements->objectAt(i));
    }
}


void xtnCoreRenderer::renderEndOf(xtnCoreElement *anElement)
{
    // Must write the end of the element, if necessary.
}



/**************************************************
* File: scanner.h.
* Desc: Implementation of the HTML scanning engine.
* $Date$
* Rev: 2005/02/03 : REV 1 : Hugo DesRosiers : Creation.
* $Log$
**************************************************/

#include <globDefs.h>

#include <coreml/elementList.h>
#include "htDoc.h"
#include "htElement.h"
#include "scanner.h"


HtScanner::HtScanner(xtnHtmlDoc *aDoc)
{
  document= aDoc;
  cursor= NULL;
}


HtScanner::~HtScanner()
{
  // ANYTHING TODO?.
}


xtnHtmlElement *HtScanner::searchFor(xtnHtmlDTD::HtmlTags aTag)
{

  if (cursor == NULL) {
    cursor= document->getContainer();
  }

  if (cursor->getTag() != aTag) {
    xtnHtmlElement *result= NULL;

    if ((cursor->getTag() != xtnHtmlDTD::tPcdata) && (cursor->getTag() != xtnHtmlDTD::tCdata) && (cursor->getTag() != xtnHtmlDTD::tComment)) {
      if (cursor->getSubElements() != NULL) {
        xtnCoreElementList *eleList;

        eleList= cursor->getSubElements();
        for (unsigned int i= 0; i < eleList->count(); i++) {
          if ((result= searchForAt(aTag, (xtnHtmlElement *)eleList->objectAt(i))) != NULL) {
            break;
          }
        }
      }
    }
    cursor= result;
  }

  return cursor;
}


xtnHtmlElement *HtScanner::searchForAt(xtnHtmlDTD::HtmlTags aTag, xtnHtmlElement *anElement, bool onlyChildren)
{
  xtnHtmlElement *result= NULL;

  if (anElement == NULL) return NULL;
  if (!onlyChildren) {
    if (anElement->getTag() == aTag)
      return anElement;
  }
  
  if ((anElement->getTag() == xtnHtmlDTD::tPcdata) || (anElement->getTag() == xtnHtmlDTD::tCdata) || (anElement->getTag() == xtnHtmlDTD::tComment))
    return NULL;

  if (anElement->getSubElements() != NULL) {
    xtnCoreElementList *eleList;

    eleList= anElement->getSubElements();
    for (unsigned int i= 0; i < eleList->count(); i++) {
      if ((result= searchForAt(aTag, (xtnHtmlElement *)eleList->objectAt(i))) != NULL) {
        break;
      }
    }
  }
  return result;
}


xtnHtmlElement *HtScanner::searchForAfter(xtnHtmlDTD::HtmlTags aTag, xtnHtmlElement *anElement, xtnHtmlElement *boundary)
{
  xtnHtmlElement *result= NULL, *tmpCur;

  if (anElement == NULL) return NULL;
  if ((tmpCur= (xtnHtmlElement *)anElement->getRight()) == NULL) {
    tmpCur= anElement;
    while ((tmpCur= (xtnHtmlElement *)tmpCur->getParent()) != NULL) {
      if (tmpCur == boundary) break;
      if ((anElement= (xtnHtmlElement *)tmpCur->getRight()) != NULL) {
        tmpCur= anElement;
        break;
      }
    }
  }

  if ((tmpCur == NULL) || (tmpCur == boundary))
    return NULL;

  if ((result= searchForAt(aTag, tmpCur)) == NULL) {
    result= searchForAfter(aTag, tmpCur, boundary);
  }
  return result;
}

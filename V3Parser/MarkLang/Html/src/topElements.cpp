/**************************************************
* File: topElements.cc.
* Desc: Implementation of the optimized version of the top elements of HTML 3.2.
* $Date$
* Rev: 22 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/11/30 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log$
**************************************************/

#include <stdlib.h>
#include <string>

#include <globDefs.h>

#include <coreml/elementList.h>

#include "nonStdElements.h"
#include "topElements.h"

/**************************************************
* Implementation: xtnTopCategory.
**************************************************/

xtnTopCategory::xtnTopCategory(xtnHtmlDTD::HtmlTags aTag)
 :  xtnHtmlElement (aTag)
{
    specialFlags= 0;
}

void xtnTopCategory::startTagged(void)
{
    specialFlags|= startPresent;
}

void xtnTopCategory::endTagged(void)
{
    specialFlags|= endPresent;
}


/**************************************************
* Implementation: xtnHHead.
**************************************************/

xtnHHead::xtnHHead()
 :  xtnTopCategory(xtnHtmlDTD::tHead)
{
}


char *xtnHHead::getTitle(void)
{
    unsigned int i, tmpCount;
    char *result= NULL;

    for (i= 0, tmpCount= subElements->count(); i < tmpCount; i++) {
	if (((xtnHtmlElement *)subElements->objectAt(i))->getTag() == xtnHtmlDTD::tTitle) {
#if defined(NeXT)
	    xtnCoreElementList *tmpTitleEle= subElements->objectAt(i)->subElements;
#else
	    xtnCoreElementList *tmpTitleEle= subElements->objectAt(i)->getSubElements();
#endif
	    if (tmpTitleEle != NULL) {
		for (i= 0, tmpCount= tmpTitleEle->count(); i < tmpCount; i++) {
		    if (((xtnHtmlElement *)tmpTitleEle->objectAt(i))->getTag() == xtnHtmlDTD::tPcdata) {
			result= ((xtnHPcData *)tmpTitleEle->objectAt(i))->getData();
		    }
		}		
	    }
	    break;
	}
    }
    return result;
}


/**************************************************
* Implementation: xtnHBody.
**************************************************/

xtnHBody::xtnHBody()
    : xtnTopCategory(xtnHtmlDTD::tBody)
{
}


/**************************************************
* Implementation: xtnHtComment.
**************************************************/

xtnHtComment::xtnHtComment(char *someData)
    : xtnHtmlElement(xtnHtmlDTD::tComment)
{
  if ((someData != NULL) && (*someData != '\0')) {
    uint tmpLength;
	data= new char[(tmpLength= strlen(someData)-1)+1];
	memcpy(data, someData, tmpLength);
    data[tmpLength]= '\0';
  }
  else data= NULL;
}


char *xtnHtComment::getData(void)
{
    return data;
}


/**************************************************
* Implementation: xtnHHtml.
**************************************************/


xtnHHtml::xtnHHtml()
    : xtnHtmlElement(xtnHtmlDTD::tHtml)
{
}



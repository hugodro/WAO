/**************************************************
* File: topElements.cc.
* Desc: Implementation of the optimized version of the top elements of HTML 3.2.
* Module: WAO : SgmlParser.
* Rev: 22 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/


#include <stdlib.h>
#include <string.h>

#include "elementList.h"
#include "nonStdElements.h"
#include "topElements.h"

/**************************************************
* Implementation: TopCategory.
**************************************************/

TopCategory::TopCategory(HtmlDTD::HtmlTags aTag)
 :  HtmlElement (aTag)
{
    specialFlags= 0;
}

void TopCategory::startTagged(void)
{
    specialFlags|= startPresent;
}

void TopCategory::endTagged(void)
{
    specialFlags|= endPresent;
}


/**************************************************
* Implementation: HHead.
**************************************************/

HHead::HHead()
 :  TopCategory(HtmlDTD::tHead)
{
}


char *HHead::getTitle(void)
{
    unsigned int i, tmpCount;
    char *result= NULL;

    for (i= 0, tmpCount= subElements->count(); i < tmpCount; i++) {
	if (((HtmlElement *)subElements->objectAt(i))->getTag() == HtmlDTD::tTitle) {
#if defined(NeXT)
	    SgmlElementList *tmpTitleEle= subElements->objectAt(i)->subElements;
#else
	    SgmlElementList *tmpTitleEle= subElements->objectAt(i)->getSubElements();
#endif
	    if (tmpTitleEle != NULL) {
		for (i= 0, tmpCount= tmpTitleEle->count(); i < tmpCount; i++) {
		    if (((HtmlElement *)tmpTitleEle->objectAt(i))->getTag() == HtmlDTD::tPcdata) {
			result= ((HPcData *)tmpTitleEle->objectAt(i))->getData();
		    }
		}		
	    }
	    break;
	}
    }
    return result;
}


/**************************************************
* Implementation: HBody.
**************************************************/

HBody::HBody()
    : TopCategory(HtmlDTD::tBody)
{
}


/**************************************************
* Implementation: CommentElement.
**************************************************/

CommentElement::CommentElement(char *someData)
    : HtmlElement(HtmlDTD::tComment)
{
    if ((someData != NULL) && (*someData != NULL)) {
	data= new char[strlen(someData)+1];
	strcpy(data, someData);
    }
    else data= NULL;
}


char *CommentElement::getData(void)
{
    return data;
}


/**************************************************
* Implementation: HHtml.
**************************************************/


HHtml::HHtml()
    : HtmlElement(HtmlDTD::tHtml)
{
}



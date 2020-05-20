/**************************************************
* File: htmlElement.cc.
* Desc: Implementation of the HTML general Element.
* Module: WAO : SgmlParser.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/


#include <string.h>

#include "htElementDef.h"
#include "elementList.h"
#include "htmlElement.h"

HtmlElement::HtmlElement(void)
{
    type= HtmlDTD::unknownTag;
    wantsAssignment= false;
}


HtmlElement::HtmlElement(HtmlDTD::HtmlTags aType)
{
    type= aType;
}


SgmlElementDef *HtmlElement::getDefinition(void)
{
    return HtmlDTD::getElementDef(type);
}


HtmlDTD::HtmlTags HtmlElement::getTag(void)
{
    return type;
}


int HtmlElement::assignAttribute(SgmlDoc::ValueType aType, char *aValue)
{
    int result= -10;

    if (wantsAssignment) {
	if (attributes != NULL) {
	    HtmlAttribute *currentAttr;

	    currentAttr= (HtmlAttribute *)attributes->lastObject();
	    result= currentAttr->setValue(aType, aValue);
	}
	else {
		// Error situation: there is no atribute to catch the value.
	}
	wantsAssignment= false;
    }
    return result;
}


void HtmlElement::toBeAssigned(void)
{
    wantsAssignment= true;
}


bool HtmlElement::expectsAssignment(void)
{
    return wantsAssignment;
}


void HtmlElement::cancelAssignment(void)
{
    wantsAssignment= false;
}



/**************************************************
* Implementation: HtmlAttribute.
**************************************************/

HtmlAttribute::HtmlAttribute(HtmlAttrDef *aDef)
    : SgmlAttribute(aDef)
{
    data= NULL;
}


int HtmlAttribute::setValue(SgmlDoc::ValueType aType, char *aValue)
{
    // TMPTMP.
    data= new char[strlen(aValue)+1];
    strcpy((char *)data, aValue);
    return 0;
}


char *HtmlAttribute::getValue(void)
{
    return (char *)data;
}


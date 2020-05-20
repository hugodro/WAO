/**************************************************
* File: htElement.cpp.
* Desc: Implementation of the HTML general Element.
* $Date$
* Rev : 2000/09/02 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* Rev : 2000/11/30 : REV 1 : Hugo DesRosiers : Created out of Hdml/hdElement.cpp.
* $Log$
**************************************************/

#include <string>

#include <globDefs.h>

#include <coreml/elementList.h>
#include "htElementDef.h"
#include "htElement.h"


xtnHtmlElement::xtnHtmlElement(void)
{
    type= xtnHtmlDTD::unknownTag;
    wantsAssignment= false;
}


xtnHtmlElement::xtnHtmlElement(xtnHtmlDTD::HtmlTags aType)
{
    type= aType;
    wantsAssignment= false;
}


xtnCoreElementDef *xtnHtmlElement::getDefinition(void)
{
    return xtnHtmlDTD::getElementDef(type);
}


xtnHtmlDTD::HtmlTags xtnHtmlElement::getTag(void)
{
  return type;
}


int xtnHtmlElement::assignAttribute(xtnCoreDoc::ValueType aType, char *aValue)
{
    int result= -10;

    if (wantsAssignment) {
	if (attributes != NULL) {
	    xtnHtmlAttribute *currentAttrib;

	    if ((currentAttrib= (xtnHtmlAttribute *)attributes->lastObject()) != NULL) {
		result= currentAttrib->setValue(aType, aValue);
		wantsAssignment= false;
	    }
	    else result= -11;
	}
	else result= -12;
    }
    return result;
}


void xtnHtmlElement::toBeAssigned(void)
{
    wantsAssignment= true;
}


bool xtnHtmlElement::expectsAssignment(void)
{
    return wantsAssignment;
}


void xtnHtmlElement::cancelAssignment(void)
{
    wantsAssignment= false;
}


bool xtnHtmlElement::endElement(void)
{
    // TODO.
    return false;
}


void xtnHtmlElement::markExpectAssignment(void)
{
    wantsAssignment= true;
}


bool xtnHtmlElement::canInclude(xtnHtmlDTD::HtmlTags aTag)
{
#if defined(OLD_CODE)
    if ((type == xtnHtmlDTD::tComment) || (type == xtnHtmlDTD::tPcdata)
	|| (type == xtnHtmlDTD::tCdata)) {
	return false;
    }
    // TODO: Use ElementDef to find out if the tag is accepted.
    return true;
#else
    xtnHtmlElementDef *theDef;

    if ((theDef= (xtnHtmlElementDef *)getDefinition()) != NULL) {
	return theDef->canInclude(aTag);
    }
    else
	return false;
#endif
}


bool xtnHtmlElement::wrapUp(void)
{
    // TODO.
    return true;
}


bool xtnHtmlElement::attributeMatch(char *anAttrib, char *aValue)
{
  xtnHtmlAttribute *target;
  if ((target= (xtnHtmlAttribute *)getAttribute(anAttrib)) != NULL) {
    char *value;

    if ((value= target->getValue()) != NULL) {
      if (strcmp(aValue, value) == 0)
        return true;
    }
  }
  return false;
}

/***************************************
* Implementation: xtnHtmlAttribute.
***************************************/

xtnHtmlAttribute::xtnHtmlAttribute(xtnCoreAttrDef *aDef)
  : xtnCoreAttribute(aDef)
{
// TMPTMP:
    data= NULL;
}


xtnHtmlAttribute::~xtnHtmlAttribute()
{
// TMPTMP:
    delete[] data;
}


int xtnHtmlAttribute::setValue(xtnCoreDoc::ValueType aType, char *aValue)
{
// TMPTMP:
    data= new char[strlen(aValue)+1];
    strcpy((char *)data, aValue);

    return 0;
}


char *xtnHtmlAttribute::getValue(void)
{
  return (char *)data;
}



/**************************************************
* File: wElement.cpp.
* Desc: Implementation of the WML general Element.
* Module: WAO : SgmlParser.
* Rev: 19 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#if defined(_WIN32)
#include <string>
#else
#include <string.h>
#endif

#include <globDefs.h>

#include <coreml/elementList.h>
#include "wElementDef.h"
#include "wElement.h"


xtnWmlElement::xtnWmlElement(void)
{
    type= xtnWmlDTD::unknownTag;
    wantsAssignment= false;
}


xtnWmlElement::xtnWmlElement(xtnWmlDTD::WmlTags aType)
{
    type= aType;
    wantsAssignment= false;
}


xtnCoreElementDef *xtnWmlElement::getDefinition(void)
{
    return xtnWmlDTD::getElementDef(type);
}


xtnWmlDTD::WmlTags xtnWmlElement::getTag(void)
{
  return type;
}


int xtnWmlElement::assignAttribute(xtnCoreDoc::ValueType aType, char *aValue)
{
    int result= -10;

    if (wantsAssignment) {
	if (attributes != NULL) {
	    xtnWmlAttribute *currentAttrib;

	    if ((currentAttrib= (xtnWmlAttribute *)attributes->lastObject()) != NULL) {
		result= currentAttrib->setValue(aType, aValue);
		wantsAssignment= false;
	    }
	    else result= -11;
	}
	else result= -12;
    }
    return result;
}


void xtnWmlElement::toBeAssigned(void)
{
    wantsAssignment= true;
}


bool xtnWmlElement::expectsAssignment(void)
{
    return wantsAssignment;
}


void xtnWmlElement::cancelAssignment(void)
{
    wantsAssignment= false;
}


bool xtnWmlElement::endElement(void)
{
    // TODO.
    return false;
}


void xtnWmlElement::markExpectAssignment(void)
{
    wantsAssignment= true;
}

bool xtnWmlElement::canInclude(xtnWmlDTD::WmlTags aTag) {
    if ((type == xtnWmlDTD::tComment) || (type == xtnWmlDTD::tPcdata)
	|| (type == xtnWmlDTD::tCdata)) {
	return false;
    }
    // TODO: Use ElementDef to find out if the tag is accepted.
    return true;
}


bool xtnWmlElement::wrapUp(void) {
    // TODO.
    return true;
}

/***************************************
* Implementation: xtnWmlAttribute.
***************************************/

xtnWmlAttribute::xtnWmlAttribute(xtnWmlAttrDef *aDef)
  : xtnCoreAttribute(aDef)
{
// TMPTMP:
    data= NULL;
}


xtnWmlAttribute::~xtnWmlAttribute()
{
// TMPTMP:
    delete[] data;
}


int xtnWmlAttribute::setValue(xtnCoreDoc::ValueType aType, char *aValue)
{
// TMPTMP:
    data= new char[strlen(aValue)+1];
    strcpy((char *)data, aValue);

    return 0;
}


char *xtnWmlAttribute::getValue(void)
{
  return (char *)data;
}



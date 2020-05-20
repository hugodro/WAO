/**************************************************
* File: wmlElement.cpp.
* Desc: Implementation of the WML general Element.
* Module: WAO : SgmlParser.
* Rev: 19 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "elementList.h"
#include "wElementDef.h"
#include "wmlElement.h"


WmlElement::WmlElement(void)
{
    type= WmlDTD::unknownTag;
    wantsAssignment= false;
}


WmlElement::WmlElement(WmlDTD::WmlTags aType)
{
    type= aType;
    wantsAssignment= false;
}


SgmlElementDef *WmlElement::getDefinition(void)
{
    return WmlDTD::getElementDef(type);
}


WmlDTD::WmlTags WmlElement::getTag(void)
{
  return type;
}


int WmlElement::assignAttribute(SgmlDoc::ValueType aType, char *aValue)
{
    int result= -10;

    if (wantsAssignment) {
	if (attributes != NULL) {
	    WmlAttribute *currentAttrib;

	    if ((currentAttrib= (WmlAttribute *)attributes->lastObject()) != NULL) {
		result= currentAttrib->setValue(aType, aValue);
		wantsAssignment= false;
	    }
	    else result= -11;
	}
	else result= -12;
    }
    return result;
}


void WmlElement::toBeAssigned(void)
{
    wantsAssignment= true;
}


boolean WmlElement::expectsAssignment(void)
{
    return wantsAssignment;
}


void WmlElement::cancelAssignment(void)
{
    wantsAssignment= false;
}


bool WmlElement::endElement(void)
{
    // TODO.
    return false;
}


void WmlElement::markExpectAssignment(void)
{
    wantsAssignment= true;
}

bool WmlElement::canInclude(WmlDTD::WmlTags) {
    // TODO.
    return true;
}


bool WmlElement::wrapUp(void) {
    // TODO.
    return true;
}

/***************************************
* Implementation: WmlAttribute.
***************************************/

WmlAttribute::WmlAttribute(WmlAttrDef *aDef)
  : SgmlAttribute(aDef)
{
  // TODO.
}


int WmlAttribute::setValue(SgmlDoc::ValueType aType, char *aValue)
{
  return 0;
  // TODO.
}


char *WmlAttribute::getValue(void)
{
  return NULL;
  // TODO.
}



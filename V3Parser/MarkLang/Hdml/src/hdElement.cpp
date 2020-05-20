/**************************************************
* File: hdElement.cpp.
* Desc: Implementation of the HDML general Element.
* Rev : 2000/09/02 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: hdElement.cpp,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1  2000/09/05 07:13:40  hugo
* Initial entry of real parsing/generating HDML support.
*
**************************************************/

#if defined(_WIN32)
#include <string>
#endif

#include <globDefs.h>

#include <coreml/elementList.h>
#include "hdElementDef.h"
#include "hdElement.h"


xtnHdmlElement::xtnHdmlElement(void)
{
    type= xtnHdmlDTD::unknownTag;
    wantsAssignment= false;
}


xtnHdmlElement::xtnHdmlElement(xtnHdmlDTD::HdmlTags aType)
{
    type= aType;
    wantsAssignment= false;
}


xtnCoreElementDef *xtnHdmlElement::getDefinition(void)
{
    return xtnHdmlDTD::getElementDef(type);
}


xtnHdmlDTD::HdmlTags xtnHdmlElement::getTag(void)
{
  return type;
}


int xtnHdmlElement::assignAttribute(xtnCoreDoc::ValueType aType, char *aValue)
{
    int result= -10;

    if (wantsAssignment) {
	if (attributes != NULL) {
	    xtnHdmlAttribute *currentAttrib;

	    if ((currentAttrib= (xtnHdmlAttribute *)attributes->lastObject()) != NULL) {
		result= currentAttrib->setValue(aType, aValue);
		wantsAssignment= false;
	    }
	    else result= -11;
	}
	else result= -12;
    }
    return result;
}


void xtnHdmlElement::toBeAssigned(void)
{
    wantsAssignment= true;
}


bool xtnHdmlElement::expectsAssignment(void)
{
    return wantsAssignment;
}


void xtnHdmlElement::cancelAssignment(void)
{
    wantsAssignment= false;
}


bool xtnHdmlElement::endElement(void)
{
    // TODO.
    return false;
}


void xtnHdmlElement::markExpectAssignment(void)
{
    wantsAssignment= true;
}

bool xtnHdmlElement::canInclude(xtnHdmlDTD::HdmlTags aTag) {
    if ((type == xtnHdmlDTD::tComment) || (type == xtnHdmlDTD::tPcdata)
	|| (type == xtnHdmlDTD::tCdata)) {
	return false;
    }
    // TODO: Use ElementDef to find out if the tag is accepted.
    return true;
}


bool xtnHdmlElement::wrapUp(void) {
    // TODO.
    return true;
}

/***************************************
* Implementation: xtnHdmlAttribute.
***************************************/

xtnHdmlAttribute::xtnHdmlAttribute(xtnHdmlAttrDef *aDef)
  : xtnCoreAttribute(aDef)
{
// TMPTMP:
    data= NULL;
}


xtnHdmlAttribute::~xtnHdmlAttribute()
{
// TMPTMP:
    delete[] data;
}


int xtnHdmlAttribute::setValue(xtnCoreDoc::ValueType aType, char *aValue)
{
// TMPTMP:
    data= new char[strlen(aValue)+1];
    strcpy((char *)data, aValue);

    return 0;
}


char *xtnHdmlAttribute::getValue(void)
{
  return (char *)data;
}



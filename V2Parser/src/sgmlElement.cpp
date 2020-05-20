/**************************************************
* File: sgmlElement.cc.
* Desc: Implementation of the HTML general Element.
* Module: WAO : SgmlParser.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#if defined(_WIN32)
#include <stdlib.h>
#include <string.h>
#endif
#include "elementList.h"
#include "sgElementDef.h"
#include "sgmlElement.h"

SgmlElement::SgmlElement()
{
    parent= 0;
    subElements= NULL;
    attributes= NULL;
}


bool SgmlElement::addSubElement(SgmlElement *anElement)
{
    if (subElements == NULL) {
	subElements= new SgmlElementList();
    }
    subElements->addObject(anElement);
    return true;
}


void SgmlElement::setParent(SgmlElement *anElement)
{
    parent= anElement;
}


void SgmlElement::linkAsChild(SgmlElement *anElement)
{
    anElement->parent= this;
    if (subElements == NULL) {
	subElements= new SgmlElementList();
    }
    subElements->addObject(anElement);
}

SgmlElement *SgmlElement::getParent(void)
{
    return parent;
}


void SgmlElement::addAttribute(SgmlAttribute *anAttrib)
{
    if (attributes == NULL) {
	attributes= new SgmlAttributeList(5);
    }
    attributes->addObject(anAttrib);
}


SgmlElementList *SgmlElement::getSubElements(void)
{
    return subElements;
}


SgmlAttributeList *SgmlElement:: getAttributes(void)
{
    return attributes;
}


/**************************************************
* Implementation: SgmlAttribute.
**************************************************/

SgmlAttribute::SgmlAttribute(SgmlAttrDef *aType)
{
    type= aType;
}


SgmlAttrDef *SgmlAttribute::getDefinition(void)
{
    return type;
}


char *SgmlAttribute::getName(void)
{
    return type->getName();
}

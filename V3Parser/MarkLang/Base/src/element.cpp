/**************************************************
* File: element.cc.
* Desc: Implementation of the HTML general Element.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/08/22 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: element.cpp,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1.1.1  2000/09/01 07:33:30  hugo
* Initial Entry
*
**************************************************/

#if defined(_WIN32)
#include <stdlib.h>
#include <string>
#else
#include <string.h>
#endif

#include <globDefs.h>

#include "elementList.h"
#include "elementDef.h"
#include "element.h"


xtnCoreElement::xtnCoreElement()
{
    parent= 0;
    subElements= NULL;
    attributes= NULL;
}


xtnCoreElement::~xtnCoreElement()
{
// TODO.
}


bool xtnCoreElement::addSubElement(xtnCoreElement *anElement)
{
    if (subElements == NULL) {
	subElements= new xtnCoreElementList();
    }
    subElements->addObject(anElement);
    return true;
}


void xtnCoreElement::setParent(xtnCoreElement *anElement)
{
    parent= anElement;
}


void xtnCoreElement::linkAsChild(xtnCoreElement *anElement)
{
    anElement->parent= this;
    if (subElements == NULL) {
	subElements= new xtnCoreElementList();
    }
    subElements->addObject(anElement);
}


xtnCoreElement *xtnCoreElement::getParent(void)
{
    return parent;
}


void xtnCoreElement::addAttribute(xtnCoreAttribute *anAttrib)
{
    if (attributes == NULL) {
	attributes= new xtnCoreAttributeList(5);
    }
    attributes->addObject(anAttrib);
}


xtnCoreElementList *xtnCoreElement::getSubElements(void)
{
    return subElements;
}


xtnCoreAttributeList *xtnCoreElement::getAttributes(void)
{
    return attributes;
}


xtnCoreAttribute *xtnCoreElement::getAttribute(char *aName)
{
  if (attributes != NULL) {
    for (unsigned int i= 0; i < attributes->count(); i++) {
      if (strcmp(attributes->objectAt(i)->getName(), aName) == 0) {
        return attributes->objectAt(i);
      }
    }
  }
  return NULL;
}


xtnCoreElement *xtnCoreElement::getLeft()
{
  xtnCoreElement *result= NULL;

  if (parent != NULL) {
    xtnCoreElementList *siblings;

    if ((siblings= parent->getSubElements()) != NULL) {
      unsigned int i;

      for (i= 0; i < siblings->count(); i++) {
        if (siblings->objectAt(i) == this)
          break;
        else
          result= siblings->objectAt(i);
      }
      // Check against weird situations: we didn't find ourself.
      if (i == siblings->count())
        result= NULL;
    }
  }

  return result;
}


xtnCoreElement *xtnCoreElement::getRight()
{
  xtnCoreElement *result= NULL;

  if (parent != NULL) {
    xtnCoreElementList *siblings;

    if ((siblings= parent->getSubElements()) != NULL) {
      unsigned int i;

      for (i= 0; i < siblings->count(); i++) {
        if (siblings->objectAt(i) == this)
          break;
      }
      // Check against weird situations: we didn't find ourself.
      if (i < (siblings->count()-1))
        result= siblings->objectAt(i+1);
    }
  }

  return result;
}


/**************************************************
* Implementation: xtnCoreAttribute.
**************************************************/

xtnCoreAttribute::xtnCoreAttribute(xtnCoreAttrDef *aType)
{
    type= aType;
}


xtnCoreAttribute::~xtnCoreAttribute()
{
// TODO.
}


xtnCoreAttrDef *xtnCoreAttribute::getDefinition(void)
{
    return type;
}


char *xtnCoreAttribute::getName(void)
{
    return type->getName();
}

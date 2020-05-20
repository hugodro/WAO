/**************************************************
* File: dtdDefinition.h.
* Desc: Definition of the Core DTD for ML parser.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/08/22 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: dtdDefinition.cpp,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1.1.1  2000/09/01 07:33:30  hugo
* Initial Entry
*
**************************************************/

#include <globDefs.h>

#include "elementDef.h"
#include "dtdDefinition.h"


xtnCoreDtdDefinition::xtnCoreDtdDefinition(void)
{
    elements= NULL;
    attributes= tailAttr= NULL;
    entities= NULL;
    nbrEleDefs= nbrAttrDefs= nbrEntiDefs= 0;
    name= NULL;
}


xtnCoreDtdDefinition::~xtnCoreDtdDefinition(void)
{
  while (attributes != NULL) {
    tailAttr= attributes->getNext();
    delete attributes;
    attributes= tailAttr;
  }
}


xtnCoreElementDef *xtnCoreDtdDefinition::getElementDef(char *aName)
{
// TODO:
    return NULL;
}


xtnCoreAttrDef *xtnCoreDtdDefinition::getAttribDef(xtnCoreElementDef *anElement, char *aName)
{
// TODO:
    return NULL;
}


xtnCoreDoc *xtnCoreDtdDefinition::createConformentDoc(char *aName)
{
// TODO:    return new xtnCoreDoc(aName);
    return NULL;
}


char *xtnCoreDtdDefinition::getName(void)
{
    return name;
}


void xtnCoreDtdDefinition::addAttribute(xtnCoreAttrDef *anAttr) {
  if (tailAttr != NULL) {
    tailAttr->linkTo(anAttr);
  }
  else {
    attributes= anAttr;
  }
  tailAttr= anAttr;
}

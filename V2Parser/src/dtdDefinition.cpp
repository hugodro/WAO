/**************************************************
* File: dtdDefinition.h.
* Desc: Definition of the generic Sgml Document parser.
* Module: WAO : SgmlParser.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "dtdDefinition.h"


DtdDefinition::DtdDefinition(void)
{
    elements= NULL;
    attributes= NULL;
    entities= NULL;
    nbrEleDefs= nbrAttrDefs= nbrEntiDefs= 0;
    name= NULL;
}


SgmlElementDef *DtdDefinition::getElementDef(char *aName)
{
// TODO:
    return NULL;
}


SgmlAttribDef *DtdDefinition::getAttribDef(SgmlElementDef *anElement, char *aName)
{
// TODO:
    return NULL;
}


SgmlDoc *DtdDefinition::createConformentDoc(char *aName)
{
// TODO:    return new GenericSgmlDoc(aName);
    return NULL;
}


char *DtdDefinition::getName(void)
{
    return name;
}

#ifndef _XTN_CORE_DTD_DEFINITION_H_
#define _XTN_CORE_DTD_DEFINITION_H_
/**************************************************
* File: dtdDefinition.h.
* Desc: Definition of the Core Document parser for ML.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/08/22 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: dtdDefinition.h,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1.1.1  2000/09/01 07:33:30  hugo
* Initial Entry
*
**************************************************/

#include <exportDefs.h>

class xtnCoreElementDef;
class xtnCoreAttrDef;
class xtnCoreEntity;
class xtnCoreDoc;


class ClExp xtnCoreDtdDefinition {
  protected:
    xtnCoreElementDef **elements;
    xtnCoreAttrDef *attributes, *tailAttr;
    xtnCoreEntity **entities;
    unsigned int nbrEleDefs, nbrAttrDefs, nbrEntiDefs;
    char *name;

  public:
    xtnCoreDtdDefinition(void);
    virtual ~xtnCoreDtdDefinition(void);

    virtual xtnCoreElementDef *getElementDef(char *aName);
    virtual xtnCoreAttrDef *getAttribDef(xtnCoreElementDef *anElement, char *aName);

    virtual xtnCoreDoc *createConformentDoc(char *aName);
    virtual char *getName(void);
    virtual void addAttribute(xtnCoreAttrDef *anAttr);
};


#endif	/* _XTN_CORE_DTD_DEFINITION_H_ */


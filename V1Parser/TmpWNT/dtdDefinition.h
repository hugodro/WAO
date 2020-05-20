#ifndef _DTDDEFINITION_H_
#define _DTDDEFINITION_H_
/**************************************************
* File: dtdDefinition.h.
* Desc: Definition of the generic Sgml Document parser.
* Module: WAO : SgmlParser.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#if !defined(NULL)
#define NULL		(0L)
#endif


class SgmlElementDef;
class SgmlAttribDef;
class SgmlEntity;
class SgmlDoc;


class DtdDefinition : public AkObject {
  protected:
    SgmlElementDef **elements;
    SgmlAttribDef **attributes;
    SgmlEntity **entities;
    unsigned int nbrEleDefs, nbrAttrDefs, nbrEntiDefs;
    char *name;

  public:
    DtdDefinition(void);
    SgmlElementDef *getElementDef(char *aName);
    SgmlAttribDef *getAttribDef(SgmlElementDef *anElement, char *aName);

    virtual SgmlDoc *createConformentDoc(char *aName);
    virtual char *getName(void);
};


#endif	/* _DTDDEFINITION_H_ */

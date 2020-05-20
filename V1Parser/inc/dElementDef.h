#ifndef _HDML_ELEMENT_DEFS_H_
#define _HDML_ELEMENT_DEFS_H_
/**************************************************
* File: dElementDef.h.
* Desc: Definition of the HDML Element Definition class.
* Module: WAO : SgmlParser.
* Rev: 29 mai 2000 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include "hdmlDTD.h"
#include "sgElementDef.h"

class HdmlElementDef {
    friend class HdmlDTD;
  protected:
    unsigned int nbrAttributes;
    SgmlAttrDef **attributes;
    HdmlDTD::HdmlTags tag;

  public:
    HdmlElementDef(char *aName);
    virtual boolean canInclude(HdmlDTD::HdmlTags aTag);
    virtual SgmlAttrDef *getAttribute(char *aName);
    virtual HdmlDTD::HdmlTags getTag(void);
};


class HdmlAttrDef : public SgmlAttrDef {
  public:
    HdmlAttrDef(void);
    HdmlAttrDef(char *aName, DataType aType, Flags aFlag);
    virtual void setDefinition(char *aName, DataType aType, Flags aFlag);
    virtual boolean isNamed(char *aName);
};



#endif    /* _HDML_ELEMENT_DEFS_H_ */

#ifndef _WML_ELEMENT_DEFS_H_
#define _WML_ELEMENT_DEFS_H_
/**************************************************
* File: wElementDef.h.
* Desc: Definition of the WML Element Definition class.
* Module: WAO : SgmlParser.
* Rev: 19 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include "wmlDTD.h"
#include "sgElementDef.h"


/************************************
* Class: WmlElementDef.
* SuperClass: SgmlElementDef.
* Desc: Equivalent of an !ELEMENT definition of the
*          WML DTD.
************************************/

class WmlElementDef : public SgmlElementDef {
    friend class WmlDTD;

  protected:
    unsigned int nbrAttributes;
    SgmlAttrDef **attributes;    
    WmlDTD::WmlTags tag;	// Remember our fast ID.

  public:
    WmlElementDef(char *aName);
    virtual boolean canInclude(WmlDTD::WmlTags aTag);
    virtual SgmlAttrDef *getAttribute(char *aName);
    virtual WmlDTD::WmlTags getTag(void);
};


class WmlAttrDef : public SgmlAttrDef {
  public:
    WmlAttrDef(void);
    WmlAttrDef(char *aName, DataType aType, Flags aFlag);
    virtual void setDefinition(char *aName, DataType aType, Flags aFlag);
    virtual boolean isNamed(char *aName);
};


#endif		/* _WML_ELEMENT_DEFS_H_ */

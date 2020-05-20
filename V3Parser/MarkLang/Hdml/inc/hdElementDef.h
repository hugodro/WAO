#ifndef _XTN_HDML_ELEMENT_DEFS_H_
#define _XTN_HDML_ELEMENT_DEFS_H_
/**************************************************
* File: dElementDef.h.
* Desc: Definition of the HDML Element Definition class.
* $Date: 2000/09/20 03:37:34 $
* Rev: 29 mai 2000 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/09/02 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: hdElementDef.h,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1  2000/09/05 07:13:37  hugo
* Initial entry of real parsing/generating HDML support.
*
**************************************************/

#include <coreml/elementDef.h>
#include "hdDTD.h"


/************************************
* Class: xtnHdmlElementDef.
* SuperClass: xtnCoreElementDef.
* Desc: Equivalent of an !ELEMENT definition of (our version of)
*          the HDML DTD.
************************************/

class xtnHdmlElementDef : public xtnCoreElementDef {
    friend class xtnHdmlDTD;

  protected:
    xtnHdmlDTD::HdmlTags tag;

  public:
    xtnHdmlElementDef(char *aName);

    virtual bool canInclude(xtnHdmlDTD::HdmlTags aTag);
    inline xtnHdmlDTD::HdmlTags getTag() { return tag; }
};


/************************************
* Class: xtnHdmlElementDef.
* SuperClass: xtnCoreElementDef.
* Desc: Equivalent of an !ATTRLIST definition of (our version of)
*        the HDML DTD.
************************************/

class xtnHdmlAttrDef : public xtnCoreAttrDef {
  public:
    xtnHdmlAttrDef();
    xtnHdmlAttrDef(char *aName, unsigned int aType, Flags aFlag);

    virtual void setDefinition(char *aName, unsigned int aType, Flags aFlag);
    virtual bool isNamed(char *aName);
};



#endif    /* _XTN_HDML_ELEMENT_DEFS_H_ */

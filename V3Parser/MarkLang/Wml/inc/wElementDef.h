#ifndef _XTN_WML_ELEMENT_DEFS_H_
#define _XTN_WML_ELEMENT_DEFS_H_
/**************************************************
* File: wElementDef.h.
* Desc: Definition of the WML Element Definition class.
* Rev: 19 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/08/23 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: wElementDef.h,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
**************************************************/

#include <coreml/xElementDef.h>
#include "wDTD.h"


/************************************
* Class: xtnWmlElementDef.
* SuperClass: xtnCoreElementDef.
* Desc: Equivalent of an !ELEMENT definition of the
*          WML DTD.
************************************/

class xtnWmlElementDef : public xtnCoreElementDef {
    friend class xtnWmlDTD;

  protected:
    xtnWmlDTD::WmlTags tag;	// Remember our fast ID.

  public:
    xtnWmlElementDef(char *aName);

    virtual bool canInclude(xtnWmlDTD::WmlTags aTag);

    inline xtnWmlDTD::WmlTags getTag(void) { return tag; }
};


/************************************
* Class: xtnWmlAttrDef.
* SuperClass: xtnXmlAttrDef.
* Desc: Equivalent of an !ATTRLIST definition of the
*          WML DTD.
************************************/

class xtnWmlAttrDef : public xtnXmlAttrDef {

  public:
    xtnWmlAttrDef(void);
    xtnWmlAttrDef(char *aName, unsigned int aType, Flags aFlag);
    virtual void setDefinition(char *aName, unsigned int aType, Flags aFlag);
    virtual bool isNamed(char *aName);
};


#endif		/* _XTN_WML_ELEMENT_DEFS_H_ */

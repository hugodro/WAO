#ifndef _HTMLELEMENT_DEFS_H_
#define _HTMLELEMENT_DEFS_H_
/**************************************************
* File: htElementDef.h.
* Desc: Definition of the HTML Element definition.
* Module: WAO : SgmlParser.
* Rev: 22 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include "htmlDTD.h"
#include "sgElementDef.h"


class HtmlElementDef : public SgmlElementDef {
    friend class HtmlDTD;

  protected:
    unsigned int nbrAttributes;
    SgmlAttrDef *attributes;    
    HtmlDTD::HtmlTags tag;	// Remember our fast ID.

  public:
    HtmlElementDef(char *aName, TagFlags firstFlag, TagFlags sndFlag);
    virtual bool canInclude(HtmlDTD::HtmlTags aTag);
    virtual SgmlAttrDef *getAttribute(char *aName);
    virtual HtmlDTD::HtmlTags getTag(void);
};


class HtmlAttrDef : public SgmlAttrDef {
  public:
    HtmlAttrDef(void);
    HtmlAttrDef(char *aName, DataType aType, Flags aFlag);
    virtual void setDefinition(char *aName, DataType aType, Flags aFlag);
    virtual bool isNamed(char *aName);
};


#endif		/* _HTMLELEMENT_DEFS_H_ */

#ifndef _HTMLELEMENT_H_
#define _HTMLELEMENT_H_
/**************************************************
* File: htmlElement.h.
* Desc: Definition of the HTML general Element.
* Module: WAO : SgmlParser.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "htmlDTD.h"
#include "sgmlElement.h"
#include "sgmlDoc.h"

class HtmlAttrDef;


class HtmlElement : public SgmlElement {
  protected:
    HtmlDTD::HtmlTags type;
    bool wantsAssignment;

  public:
    HtmlElement(void);
    HtmlElement(HtmlDTD::HtmlTags aType);
    virtual SgmlElementDef *getDefinition(void);
    virtual HtmlDTD::HtmlTags getTag(void);
    virtual int assignAttribute(SgmlDoc::ValueType aType, char *aValue);
    virtual void toBeAssigned(void);
    virtual bool expectsAssignment(void);
    virtual void cancelAssignment(void);
};


class HtmlAttribute : public SgmlAttribute {
  protected:
    void *data;

  public:
    HtmlAttribute(HtmlAttrDef *aDef);
    virtual int setValue(SgmlDoc::ValueType aType, char *aValue);
    virtual char *getValue(void);
};


#endif		/* _HTMLELEMENT_H_ */

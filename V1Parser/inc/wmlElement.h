#ifndef _WML_ELEMENT_H_
#define _WML_ELEMENT_H_
/**************************************************
* File: wmlElement.h.
* Desc: Definition of the WML general Element.
* Module: WAO : SgmlParser.
* Rev: 19 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "wmlDTD.h"
#include "sgmlElement.h"
#include "sgmlDoc.h"


class WmlAttrDef;

/************************************
* Class: WmlElement.
* SuperClass: SgmlElement.
* Desc: Generic node for an in-memory instance of a
*          WML document tree.
************************************/

class WmlElement : public SgmlElement {
  protected:
    WmlDTD::WmlTags type;
    boolean wantsAssignment;

  public:
    WmlElement(void);
    WmlElement(WmlDTD::WmlTags aType);
    virtual SgmlElementDef *getDefinition(void);
    virtual WmlDTD::WmlTags getTag(void);
    virtual int assignAttribute(SgmlDoc::ValueType aType, char *aValue);
    virtual void toBeAssigned(void);
    virtual boolean expectsAssignment(void);
    virtual void cancelAssignment(void);

    // New parsing approach: an element gets a signal that the parsing is over, and
    // performs cleanup and fusion into the parse tree.
    virtual bool endElement(void);
    virtual void markExpectAssignment(void);	// Same as toBeAssigned();
    virtual bool canInclude (WmlDTD::WmlTags aTag);
    virtual bool wrapUp(void);
};


/************************************
* Class: WmlAttribute
* SuperClass: SgmlAttribute
* Desc: Generic attribute to be attached to nodes in an in-memory
*          instance of a WML document tree.
************************************/

class WmlAttribute : public SgmlAttribute {
  protected:
    void *data;

  public:
    WmlAttribute(WmlAttrDef *aDef);
    virtual int setValue(SgmlDoc::ValueType aType, char *aValue);
    virtual char *getValue(void);
};


#endif		/* _WML_ELEMENT_H_ */

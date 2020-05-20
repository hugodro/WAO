#ifndef _HDML_ELEMENT_H_
#define _HDML_ELEMENT_H_
/**************************************************
* File: hdmlElement.h.
* Desc: Definition of the HDML general Element.
* Module: WAO : SgmlParser.
* Rev: 29 mai 2000 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "hdmlDTD.h"
#include "sgmlElement.h"
#include "sgmlDoc.h"


class HdmlAttrDef;

/************************************
* Class: HdmlElement.
* SuperClass: SgmlElement.
* Desc: Generic node for an in-memory instance of a
*          HDML document tree.
************************************/

class HdmlElement : public SgmlElement {
  protected:
    HdmlDTD::HdmlTags type;
    boolean wantsAssignment;

  public:
    HdmlElement(void);
    HdmlElement(HdmlDTD::HdmlTags aType);
    virtual SgmlElementDef *getDefinition(void);
    virtual HdmlDTD::HdmlTags getTag(void);
    virtual int assignAttribute(SgmlDoc::ValueType aType, char *aValue);
    virtual void toBeAssigned(void);
    virtual boolean expectsAssignment(void);
    virtual void cancelAssignment(void);

    // New parsing approach: an element gets a signal that the parsing is over, and
    // performs cleanup and fusion into the parse tree.
    virtual bool endElement(void);
    virtual void markExpectAssignment(void);	// Same as toBeAssigned();
    virtual bool canInclude (HdmlDTD::HdmlTags aTag);
    virtual bool wrapUp(void);
};


/************************************
* Class: HdmlAttribute
* SuperClass: SgmlAttribute
* Desc: Generic attribute to be attached to nodes in an in-memory
*          instance of a HDML document tree.
************************************/

class HdmlAttribute : public SgmlAttribute {
  protected:
    void *data;

  public:
    HdmlAttribute(HdmlAttrDef *aDef);
    virtual int setValue(SgmlDoc::ValueType aType, char *aValue);
    virtual char *getValue(void);
};


#endif		/* _HDML_ELEMENT_H_ */

#ifndef _XTN_HDML_ELEMENT_H_
#define _XTN_HDML_ELEMENT_H_
/**************************************************
* File: hdElement.h.
* Desc: Definition of the HDML general Element.
* $Date: 2000/09/20 03:37:34 $
* Rev: 2000/09/02 : REV 1 : Hugo DesRosiers : Creation.
* $Log: hdElement.h,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1  2000/09/05 07:13:37  hugo
* Initial entry of real parsing/generating HDML support.
*
**************************************************/

#include <coreml/element.h>
#include <coreml/doc.h>

#include "hdDTD.h"


class xtnHdmlAttrDef;

/************************************
* Class: xtnHdmlElement.
* SuperClass: xtnCoreElement.
* Desc: Generic node for an in-memory instance of a
*          HDML document tree.
************************************/

class xtnHdmlElement : public xtnCoreElement {
  protected:
    xtnHdmlDTD::HdmlTags type;
    bool wantsAssignment;

  public:
    xtnHdmlElement(void);
    xtnHdmlElement(xtnHdmlDTD::HdmlTags aType);
    virtual xtnCoreElementDef *getDefinition(void);
    virtual xtnHdmlDTD::HdmlTags getTag(void);
    virtual int assignAttribute(xtnCoreDoc::ValueType aType, char *aValue);
    virtual void toBeAssigned(void);
    virtual bool expectsAssignment(void);
    virtual void cancelAssignment(void);

    // New parsing approach: an element gets a signal that the parsing is over, and
    // performs cleanup and fusion into the parse tree.
    virtual bool endElement(void);
    virtual void markExpectAssignment(void);	// Same as toBeAssigned();
    virtual bool canInclude(xtnHdmlDTD::HdmlTags aTag);
    virtual bool wrapUp(void);
};


/************************************
* Class: xtnHdmlAttribute
* SuperClass: xtnCoreAttribute
* Desc: Generic attribute to be attached to nodes in an in-memory
*          instance of a HDML document tree.
************************************/

class xtnHdmlAttribute : public xtnCoreAttribute {
  protected:
    void *data;

  public:
    xtnHdmlAttribute(xtnHdmlAttrDef *aDef);
    virtual ~xtnHdmlAttribute();

    virtual int setValue(xtnCoreDoc::ValueType aType, char *aValue);
    virtual char *getValue(void);
};


#endif		/* _XTN_HDML_ELEMENT_H_ */

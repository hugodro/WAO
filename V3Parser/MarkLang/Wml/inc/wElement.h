#ifndef _XTN_WML_ELEMENT_H_
#define _XTN_WML_ELEMENT_H_
/**************************************************
* File: wElement.h.
* Desc: Definition of the WML general Element.
* $Date: 2000/09/20 03:37:34 $
* Rev: 19 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/08/22 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: wElement.h,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
**************************************************/

#include <coreml/element.h>
#include <coreml/doc.h>

#include "wDTD.h"


class xtnWmlAttrDef;

/************************************
* Class: xtnWmlElement.
* SuperClass: xtnCoreElement.
* Desc: Generic node for an in-memory instance of a
*          WML document tree.
************************************/

class xtnWmlElement : public xtnCoreElement {
  protected:
    xtnWmlDTD::WmlTags type;
    bool wantsAssignment;

  public:
    xtnWmlElement(void);
    xtnWmlElement(xtnWmlDTD::WmlTags aType);
    virtual xtnCoreElementDef *getDefinition(void);
    virtual xtnWmlDTD::WmlTags getTag(void);
    virtual int assignAttribute(xtnCoreDoc::ValueType aType, char *aValue);
    virtual void toBeAssigned(void);
    virtual bool expectsAssignment(void);
    virtual void cancelAssignment(void);

    // New parsing approach: an element gets a signal that the parsing is over, and
    // performs cleanup and fusion into the parse tree.
    virtual bool endElement(void);
    virtual void markExpectAssignment(void);	// Same as toBeAssigned();
    virtual bool canInclude(xtnWmlDTD::WmlTags aTag);
    virtual bool wrapUp(void);
};


/************************************
* Class: xtnWmlAttribute
* SuperClass: xtnCoreAttribute
* Desc: Generic attribute to be attached to nodes in an in-memory
*          instance of a WML document tree.
************************************/

class xtnWmlAttribute : public xtnCoreAttribute {
  protected:
    void *data;

  public:
    xtnWmlAttribute(xtnWmlAttrDef *aDef);
    virtual ~xtnWmlAttribute();

    virtual int setValue(xtnCoreDoc::ValueType aType, char *aValue);
    virtual char *getValue(void);
};


#endif		/* _XTN_WML_ELEMENT_H_ */

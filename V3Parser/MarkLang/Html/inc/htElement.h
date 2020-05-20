#ifndef _XTN_HTML_ELEMENT_H_
#define _XTN_HTML_ELEMENT_H_
/**************************************************
* File: htElement.h.
* Desc: Definition of the HTML general Element.
* $Date$
* Rev: 2000/11/30 : REV 0 : Hugo DesRosiers : Created from Hdml/hdElement.h.
* $Log$
**************************************************/

#include <coreml/element.h>
#include <coreml/doc.h>

#include "htDTD.h"


class xtnHtmlAttrDef;

/************************************
* Class: xtnHtmlElement.
* SuperClass: xtnCoreElement.
* Desc: Generic node for an in-memory instance of a
*          HTML document tree.
************************************/

class xtnHtmlElement : public xtnCoreElement {
  protected:
    xtnHtmlDTD::HtmlTags type;
    bool wantsAssignment;

  public:
    xtnHtmlElement(void);
    xtnHtmlElement(xtnHtmlDTD::HtmlTags aType);
    virtual xtnCoreElementDef *getDefinition(void);
    virtual xtnHtmlDTD::HtmlTags getTag(void);
    virtual int assignAttribute(xtnCoreDoc::ValueType aType, char *aValue);
    virtual void toBeAssigned(void);
    virtual bool expectsAssignment(void);
    virtual void cancelAssignment(void);

    // New parsing approach: an element gets a signal that the parsing is over, and
    // performs cleanup and fusion into the parse tree.
    virtual bool endElement(void);
    virtual void markExpectAssignment(void);	// Same as toBeAssigned();
    virtual bool canInclude(xtnHtmlDTD::HtmlTags aTag);
    virtual bool wrapUp(void);

    virtual bool attributeMatch(char *anAttrib, char *aValue);

};


/************************************
* Class: xtnHtmlAttribute
* SuperClass: xtnCoreAttribute
* Desc: Generic attribute to be attached to nodes in an in-memory
*          instance of a HTML document tree.
************************************/

class xtnHtmlAttribute : public xtnCoreAttribute {
  protected:
    void *data;

  public:
    xtnHtmlAttribute(xtnCoreAttrDef *aDef);
    virtual ~xtnHtmlAttribute();

    virtual int setValue(xtnCoreDoc::ValueType aType, char *aValue);
    virtual char *getValue(void);
};


#endif		/* _XTN_HTML_ELEMENT_H_ */

#ifndef _XTN_CORE_ELEMENT_H_
#define _XTN_CORE_ELEMENT_H_
/**************************************************
* File: element.h.
* Desc: Definition of the XTN_CORE_ general Element.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/08/22 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
**************************************************/

#include <exportDefs.h>

class xtnCoreElementList;
class xtnCoreAttributeList;
class xtnCoreElementDef;
class xtnCoreAttrDef;
class xtnCoreAttribute;


/*************************************
* Class: xtnCoreElement.
* Super: nil.
* Desc: 
*************************************/

class ClExp xtnCoreElement {
  protected:
    xtnCoreElement *parent;
    xtnCoreElementList *subElements;
    xtnCoreAttributeList *attributes;
    unsigned int linePos[2];

  public:
    xtnCoreElement();
    virtual ~xtnCoreElement();

    virtual xtnCoreElementDef *getDefinition()= 0;
    virtual bool addSubElement(xtnCoreElement *anElement);
    virtual void setParent(xtnCoreElement *anElement);
    virtual void linkAsChild(xtnCoreElement *anElement);
    virtual xtnCoreElement *getParent();
    virtual void addAttribute(xtnCoreAttribute *anAttrib);
    virtual xtnCoreElementList *getSubElements();
    virtual xtnCoreAttributeList *getAttributes();
    virtual xtnCoreAttribute *getAttribute(char *aName);
    virtual xtnCoreElement *getLeft();
    virtual xtnCoreElement *getRight();

    inline void setStartPos(unsigned int aPos) { linePos[0]= aPos; }
    inline void setEndPos(unsigned int aPos) { linePos[1]= aPos; }
    inline unsigned int getStartPos() { return linePos[0]; }
    inline unsigned int getEndPos() { return linePos[1]; }
};

/*************************************
* Class: xtnCoreAttribute.
* Super: nil.
* Desc: 
*************************************/

class ClExp xtnCoreAttribute {
  protected:
    xtnCoreAttrDef *type;

  public:
    xtnCoreAttribute(xtnCoreAttrDef *aType);
    virtual ~xtnCoreAttribute();

    virtual xtnCoreAttrDef *getDefinition();
    virtual char *getName();
};


#endif		/* _XTN_CORE_ELEMENT_H_ */

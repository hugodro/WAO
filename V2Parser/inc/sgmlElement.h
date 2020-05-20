#ifndef _SGMLELEMENT_H_
#define _SGMLELEMENT_H_
/**************************************************
* File: sgmlElement.h.
* Desc: Definition of the SGML general Element.
* Module: WAO : SgmlParser.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include <akra/portableDefs.h>


class SgmlElementList;
class SgmlAttributeList;
class SgmlElementDef;
class SgmlAttrDef;
class SgmlAttribute;


class SgmlElement : public AkObject {
  protected:
    SgmlElement *parent;
    SgmlElementList *subElements;
    SgmlAttributeList *attributes;

  public:
    SgmlElement(void);

    virtual SgmlElementDef *getDefinition(void)= 0;
    virtual bool addSubElement(SgmlElement *anElement);
    virtual void setParent(SgmlElement *anElement);
    virtual void linkAsChild(SgmlElement *anElement);
    virtual SgmlElement *getParent(void);
    virtual void addAttribute(SgmlAttribute *anAttrib);
    virtual SgmlElementList *getSubElements(void);
    virtual SgmlAttributeList *getAttributes(void);
};


class SgmlAttribute : public AkObject {
  protected:
    SgmlAttrDef *type;
  public:
    SgmlAttribute(SgmlAttrDef *aType);
    virtual SgmlAttrDef *getDefinition(void);
    virtual char *getName(void);
};


#endif		/* _SGMLELEMENT_H_ */

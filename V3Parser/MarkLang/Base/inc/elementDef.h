#ifndef _XTN_CORE_ELEMENT_DEFS_H_
#define _XTN_CORE_ELEMENT_DEFS_H_
/**************************************************
* File: elementDef.h.
* Desc: Definition of the generic xtnCoreElementDef for ML parsing.
* Rev: 22 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev : 2000/08/22 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: elementDef.h,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1.1.2  2000/09/20 03:26:46  hugo
* Initial entry
*
**************************************************/

#include <exportDefs.h>

class xtnCoreAttrDef;


/*************************************
* Class: xtnCoreElementDef.
* Super: nil.
* Desc: 
*************************************/

class ClExp xtnCoreElementDef {
  protected:
    char *name;
    xtnCoreAttrDef **attributes;    
    unsigned int nbrAttributes, arraySize;

  public:
    xtnCoreElementDef(char *aName);
    virtual ~xtnCoreElementDef();

    virtual int canIncludeElement(xtnCoreElementDef *aDef);
    virtual xtnCoreAttrDef *getAttribute(char *aName);
    virtual void addAttribute(xtnCoreAttrDef *anAttr);
};


/*************************************
* Class: xtnCoreAttrDef.
* Super: nil.
* Desc: 
*************************************/

class ClExp xtnCoreAttrDef {
  public:
    enum DataType {
	cdata, url, dtName, number, color, oneOf, flag, nmToken
	, custom
	, nbrDataType
    };
    enum Flags {
	required, implied
    };

  protected:
    xtnCoreAttrDef *next;
    char *name;
    unsigned int type;
    unsigned int utilFlag;

  public:
    xtnCoreAttrDef();
    xtnCoreAttrDef(const char *aName, unsigned int aType, unsigned int aFlag);
    virtual ~xtnCoreAttrDef();

    virtual void setDefinition(char *aName, unsigned int aType, unsigned int aFlag);
    virtual bool isNamed(char *aName);
    virtual bool isAssignable();
    inline char *getName() { return name; }
    inline void linkTo(xtnCoreAttrDef *anAttr) { next= anAttr; }
    inline xtnCoreAttrDef *getNext() { return next; }
};


#endif 	/* _XTN_CORE_ELEMENT_DEFS_H_ */

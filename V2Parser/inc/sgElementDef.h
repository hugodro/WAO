#ifndef _SGMLELEMENT_DEFS_H_
#define _SGMLELEMENT_DEFS_H_
/**************************************************
* File: sgElementDef.h.
* Desc: Definition of the generic Sgml Element definition.
* Module: WAO : SgmlParser.
* Rev: 22 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include <akra/portableDefs.h>


class SgmlAttrDef;


class SgmlElementDef : public AkObject {
  public:
    enum TagFlags {
	mandatory, optional, illegal
    };

  protected:
    char *name;
    TagFlags startFlag;
    TagFlags endFlag;

  public:
    SgmlElementDef(char *aName, TagFlags firstFlag, TagFlags sndFlag);
    virtual int canIncludeElement(SgmlElementDef *aDef);
    virtual TagFlags startType(void);
    virtual TagFlags endType(void);
    virtual SgmlAttrDef *getAttribute(char *aName);
};


class SgmlAttrDef : public AkObject {
  public:
    enum DataType {
	cdata, url, dtName, number, color, oneOf, flag, custom
	, nmToken, id, dtBoolean    // XML additions.
    };
    enum Flags {
	required, implied
    };

  protected:
    char *name;
    DataType type;
    Flags utilFlag;

  public:
    SgmlAttrDef(void);
    SgmlAttrDef(char *aName, DataType aType, Flags aFlag);
    virtual void setDefinition(char *aName, DataType aType, Flags aFlag);
    virtual bool isNamed(char *aName);
    virtual bool isAssignable(void);
    virtual char *getName(void);
};


#endif 	/* _SGMLELEMENT_DEFS_H_ */

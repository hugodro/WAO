#ifndef _XTN_SGML_ELEMENT_DEFS_H_
#define _XTN_SGML_ELEMENT_DEFS_H_
/**************************************************
* File: sgElementDef.h.
* Desc: Definition of the SGML DTD parsing.
* Rev: 22 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev : 2000/08/23 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: sgElementDef.h,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1.1.1  2000/09/01 07:33:30  hugo
* Initial Entry
*
**************************************************/

#include <exportDefs.h>

#include <coreml/elementDef.h>

/*************************************
* Class: xtnSgmlElementDef.
* Super: nil.
* Desc: 
*************************************/

class ClExp xtnSgmlElementDef : public xtnCoreElementDef {
  public:
    enum TagFlags {
	mandatory, optional, illegal
    };

  protected:
    unsigned int startFlag;
    unsigned int endFlag;

  public:
    xtnSgmlElementDef(char *aName, unsigned int bFlag, unsigned int eFlag);
    inline unsigned int startType(void) {  return startFlag; }
    inline unsigned int endType(void) { return endFlag; }
};



class ClExp xtnSgmlAttrDef : public xtnCoreAttrDef {
    // TODO: Move this and the XML conterpart into the Core.
  public:
    enum DataTypeSGML {
        id= nbrDataType
	, nbrSgmlDataType
    };

  public:
    enum SgmlDataType {
	mandatory, optional, illegal
    };

  xtnSgmlAttrDef(const char *aName, unsigned int aType, unsigned int aFlag);
};

#endif /* _XTN_SGML_ELEMENT_DEFS_H_ */

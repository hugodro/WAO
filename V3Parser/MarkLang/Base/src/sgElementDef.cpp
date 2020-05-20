/**************************************************
* File: sgElementDef.cpp.
* Desc: Definition of the SGML DTD parsing.
* Rev: 22 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev : 2000/08/23 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: sgElementDef.cpp,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1.1.1  2000/09/01 07:33:30  hugo
* Initial Entry
*
**************************************************/

#include "sgElementDef.h"


xtnSgmlElementDef::xtnSgmlElementDef(char *aName, unsigned int bFlag, unsigned int eFlag)
  : xtnCoreElementDef(aName)
{
    startFlag= bFlag;
    endFlag= eFlag;
}


xtnSgmlAttrDef::xtnSgmlAttrDef(const char *aName, unsigned int aType, unsigned int aFlag)
 : xtnCoreAttrDef(aName, aType, aFlag)
{
}

#ifndef _XTN_XML_ELEMENT_DEFS_H_
#define _XTN_XML_ELEMENT_DEFS_H_
/**************************************************
* File: xElementDef.h.
* Desc: Definition of the XML extensions for parsing.
* $Date: 2000/09/20 03:37:34 $
* $Log: xElementDef.h,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1.1.2  2000/09/20 03:26:47  hugo
* Initial entry
*
**************************************************/

#include <exportDefs.h>

#include "elementDef.h"


/*************************************
* Class: xtnXmlAttrDef.
* Super: xtnCoreAttrDef.
* Desc: 
*************************************/

class ClExp xtnXmlAttrDef : public xtnCoreAttrDef {
  public:
    enum DataTypeXML {
        id= nbrDataType, dtBoolean
	, nbrXmlDataType
    };

  public:
    xtnXmlAttrDef();
    xtnXmlAttrDef(char *aName, unsigned int aType, Flags aFlag);
};


#endif 	/* _XTN_XML_ELEMENT_DEFS_H_ */

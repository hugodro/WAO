#ifndef _SGMLDOCUMENT_H_
#define _SGMLDOCUMENT_H_
/**************************************************
* File: sgmlDoc.h.
* Desc: Definition of the generic SGML document.
* Module: WAO : SgmlParser.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include "sgmlDoc.h"

#if !defined(NULL)
#define NULL		(0L)
#endif

class DtdDefinition;


class SgmlDoc : public AkObject {
  public:
    enum ValueType {
	literal, unqLiterhack, name, nameToken, pcData, cData
    };

  protected:
    DtdDefinition *docType;
    char *dateParsed;
    char *sourceName;
    
  public:
    SgmlDoc(char *aName);
    virtual ~SgmlDoc(void);

    char *getDateParsed(void);
    char *getSourceName(void);
    DtdDefinition *getDocType(void);

    virtual void initForParse(void);
    virtual void treatComment(char *data);
};


#endif	/* _SGMLDOCUMENT_H_ */

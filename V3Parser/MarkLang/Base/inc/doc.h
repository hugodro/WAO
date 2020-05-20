#ifndef _XTN_CORE_DOCUMENT_H_
#define _XTN_CORE_DOCUMENT_H_
/**************************************************
* File: doc.h.
* Desc: Definition of the generic Core document.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/08/22 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: doc.h,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1.1.1  2000/09/01 07:33:30  hugo
* Initial Entry
*
**************************************************/

#include <exportDefs.h>

class xtnCoreDtdDefinition;


class ClExp xtnCoreDoc {
  public:
    enum ValueType {
	literal, unqLiterhack, name, nameToken, pcData, cData
    };

  protected:
    xtnCoreDtdDefinition *docType;
    char *dateParsed;
    char *sourceName;
    
  public:
    xtnCoreDoc(char *aName);
    virtual ~xtnCoreDoc();

    char *getDateParsed();
    char *getSourceName();
    xtnCoreDtdDefinition *getDocType();

    virtual void initForParse();
    virtual void treatComment(char *data);
};


#endif	/* _XTN_CORE_DOCUMENT_H_ */

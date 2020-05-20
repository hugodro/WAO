#ifndef _XTN_WML_PAGE_H_
#define _XTN_WML_PAGE_H_
/*******************************************
 * File: wmlPage.h.
 * Desc: Definition of the xtnWmlPage class.
 * History: 2000/04/04 : REV 0 : [HD] : Creation.
******************************************/

#include <exportDefs.h>

#include <coreml/documents.h>


/*****************************************
* Class: xtnWmlPage.
* Super-Class: nil.
* Desc: Container for pre-defined WML pages.
*****************************************/

class ClExp xtnWmlPage : public xtnMLDoc {

  public:
    xtnWmlPage(void);
    xtnWmlPage(char *someData, unsigned int length);

    virtual unsigned int getClass(void);
};


#endif	/* _XTN_WML_PAGE_H_ */


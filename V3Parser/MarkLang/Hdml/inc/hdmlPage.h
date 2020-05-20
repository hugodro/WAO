#ifndef _XTN_HDML_PAGE_H_
#define _XTN_HDML_PAGE_H_
/*******************************************
 * File: hdmlPage.h.
 * Desc: Definition of the xtnHdmlPage class.
 * History: 2000/04/04 : REV 0 : [HD] : Creation.
******************************************/

#include <exportDefs.h>

#include <httpsup/documents.h>


/*****************************************
* Class: xtnHdmlPage.
* Super-Class: nil.
* Desc: Container for pre-defined WML pages.
*****************************************/

class ClExp xtnHdmlPage : public xtnMLDoc {

  public:
    xtnHdmlPage();
    xtnHdmlPage(char *someData, unsigned int length);

    virtual unsigned int getClass(void);
};

#endif	/* _XTN_HDML_PAGE_H_ */


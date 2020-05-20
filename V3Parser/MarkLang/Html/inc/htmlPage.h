#ifndef _XTN_HTML_PAGE_H_
#define _XTN_HTML_PAGE_H_
/*******************************************
 * File: htmlPage.h.
 * Desc: Definition of the xtnHtmlPage class.
 * History: 2000/04/04 : REV 0 : [HD] : Creation.
******************************************/

#include <exportDefs.h>

#include <coreml/documents.h>


/*****************************************
* Class: xtnHtmlPage.
* Super-Class: nil.
* Desc: Container for pre-defined WML pages.
*****************************************/

class ClExp xtnHtmlPage : public xtnMLDoc {

  public:
    xtnHtmlPage();
    xtnHtmlPage(char *someData, unsigned int length);

    virtual unsigned int getClass(void);
};

#endif	/* _XTN_HTML_PAGE_H_ */


#ifndef _XTN_TOPELEMENTS_H_
#define _XTN_TOPELEMENTS_H_
/**************************************************
* File: topElements.h.
* Desc: Definition of the optimized version of the top elements of HTML 3.2.
* $Date$
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/11/30 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log$
**************************************************/

#include "htElement.h"


class xtnTopCategory : public xtnHtmlElement {
  public:
    enum ParseFlag {
	startPresent= 0x1, endPresent= 0x2
    };

  protected:
    unsigned int specialFlags;
  public:
    xtnTopCategory(xtnHtmlDTD::HtmlTags aTag);
    virtual void startTagged(void);
    virtual void endTagged(void);
};


class xtnHHead : public xtnTopCategory {
  public:
    xtnHHead();
    virtual char *getTitle(void);
};


class xtnHBody : public xtnTopCategory {
  public:
    xtnHBody();
};


class xtnHHtml : public xtnHtmlElement {
  protected:
  public:
    xtnHHtml();
};


// TODO: Move this to the core package.
class xtnHtComment : public xtnHtmlElement {
  protected:
    char *data;

  public:
    xtnHtComment(char *someData);
    virtual char *getData(void);
};



#endif		/* _XTN_TOPELEMENTS_H_ */

#ifndef _TOPELEMENTS_H_
#define _TOPELEMENTS_H_
/**************************************************
* File: topElements.h.
* Desc: Definition of the optimized version of the top elements of HTML 3.2.
* Module: WAO : SgmlParser.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "htmlElement.h"

class TopCategory : public HtmlElement {
  public:
    enum ParseFlag {
	startPresent= 0x1, endPresent= 0x2
    };

  protected:
    unsigned int specialFlags;
  public:
    TopCategory(HtmlDTD::HtmlTags aTag);
    virtual void startTagged(void);
    virtual void endTagged(void);
};


class HHead : public TopCategory {
  public:
    HHead();
    virtual char *getTitle(void);
};


class HBody : public TopCategory {
  public:
    HBody();
};


class CommentElement : public HtmlElement {
  protected:
    char *data;

  public:
    CommentElement(char *someData);
    virtual char *getData(void);
};


class HHtml : public HtmlElement {
  protected:
  public:
    HHtml();
};

#endif		/* _TOPELEMENTS_H_ */

#ifndef _HTMLDOCUMENT_H_
#define _HTMLDOCUMENT_H_
/**************************************************
* File: htmlDoc.h.
* Desc: Definition of the HTML conforment document.
* Module: WAO : SgmlParser.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include "sgmlDoc.h"
#include "htmlDTD.h"


class HHtml;
class HHead;
class HBody;


class HtmlDoc : public SgmlDoc {
  public:
    enum State {
	initial, postHtml, inHead, postHead, inBody, postBody, postDoc
    };


  protected:
    HHtml *container;
    HHead *head;
    HBody *body;
    HtmlElement *currentElement;
    State state;

  public:
    HtmlDoc(char *aName, HtmlDTD *aDtd);

    virtual void treatComment(char *data);

    virtual int pushElement(HtmlDTD::HtmlTags anElement);
    virtual int addAttribute(char *attrName, boolean assignFlag);
    virtual int addValue(ValueType aType, char *aValue);
    virtual int addData(char *someData);
    virtual int popElement(HtmlDTD::HtmlTags anElement);

    virtual State getState(void);
    virtual void setState(State aState);
    virtual void gotHeadStart(void);
    virtual void gotHeadEnd(void);
    virtual void gotBodyStart(void);
    virtual void gotBodyEnd(void);
    virtual HtmlElement *getContainer(void);
    virtual char *getTitle(void);
    virtual HBody *getBody(void);

    inline HtmlElement *getCurrentElement(void) { return currentElement; }
};


#endif	/* _HTMLDOCUMENT_H_ */

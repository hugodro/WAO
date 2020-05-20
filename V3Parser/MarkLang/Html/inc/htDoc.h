#ifndef _XTN_HTMLDOCUMENT_H_
#define _XTN_HTMLDOCUMENT_H_
/**************************************************
* File: htDoc.h.
* Desc: Definition of the HTML conforment document.
* $Date$
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/11/30 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log$
**************************************************/

#include <exportDefs.h>

#include <coreml/doc.h>
#include "htDTD.h"


class xtnHHtml;
class xtnHHead;
class xtnHBody;
class xtnHtEleContainer;

class xtnHtmlDoc : public xtnCoreDoc {
  public:
    enum State {
	initial, postHtml, inHead, postHead, inBody, postBody, postDoc
    };


  protected:
    xtnHHtml *container;
    xtnHHead *head;
    xtnHBody *body;
    xtnHtmlElement *currentElement;
    xtnHtEleContainer *rootElements;
    xtnHtEleContainer *tailRootElements;
    State state;

  public:
    xtnHtmlDoc(char *aName, xtnHtmlDTD *aDtd);

    virtual void treatComment(char *data);

    virtual int pushElement(xtnHtmlDTD::HtmlTags anElement);
    virtual int addAttribute(char *attrName, bool assignFlag);
    virtual int addValue(ValueType aType, char *aValue);
    virtual int addData(char *someData, unsigned int lineNbr= 0);
    virtual int popElement(xtnHtmlDTD::HtmlTags anElement);

    virtual State getState(void);
    virtual void setState(State aState);
    virtual void gotHeadStart(void);
    virtual void gotHeadEnd(void);
    virtual void gotBodyStart(void);
    virtual void gotBodyEnd(void);
    virtual xtnHtmlElement *getContainer(void);
    virtual char *getTitle(void);
    virtual xtnHBody *getBody(void);

    inline xtnHtmlElement *getCurrentElement(void) { return currentElement; }

    // New parsing approach: the DTD has the logic, but the doc is the front-end to it.
    virtual int startElement(xtnHtmlDTD::HtmlTags anElement, unsigned int linePos= 0);
    virtual int endCurrentElement(unsigned int linePos= 0);
    virtual int endElement(xtnHtmlDTD::HtmlTags anElement, unsigned int linePos= 0);
    virtual int closeCurrentItem();
    virtual void addRootElement(xtnHtmlElement *anElement);

};


#endif	/* _XTN_HTMLDOCUMENT_H_ */

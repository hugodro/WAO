#ifndef _WMLDOCUMENT_H_
#define _WMLDOCUMENT_H_
/**************************************************
* File: wmlDoc.h.
* Desc: Definition of the WML conforment document.
* Module: WAO : SgmlParser.
* Rev: 19 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include "sgmlDoc.h"
#include "wmlDTD.h"


class WWml;
class XmlDef;
class WEleContainer;


class WmlDoc : public SgmlDoc {
  public:
    enum State {
	initial, postWml, inHead, postHead, inBody, postBody, postDoc
    };


  protected:
    XmlDef *wmlDefinition;
    WEleContainer *rootElements;
    WEleContainer *tailRootElements;
    WWml *container;
    WmlElement *currentElement;
    State state;

  public:
    WmlDoc(char *aName, WmlDTD *aDtd);

    virtual void treatComment(char *data);

    virtual int pushElement(WmlDTD::WmlTags anElement);
    virtual int addAttribute(char *attrName, boolean assignFlag);
    virtual int addValue(ValueType aType, char *aValue);
    virtual int addData(char *someData);
    virtual int popElement(WmlDTD::WmlTags anElement);

    virtual State getState(void);
    virtual void setState(State aState);
    virtual void gotHeadStart(void);
    virtual void gotHeadEnd(void);
    virtual void gotBodyStart(void);
    virtual void gotBodyEnd(void);
    virtual WmlElement *getContainer(void);

    // New parsing approach: the DTD has the logic, but the doc is the front-end to it.
    virtual int startElement(WmlDTD::WmlTags anElement);
    virtual int endCurrentElement(void);
    virtual int endElement(WmlDTD::WmlTags anElement);
    virtual int startCData(char *rawData);
    virtual int endCData(char *rawData);
    virtual int closeCurrentItem(void);
    virtual void addRootElement(WmlElement *anElement);
};


#endif	/* _WMLDOCUMENT_H_ */

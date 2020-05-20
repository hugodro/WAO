#ifndef _XTN_WML_DOCUMENT_H_
#define _XTN_WML_DOCUMENT_H_
/**************************************************
* File: wDoc.h.
* Desc: Definition of the WML conforment document.
* $Date: 2000/09/20 03:37:34 $
* Rev: 19 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/08/22 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: wDoc.h,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
**************************************************/

#include <exportDefs.h>

#include <coreml/doc.h>
#include "wDTD.h"


class xtnWWml;
class xtnXmlDef;
class xtnWEleContainer;


class ClExp xtnWmlDoc : public xtnCoreDoc {
  public:
    enum State {
	initial, postWml, inHead, postHead, inBody, postBody, postDoc
    };


  protected:
    xtnXmlDef *wmlDefinition;
    xtnWEleContainer *rootElements;
    xtnWEleContainer *tailRootElements;
    xtnWWml *headWml;
    xtnWmlElement *currentElement;
    State state;

  public:
    xtnWmlDoc(char *aName, xtnWmlDTD *aDtd);
    virtual ~xtnWmlDoc();

    virtual void treatComment(char *data);

    virtual int pushElement(xtnWmlDTD::WmlTags anElement);
    virtual int addAttribute(char *attrName, bool assignFlag);
    virtual int addValue(ValueType aType, char *aValue);
    virtual int addData(char *someData);
    virtual int popElement(xtnWmlDTD::WmlTags anElement);

    virtual State getState();
    virtual void setState(State aState);
    virtual xtnWmlElement *getHead();

    // New parsing approach: the DTD has the logic, but the doc is the front-end to it.
    virtual int startElement(xtnWmlDTD::WmlTags anElement);
    virtual int endCurrentElement();
    virtual int endElement(xtnWmlDTD::WmlTags anElement);
    virtual int startCData(char *rawData);
    virtual int endCData(char *rawData);
    virtual int closeCurrentItem();
    virtual void addRootElement(xtnWmlElement *anElement);
};


#endif	/* _XTN_WML_DOCUMENT_H_ */

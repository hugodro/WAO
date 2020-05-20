#ifndef _XTN_HDML_DOCUMENT_H_
#define _XTN_HDML_DOCUMENT_H_
/**************************************************
* File: dDoc.h.
* Desc: Definition of the HDML conforment document.
* $Date: 2000/09/20 03:37:34 $
* Rev: 2000/09/02 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: hdDoc.h,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1  2000/09/05 07:13:37  hugo
* Initial entry of real parsing/generating HDML support.
*
**************************************************/

#include <exportDefs.h>

#include <coreml/doc.h>
#include "hdDTD.h"


class xtnHdDeck;
class xtnEleContainer;
class xtnHdEleContainer;
class xtnHdmlElement;


class ClExp xtnHdmlDoc : public xtnCoreDoc {
  public:
    enum State {
	initial, postHdml, inHead, postHead, inBody, postBody, postDoc
    };


  protected:
    xtnHdmlDTD *hdmlDefinition;
    xtnHdEleContainer *rootElements;
    xtnHdEleContainer *tailRootElements;
    xtnHdDeck *headHdml;
    xtnHdmlElement *currentElement;
    State state;

  public:
    xtnHdmlDoc(char *aName, xtnHdmlDTD *aDtd);
    virtual ~xtnHdmlDoc();

    virtual void treatComment(char *data);

    // TODO-000902 [HD]: Get rid of old parsing approach.
    virtual int pushElement(xtnHdmlDTD::HdmlTags anElement);
    virtual int addAttribute(char *attrName, bool assignFlag);
    virtual int addValue(ValueType aType, char *aValue);
    virtual int addData(char *someData);
    virtual int popElement(xtnHdmlDTD::HdmlTags anElement);

    virtual State getState();
    virtual void setState(State aState);
    virtual xtnHdmlElement *getHead();

    // New parsing approach: the DTD has the logic, but the doc is the front-end to it.
    virtual int startElement(xtnHdmlDTD::HdmlTags anElement);
    virtual int endCurrentElement();
    virtual int endElement(xtnHdmlDTD::HdmlTags anElement);
    virtual int startCData(char *rawData);
    virtual int endCData(char *rawData);
    virtual int closeCurrentItem();
    virtual void addRootElement(xtnHdmlElement *anElement);
};


#endif	/* _XTN_HDML_DOCUMENT_H_ */

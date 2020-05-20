#ifndef _XTN_HDMLDTD_DEF_H_
#define _XTN_HDMLDTD_DEF_H_
/**************************************************
* File: hdDTD.h.
* Desc: Definition of an optimized DtdDef for HDML 2.0.
* Rev: 29 mai 2000 : REV 0 : Hugo DesRosiers : Creation.
* Rev : 2000/09/02 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: hdDTD.h,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1  2000/09/05 07:13:37  hugo
* Initial entry of real parsing/generating HDML support.
*
**************************************************/

#include <coreml/dtdDefinition.h>

class xtnHdmlElement;
class xtnHdmlElementDef;


class xtnHdmlDTD : public xtnCoreDtdDefinition {
  public:
    enum HdmlTags {
      tAction
      , tB
      , tBr
      , tCe
      , tCenter
      , tChoice
      , tDisplay
      , tEntry
      , tDeck    // Warning: the tag for this entity is HDML.
      , tI, tImg
      , tLine
      , tNoDisplay
      , tRight
      , tTab
      , tWrap
      , tPcdata, tCdata
      , numOfElements
      , unknownTag, emptyTag, tComment
    };


/* NmToken Values.
      , tSoft1, tSoft2, tSoft3, tSoft4, tSoft5, tSoft6, tSoft7, tSoft8
      , tAccept, tPrev, tHelp
*/

    enum HdmlEntity {
	eCard
	, eText

	// TODO: get rid of the useless entities (carried over from HTML).
        , addressContent
	, block, bodyContent
	, flow, font, form
	, headContent, heading, headMisc
	, list
	, phrase
	, preformatted, preExclusion
	, special
    };


    // TMPTMP: no category is yet defined for HDML.
    enum EntityCategory {
	ecText
    };


  protected:
    static char *tagNames[numOfElements];
    static xtnHdmlElementDef *elementDef[numOfElements];

  public:
    static HdmlTags identifyTag(char *aName);
    static xtnHdmlElementDef * getElementDef(HdmlTags aTag);
    static bool isFromEntity(HdmlTags aTag, HdmlEntity anEntity);

  public:
    xtnHdmlDTD();
    virtual ~xtnHdmlDTD();

    void loadDefinitions(void);

    virtual xtnCoreDoc *createConformentDoc(char *aName);
    virtual xtnHdmlElement *instanciateType(HdmlTags aType);
    virtual bool useVersion(char *versName);
    virtual bool checkCategory(HdmlTags aTag, EntityCategory aCategory);
};


#endif		/* _XTN_HDMLDTD_DEF_H_ */

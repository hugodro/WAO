#ifndef _HDMLDTD_DEF_H_
#define _HDMLDTD_DEF_H_
/**************************************************
* File: hdmlDTD.h.
* Desc: Definition of an optimized DtdDef for HDML 2.0.
* Module: WAO : SgmlParser.
* Rev: 29 mai 2000 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include <akra/portableDefs.h>
#include "dtdDefinition.h"

class HdmlElement;
class HdmlElementDef;


class HdmlDTD : public DtdDefinition {
  public:
    enum HdmlTags {
      tAction
      , tB, tBr
      , tCe, tCenter, tChoice
      , tDeck, tDisplay
      , tEntry
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


/*
      , tSoft1, tSoft2, tSoft3, tSoft4, tSoft5, tSoft6, tSoft7, tSoft8
      , tAccept, tPrev, tHelp
*/

    enum HdmlEntity {
	text, font, phrase, special, form, headContent, headMisc, list, heading,
	block, preformatted, bodyContent, flow, addressContent, preExclusion
    };

  protected:
    static char *tagNames[numOfElements];
    static HdmlElementDef *elementDef[numOfElements];

  public:
    static HdmlTags identifyTag(char *aName);
    static HdmlElementDef * getElementDef(HdmlTags aTag);
    static boolean isFromEntity(HdmlTags aTag, HdmlEntity anEntity);

  public:
    HdmlDTD(void);

    virtual SgmlDoc *createConformentDoc(char *aName);
    virtual HdmlElement *instanciateType(HdmlTags aType);
    virtual boolean useVersion(char *versName);
    void loadDefinitions(void);
    virtual boolean checkCategory(HdmlTags aTag, EntityCategory aCategory);
};


#endif		/* _HDMLDTD_DEF_H_ */

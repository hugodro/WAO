#ifndef _WMLDTD_DEF_H_
#define _WMLDTD_DEF_H_
/**************************************************
* File: wmlDTD.h.
* Desc: Definition of an optimized DtdDef for WML 1.1.
* Module: WAO : SgmlParser.
* Rev: 19 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include <akra/portableDefs.h>
#include "dtdDefinition.h"

class WmlElement;
class WmlElementDef;


class WmlDTD : public DtdDefinition {
  public:
    enum WmlTags {
	tA, tAccess, tAnchor,
	tB, tBig, tBr,
	tCard,
	tDo,
	tEm,
	tFieldset,
	tGo,
	tHead,
	tI, tImg, tInput,
	tMeta,
	tNoop,
	tOnevent, tOptgroup, tOption,
	tP, tPostfield, tPrev,
	tRefresh,
	tSelect, tSetvar, tSmall, tStrong,
	tTable, tTd, tTemplate, tTimer, tTr,
	tU,
	tWml,
	tPcdata, tCdata
	, numOfElements
	, unknownTag, emptyTag, tComment
    };

    enum EntityCategory {
	eHead, eBody
    };

    enum WmlEntity {
	text, font, phrase, special, form, headContent, headMisc, list, heading,
	block, preformatted, bodyContent, flow, addressContent, preExclusion
    };

  protected:
    static char *tagNames[numOfElements];
    static WmlElementDef *elementDef[numOfElements];

  public:
    static WmlTags identifyTag(char *aName);
    static WmlElementDef * getElementDef(WmlTags aTag);
    static boolean isFromEntity(WmlTags aTag, WmlEntity anEntity);

  public:
    WmlDTD(void);

    virtual SgmlDoc *createConformentDoc(char *aName);
    virtual WmlElement *instanciateType(WmlTags aType);
    virtual boolean useVersion(char *versName);
    void loadDefinitions(void);
    virtual boolean checkCategory(WmlTags aTag, EntityCategory aCategory);
};


#endif		/* _WMLDTD_DEF_H_ */

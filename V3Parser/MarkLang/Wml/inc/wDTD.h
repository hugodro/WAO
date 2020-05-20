#ifndef _WMLDTD_DEF_H_
#define _WMLDTD_DEF_H_
/**************************************************
* File: wmlDTD.h.
* Desc: Definition of an optimized DtdDef for WML 1.1.
* Module: WAO : SgmlParser.
* Rev: 19 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <coreml/dtdDefinition.h>

class xtnWmlElement;
class xtnWmlElementDef;


class xtnWmlDTD : public xtnCoreDtdDefinition {
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
    static xtnWmlElementDef *elementDef[numOfElements];

  public:
    static WmlTags identifyTag(char *aName);
    static xtnWmlElementDef * getElementDef(WmlTags aTag);
    static bool isFromEntity(WmlTags aTag, WmlEntity anEntity);

  public:
    xtnWmlDTD();
    virtual ~xtnWmlDTD();

    void loadDefinitions();

    virtual xtnCoreDoc *createConformentDoc(char *aName);
    virtual xtnWmlElement *instanciateType(WmlTags aType);
    virtual bool useVersion(char *versName);
    virtual bool checkCategory(WmlTags aTag, EntityCategory aCategory);
};


#endif		/* _WMLDTD_DEF_H_ */

#ifndef _HTMLDTD_DEF_H_
#define _HTMLDTD_DEF_H_
/**************************************************
* File: htmlDTD.h.
* Desc: Definition of an optimized DtdDef for HTML.
* Module: WAO : SgmlParser.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include <akra/portableDefs.h>
#include "dtdDefinition.h"

class HtmlElement;
class HtmlElementDef;


class HtmlDTD : public DtdDefinition {
  public:
    enum HtmlTags {
	tA= 0, tAddress, tApplet, tArea,
	tBase, tBasefont, tBlockquote, tBody, tBr, tB, tBig,
	tCaption, tCenter, tCite, tCode,
	tDfn, tDir, tDiv, tDl, tDd, tDt,
	tEm,
	tFont, tForm,
	tH1, tH2, tH3, tH4, tH5, tH6, tHead, tHr, tHtml,
	tI, tIm, tImg, tInput, tIsindex,
	tKbd,
	tLabel, tLink, tLi, tListing,
	tMap, tMenu, tMeta,
    tNoscript,
	tOption, tOl,
	tP, tParam, tPlaintext, tPre,
	tS, tSamp, tScript, tSelect, tSmall, tSpacer, tSpan, tStrike, tStrong, tStyle, tSub, tSup,
	tTable, tTd, tTextarea, tTh, tTitle, tTr, tTt,
	tU, tUl,
	tVar,
	tXmp,
	tPcdata, tCdata
	, numOfElements
	, unknownTag, emptyTag, tComment
    };
    enum EntityCategory {
	eHead, eBody
    };
    enum HtmlEntity {
	text, font, phrase, special, form, headContent, headMisc, list, heading,
	block, preformatted, bodyContent, flow, addressContent, preExclusion
    };

  protected:
    static char *tagNames[numOfElements];
    static HtmlElementDef *elementDef[numOfElements];

  public:
    static HtmlTags identifyTag(char *aName);
    static HtmlElementDef * getElementDef(HtmlTags aTag);
    static bool isFromEntity(HtmlTags aTag, HtmlEntity anEntity);

  public:
    HtmlDTD(void);

    virtual SgmlDoc *createConformentDoc(char *aName);
    virtual HtmlElement *instanciateType(HtmlTags aType);
    virtual bool useVersion(char *versName);
    void loadDefinitions(void);
    virtual bool checkCategory(HtmlTags aTag, EntityCategory aCategory);

    inline const char *nameTag(HtmlTags aTag) {
		if (aTag == tPcdata) return "pc Data";
                            else if (aTag == tCdata) return "c Data";
                            else return ((aTag < numOfElements) ? tagNames[aTag] : "unknown");
    }
};


#endif		/* _HTMLDTD_DEF_H_ */

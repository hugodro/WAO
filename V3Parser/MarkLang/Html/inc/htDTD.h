#ifndef _HTMLDTD_DEF_H_
#define _HTMLDTD_DEF_H_
/**************************************************
* File: htDTD.h.
* Desc: Definition of an optimized DtdDef for HTML.
* $Date$
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/11/30 : REV 1 : Hugo DesRosiers : Brought to Extenta context.
* $Log$
**************************************************/

#include <coreml/dtdDefinition.h>

class xtnHtmlElement;
class xtnHtmlElementDef;


class xtnHtmlDTD : public xtnCoreDtdDefinition {
 public:
  enum HtmlTags {
	tA= 0, tAddress, tApplet, tArea
	, tBase, tBasefont, tBlockquote, tBody, tBr, tB, tBig
	, tCaption, tCenter, tCite, tCode
	, tDfn, tDir, tDiv, tDl, tDd, tDt
	, tEm
	, tFont, tForm
	, tH1, tH2, tH3, tH4, tH5, tH6, tHead, tHr, tHtml
	, tI, tImg, tInput, tIsindex
	, tKbd
	, tLink, tLi, tListing
	, tMap, tMenu, tMeta
	, tOption, tOl
	, tP, tParam, tPlaintext, tPre
	, tS, tSamp, tScript, tSelect, tSmall, tSpan
	, tStrike, tStrong, tStyle, tSub, tSup
	, tTable, tTd, tTextarea, tTh, tTitle, tTr, tTt
	, tU, tUl
	, tVar
	, tXmp, tNoScript
	, tObject, tEmbed
	, tPcdata, tCdata, tComment
	, numOfElements
	, unknownTag, emptyTag
  };
  enum EntityCategory {
    eHead, eBody
  };
  enum HtmlEntity {
    text, font, phrase, special, form, headContent, headMisc, list, heading,
    block, preformatted, bodyContent, flow, addressContent, preExclusion
  };

  public:
    static inline const char *nameTag(HtmlTags aTag) {
		if (aTag == tPcdata) return "pc Data";
                            else if (aTag == tCdata) return "c Data";
                            else return ((aTag < numOfElements) ? tagNames[aTag] : "unknown");
    }

  protected:
    static char *tagNames[numOfElements];
    static xtnHtmlElementDef *elementDef[numOfElements];

  public:
    static HtmlTags identifyTag(char *aName);
    static xtnHtmlElementDef *getElementDef(HtmlTags aTag);
    static bool isFromEntity(HtmlTags aTag, HtmlEntity anEntity);

  public:
    xtnHtmlDTD(void);

    virtual xtnCoreDoc *createConformentDoc(char *aName);
    virtual xtnHtmlElement *instanciateType(HtmlTags aType);
    virtual bool useVersion(char *versName);
    void loadDefinitions(void);
    virtual bool checkCategory(HtmlTags aTag, EntityCategory aCategory);
    virtual bool hitBoundaryForEnding(xtnHtmlElement *aBoundary, HtmlTags aTag);
};


#endif		/* _HTMLDTD_DEF_H_ */

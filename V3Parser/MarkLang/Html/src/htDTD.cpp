/**************************************************
* File: htDTD.cc.
* Desc: Implementation of an optimized DtdDef for HTML.
* $Date$
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/11/30 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log$
**************************************************/

#if defined(_WIN32)
#include <string>
#else
#include <string.h>
#endif

#include <coreml/sgElementDef.h>
#include "htElements.h"
#include "htDoc.h"
#include "htElementDef.h"
#include "htDTD.h"

char *xtnHtmlDTD::tagNames[xtnHtmlDTD::numOfElements]= {
    "A", "ADDRESS", "APPLET", "AREA",
    "BASE", "BASEFONT", "BLOCKQUOTE", "BODY", "BR", "B", "BIG",
    "CAPTION", "CENTER", "CITE", "CODE",
    "DFN", "DIR", "DIV", "DL", "DD", "DT",
    "EM",
    "FONT", "FORM",
    "H1", "H2", "H3", "H4", "H5", "H6", "HEAD", "HR", "HTML",
    "I", "IMG", "INPUT", "ISINDEX",
    "KBD",
    "LINK", "LI", "LISTING",
    "MAP", "MENU", "META",
    "OPTION", "OL",
    "P", "PARAM", "PLAINTEXT", "PRE",
    "S", "SAMP", "SCRIPT", "SELECT", "SMALL", "SPAN", "STRIKE", "STRONG", "STYLE", "SUB", "SUP",
    "TABLE", "TD", "TEXTAREA", "TH", "TITLE", "TR", "TT",
    "U", "UL",
    "VAR"
    , "XMP", "NOSCRIPT"
    , "OBJECT", "EMBED"
    , NULL, NULL, NULL		// tPcData, tCdata and tComment have no tag names.
};


xtnHtmlElementDef *xtnHtmlDTD::elementDef[xtnHtmlDTD::numOfElements] = { NULL };


xtnHtmlDTD::HtmlTags xtnHtmlDTD::identifyTag(char *aName)
{
    unsigned int i;

    if (aName != NULL) {
	for (i= 0; i < numOfElements - 3; i++) {	// The last three elements (tPcData, tCdata, tComment) have no names.
	    if (strcmp(tagNames[i], aName) == 0) {
		return (HtmlTags)i;
	    }
	}
    }
    return unknownTag;
}


xtnHtmlElementDef *xtnHtmlDTD::getElementDef(xtnHtmlDTD::HtmlTags aTag)
{
    return elementDef[aTag];
}


xtnHtmlDTD::xtnHtmlDTD(void)
{
    loadDefinitions();
}


xtnCoreDoc *xtnHtmlDTD::createConformentDoc(char *aName)
{
    return new xtnHtmlDoc(aName, this);
}


xtnHtmlElement *xtnHtmlDTD::instanciateType(HtmlTags aType)
{
    switch(aType) {
	case tA:
	    return new xtnHAnchor();
	    break;
	case tAddress:
	    return new xtnHAddress();
	    break;
	case tApplet:
	    return new xtnHApplet();
	    break;
	case tArea:
	    return new xtnHArea();
	    break;
	case tBase:
	    return new xtnHBase();
	    break;
	case tBasefont:
	    return new xtnHBaseFont();
	    break;
	case tBlockquote:
	    return new xtnHBlockQuote();
	    break;
	case tBody:
	    return new xtnHBody();
	    break;
	case tBr:
	    return new xtnHBreak();
	    break;
	case tB:
	    return new xtnHBold();
	    break;
	case tBig:
	    return new xtnHBig();
	    break;
	case tCaption:
	    return new xtnHCaption();
	    break;
	case tCenter:
	    return new xtnHCenter();
	    break;
	case tCite:
	    return new xtnHCite();
	    break;
	case tCode:
	    return new xtnHCode();
	    break;
	case tDfn:
	    return new xtnHDfn();
	    break;
	case tDir:
	    return new xtnHDir();
	    break;
	case tDiv:
	    return new xtnHDiv();
	    break;
	case tDl:
	    return new xtnHDefList();
	    break;
	case tDd:
	    return new xtnHDefDef();
	    break;
	case tDt:
	    return new xtnHDefTerm();
	    break;
	case tEm:
	    return new xtnHEm();
	    break;
	case tFont:
	    return new xtnHFont();
	    break;
	case tForm:
	    return new xtnHForm();
	    break;
	case tH1:
	    return new xtnHHeading(1);
	    break;
	case tH2:
	    return new xtnHHeading(2);
	    break;
	case tH3:
	    return new xtnHHeading(3);
	    break;
	case tH4:
	    return new xtnHHeading(4);
	    break;
	case tH5:
	    return new xtnHHeading(5);
	    break;
	case tH6:
	    return new xtnHHeading(6);
	    break;
	case tHead:
	    return new xtnHHead();
	    break;
	case tHr:
	    return new xtnHHr();
	    break;
	case tHtml:
	    return new xtnHHtml();
	    break;
	case tI:
	    return new xtnHItalic();
	    break;
	case tImg:
	    return new xtnHImg();
	    break;
	case tInput:
	    return new xtnHInput();
	    break;
	case tIsindex:
	    return new xtnHIsIndex();
	    break;
	case tKbd:
	    return new xtnHKbd();
	    break;
	case tLink:
	    return new xtnHLink();
	    break;
	case tLi:
	    return new xtnHLiElement();
	    break;
	case tListing:
	    return new xtnHListing();
	    break;
	case tMap:
	    return new xtnHMap();
	    break;
	case tMenu:
	    return new xtnHMenu();
	    break;
	case tMeta:
	    return new xtnHMeta();
	    break;
	case tOption:
	    return new xtnHOption();
	    break;
	case tOl:
	    return new xtnHOList();
	    break;
	case tP:
	    return new xtnHPara();
	    break;
	case tParam:
	    return new xtnHParam();
	    break;
	case tPlaintext:
	    return new xtnHPlainText();
	    break;
	case tPre:
	    return new xtnHPre();
	    break;
	case tS:
	    return new xtnHStrike();
	    break;
	case tSamp:
	    return new xtnHSamp();
	    break;
	case tScript:
	    return new xtnHScript();
	    break;
	case tSelect:
	    return new xtnHSelect();
	    break;
	case tSmall:
	    return new xtnHSmall();
	    break;
	case tSpan:
	    return new xtnHSpan();
	    break;
	case tStrike:
	    return new xtnHStrike();
	    break;
	case tStrong:
	    return new xtnHStrong();
	    break;
	case tStyle:
	    return new xtnHStyle();
	    break;
	case tSub:
	    return new xtnHSub();
	    break;
	case tSup:
	    return new xtnHSup();
	    break;
	case tTable:
	    return new xtnHTable();
	    break;
	case tTd:
	    return new xtnHTableData();
	    break;
	case tTextarea:
	    return new xtnHTextArea();
	    break;
	case tTh:
	    return new xtnHTableHeader();
	    break;
	case tTitle:
	    return new xtnHTitle();
	    break;
	case tTr:
	    return new xtnHTableRow();
	    break;
	case tTt:
	    return new xtnHTeleType();
	    break;
	case tU:
	    return new xtnHUnderscore();
	    break;
	case tUl:
	    return new xtnHUList();
	    break;
	case tVar:
	    return new xtnHVar();
	    break;
	case tXmp :
	    return new xtnHXmp();
	    break;
	case tNoScript :
	    return new xtnHNoScript();
	    break;
	case tObject :
	    return new xtnHObject();
	    break;
	case tEmbed :
	    return new xtnHEmbed();
	    break;
	case tPcdata :
	    return new xtnHPcData();
	    break;
    }
    return NULL;
}


bool xtnHtmlDTD::useVersion(char *versName)
{
// ATTN: Pick up the correct version.
// By default, the version will be "-//W3C//DTD HTML 3.2//EN".
    return true;
}


void xtnHtmlDTD::loadDefinitions(void)
{
    xtnSgmlAttrDef **coreAttributes;
    xtnCoreAttrDef *tmpAttr[15];
    unsigned int nbrCoreAttrs= 0, i, tmpCount;

    name= new char[25];
    strcpy(name, "-//W3C//DTD HTML 3.2//EN");

    coreAttributes= new xtnSgmlAttrDef*[2];
    coreAttributes[nbrCoreAttrs++]= new xtnSgmlAttrDef("id", xtnSgmlAttrDef::id, xtnSgmlAttrDef::optional);
    coreAttributes[nbrCoreAttrs++]= new xtnSgmlAttrDef("class", xtnSgmlAttrDef::id, xtnSgmlAttrDef::optional);

    for (i= 0; i < nbrCoreAttrs; i++)
      addAttribute(coreAttributes[i]);

    elementDef[tHtml]= new xtnHtmlElementDef(tagNames[tHtml],
			xtnSgmlElementDef::optional, xtnSgmlElementDef::optional);
    for (i= 0; i < nbrCoreAttrs; i++)
      elementDef[tHtml]->addAttribute(coreAttributes[i]);

	// Html elements.
    elementDef[tHead]= new xtnHtmlElementDef(tagNames[tHead],
			xtnSgmlElementDef::optional, xtnSgmlElementDef::optional);
    elementDef[tBody]= new xtnHtmlElementDef(tagNames[tBody],
			xtnSgmlElementDef::optional, xtnSgmlElementDef::optional);
    for (i= 0; i < nbrCoreAttrs; i++) {
      elementDef[tHtml]->addAttribute(coreAttributes[i]);
      elementDef[tBody]->addAttribute(coreAttributes[i]);
    }

	// Attributes for Body element.
    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("background", xtnSgmlAttrDef::url, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("bgcolor", xtnSgmlAttrDef::color, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("text", xtnSgmlAttrDef::color, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("link", xtnSgmlAttrDef::color, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("vlink", xtnSgmlAttrDef::color, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("alink", xtnSgmlAttrDef::color, xtnSgmlAttrDef::implied);
    // Non-3.2 conformant.
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("leftmargin", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("marginwidth", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("topmargin", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("marginheight", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("onload", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tBody]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }


	// Html.Head elements.
    elementDef[tStyle]= new xtnHtmlElementDef(tagNames[tStyle],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tScript]= new xtnHtmlElementDef(tagNames[tScript],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tNoScript]= new xtnHtmlElementDef(tagNames[tNoScript],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tTitle]= new xtnHtmlElementDef(tagNames[tTitle],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tIsindex]= new xtnHtmlElementDef(tagNames[tIsindex],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::illegal);
    elementDef[tBase]= new xtnHtmlElementDef(tagNames[tBase],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::illegal);
    elementDef[tMeta]= new xtnHtmlElementDef(tagNames[tMeta],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::illegal);
    elementDef[tLink]= new xtnHtmlElementDef(tagNames[tLink],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::illegal);
    elementDef[tObject]= new xtnHtmlElementDef(tagNames[tObject],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tEmbed]= new xtnHtmlElementDef(tagNames[tEmbed],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    for (i= 0; i < nbrCoreAttrs; i++) {
      elementDef[tStyle]->addAttribute(coreAttributes[i]);
      elementDef[tScript]->addAttribute(coreAttributes[i]);
      elementDef[tNoScript]->addAttribute(coreAttributes[i]);
      elementDef[tTitle]->addAttribute(coreAttributes[i]);
      elementDef[tIsindex]->addAttribute(coreAttributes[i]);
      elementDef[tBase]->addAttribute(coreAttributes[i]);
      elementDef[tMeta]->addAttribute(coreAttributes[i]);
      elementDef[tLink]->addAttribute(coreAttributes[i]);
      elementDef[tObject]->addAttribute(coreAttributes[i]);
      elementDef[tEmbed]->addAttribute(coreAttributes[i]);
    }


	// Attributes for head elements.
    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("type", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tStyle]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }


    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("prompt", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tIsindex]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }

	// ATTN: Non-3.2 conformant.
// MOD-980907 [HD]: Added 'target' attribute to parse 'Folio' documents (conformant 4.0).
    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("href", xtnSgmlAttrDef::url, xtnSgmlAttrDef::required);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("target", xtnSgmlAttrDef::url, xtnSgmlAttrDef::required);
    elementDef[tBase]->addAttribute(tmpAttr[i]);

    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("http-equiv", xtnSgmlAttrDef::dtName, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("name", xtnSgmlAttrDef::dtName, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("content", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::required);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tMeta]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }

    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("href", xtnSgmlAttrDef::url, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("rel", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("rev", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("title", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    // Non-3.2 conformant.
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("type", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tLink]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }

	// ATTN: Non-3.2 conformant (not conformant  4.0).
    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("language", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("src", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tScript]->addAttribute(tmpAttr[i]);
      elementDef[tNoScript]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }

	// Html.Body elements.
    elementDef[tH1]= new xtnHtmlElementDef(tagNames[tH1],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tH2]= new xtnHtmlElementDef(tagNames[tH2],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tH3]= new xtnHtmlElementDef(tagNames[tH3],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tH4]= new xtnHtmlElementDef(tagNames[tH4],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tH5]= new xtnHtmlElementDef(tagNames[tH5],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tH6]= new xtnHtmlElementDef(tagNames[tH6],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tAddress]= new xtnHtmlElementDef(tagNames[tAddress],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);

    for (i= 0; i < nbrCoreAttrs; i++) {
      elementDef[tH1]->addAttribute(coreAttributes[i]);
      elementDef[tH2]->addAttribute(coreAttributes[i]);
      elementDef[tH3]->addAttribute(coreAttributes[i]);
      elementDef[tH4]->addAttribute(coreAttributes[i]);
      elementDef[tH5]->addAttribute(coreAttributes[i]);
      elementDef[tH6]->addAttribute(coreAttributes[i]);
      elementDef[tAddress]->addAttribute(coreAttributes[i]);
    }

	// Attributes for Heading element.

    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("language", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tH1]->addAttribute(tmpAttr[i]);
      elementDef[tH2]->addAttribute(tmpAttr[i]);
      elementDef[tH3]->addAttribute(tmpAttr[i]);
      elementDef[tH4]->addAttribute(tmpAttr[i]);
      elementDef[tH5]->addAttribute(tmpAttr[i]);
      elementDef[tH6]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }


	// Html.Body.Block elements.
    elementDef[tP]= new xtnHtmlElementDef(tagNames[tP],
			xtnSgmlAttrDef::mandatory, xtnSgmlElementDef::optional);
    elementDef[tUl]= new xtnHtmlElementDef(tagNames[tUl],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tOl]= new xtnHtmlElementDef(tagNames[tOl],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);

    elementDef[tLi]= new xtnHtmlElementDef(tagNames[tLi],
			xtnSgmlAttrDef::mandatory, xtnSgmlElementDef::optional);
    elementDef[tDl]= new xtnHtmlElementDef(tagNames[tDl],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tDt]= new xtnHtmlElementDef(tagNames[tDt],
			xtnSgmlAttrDef::mandatory, xtnSgmlElementDef::optional);
    elementDef[tDd]= new xtnHtmlElementDef(tagNames[tDd],
			xtnSgmlAttrDef::mandatory, xtnSgmlElementDef::optional);
    elementDef[tDir]= new xtnHtmlElementDef(tagNames[tDir],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tMenu]= new xtnHtmlElementDef(tagNames[tMenu],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tPre]= new xtnHtmlElementDef(tagNames[tPre],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tXmp]= new xtnHtmlElementDef(tagNames[tXmp],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tListing]= new xtnHtmlElementDef(tagNames[tListing],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tPlaintext]= new xtnHtmlElementDef(tagNames[tPlaintext],
			xtnSgmlAttrDef::mandatory, xtnSgmlElementDef::optional);
    elementDef[tDiv]= new xtnHtmlElementDef(tagNames[tDiv],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tCenter]= new xtnHtmlElementDef(tagNames[tCenter],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tBlockquote]= new xtnHtmlElementDef(tagNames[tBlockquote],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tForm]= new xtnHtmlElementDef(tagNames[tForm],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tHr]= new xtnHtmlElementDef(tagNames[tHr],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::illegal);
    elementDef[tTable]= new xtnHtmlElementDef(tagNames[tTable],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tTr]= new xtnHtmlElementDef(tagNames[tTr],
			xtnSgmlAttrDef::mandatory, xtnSgmlElementDef::optional);
    elementDef[tTh]= new xtnHtmlElementDef(tagNames[tTh],
			xtnSgmlAttrDef::mandatory, xtnSgmlElementDef::optional);
    elementDef[tTd]= new xtnHtmlElementDef(tagNames[tTd],
			xtnSgmlAttrDef::mandatory, xtnSgmlElementDef::optional);
    elementDef[tCaption]= new xtnHtmlElementDef(tagNames[tCaption],
			xtnSgmlAttrDef::mandatory, xtnSgmlElementDef::optional);
    for (i= 0; i < nbrCoreAttrs; i++) {
      elementDef[tP]->addAttribute(coreAttributes[i]);
      elementDef[tUl]->addAttribute(coreAttributes[i]);
      elementDef[tOl]->addAttribute(coreAttributes[i]);
      elementDef[tLi]->addAttribute(coreAttributes[i]);
      elementDef[tDl]->addAttribute(coreAttributes[i]);
      elementDef[tDt]->addAttribute(coreAttributes[i]);
      elementDef[tDd]->addAttribute(coreAttributes[i]);
      elementDef[tDir]->addAttribute(coreAttributes[i]);
      elementDef[tMenu]->addAttribute(coreAttributes[i]);
      elementDef[tPre]->addAttribute(coreAttributes[i]);
      elementDef[tXmp]->addAttribute(coreAttributes[i]);
      elementDef[tListing]->addAttribute(coreAttributes[i]);
      elementDef[tPlaintext]->addAttribute(coreAttributes[i]);
      elementDef[tDiv]->addAttribute(coreAttributes[i]);
      elementDef[tCenter]->addAttribute(coreAttributes[i]);
      elementDef[tBlockquote]->addAttribute(coreAttributes[i]);
      elementDef[tForm]->addAttribute(coreAttributes[i]);
      elementDef[tHr]->addAttribute(coreAttributes[i]);
      elementDef[tTable]->addAttribute(coreAttributes[i]);
      elementDef[tTr]->addAttribute(coreAttributes[i]);
      elementDef[tTh]->addAttribute(coreAttributes[i]);
      elementDef[tTd]->addAttribute(coreAttributes[i]);
      elementDef[tCaption]->addAttribute(coreAttributes[i]);
	}

    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("align", xtnSgmlAttrDef::oneOf, xtnSgmlAttrDef::implied);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tP]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }

    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("type", xtnSgmlAttrDef::oneOf, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("compact", xtnSgmlAttrDef::flag, xtnSgmlAttrDef::implied);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tUl]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }

    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("type", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("start", xtnSgmlAttrDef::number, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("compact", xtnSgmlAttrDef::flag, xtnSgmlAttrDef::implied);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tOl]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }

    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("type", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("value", xtnSgmlAttrDef::number, xtnSgmlAttrDef::implied);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tLi]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }

    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("compact", xtnSgmlAttrDef::flag, xtnSgmlAttrDef::implied);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tDl]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }

    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("compact", xtnSgmlAttrDef::flag, xtnSgmlAttrDef::implied);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tDir]->addAttribute(tmpAttr[i]);
      elementDef[tMenu]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }

    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("width", xtnSgmlAttrDef::number, xtnSgmlAttrDef::implied);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tPre]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }

    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("align", xtnSgmlAttrDef::oneOf, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("style", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tDiv]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }

    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("action", xtnSgmlAttrDef::url, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("method", xtnSgmlAttrDef::oneOf, xtnSgmlAttrDef::implied);    // Def: get.
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("enctype", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);    // Def: "application/x-www-form-urlencoded".
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("name", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tForm]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }

    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("align", xtnSgmlAttrDef::oneOf, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("noshade", xtnSgmlAttrDef::flag, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("size", xtnSgmlAttrDef::number, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("width", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tHr]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }

    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("align", xtnSgmlAttrDef::oneOf, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("width", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("border", xtnSgmlAttrDef::number, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("cellspacing", xtnSgmlAttrDef::number, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("cellpadding", xtnSgmlAttrDef::number, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("bgcolor", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    // Non-3.2 conformatn.
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("height", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tTable]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }

    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("align", xtnSgmlAttrDef::oneOf, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("valign", xtnSgmlAttrDef::oneOf, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("bgcolor", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    // Non-3.2 conformatn.
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("height", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tTr]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }

    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("nowrap", xtnSgmlAttrDef::flag, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("rowspan", xtnSgmlAttrDef::number, xtnSgmlAttrDef::implied);    // Def: 1.
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("colspan", xtnSgmlAttrDef::number, xtnSgmlAttrDef::implied);    // Def: 1.
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("align", xtnSgmlAttrDef::oneOf, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("valign", xtnSgmlAttrDef::oneOf, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("width", xtnSgmlAttrDef::number, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("height", xtnSgmlAttrDef::number, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("bgcolor", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tTh]->addAttribute(tmpAttr[i]);
      elementDef[tTd]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }

    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("align", xtnSgmlAttrDef::oneOf, xtnSgmlAttrDef::implied);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tCaption]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }


	// Html.Body.Text elements.
	// Html.Body.Text.Font elements.
    elementDef[tTt]= new xtnHtmlElementDef(tagNames[tTt],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tI]= new xtnHtmlElementDef(tagNames[tI],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tB]= new xtnHtmlElementDef(tagNames[tB],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tU]= new xtnHtmlElementDef(tagNames[tU],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tStrike]= new xtnHtmlElementDef(tagNames[tStrike],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tBig]= new xtnHtmlElementDef(tagNames[tBig],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tSmall]= new xtnHtmlElementDef(tagNames[tSmall],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tSub]= new xtnHtmlElementDef(tagNames[tSub],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tSup]= new xtnHtmlElementDef(tagNames[tSup],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    for (i= 0; i < nbrCoreAttrs; i++) {
      elementDef[tTt]->addAttribute(coreAttributes[i]);
      elementDef[tI]->addAttribute(coreAttributes[i]);
      elementDef[tB]->addAttribute(coreAttributes[i]);
      elementDef[tU]->addAttribute(coreAttributes[i]);
      elementDef[tStrike]->addAttribute(coreAttributes[i]);
      elementDef[tBig]->addAttribute(coreAttributes[i]);
      elementDef[tSmall]->addAttribute(coreAttributes[i]);
      elementDef[tSub]->addAttribute(coreAttributes[i]);
      elementDef[tSup]->addAttribute(coreAttributes[i]);
    }

	// Html.Body.Text.Phrase elements.
    elementDef[tEm]= new xtnHtmlElementDef(tagNames[tEm],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tStrong]= new xtnHtmlElementDef(tagNames[tStrong],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tDfn]= new xtnHtmlElementDef(tagNames[tDfn],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tCode]= new xtnHtmlElementDef(tagNames[tCode],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tSamp]= new xtnHtmlElementDef(tagNames[tSamp],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tKbd]= new xtnHtmlElementDef(tagNames[tKbd],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tVar]= new xtnHtmlElementDef(tagNames[tVar],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tCite]= new xtnHtmlElementDef(tagNames[tCite],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    for (i= 0; i < nbrCoreAttrs; i++) {
      elementDef[tEm]->addAttribute(coreAttributes[i]);
      elementDef[tStrong]->addAttribute(coreAttributes[i]);
      elementDef[tDfn]->addAttribute(coreAttributes[i]);
      elementDef[tCode]->addAttribute(coreAttributes[i]);
      elementDef[tSamp]->addAttribute(coreAttributes[i]);
      elementDef[tKbd]->addAttribute(coreAttributes[i]);
      elementDef[tVar]->addAttribute(coreAttributes[i]);
      elementDef[tCite]->addAttribute(coreAttributes[i]);
    }


	// Html.Body.Text.Anchor elements.
#if defined(ACCEPT_FOLIO)
/* MOD-980908 [HD]: Modified to accomodate Folio documents (no closing </A>). */
    elementDef[tA]= new xtnHtmlElementDef(tagNames[tA],
			xtnSgmlAttrDef::mandatory, xtnSgmlElementDef::optional);
#else
    elementDef[tA]= new xtnHtmlElementDef(tagNames[tA],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
#endif
    for (i= 0; i < nbrCoreAttrs; i++) {
      elementDef[tA]->addAttribute(coreAttributes[i]);
    }

    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("name", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("href", xtnSgmlAttrDef::url, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("rel", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("rev", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("title", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
	// ATTN: Non HTML 3.2 conformant (conformant 4.0).
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("target", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("onmouseover", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("onmouseout", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("onclick", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tA]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }

	// Html.Body.Text.Img element.
    elementDef[tImg]= new xtnHtmlElementDef(tagNames[tImg],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::illegal);
    for (i= 0; i < nbrCoreAttrs; i++) {
      elementDef[tImg]->addAttribute(coreAttributes[i]);
    }

    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("src", xtnSgmlAttrDef::url, xtnSgmlAttrDef::required);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("alt", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("align", xtnSgmlAttrDef::oneOf, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("height", xtnSgmlAttrDef::number, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("width", xtnSgmlAttrDef::number, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("border", xtnSgmlAttrDef::number, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("hspace", xtnSgmlAttrDef::number, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("vspace", xtnSgmlAttrDef::number, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("usemap", xtnSgmlAttrDef::url, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("ismap", xtnSgmlAttrDef::flag, xtnSgmlAttrDef::implied);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tImg]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }

	// Html.Body.Text.Applet elements.
    elementDef[tApplet]= new xtnHtmlElementDef(tagNames[tApplet],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    for (i= 0; i < nbrCoreAttrs; i++) {
      elementDef[tApplet]->addAttribute(coreAttributes[i]);
    }

    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("codebase", xtnSgmlAttrDef::url, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("code", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::required);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("alt", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("name", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("width", xtnSgmlAttrDef::number, xtnSgmlAttrDef::required);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("height", xtnSgmlAttrDef::number, xtnSgmlAttrDef::required);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("align", xtnSgmlAttrDef::oneOf, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("hspace", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("vspace", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tApplet]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }

    elementDef[tParam]= new xtnHtmlElementDef(tagNames[tParam],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::illegal);
    elementDef[tFont]= new xtnHtmlElementDef(tagNames[tFont],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tBasefont]= new xtnHtmlElementDef(tagNames[tBasefont],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::illegal);
    elementDef[tBr]= new xtnHtmlElementDef(tagNames[tBr],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::illegal);
    elementDef[tMap]= new xtnHtmlElementDef(tagNames[tMap],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tArea]= new xtnHtmlElementDef(tagNames[tArea],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::illegal);
    for (i= 0; i < nbrCoreAttrs; i++) {
      elementDef[tParam]->addAttribute(coreAttributes[i]);
      elementDef[tFont]->addAttribute(coreAttributes[i]);
      elementDef[tBasefont]->addAttribute(coreAttributes[i]);
      elementDef[tBr]->addAttribute(coreAttributes[i]);
      elementDef[tMap]->addAttribute(coreAttributes[i]);
      elementDef[tArea]->addAttribute(coreAttributes[i]);
    }

    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("name", xtnSgmlAttrDef::dtName, xtnSgmlAttrDef::required);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("value", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tParam]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }

    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("size", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("color", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
	// ATTN: Non HTML 3.2 conformant (non conformant 4.0).
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("face", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("onmouseover", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("onmouseout", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("bgcolor", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tFont]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }

    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("size", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tBasefont]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }

    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("clear", xtnSgmlAttrDef::oneOf, xtnSgmlAttrDef::required);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tBr]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }

    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("name", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::required);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tMap]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }

    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("shape", xtnSgmlAttrDef::oneOf, xtnSgmlAttrDef::implied);    // Def: rect.
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("coords", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("href", xtnSgmlAttrDef::url, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("nohref", xtnSgmlAttrDef::flag, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("alt", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::required);
    // Non-3.2 conformant.
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("target", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::required);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tArea]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }


	// Html.Body.Text.Form fields elements.
    elementDef[tInput]= new xtnHtmlElementDef(tagNames[tInput],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::illegal);
    elementDef[tSelect]= new xtnHtmlElementDef(tagNames[tSelect],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tOption]= new xtnHtmlElementDef(tagNames[tOption],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    elementDef[tTextarea]= new xtnHtmlElementDef(tagNames[tTextarea],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);
    for (i= 0; i < nbrCoreAttrs; i++) {
      elementDef[tInput]->addAttribute(coreAttributes[i]);
      elementDef[tSelect]->addAttribute(coreAttributes[i]);
      elementDef[tOption]->addAttribute(coreAttributes[i]);
      elementDef[tTextarea]->addAttribute(coreAttributes[i]);
    }

    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("type", xtnSgmlAttrDef::oneOf, xtnSgmlAttrDef::implied);    // Def: TEXT.
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("name", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("value", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("checked", xtnSgmlAttrDef::flag, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("size", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::required);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("maxlength", xtnSgmlAttrDef::number, xtnSgmlAttrDef::required);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("src", xtnSgmlAttrDef::url, xtnSgmlAttrDef::required);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("align", xtnSgmlAttrDef::oneOf, xtnSgmlAttrDef::required);
    // Non-3.2 conformant.
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("for", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::required);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("style", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::required);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("title", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::required);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("onclick", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);

    for (i= 0; i < tmpCount; i++) {
      elementDef[tInput]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }

    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("name", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::required);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("size", xtnSgmlAttrDef::number, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("multiple", xtnSgmlAttrDef::flag, xtnSgmlAttrDef::implied);
	// ATTN: Non HTML 3.2 conformant.
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("onchange", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tSelect]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }

    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("selected", xtnSgmlAttrDef::flag, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("value", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tOption]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }

    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("name", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::required);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("rows", xtnSgmlAttrDef::number, xtnSgmlAttrDef::required);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("cols", xtnSgmlAttrDef::number, xtnSgmlAttrDef::required);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tTextarea]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }


    elementDef[tPcdata]= new xtnHtmlElementDef(tagNames[tPcdata],
			xtnSgmlAttrDef::illegal, xtnSgmlAttrDef::illegal);
    elementDef[tPcdata]->tag= tPcdata;
    elementDef[tComment]= new xtnHtmlElementDef(tagNames[tComment],
			xtnSgmlAttrDef::illegal, xtnSgmlAttrDef::illegal);
    elementDef[tComment]->tag= tComment;

	// Non HTML 3.2 elements.
    elementDef[tSpan]= new xtnHtmlElementDef(tagNames[tSpan],
			xtnSgmlAttrDef::mandatory, xtnSgmlAttrDef::mandatory);

    for (i= 0; i < nbrCoreAttrs; i++) {
      elementDef[tSpan]->addAttribute(coreAttributes[i]);
    }

    tmpCount= 0;
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("style", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    tmpAttr[tmpCount++]= new xtnSgmlAttrDef("dir", xtnSgmlAttrDef::cdata, xtnSgmlAttrDef::implied);
    for (i= 0; i < tmpCount; i++) {
      elementDef[tSpan]->addAttribute(tmpAttr[i]);
      addAttribute(tmpAttr[i]);
    }

}


bool xtnHtmlDTD::checkCategory(xtnHtmlDTD::HtmlTags aTag, xtnHtmlDTD::EntityCategory aCategory)
{
// ATTN-980323 [HD]: Very weak implementation.

    switch(aTag) {
	case tHtml:
	    return false;

	case tTitle:
	case tIsindex:
	case tBase:
	case tStyle:
	case tMeta:
	case tLink:
	    if (aCategory == eHead) return true;
	    else return false;

	case tScript:	// Fits in any categories ?
	case tNoScript:	// Fits in any categories ?
	case tObject:	// Fits in any categories ?
	    return true;

	default:
	    if (aCategory == eBody) return true;
	    return false;
    }
}


bool xtnHtmlDTD::isFromEntity(HtmlTags aTag, HtmlEntity anEntity)
{
    switch(anEntity) {
	case text:
	    if (aTag == tPcdata) return true;
	    return (isFromEntity(aTag, font) || isFromEntity(aTag, phrase)
	    	|| isFromEntity(aTag, special) || isFromEntity(aTag, form));
	    break;
	case font:
	    switch(aTag) {
		case tTt:
		case tI:
		case tB:
		case tU:
		case tStrike:
		case tBig:
		case tSmall:
		case tSub:
		case tSup:
		    return true;
		    break;
	    }
	    break;
	case phrase:
	    switch(aTag) {
		case tEm:
		case tStrong:
		case tDfn:
		case tCode:
		case tSamp:
		case tKbd:
		case tVar:
		case tCite:
		    return true;
		    break;
	    }
	    break;
	case special:
	    switch(aTag) {
		case tA:
		case tImg:
		case tApplet:
		case tFont:
		case tBasefont:
		case tBr:
		case tScript:
		case tNoScript:
		case tMap:
        case tSpan:
		    return true;
		    break;
	    }
	    break;
	case form:
	    switch(aTag) {
		case tInput:
		case tSelect:
		case tTextarea:
		    return true;
		    break;
	    }
	    break;
	case headContent:
	    switch(aTag) {
		case tTitle:
		case tIsindex:
		case tBase:
		    return true;
		    break;
	    }
	    break;
	case headMisc:
	    switch(aTag) {
		case tScript:
		case tNoScript:
		case tObject:
		case tEmbed:
		case tStyle:
		case tMeta:
		case tLink:
		    return true;
		    break;
	    }
	    break;
	case list:
	    switch(aTag) {
		case tUl: case tOl: case tDir: case tMenu:
		    return true;
		    break;
	    }
	    break;
	case heading:
	    switch(aTag) {
		case tH1: case tH2: case tH3: case tH4: case tH5: case tH6:
		    return true;
		    break;
	    }
	    break;
	case block:
	    switch(aTag) {
		case tP:
		case tDl:
		case tDiv:
		case tCenter:
		case tBlockquote:
		case tForm:
		case tIsindex:
		case tHr:
		case tTable:
		case tObject:
		case tScript:
		case tNoScript:
		    return true;
		    break;
	    }
	    if (isFromEntity(aTag, list) || isFromEntity(aTag, preformatted)) return true;
	    break;
	case preformatted:
	    if (aTag == tPre) return true;
	    break;
	case bodyContent:
	    if (aTag == tAddress) return true;
	    return (isFromEntity(aTag, heading) || isFromEntity(aTag, text)
	    	|| isFromEntity(aTag, block));
	    break;
	case flow:
	    return (isFromEntity(aTag, text) || isFromEntity(aTag, block));
	    break;
	case addressContent:
	    if (aTag == xtnHtmlDTD::tP) return true;
	    return (isFromEntity(aTag, xtnHtmlDTD::text));
	    break;
	case preExclusion:
	    switch(aTag) {
// MOD-990625 [HD]: Took out the IMG tag so that old directory lists could be parsed.
// WARNING: HTML3.2 defines IMG as excluded from PRE !
//		case tImg:

		case tBig:
		case tSmall:
		case tSub:
		case tSup:
		case tFont:
		    return true;
		    break;
	    }
	    break;
	default:
	    return false;
	    break;
    }
    return false;
}


bool xtnHtmlDTD::hitBoundaryForEnding(xtnHtmlElement *aBoundary, HtmlTags aTag)
{
  HtmlTags boundType;
  bool result= false;

  boundType= aBoundary->getTag();
  switch(aTag) {
    case tTr:
      result= (boundType == tTable);
      break;
  }
  return result;
}


/**************************************************
* File: htmlDTD.cc.
* Desc: Implementation of an optimized DtdDef for HTML.
* Module: WAO : SgmlParser.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <string.h>

#include "htElements.h"
#include "htmlDoc.h"
#include "htElementDef.h"
#include "htmlDTD.h"

char *HtmlDTD::tagNames[HtmlDTD::numOfElements]= {
    "A", "ADDRESS", "APPLET", "AREA",
    "BASE", "BASEFONT", "BLOCKQUOTE", "BODY", "BR", "B", "BIG",
    "CAPTION", "CENTER", "CITE", "CODE",
    "DFN", "DIR", "DIV", "DL", "DD", "DT",
    "EM",
    "FONT", "FORM",
    "H1", "H2", "H3", "H4", "H5", "H6", "HEAD", "HR", "HTML",
    "I", "IM", "IMG", "INPUT", "ISINDEX",
    "KBD",
    "LABEL", "LINK", "LI", "LISTING",
    "MAP", "MENU", "META",
    "NOSCRIPT",
    "OPTION", "OL",
    "P", "PARAM", "PLAINTEXT", "PRE",
    "S", "SAMP", "SCRIPT", "SELECT", "SMALL", "SPACER", "SPAN", "STRIKE", "STRONG", "STYLE", "SUB", "SUP",
    "TABLE", "TD", "TEXTAREA", "TH", "TITLE", "TR", "TT",
    "U", "UL",
    "VAR",
    "XMP"
    , NULL, NULL		// tPcData and tCdata have no tag names.
};


HtmlElementDef *HtmlDTD::elementDef[HtmlDTD:: numOfElements] = { NULL };


HtmlDTD::HtmlTags HtmlDTD::identifyTag(char *aName)
{
    unsigned int i;

    if (aName != NULL) {
	for (i= 0; i < numOfElements - 2; i++) {	// The last two elements (tPcData, tCdata) have no names.
	    if (strcmp(tagNames[i], aName) == 0) {
		return (HtmlTags)i;
	    }
	}
    }
    return unknownTag;
}


HtmlElementDef * HtmlDTD::getElementDef(HtmlDTD::HtmlTags aTag)
{
    return elementDef[aTag];
}


HtmlDTD::HtmlDTD(void)
{
    loadDefinitions();
}


SgmlDoc *HtmlDTD::createConformentDoc(char *aName)
{
    return new HtmlDoc(aName, this);
}


HtmlElement *HtmlDTD::instanciateType(HtmlTags aType)
{
    switch(aType) {
	case tA:
	    return new HAnchor();
	    break;
	case tAddress:
	    return new HAddress();
	    break;
	case tApplet:
	    return new HApplet();
	    break;
	case tArea:
	    return new HArea();
	    break;
	case tBase:
	    return new HBase();
	    break;
	case tBasefont:
	    return new HBaseFont();
	    break;
	case tBlockquote:
	    return new HBlockQuote();
	    break;
	case tBody:
	    return new HBody();
	    break;
	case tBr:
	    return new HBreak();
	    break;
	case tB:
	    return new HBold();
	    break;
	case tBig:
	    return new HBig();
	    break;
	case tCaption:
	    return new HCaption();
	    break;
	case tCenter:
	    return new HCenter();
	    break;
	case tCite:
	    return new HCite();
	    break;
	case tCode:
	    return new HCode();
	    break;
	case tDfn:
	    return new HDfn();
	    break;
	case tDir:
	    return new HDir();
	    break;
	case tDiv:
	    return new HDiv();
	    break;
	case tDl:
	    return new HDefList();
	    break;
	case tDd:
	    return new HDefDef();
	    break;
	case tDt:
	    return new HDefTerm();
	    break;
	case tEm:
	    return new HEm();
	    break;
	case tFont:
	    return new HFont();
	    break;
	case tForm:
	    return new HForm();
	    break;
	case tH1:
	    return new HHeading(1);
	    break;
	case tH2:
	    return new HHeading(2);
	    break;
	case tH3:
	    return new HHeading(3);
	    break;
	case tH4:
	    return new HHeading(4);
	    break;
	case tH5:
	    return new HHeading(5);
	    break;
	case tH6:
	    return new HHeading(6);
	    break;
	case tHead:
	    return new HHead();
	    break;
	case tHr:
	    return new HHr();
	    break;
	case tHtml:
	    return new HHtml();
	    break;
	case tI:
	    return new HItalic();
	    break;
	case tImg:
	    return new HImg();
	    break;
	case tInput:
	    return new HInput();
	    break;
	case tIsindex:
	    return new HIsIndex();
	    break;
	case tKbd:
	    return new HKbd();
	    break;
	case tLink:
	    return new HLink();
	    break;
	case tLi:
	    return new HLiElement();
	    break;
	case tListing:
	    return new HListing();
	    break;
	case tMap:
	    return new HMap();
	    break;
	case tMenu:
	    return new HMenu();
	    break;
	case tMeta:
	    return new HMeta();
	    break;
	case tOption:
	    return new HOption();
	    break;
	case tOl:
	    return new HOList();
	    break;
	case tP:
	    return new HPara();
	    break;
	case tParam:
	    return new HParam();
	    break;
	case tPlaintext:
	    return new HPlainText();
	    break;
	case tPre:
	    return new HPre();
	    break;
	case tS:
	    return new HStrike();
	    break;
	case tSamp:
	    return new HSamp();
	    break;
	case tScript:
	    return new HScript();
	    break;
	case tSelect:
	    return new HSelect();
	    break;
	case tSmall:
	    return new HSmall();
	    break;
	case tSpan:
	    return new HSpan();
	    break;
	case tStrike:
	    return new HStrike();
	    break;
	case tStrong:
	    return new HStrong();
	    break;
	case tStyle:
	    return new HStyle();
	    break;
	case tSub:
	    return new HSub();
	    break;
	case tSup:
	    return new HSup();
	    break;
	case tTable:
	    return new HTable();
	    break;
	case tTd:
	    return new HTableData();
	    break;
	case tTextarea:
	    return new HTextArea();
	    break;
	case tTh:
	    return new HTableHeader();
	    break;
	case tTitle:
	    return new HTitle();
	    break;
	case tTr:
	    return new HTableRow();
	    break;
	case tTt:
	    return new HTeleType();
	    break;
	case tU:
	    return new HUnderscore();
	    break;
	case tUl:
	    return new HUList();
	    break;
	case tVar:
	    return new HVar();
	    break;
	case tXmp :
	    return new HXmp();
	    break;
	case tPcdata :
	    return new HPcData();
	    break;
    }
    return NULL;
}


bool HtmlDTD::useVersion(char *versName)
{
// ATTN: Pick up the correct version.
// By default, the version will be "-//W3C//DTD HTML 3.2//EN".
    return true;
}


void HtmlDTD::loadDefinitions(void)
{
    name= new char[25];
    strcpy(name, "-//W3C//DTD HTML 3.2//EN");

    elementDef[tHtml]= new HtmlElementDef(tagNames[tHtml],
			SgmlElementDef::optional, SgmlElementDef::optional);

	// Html elements.
    elementDef[tHead]= new HtmlElementDef(tagNames[tHead],
			SgmlElementDef::optional, SgmlElementDef::optional);
    elementDef[tBody]= new HtmlElementDef(tagNames[tBody],
			SgmlElementDef::optional, SgmlElementDef::optional);

	// Attributes for Body element.
    elementDef[tBody]->nbrAttributes= 6;
    elementDef[tBody]->attributes= new HtmlAttrDef[6];
    elementDef[tBody]->attributes[0].setDefinition("background", SgmlAttrDef::url, SgmlAttrDef::implied);
    elementDef[tBody]->attributes[1].setDefinition("bgcolor", SgmlAttrDef::color, SgmlAttrDef::implied);
    elementDef[tBody]->attributes[2].setDefinition("text", SgmlAttrDef::color, SgmlAttrDef::implied);
    elementDef[tBody]->attributes[3].setDefinition("link", SgmlAttrDef::color, SgmlAttrDef::implied);
    elementDef[tBody]->attributes[4].setDefinition("vlink", SgmlAttrDef::color, SgmlAttrDef::implied);
    elementDef[tBody]->attributes[5].setDefinition("alink", SgmlAttrDef::color, SgmlAttrDef::implied);

	// Html.Head elements.
    elementDef[tStyle]= new HtmlElementDef(tagNames[tStyle],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tScript]= new HtmlElementDef(tagNames[tScript],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tTitle]= new HtmlElementDef(tagNames[tTitle],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tIsindex]= new HtmlElementDef(tagNames[tIsindex],
			SgmlElementDef::mandatory, SgmlElementDef::illegal);
    elementDef[tBase]= new HtmlElementDef(tagNames[tBase],
			SgmlElementDef::mandatory, SgmlElementDef::illegal);
    elementDef[tMeta]= new HtmlElementDef(tagNames[tMeta],
			SgmlElementDef::mandatory, SgmlElementDef::illegal);
    elementDef[tLink]= new HtmlElementDef(tagNames[tLink],
			SgmlElementDef::mandatory, SgmlElementDef::illegal);

	// Attributes for head elements.
    elementDef[tIsindex]->nbrAttributes= 1;
    elementDef[tIsindex]->attributes= new HtmlAttrDef("prompt", SgmlAttrDef::cdata, SgmlAttrDef::implied);
	// ATTN: Non-3.2 conformant.
// MOD-980907 [HD]: Added 'target' attribute to parse 'Folio' documents (conformant 4.0).
    elementDef[tBase]->nbrAttributes= 2;
    elementDef[tBase]->attributes= new HtmlAttrDef[2];
    elementDef[tBase]->attributes[0].setDefinition("href", SgmlAttrDef::url, SgmlAttrDef::required);
    elementDef[tBase]->attributes[1].setDefinition("target", SgmlAttrDef::url, SgmlAttrDef::required);
    elementDef[tMeta]->nbrAttributes= 3;
    elementDef[tMeta]->attributes= new HtmlAttrDef[3];
    elementDef[tMeta]->attributes[0].setDefinition("http-equiv", SgmlAttrDef::dtName, SgmlAttrDef::implied);
    elementDef[tMeta]->attributes[1].setDefinition("name", SgmlAttrDef::dtName, SgmlAttrDef::implied);
    elementDef[tMeta]->attributes[2].setDefinition("content", SgmlAttrDef::cdata, SgmlAttrDef::required);
    elementDef[tLink]->nbrAttributes= 4;
    elementDef[tLink]->attributes= new HtmlAttrDef[4];
    elementDef[tLink]->attributes[0].setDefinition("href", SgmlAttrDef::url, SgmlAttrDef::implied);
    elementDef[tLink]->attributes[1].setDefinition("rel", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tLink]->attributes[2].setDefinition("rev", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tLink]->attributes[3].setDefinition("title", SgmlAttrDef::cdata, SgmlAttrDef::implied);
	// ATTN: Non-3.2 conformant (not conformant  4.0).
    elementDef[tScript]->nbrAttributes= 1;
    elementDef[tScript]->attributes= new HtmlAttrDef("language", SgmlAttrDef::cdata, SgmlAttrDef::implied);

	// Html.Body elements.
    elementDef[tH1]= new HtmlElementDef(tagNames[tH1],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tH2]= new HtmlElementDef(tagNames[tH2],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tH3]= new HtmlElementDef(tagNames[tH3],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tH4]= new HtmlElementDef(tagNames[tH4],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tH5]= new HtmlElementDef(tagNames[tH5],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tH6]= new HtmlElementDef(tagNames[tH6],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tAddress]= new HtmlElementDef(tagNames[tAddress],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);

	// Attributes for Heading element.
    elementDef[tH1]->nbrAttributes= 1;
    elementDef[tH2]->nbrAttributes= 1;
    elementDef[tH3]->nbrAttributes= 1;
    elementDef[tH4]->nbrAttributes= 1;
    elementDef[tH5]->nbrAttributes= 1;
    elementDef[tH6]->nbrAttributes= 1;
    elementDef[tH1]->attributes= new HtmlAttrDef("align", SgmlAttrDef::oneOf, SgmlAttrDef::implied);
    elementDef[tH2]->attributes= elementDef[tH1]->attributes;
    elementDef[tH3]->attributes= elementDef[tH1]->attributes;
    elementDef[tH4]->attributes= elementDef[tH1]->attributes;
    elementDef[tH5]->attributes= elementDef[tH1]->attributes;
    elementDef[tH6]->attributes= elementDef[tH1]->attributes;


	// Html.Body.Block elements.
    elementDef[tP]= new HtmlElementDef(tagNames[tP],
			SgmlElementDef::mandatory, SgmlElementDef::optional);
    elementDef[tP]->nbrAttributes= 1;
    elementDef[tP]->attributes= new HtmlAttrDef("align", SgmlAttrDef::oneOf, SgmlAttrDef::implied);

    elementDef[tUl]= new HtmlElementDef(tagNames[tUl],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tUl]->nbrAttributes= 2;
    elementDef[tUl]->attributes= new HtmlAttrDef[2];
    elementDef[tUl]->attributes[0].setDefinition("type", SgmlAttrDef::oneOf, SgmlAttrDef::implied);
    elementDef[tUl]->attributes[1].setDefinition("compact", SgmlAttrDef::flag, SgmlAttrDef::implied);

   elementDef[tOl]= new HtmlElementDef(tagNames[tOl],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tOl]->nbrAttributes= 3;
    elementDef[tOl]->attributes= new HtmlAttrDef[3];
    elementDef[tOl]->attributes[0].setDefinition("type", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tOl]->attributes[1].setDefinition("start", SgmlAttrDef::number, SgmlAttrDef::implied);
    elementDef[tOl]->attributes[2].setDefinition("compact", SgmlAttrDef::flag, SgmlAttrDef::implied);

   elementDef[tLi]= new HtmlElementDef(tagNames[tLi],
			SgmlElementDef::mandatory, SgmlElementDef::optional);
    elementDef[tLi]->nbrAttributes= 2;
    elementDef[tLi]->attributes= new HtmlAttrDef[2];
    elementDef[tLi]->attributes[0].setDefinition("type", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tLi]->attributes[1].setDefinition("value", SgmlAttrDef::number, SgmlAttrDef::implied);

    elementDef[tDl]= new HtmlElementDef(tagNames[tDl],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tDl]->nbrAttributes= 1;
    elementDef[tDl]->attributes= new HtmlAttrDef("compact", SgmlAttrDef::flag, SgmlAttrDef::implied);

    elementDef[tDt]= new HtmlElementDef(tagNames[tDt],
			SgmlElementDef::mandatory, SgmlElementDef::optional);
    elementDef[tDd]= new HtmlElementDef(tagNames[tDd],
			SgmlElementDef::mandatory, SgmlElementDef::optional);

    elementDef[tDir]= new HtmlElementDef(tagNames[tDir],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tMenu]= new HtmlElementDef(tagNames[tMenu],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tMenu]->nbrAttributes= elementDef[tDir]->nbrAttributes= 1;
    elementDef[tMenu]->attributes= elementDef[tDir]->attributes= new HtmlAttrDef("compact", SgmlAttrDef::flag, SgmlAttrDef::implied);

    elementDef[tPre]= new HtmlElementDef(tagNames[tPre],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tPre]->nbrAttributes= 1;
    elementDef[tPre]->attributes= new HtmlAttrDef("width", SgmlAttrDef::number, SgmlAttrDef::implied);

    elementDef[tXmp]= new HtmlElementDef(tagNames[tXmp],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tListing]= new HtmlElementDef(tagNames[tListing],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tPlaintext]= new HtmlElementDef(tagNames[tPlaintext],
			SgmlElementDef::mandatory, SgmlElementDef::optional);

    elementDef[tDiv]= new HtmlElementDef(tagNames[tDiv],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tCenter]= new HtmlElementDef(tagNames[tCenter],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tDiv]->nbrAttributes= 1;
    elementDef[tDiv]->attributes= new HtmlAttrDef("align", SgmlAttrDef::oneOf, SgmlAttrDef::implied);

    elementDef[tBlockquote]= new HtmlElementDef(tagNames[tBlockquote],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);

    elementDef[tForm]= new HtmlElementDef(tagNames[tForm],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tForm]->nbrAttributes= 3;
    elementDef[tForm]->attributes= new HtmlAttrDef[3];
    elementDef[tForm]->attributes[0].setDefinition("action", SgmlAttrDef::url, SgmlAttrDef::implied);
    elementDef[tForm]->attributes[1].setDefinition("method", SgmlAttrDef::oneOf, SgmlAttrDef::implied);    // Def: get.
    elementDef[tForm]->attributes[2].setDefinition("enctype", SgmlAttrDef::cdata, SgmlAttrDef::implied);    // Def: "application/x-www-form-urlencoded".

    elementDef[tHr]= new HtmlElementDef(tagNames[tHr],
			SgmlElementDef::mandatory, SgmlElementDef::illegal);
    elementDef[tHr]->nbrAttributes= 4;
    elementDef[tHr]->attributes= new HtmlAttrDef[4];
    elementDef[tHr]->attributes[0].setDefinition("align", SgmlAttrDef::oneOf, SgmlAttrDef::implied);
    elementDef[tHr]->attributes[1].setDefinition("noshade", SgmlAttrDef::flag, SgmlAttrDef::implied);
    elementDef[tHr]->attributes[2].setDefinition("size", SgmlAttrDef::number, SgmlAttrDef::implied);
    elementDef[tHr]->attributes[3].setDefinition("width", SgmlAttrDef::cdata, SgmlAttrDef::implied);

    elementDef[tTable]= new HtmlElementDef(tagNames[tTable],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tTr]= new HtmlElementDef(tagNames[tTr],
			SgmlElementDef::mandatory, SgmlElementDef::optional);
    elementDef[tTh]= new HtmlElementDef(tagNames[tTh],
			SgmlElementDef::mandatory, SgmlElementDef::optional);
    elementDef[tTd]= new HtmlElementDef(tagNames[tTd],
			SgmlElementDef::mandatory, SgmlElementDef::optional);
    elementDef[tCaption]= new HtmlElementDef(tagNames[tCaption],
			SgmlElementDef::mandatory, SgmlElementDef::optional);

    elementDef[tTable]->nbrAttributes= 6;
    elementDef[tTable]->attributes= new HtmlAttrDef[6];
    elementDef[tTable]->attributes[0].setDefinition("align", SgmlAttrDef::oneOf, SgmlAttrDef::implied);
    elementDef[tTable]->attributes[1].setDefinition("width", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tTable]->attributes[2].setDefinition("border", SgmlAttrDef::number, SgmlAttrDef::implied);
    elementDef[tTable]->attributes[3].setDefinition("cellspacing", SgmlAttrDef::number, SgmlAttrDef::implied);
    elementDef[tTable]->attributes[4].setDefinition("cellpadding", SgmlAttrDef::number, SgmlAttrDef::implied);
    elementDef[tTable]->attributes[5].setDefinition("bgcolor", SgmlAttrDef::cdata, SgmlAttrDef::implied);

    elementDef[tTr]->nbrAttributes= 3;
    elementDef[tTr]->attributes= new HtmlAttrDef[3];
    elementDef[tTr]->attributes[0].setDefinition("align", SgmlAttrDef::oneOf, SgmlAttrDef::implied);
    elementDef[tTr]->attributes[1].setDefinition("valign", SgmlAttrDef::oneOf, SgmlAttrDef::implied);
    elementDef[tTr]->attributes[2].setDefinition("bgcolor", SgmlAttrDef::cdata, SgmlAttrDef::implied);

    elementDef[tTd]->nbrAttributes= elementDef[tTh]->nbrAttributes= 8;
    elementDef[tTd]->attributes= elementDef[tTh]->attributes= new HtmlAttrDef[8];
    elementDef[tTh]->attributes[0].setDefinition("nowrap", SgmlAttrDef::flag, SgmlAttrDef::implied);
    elementDef[tTh]->attributes[1].setDefinition("rowspan", SgmlAttrDef::number, SgmlAttrDef::implied);    // Def: 1.
    elementDef[tTh]->attributes[2].setDefinition("colspan", SgmlAttrDef::number, SgmlAttrDef::implied);    // Def: 1.
    elementDef[tTh]->attributes[3].setDefinition("align", SgmlAttrDef::oneOf, SgmlAttrDef::implied);
    elementDef[tTh]->attributes[4].setDefinition("valign", SgmlAttrDef::oneOf, SgmlAttrDef::implied);
    elementDef[tTh]->attributes[5].setDefinition("width", SgmlAttrDef::number, SgmlAttrDef::implied);
    elementDef[tTh]->attributes[6].setDefinition("height", SgmlAttrDef::number, SgmlAttrDef::implied);
    elementDef[tTh]->attributes[7].setDefinition("bgcolor", SgmlAttrDef::cdata, SgmlAttrDef::implied);

    elementDef[tCaption]->nbrAttributes= 1;
    elementDef[tCaption]->attributes= new HtmlAttrDef("align", SgmlAttrDef::oneOf, SgmlAttrDef::implied);


	// Html.Body.Text elements.
	// Html.Body.Text.Font elements.
    elementDef[tTt]= new HtmlElementDef(tagNames[tTt],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tI]= new HtmlElementDef(tagNames[tI],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tB]= new HtmlElementDef(tagNames[tB],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tU]= new HtmlElementDef(tagNames[tU],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tStrike]= new HtmlElementDef(tagNames[tStrike],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tBig]= new HtmlElementDef(tagNames[tBig],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tSmall]= new HtmlElementDef(tagNames[tSmall],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tSub]= new HtmlElementDef(tagNames[tSub],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tSup]= new HtmlElementDef(tagNames[tSup],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);

	// Html.Body.Text.Phrase elements.
    elementDef[tEm]= new HtmlElementDef(tagNames[tEm],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tStrong]= new HtmlElementDef(tagNames[tStrong],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tDfn]= new HtmlElementDef(tagNames[tDfn],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tCode]= new HtmlElementDef(tagNames[tCode],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tSamp]= new HtmlElementDef(tagNames[tSamp],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tKbd]= new HtmlElementDef(tagNames[tKbd],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tVar]= new HtmlElementDef(tagNames[tVar],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tCite]= new HtmlElementDef(tagNames[tCite],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);


	// Html.Body.Text.Anchor elements.
#if defined(ACCEPT_FOLIO)
/* MOD-980908 [HD]: Modified to accomodate Folio documents (no closing </A>). */
    elementDef[tA]= new HtmlElementDef(tagNames[tA],
			SgmlElementDef::mandatory, SgmlElementDef::optional);
#else
    elementDef[tA]= new HtmlElementDef(tagNames[tA],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
#endif
    elementDef[tA]->nbrAttributes= 8;
    elementDef[tA]->attributes= new HtmlAttrDef[8];
    elementDef[tA]->attributes[0].setDefinition("name", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tA]->attributes[1].setDefinition("href", SgmlAttrDef::url, SgmlAttrDef::implied);
    elementDef[tA]->attributes[2].setDefinition("rel", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tA]->attributes[3].setDefinition("rev", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tA]->attributes[4].setDefinition("title", SgmlAttrDef::cdata, SgmlAttrDef::implied);
	// ATTN: Non HTML 3.2 conformant (conformant 4.0).
    elementDef[tA]->attributes[5].setDefinition("target", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tA]->attributes[6].setDefinition("onmouseover", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tA]->attributes[7].setDefinition("onmouseout", SgmlAttrDef::cdata, SgmlAttrDef::implied);

	// Html.Body.Text.Img element.
    elementDef[tImg]= new HtmlElementDef(tagNames[tImg],
			SgmlElementDef::mandatory, SgmlElementDef::illegal);
    elementDef[tImg]->nbrAttributes= 10;
    elementDef[tImg]->attributes= new HtmlAttrDef[10];
    elementDef[tImg]->attributes[0].setDefinition("src", SgmlAttrDef::url, SgmlAttrDef::required);
    elementDef[tImg]->attributes[1].setDefinition("alt", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tImg]->attributes[2].setDefinition("align", SgmlAttrDef::oneOf, SgmlAttrDef::implied);
    elementDef[tImg]->attributes[3].setDefinition("height", SgmlAttrDef::number, SgmlAttrDef::implied);
    elementDef[tImg]->attributes[4].setDefinition("width", SgmlAttrDef::number, SgmlAttrDef::implied);
    elementDef[tImg]->attributes[5].setDefinition("border", SgmlAttrDef::number, SgmlAttrDef::implied);
    elementDef[tImg]->attributes[6].setDefinition("hspace", SgmlAttrDef::number, SgmlAttrDef::implied);
    elementDef[tImg]->attributes[7].setDefinition("vspace", SgmlAttrDef::number, SgmlAttrDef::implied);
    elementDef[tImg]->attributes[8].setDefinition("usemap", SgmlAttrDef::url, SgmlAttrDef::implied);
    elementDef[tImg]->attributes[9].setDefinition("ismap", SgmlAttrDef::flag, SgmlAttrDef::implied);

	// Html.Body.Text.Applet elements.
    elementDef[tApplet]= new HtmlElementDef(tagNames[tApplet],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tApplet]->nbrAttributes= 9;
    elementDef[tApplet]->attributes= new HtmlAttrDef[9];
    elementDef[tApplet]->attributes[0].setDefinition("codebase", SgmlAttrDef::url, SgmlAttrDef::implied);
    elementDef[tApplet]->attributes[1].setDefinition("code", SgmlAttrDef::cdata, SgmlAttrDef::required);
    elementDef[tApplet]->attributes[2].setDefinition("alt", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tApplet]->attributes[3].setDefinition("name", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tApplet]->attributes[4].setDefinition("width", SgmlAttrDef::number, SgmlAttrDef::required);
    elementDef[tApplet]->attributes[5].setDefinition("height", SgmlAttrDef::number, SgmlAttrDef::required);
    elementDef[tApplet]->attributes[6].setDefinition("align", SgmlAttrDef::oneOf, SgmlAttrDef::implied);
    elementDef[tApplet]->attributes[7].setDefinition("hspace", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tApplet]->attributes[8].setDefinition("vspace", SgmlAttrDef::cdata, SgmlAttrDef::implied);

    elementDef[tParam]= new HtmlElementDef(tagNames[tParam],
			SgmlElementDef::mandatory, SgmlElementDef::illegal);
    elementDef[tParam]->nbrAttributes= 2;
    elementDef[tParam]->attributes= new HtmlAttrDef[2];
    elementDef[tParam]->attributes[0].setDefinition("name", SgmlAttrDef::dtName, SgmlAttrDef::required);
    elementDef[tParam]->attributes[1].setDefinition("value", SgmlAttrDef::cdata, SgmlAttrDef::implied);

    elementDef[tFont]= new HtmlElementDef(tagNames[tFont],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tFont]->nbrAttributes= 6;
    elementDef[tFont]->attributes= new HtmlAttrDef[6];
    elementDef[tFont]->attributes[0].setDefinition("size", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tFont]->attributes[1].setDefinition("color", SgmlAttrDef::cdata, SgmlAttrDef::implied);
	// ATTN: Non HTML 3.2 conformant (non conformant 4.0).
    elementDef[tFont]->attributes[2].setDefinition("face", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tFont]->attributes[3].setDefinition("onmouseover", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tFont]->attributes[4].setDefinition("onmouseout", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tFont]->attributes[5].setDefinition("bgcolor", SgmlAttrDef::cdata, SgmlAttrDef::implied);

    elementDef[tBasefont]= new HtmlElementDef(tagNames[tBasefont],
			SgmlElementDef::mandatory, SgmlElementDef::illegal);
    elementDef[tBasefont]->nbrAttributes= 1;
    elementDef[tBasefont]->attributes= new HtmlAttrDef("size", SgmlAttrDef::cdata, SgmlAttrDef::implied);

    elementDef[tBr]= new HtmlElementDef(tagNames[tBr],
			SgmlElementDef::mandatory, SgmlElementDef::illegal);
    elementDef[tBr]->nbrAttributes= 1;
    elementDef[tBr]->attributes= new HtmlAttrDef("clear", SgmlAttrDef::oneOf, SgmlAttrDef::required);

    elementDef[tMap]= new HtmlElementDef(tagNames[tMap],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tMap]->nbrAttributes= 1;
    elementDef[tMap]->attributes= new HtmlAttrDef("name", SgmlAttrDef::cdata, SgmlAttrDef::required);

    elementDef[tArea]= new HtmlElementDef(tagNames[tArea],
			SgmlElementDef::mandatory, SgmlElementDef::illegal);
    elementDef[tArea]->nbrAttributes= 5;
    elementDef[tArea]->attributes= new HtmlAttrDef[5];
    elementDef[tArea]->attributes[0].setDefinition("shape", SgmlAttrDef::oneOf, SgmlAttrDef::implied);    // Def: rect.
    elementDef[tArea]->attributes[1].setDefinition("coords", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tArea]->attributes[2].setDefinition("href", SgmlAttrDef::url, SgmlAttrDef::implied);
    elementDef[tArea]->attributes[3].setDefinition("nohref", SgmlAttrDef::flag, SgmlAttrDef::implied);
    elementDef[tArea]->attributes[4].setDefinition("alt", SgmlAttrDef::cdata, SgmlAttrDef::required);

	// Html.Body.Text.Form fields elements.
    elementDef[tInput]= new HtmlElementDef(tagNames[tInput],
			SgmlElementDef::mandatory, SgmlElementDef::illegal);
    elementDef[tInput]->nbrAttributes= 8;
    elementDef[tInput]->attributes= new HtmlAttrDef[8];
    elementDef[tInput]->attributes[0].setDefinition("type", SgmlAttrDef::oneOf, SgmlAttrDef::implied);    // Def: TEXT.
    elementDef[tInput]->attributes[1].setDefinition("name", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tInput]->attributes[2].setDefinition("value", SgmlAttrDef::cdata, SgmlAttrDef::implied);
    elementDef[tInput]->attributes[3].setDefinition("checked", SgmlAttrDef::flag, SgmlAttrDef::implied);
    elementDef[tInput]->attributes[4].setDefinition("size", SgmlAttrDef::cdata, SgmlAttrDef::required);
    elementDef[tInput]->attributes[5].setDefinition("maxlength", SgmlAttrDef::number, SgmlAttrDef::required);
    elementDef[tInput]->attributes[6].setDefinition("src", SgmlAttrDef::url, SgmlAttrDef::required);
    elementDef[tInput]->attributes[7].setDefinition("align", SgmlAttrDef::oneOf, SgmlAttrDef::required);

    elementDef[tSelect]= new HtmlElementDef(tagNames[tSelect],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tSelect]->nbrAttributes= 3;
    elementDef[tSelect]->attributes= new HtmlAttrDef[3];
    elementDef[tSelect]->attributes[0].setDefinition("name", SgmlAttrDef::cdata, SgmlAttrDef::required);
    elementDef[tSelect]->attributes[1].setDefinition("size", SgmlAttrDef::number, SgmlAttrDef::implied);
    elementDef[tSelect]->attributes[2].setDefinition("multiple", SgmlAttrDef::flag, SgmlAttrDef::implied);

    elementDef[tOption]= new HtmlElementDef(tagNames[tOption],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tOption]->nbrAttributes= 2;
    elementDef[tOption]->attributes= new HtmlAttrDef[2];
    elementDef[tOption]->attributes[0].setDefinition("selected", SgmlAttrDef::flag, SgmlAttrDef::implied);
    elementDef[tOption]->attributes[0].setDefinition("value", SgmlAttrDef::cdata, SgmlAttrDef::implied);

    elementDef[tTextarea]= new HtmlElementDef(tagNames[tTextarea],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tTextarea]->nbrAttributes= 3;
    elementDef[tTextarea]->attributes= new HtmlAttrDef[3];
    elementDef[tTextarea]->attributes[0].setDefinition("name", SgmlAttrDef::cdata, SgmlAttrDef::required);
    elementDef[tTextarea]->attributes[1].setDefinition("rows", SgmlAttrDef::number, SgmlAttrDef::required);
    elementDef[tTextarea]->attributes[2].setDefinition("cols", SgmlAttrDef::number, SgmlAttrDef::required);


    elementDef[tPcdata]= new HtmlElementDef(tagNames[tPcdata],
			SgmlElementDef::illegal, SgmlElementDef::illegal);
    elementDef[tPcdata]->tag= tPcdata;

	// Non HTML 3.2 elements.
    elementDef[tSpan]= new HtmlElementDef(tagNames[tSpan],
			SgmlElementDef::mandatory, SgmlElementDef::mandatory);
    elementDef[tSpan]->nbrAttributes= 1;
    elementDef[tSpan]->attributes= new HtmlAttrDef("style", SgmlAttrDef::cdata, SgmlAttrDef::implied);

}


bool HtmlDTD::checkCategory(HtmlDTD::HtmlTags aTag, HtmlDTD::EntityCategory aCategory)
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

	case tScript:	// Fits in both categories ?
	    return true;

	default:
	    if (aCategory == eBody) return true;
	    return false;
    }
}


bool HtmlDTD::isFromEntity(HtmlTags aTag, HtmlEntity anEntity)
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
		case tMap:
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
	    if (aTag == HtmlDTD::tP) return true;
	    return (isFromEntity(aTag, HtmlDTD::text));
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


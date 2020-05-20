/**************************************************
* File: wmlAnalyzer.cpp.
* Desc: «desc».
* Module: «module».
* Rev: 20 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <ctype.h>
#if !defined(_WIN32)
#include <iostream.h>
#endif
#include "wmlDTD.h"
#include "wmlDoc.h"
#include "wmlAnalyzer.h"

// Tmp debug help.
void tmpDebug(SgmlAnalyzer::SgmlToken aToken, char *rawData);


WmlAnalyzer::WmlAnalyzer(void)
{
    state= initial;
    dtd= new WmlDTD();
}


int WmlAnalyzer::handle(SgmlToken aToken, char *rawData)
{
    WmlDoc *doc= (WmlDoc *)currentDoc;	// Just to do away with casting.
    int errorCode;
    WmlDoc::State docState;
    WmlDTD::WmlTags tag;
    char *tmpChar;
    boolean assignation;

    tmpDebug(aToken, rawData);

    if ((state != parseDoc) && ((aToken != markupStart) && (aToken != comment))) {
	state= parseDoc;		// Skip the DocType definition.
	((WmlDTD *)dtd)->useVersion("-//WAPFORUM//DTD WML 1.1//EN");
    }

    docState= doc->getState();
    switch(aToken) {
	case startTag:
	    tag= preProcessTag(rawData);
	    if ((tag != WmlDTD::emptyTag) && (tag != WmlDTD::unknownTag)) {
		if ((errorCode= doc->startElement(tag)) != 0) {
		    if ((flags & silent) != 1) {
#if !defined(_WIN32)
		       cout << "ERRMSG: Tag is refused from sequence [" << rawData << "]\n";
#endif
		    }
		}
	    }
	    break;

              case fastEndTag:
                  // TODO: Insure that we are in a tag defintion, and close it if so.
	    if ((errorCode= doc->endCurrentElement()) != 0) {
		if ((flags & silent) != 1) {
#if !defined(_WIN32)
		    cout << "ERRMSG: Immediate closing of tag is refused,\n";
#endif
		}
	    }
	    break;

	case endTag:
	    tag= preProcessTag(rawData);
	    if ((tag != WmlDTD::emptyTag) && (tag != WmlDTD::unknownTag)) {
		if ((errorCode= doc->endElement(tag)) != 0) {
		    if ((flags & silent) != 1) {
#if !defined(_WIN32)
		       cout << "ERRMSG: Tag is refused from sequence [" << rawData << "]\n";
#endif
		    }
		}
	    }
	    break;

	case attribute:
	    tmpChar= rawData;
	    assignation= false;
	    while (*tmpChar != '\0') {
		if (toupper(*tmpChar)) *tmpChar= tolower(*tmpChar);
		tmpChar++;
	    }
	    if (tmpChar > rawData) {
		tmpChar--;
		if (*tmpChar == '=') {
		    assignation= true;
		    *tmpChar= '\0';
		}
	    }

	    if ((errorCode= doc->addAttribute(rawData, assignation)) != 0) {
		if ((flags & silent) != 1) {
#if !defined(_WIN32)
		    cout << "ERRMSG: Unknown attribute [" << rawData << "].\n";
#endif
		}
	    }
	    break;

	case literal:
	    doc->addValue(SgmlDoc::literal, rawData);
	    break;
	case unqLiteralHack:
	    doc->addValue(SgmlDoc::unqLiterhack, rawData);
	    break;
	case name:
	    doc->addValue(SgmlDoc::name, rawData);
	    break;
	case nameToken:
	    doc->addValue(SgmlDoc::nameToken, rawData);
	    break;
	case dataChar:
	case pcDataChar:
	    doc->addData(rawData);
	    break;
	case comment:
	    doc->treatComment(rawData);
	    break;
	case markupStart:
	    // TODO: Send the markup def into the DTD.
	    state= parseDoc;
	    break;
              case markup:
	    // TODO: Compile the markup def into the current DTD.
	    break;
              case procInstrName:
	     // TODO-000123 [HD]: Make sure that the name is not 'xml'.
	     // Then process the processing instruction into the DTD.
	    break;
              case procInstr:
	    // TODO: Compile the processing instruction into the DTD.
	    break;
              case cDataStart:
	    // The doc has to test that the rawData is not 'XML' (case insensitive).
	    doc->startCData(rawData);
	    break;
              case cDataEnd:
	    // TODO: Make sure that a CDATA end is done this way (look at xml.lcc).
	    doc->endCData(rawData);
	    break;
              case itemEnd:
	    doc->closeCurrentItem();
	    break;
    }
    return 0;
}


WmlDTD::WmlTags WmlAnalyzer::preProcessTag(char *rawData)
{
    char *postScanner;

    if (*rawData == '\0') return WmlDTD::emptyTag;

    postScanner= rawData;
    while ((*postScanner != '\0') && (*postScanner != '\n') && (*postScanner != '\r') && (*postScanner != ' ') && (*postScanner != '\t')) {
	if (islower(*postScanner)) *postScanner= toupper(*postScanner);
	postScanner++;
    }
    *postScanner= '\0';		// Insure there is no trailing spaces.
    if (*rawData != '\0') {
	return WmlDTD::identifyTag(rawData);	// Warning: quick exit.
    }
    return WmlDTD::emptyTag;
}


void tmpDebug(SgmlAnalyzer::SgmlToken aToken, char *rawData)
{
    static char *tagNames[SgmlAnalyzer::nbrTokens]= {
	"startTag", "endTag", "attribute", "dataChar"
	, "pcDataChar", "comment",
	"literal", "unqLiteralHack",
	"name", "nameToken"
	, "markupStart", "markup", "per"
	, "procInstrName", "procInstr", "itemEnd"
	, "cDataStart", "cDataEnd", "fastEndTag"
    };

    if (rawData != NULL) {
	cout << "{" << tagNames[aToken] << "} [" << rawData << "]\n";
    }
    else {
	cout << "{" << tagNames[aToken] << "}\n";
    }
}

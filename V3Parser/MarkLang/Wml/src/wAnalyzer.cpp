/**************************************************
* File: wAnalyzer.cpp.
* Desc: Definition of the WML optimized parsing analyzer.
* $Date: 2000/09/20 03:37:34 $
* Rev: 20 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
* Rev : 2000/08/23 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: wAnalyzer.cpp,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
**************************************************/
// TMPTMP: DEBUG:
#include <iostream>

#include <ctype.h>
#include "wDTD.h"
#include "wDoc.h"
#include "wAnalyzer.h"

// Tmp debug help.
void tmpDebug(unsigned int aToken, char *rawData);


xtnWmlAnalyzer::xtnWmlAnalyzer(void)
{
    state= initial;
    dtd= new xtnWmlDTD();
}


int xtnWmlAnalyzer::handle(unsigned int aToken, char *rawData)
{
    xtnWmlDoc *doc= (xtnWmlDoc *)currentDoc;	// Just to do away with casting.
    int errorCode;
    xtnWmlDoc::State docState;
    xtnWmlDTD::WmlTags tag;
    char *tmpChar;
    bool assignation;

    std::cerr << "@DBG [xtnWmlAnalyzer.handle]:";
    tmpDebug(aToken, rawData);

    if ((state != parseDoc) && ((aToken != markupStart) && (aToken != comment))) {
	state= parseDoc;		// Skip the DocType definition.
	((xtnWmlDTD *)dtd)->useVersion("-//WAPFORUM//DTD WML 1.1//EN");
    }

    docState= doc->getState();
    switch(aToken) {
	case startTag:
	    tag= preProcessTag(rawData);
	    if ((tag != xtnWmlDTD::emptyTag) && (tag != xtnWmlDTD::unknownTag)) {
		if ((errorCode= doc->startElement(tag)) != 0) {
		    if ((flags & silent) != 1) {
		       std::cerr << "@ERR [xtnWmlAnalyzer.handle]: Tag is refused from sequence [" << rawData << "]\n";
		    }
		}
	    }
	    break;

	case fastEndTag:
                  // TODO: Insure that we are in a tag defintion, and close it if so.
	    if ((errorCode= doc->endCurrentElement()) != 0) {
		if ((flags & silent) != 1) {
		    std::cerr << "@ERR [xtnWmlAnalyzer.handle]: Immediate closing of tag is refused,\n";
		}
	    }
	    break;

	case endTag:
	    tag= preProcessTag(rawData+1);
	    if ((tag != xtnWmlDTD::emptyTag) && (tag != xtnWmlDTD::unknownTag)) {
		if ((errorCode= doc->endElement(tag)) != 0) {
		    if ((flags & silent) != 1) {
		       std::cerr << "@ERR [xtnWmlAnalyzer.handle]: Tag is refused from sequence [" << rawData << "]\n";
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
		    std::cerr << "@ERR [xtnWmlAnalyzer.handle]: Unknown attribute [" << rawData << "].\n";
		}
	    }
	    break;

	case literal:
	    doc->addValue(xtnCoreDoc::literal, rawData);
	    break;
	case unqLiteralHack:
	    doc->addValue(xtnCoreDoc::unqLiterhack, rawData);
	    break;
	case name:
	    doc->addValue(xtnCoreDoc::name, rawData);
	    break;
	case nameToken:
	    doc->addValue(xtnCoreDoc::nameToken, rawData);
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


xtnWmlDTD::WmlTags xtnWmlAnalyzer::preProcessTag(char *rawData)
{
    char *postScanner;

    if (*rawData == '\0') return xtnWmlDTD::emptyTag;

    postScanner= rawData;
    while ((*postScanner != '\0') && (*postScanner != '\n') && (*postScanner != '\r') && (*postScanner != ' ') && (*postScanner != '\t')) {
	if (islower(*postScanner)) *postScanner= toupper(*postScanner);
	postScanner++;
    }
    *postScanner= '\0';		// Insure there is no trailing spaces.
    if (*rawData != '\0') {
	return xtnWmlDTD::identifyTag(rawData);	// Warning: quick exit.
    }
    return xtnWmlDTD::emptyTag;
}


void tmpDebug(unsigned int aToken, char *rawData)
{
    static char *tagNames[xtnXmlAnalyzer::nbrXmlTokens]= {
	"startTag", "endTag", "attribute", "dataChar"
	, "pcDataChar", "comment"
	, "literal", "unqLiteralHack"
	, "name", "nameToken"
	, "markupStart", "markup", "per"
	, "procInstrName", "procInstr", "itemEnd"
	, "cDataStart", "cDataEnd", "fastEndTag"
    };

    if (rawData != NULL) {
	std::cerr << " {" << tagNames[aToken] << "} [" << rawData << "]\n";
    }
    else {
	std::cerr << " {" << tagNames[aToken] << "}\n";
    }
}

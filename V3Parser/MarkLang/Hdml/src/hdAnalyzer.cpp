/**************************************************
* File: hdAnalyzer.cpp.
* Desc: Definition of the HDML optimized parsing analyzer.
* $Date: 2000/09/20 03:37:34 $
* Rev : 2000/09/02 : REV 1 : Hugo DesRosiers : Creation.
* $Log: hdAnalyzer.cpp,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1  2000/09/05 07:13:40  hugo
* Initial entry of real parsing/generating HDML support.
*
**************************************************/
// TMPTMP: DEBUG:
#include <iostream>
#if defined(_WIN32)
using std::cerr;
#endif

#include <ctype.h>

#include "hdDTD.h"
#include "hdDoc.h"
#include "hdAnalyzer.h"

// Tmp debug help.
void tmpDebug(unsigned int aToken, char *rawData);


xtnHdmlAnalyzer::xtnHdmlAnalyzer(void)
  : xtnSgmlAnalyzer()
{
    state= initial;
    dtd= new xtnHdmlDTD();
}


int xtnHdmlAnalyzer::handle(unsigned int aToken, char *rawData)
{
    xtnHdmlDoc *doc= (xtnHdmlDoc *)currentDoc;	// Just to do away with casting.
    int errorCode;
    xtnHdmlDoc::State docState;
    xtnHdmlDTD::HdmlTags tag;
    char *tmpChar;
    bool assignation;

    cerr << "@DBG [xtnHdmlAnalyzer.handle]:";
    tmpDebug(aToken, rawData);

    if ((state != parseDoc) && ((aToken != markupStart) && (aToken != comment))) {
	state= parseDoc;		// Skip the DocType definition.
	((xtnHdmlDTD *)dtd)->useVersion("-//EXTENTA//DTD HDML 2.0//EN");
    }

    docState= doc->getState();
    switch(aToken) {
	case startTag:
	    tag= preProcessTag(rawData);
	    if ((tag != xtnHdmlDTD::emptyTag) && (tag != xtnHdmlDTD::unknownTag)) {
		if ((errorCode= doc->startElement(tag)) != 0) {
		    if ((flags & silent) != 1) {
		       cerr << "@ERR [xtnHdmlAnalyzer.handle]: Tag is refused from sequence [" << rawData << "]\n";
		    }
		}
	    }
	    break;

	case endTag:
	    tag= preProcessTag(rawData+1);
	    if ((tag != xtnHdmlDTD::emptyTag) && (tag != xtnHdmlDTD::unknownTag)) {
		if ((errorCode= doc->endElement(tag)) != 0) {
		    if ((flags & silent) != 1) {
		       cerr << "@ERR [xtnHdmlAnalyzer.handle]: Tag is refused from sequence [" << rawData << "]\n";
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
		    cerr << "@ERR [xtnHdmlAnalyzer.handle]: Unknown attribute [" << rawData << "].\n";
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
	case itemEnd:
	    doc->closeCurrentItem();
	    break;
    }
    return 0;
}


xtnHdmlDTD::HdmlTags xtnHdmlAnalyzer::preProcessTag(char *rawData)
{
    char *postScanner;

    if (*rawData == '\0') return xtnHdmlDTD::emptyTag;

    postScanner= rawData;
    while ((*postScanner != '\0') && (*postScanner != '\n') && (*postScanner != '\r') && (*postScanner != ' ') && (*postScanner != '\t')) {
	if (islower(*postScanner)) *postScanner= toupper(*postScanner);
	postScanner++;
    }
    *postScanner= '\0';		// Insure there is no trailing spaces.
    if (*rawData != '\0') {
	return xtnHdmlDTD::identifyTag(rawData);	// Warning: quick exit.
    }
    return xtnHdmlDTD::emptyTag;
}


void tmpDebug(unsigned int aToken, char *rawData)
{
    static char *tagNames[xtnCoreAnalyzer::nbrTokens]= {
	"startTag", "endTag", "attribute", "dataChar"
	, "pcDataChar", "comment"
	, "literal", "unqLiteralHack"
	, "name", "nameToken"
	, "markupStart", "markup", "per"
	, "procInstrName", "procInstr", "itemEnd"
    };

    if (rawData != NULL) {
	cerr << " {" << tagNames[aToken] << "} [" << rawData << "]\n";
    }
    else {
	cerr << " {" << tagNames[aToken] << "}\n";
    }
}

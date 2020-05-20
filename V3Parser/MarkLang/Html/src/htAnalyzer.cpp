/**************************************************
* File: htAnalyzer.cpp.
* Desc: Definition of the HTML optimized parsing analyzer.
* $Date$
* Rev : 2000/09/02 : REV 1 : Hugo DesRosiers : Creation.
* Rev: 2000/11/30 : REV 2 : Hugo DesRosiers : Produced out of Hdml:hdAnalyzer.cpp.
* $Log$
**************************************************/
// TMPTMP: DEBUG:
#include <iostream>

#include <ctype.h>

#include <coreml/sgLexer.h>

#include "htDTD.h"
#include "htDoc.h"
#include "htElement.h"
#include "htAnalyzer.h"

// Tmp debug help.
static void tmpDebug(unsigned int aToken, char *rawData);

// TODO: Extract all the logic from this layer that is sgml proper, and migrate it to
// the core package.

xtnHtmlAnalyzer::xtnHtmlAnalyzer(void)
  : xtnSgmlAnalyzer()
{
    state= initial;
    dtd= new xtnHtmlDTD();
}


int xtnHtmlAnalyzer::handle(unsigned int aToken, char *rawData)
{
  xtnHtmlDoc *doc= (xtnHtmlDoc *)currentDoc;	// Just to do away with casting.
  int errorCode;
  xtnHtmlDoc::State docState;
  xtnHtmlDTD::HtmlTags tag;
  char *tmpChar;
  bool assignation;

  if ((flags & debug) != 0) {
    std::cout << "@DBG [xtnHtmlAnalyzer.handle]:";
    tmpDebug(aToken, rawData);
  }

  if ((state != parseDoc) && ((aToken != markupStart) && (aToken != comment))) {
    state= parseDoc;		// Skip the DocType definition.
    ((xtnHtmlDTD *)dtd)->useVersion("-//W3C//DTD HTML 3.2//EN");
  }

  docState= doc->getState();
  switch(aToken) {
    case startTag:
      tag= preProcessTag(rawData);
      if ((tag != xtnHtmlDTD::emptyTag) && (tag != xtnHtmlDTD::unknownTag)) {
        if ((errorCode= doc->startElement(tag, lexer->lineno())) != 0) {
            if ((flags & silent) != 1) {
               std::cerr << "@ERR [xtnHtmlAnalyzer.handle]: StartTag " << xtnHtmlDTD::nameTag(tag) << " is refused from sequence [" << (doc->getCurrentElement() != NULL ? xtnHtmlDTD::nameTag(doc->getCurrentElement()->getTag()) : "top level") << "]\n";
            }
        }
      }
      break;

  case endTag:
    tag= preProcessTag(rawData);
    if ((tag != xtnHtmlDTD::emptyTag) && (tag != xtnHtmlDTD::unknownTag)) {
      if ((errorCode= doc->endElement(tag, lexer->lineno())) != 0) {
        if ((flags & silent) != 1) {
          xtnHtmlElement *curEl;
          curEl= doc->getCurrentElement();
          std::cerr << "@ERR [xtnHtmlAnalyzer.handle]: EndTag " << xtnHtmlDTD::nameTag(tag) << "(l:" << lexer->lineno() << ") is refused (err: " << errorCode << ") from ";
          if (curEl == NULL) {
            std::cerr << "top level" << "]\n";
          }
          else {
            std::cerr << "sequence [" << xtnHtmlDTD::nameTag(curEl->getTag()) << "] (l:" << curEl->getStartPos() << ")\n";
          }
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
          std::cerr << "@ERR [xtnHtmlAnalyzer.handle]: Unknown attribute [" << rawData << "] in element " <<  xtnHtmlDTD::nameTag(doc->getCurrentElement()->getTag()) << ".\n";
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
    doc->addData(rawData, lexer->lineno());
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


xtnHtmlDTD::HtmlTags xtnHtmlAnalyzer::preProcessTag(char *rawData)
{
    char *postScanner;

    if (*rawData == '\0') return xtnHtmlDTD::emptyTag;

    postScanner= rawData;
    while ((*postScanner != '\0') && (*postScanner != '\n') && (*postScanner != '\r') && (*postScanner != ' ') && (*postScanner != '\t')) {
	if (islower(*postScanner)) *postScanner= toupper(*postScanner);
	postScanner++;
    }
    *postScanner= '\0';		// Insure there is no trailing spaces.
    if (*rawData != '\0') {
	return xtnHtmlDTD::identifyTag(rawData);	// Warning: quick exit.
    }
    return xtnHtmlDTD::emptyTag;
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
	std::cout << " {" << tagNames[aToken] << "} [" << rawData << "]\n";
    }
    else {
	std::cout << " {" << tagNames[aToken] << "}\n";
    }
}

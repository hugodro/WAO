/**************************************************
* File: sgmlAnalyzer.h.
* Desc: Implementation of the generic Sgml Document parser.
* Module: WAO : SgmlParser.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <ostream>

#if defined(USE_SGML)
#include "sgFlexer.h"
#else
#include "xmlLexer.h"
#endif
#include "dtdDefinition.h"
#include "sgmlDoc.h"
#include "sgmlAnalyzer.h"


SgmlAnalyzer::SgmlAnalyzer(void)
{
    dtd= NULL;
    currentDoc= NULL;
    renderDeleguate= NULL;
#if defined(USE_SGML)
    lexer= new sgmlFlexLexer(this);
#else
    lexer= new xmlFlexLexer(this);
#endif
}


SgmlDoc *SgmlAnalyzer::createDoc(char *aName)
{
    if (dtd != NULL) {
	return dtd->createConformentDoc(aName);
    }
    else {
	return new SgmlDoc(aName);
    }
}


int SgmlAnalyzer::parseDTD(std::istream *aStream, char *aName)
{
    lexer->yylex(aStream);
    return 0;
}


int SgmlAnalyzer::parseDoc(std::istream *aStream, char *aName)
{
    lexer->yylex(aStream);
    return 0;
}


int SgmlAnalyzer::parseConformentDoc(std::istream *aStream, char *aName)
{
    currentDoc= createDoc(aName);
    currentDoc->initForParse();
    lexer->yylex(aStream);
    return 0;
}


void SgmlAnalyzer::setFlags(unsigned int value)
{
    flags= value;
}


int SgmlAnalyzer::handle(SgmlToken aToken, char *rawData)
{
    if (currentDoc != NULL) {
	// TODO.
    }
    return 0;
}


SgmlDoc *SgmlAnalyzer::getCurrentDoc(void)
{
    return currentDoc;
}


/**************************************************
* File: analyzer.h.
* Desc: Implementation of the core Marked document parser.
* $Date: 2000/09/20 03:37:34 $
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/08/22 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: analyzer.cpp,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1.1.1  2000/09/01 07:33:30  hugo
* Initial Entry
*
**************************************************/

#include <iostream>

#define yyFlexLexerOnce
#include <FlexLexer.h>

#include "dtdDefinition.h"
#include "doc.h"
#include "analyzer.h"


xtnCoreAnalyzer::xtnCoreAnalyzer(void)
{
    dtd= NULL;
    currentDoc= NULL;
    renderDeleguate= NULL;

// TODO-000822 [HD]: Mechanism to supply the Flexer goes in sub-classes.
//    lexer= new sgmlFlexLexer(this);

    lexer= NULL;
}


xtnCoreAnalyzer::~xtnCoreAnalyzer(void)
{
// TODO.
}


xtnCoreDoc *xtnCoreAnalyzer::createDoc(char *aName)
{
    if (dtd != NULL) {
	return dtd->createConformentDoc(aName);
    }
    else {
	return new xtnCoreDoc(aName);
    }
}


int xtnCoreAnalyzer::parseDTD(std::istream *aStream, char *aName)
{
    lexer->yylex(aStream);
    return 0;
}


int xtnCoreAnalyzer::parseDoc(std::istream *aStream, char *aName)
{
    lexer->yylex(aStream);
    return 0;
}


int xtnCoreAnalyzer::parseConformentDoc(std::istream *aStream, char *aName)
{
    currentDoc= createDoc(aName);
    currentDoc->initForParse();
    lexer->yylex(aStream);
    return 0;
}


void xtnCoreAnalyzer::setFlags(unsigned int value)
{
    flags= value;
}


int xtnCoreAnalyzer::handle(unsigned int aToken, char *rawData)
{
    if (currentDoc != NULL) {
	// TODO.
    }
    return 0;
}


xtnCoreDoc *xtnCoreAnalyzer::getCurrentDoc(void)
{
    return currentDoc;
}


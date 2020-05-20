#ifndef _XML_FLEXLEXER_H_
#define _XML_FLEXLEXER_H_
/**************************************************
* File: xmlFlexer.h.
* Desc: Definition of the XML version of a FlexLexer.
* Module: WAO : SgmlParser.
* Rev: 16 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#if !defined(yyFlexLexer)
#define yyFlexLexer xxFlexLexer
#include <FlexLexer.h>
#endif

#include <exportDefs.h>

class xtnCoreAnalyzer;


class ClExp xtnXmlFlexLexer : public yyFlexLexer {
  protected:
    xtnCoreAnalyzer *analyzer;

  public:
    xtnXmlFlexLexer(xtnCoreAnalyzer *anAnalyzer);
    virtual ~xtnXmlFlexLexer();

    virtual int yylex();
#if defined(_WIN32)
    virtual void LexerOutput(const char* buf, int size);
#endif
};

#endif		/* _XML_FLEXLEXER_H_ */

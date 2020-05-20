#ifndef _XML_FLEXLEXER_H_
#define _XML_FLEXLEXER_H_
/**************************************************
* File: xmlFlexer.h.
* Desc: Definition of the XML version of a FlexLexer.
* Module: WAO : SgmlParser.
* Rev: 16 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <FlexLexer.h>


class SgmlAnalyzer;


class xmlFlexLexer : public yyFlexLexer {
  protected:
    SgmlAnalyzer *analyzer;

  public:
    xmlFlexLexer(SgmlAnalyzer *anAnalyzer);
    inline setDebugOn(void) { yy_flex_debug= 1; }

#if defined(_WIN32)
    virtual void LexerOutput(const char* buf, int size);
#endif
    virtual int yylex();
};

#endif		/* _XML_FLEXLEXER_H_ */

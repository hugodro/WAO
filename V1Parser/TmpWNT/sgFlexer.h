#ifndef _SGMLFLEXLEXER_H_
#define _SGMLFLEXLEXER_H_
/**************************************************
* File: sgFlexer.h.
* Desc: Definition of the SGML version of a FlexLexer.
* Module: WAO : SgmlParser.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <FlexLexer.h>

class SgmlAnalyzer;

class sgmlFlexLexer : public yyFlexLexer {
  protected:
    SgmlAnalyzer *analyzer;

  public:
    sgmlFlexLexer(SgmlAnalyzer *anAnalyzer);
#if defined(_WIN32)
    virtual void LexerOutput(const char* buf, int size);
#endif
    virtual int yylex();
};

#endif		/* _SGMLFLEXLEXER_H_ */

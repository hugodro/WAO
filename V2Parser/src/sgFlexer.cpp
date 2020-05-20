/**************************************************
* File: sgFlexer.cc.
* Desc: Implementation of the SGML version of a FlexLexer.
* Module: WAO : SgmlParser.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/
#include "sgFlexer.h"


sgmlFlexLexer::sgmlFlexLexer(SgmlAnalyzer *anAnalyzer)
  : yyFlexLexer()
{
    analyzer= anAnalyzer;
}

#if defined(_WIN32)
void sgmlFlexLexer::LexerOutput( const char* buf, int size )
{
    // Should do an output, but we cancel from NT linking problems.
}
#endif

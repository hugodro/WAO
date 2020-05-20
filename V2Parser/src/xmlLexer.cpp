/**************************************************
* File: xmlLexer.cc.
* Desc: Implementation of the XML version of a FlexLexer.
* Module: WAO : SgmlParser.
* Rev: 19 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "xmlLexer.h"


xmlFlexLexer::xmlFlexLexer(SgmlAnalyzer *anAnalyzer)
  : yyFlexLexer()
{
    analyzer= anAnalyzer;
}

#if defined(_WIN32)
void xmlFlexLexer::LexerOutput( const char* buf, int size )
{
    // Should do an output, but we cancel from NT linking problems.
}
#endif

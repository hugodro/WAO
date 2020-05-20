/**************************************************
* File: baseFlex.cc.
* Desc: Implementation of the base interface FlexLexer for ML parsing.
* $Date: 2000/09/20 03:37:34 $
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/08/22 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: baseFlex.cpp,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1.1.1  2000/09/01 07:33:30  hugo
* Initial Entry
*
**************************************************/

#include "baseFlex.h"


xtnCoreFlexLexer::xtnCoreFlexLexer(xtnCoreAnalyzer *anAnalyzer)
  : yyFlexLexer()
{
    analyzer= anAnalyzer;
}


xtnCoreFlexLexer::~xtnCoreFlexLexer()
{
// TODO.
}


int xtnCoreFlexLexer::yylex()
{
// The default implementation just generates an error.
    return -1;
}


int xtnCoreFlexLexer::yylex(istream *inStream, ostream *outStream)
{
    return FlexLexer::yylex(inStream, outStream);
}


#if defined(_WIN32)
void xtnCoreFlexLexer::LexerOutput( const char* buf, int size )
{
    // Should do an output, but we cancel from NT linking problems.
}
#endif

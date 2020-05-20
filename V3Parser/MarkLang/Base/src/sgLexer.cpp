/**************************************************
* File: sgLexer.cpp.
* Desc: Implementation of the SGML version of a FlexLexer.
* $Date: 2000/09/20 03:37:34 $
* Rev: 2000/09/03 : REV 0 : Hugo DesRosiers : Creation.
* $Log: sgLexer.cpp,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1.1.1  2000/09/20 03:26:47  hugo
* Initial entry
*
**************************************************/

#include "sgLexer.h"


xtnSgmlFlexLexer::xtnSgmlFlexLexer(xtnCoreAnalyzer *anAnalyzer)
{
// TODO: Make sure that anAnalyzer is a member of the xtnSgmlAnalyzer class.
    analyzer= anAnalyzer;
}


xtnSgmlFlexLexer::~xtnSgmlFlexLexer()
{
// TODO.
}


// NOTE: the xtnSgmlFlexLexer::yylex method is in the file generated by the
//  flexing of xLexer.l.


#if defined(_WIN32)
void xtnSgmlFlexLexer::LexerOutput( const char* buf, int size )
{
    // Should do an output, but we cancel from NT linking problems.
}
#endif
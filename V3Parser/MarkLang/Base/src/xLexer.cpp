/**************************************************
* File: xLexer.cpp.
* Desc: Implementation of the XML version of a FlexLexer.
* $Date: 2000/09/20 03:37:34 $
* Rev: 19 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/08/23 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: xLexer.cpp,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1.1.1  2000/09/01 07:33:30  hugo
* Initial Entry
*
**************************************************/

#include "xLexer.h"


xtnXmlFlexLexer::xtnXmlFlexLexer(xtnCoreAnalyzer *anAnalyzer)
{
// TODO: Make sure that anAnalyzer is a member of the xtnXmlAnalyzer class.
    analyzer= anAnalyzer;
}


xtnXmlFlexLexer::~xtnXmlFlexLexer()
{
// TODO.
}


// NOTE: the xtnXmlFlexLexer::yylex method is in the file generated by the
//  flexing of xLexer.l.


#if defined(_WIN32)
void xtnXmlFlexLexer::LexerOutput( const char* buf, int size )
{
    // Should do an output, but we cancel from NT linking problems.
}
#endif

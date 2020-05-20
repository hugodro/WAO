/**************************************************
* File: xAnalyzer.cpp.
* Desc: Implementation of the XML extension of the Analyzer.
* Rev: 22 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/08/22 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: xAnalyzer.cpp,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1.1.1  2000/09/01 07:33:30  hugo
* Initial Entry
*
**************************************************/

#include "xLexer.h"
#include "xAnalyzer.h"

xtnXmlAnalyzer::xtnXmlAnalyzer()
  : xtnCoreAnalyzer()
{
    lexer= new xtnXmlFlexLexer(this);
}


xtnXmlAnalyzer::~xtnXmlAnalyzer()
{
    // TODO.
}

/**************************************************
* File: sgAnalyzer.cpp.
* Desc: Implementation of the SGML extension of the Analyzer.
* Rev: 2000/09/03 : REV 0 : Hugo DesRosiers : Creation.
* $Log: sgAnalyzer.cpp,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1.1.1  2000/09/20 03:26:47  hugo
* Initial entry
*
**************************************************/

#include "sgLexer.h"
#include "sgAnalyzer.h"

xtnSgmlAnalyzer::xtnSgmlAnalyzer()
  : xtnCoreAnalyzer()
{
    lexer= new xtnSgmlFlexLexer(this);
}


xtnSgmlAnalyzer::~xtnSgmlAnalyzer()
{
    // TODO.
}

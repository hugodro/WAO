#ifndef _XTN_CORE_FLEXLEXER_H_
#define _XTN_CORE_FLEXLEXER_H_
/**************************************************
* File: baseFlex.h.
* Desc: Definition of the Core ML version of a FlexLexer.
* $Date: 2000/09/20 03:37:34 $
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/08/22 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: baseFlex.h,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1.1.1  2000/09/01 07:33:30  hugo
* Initial Entry
*
**************************************************/

#include <FlexLexer.h>

#include <exportDefs.h>

class xtnCoreAnalyzer;


class ClExp xtnCoreFlexLexer : public yyFlexLexer {
  protected:
    xtnCoreAnalyzer *analyzer;

  public:
    xtnCoreFlexLexer(xtnCoreAnalyzer *anAnalyzer);
    virtual ~xtnCoreFlexLexer();

    virtual int yylex();
    // NOTE-000824 [HD]: The following is a fix for the g++ compiler, which
    // can't retrace the non-virt stream-based yylex defined in FlexLexer.
    int yylex(istream *inStream, ostream *outStream= 0);

#if defined(_WIN32)
    virtual void LexerOutput(const char* buf, int size);
#endif

    inline void setDebugOn() { yy_flex_debug= 1; }
};

#endif		/* _XTN_CORE_FLEXLEXER_H_ */

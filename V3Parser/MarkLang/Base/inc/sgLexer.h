#ifndef _XTN_SGML_FLEXLEXER_H_
#define _XTN_SGML_FLEXLEXER_H_
/**************************************************
* File: flexer.h.
* Desc: Definition of the SGML version of a FlexLexer.
* $Date: 2000/09/20 03:37:34 $
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/08/22 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: sgLexer.h,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1.1.2  2000/09/20 03:26:47  hugo
* Initial entry
*
**************************************************/

#if !defined(yyFlexLexer)
#define yyFlexLexer sgFlexLexer
#include <FlexLexer.h>
#endif

#include <exportDefs.h>

class xtnCoreAnalyzer;


class ClExp xtnSgmlFlexLexer : public yyFlexLexer {
  protected:
    xtnCoreAnalyzer *analyzer;

  public:
    xtnSgmlFlexLexer(xtnCoreAnalyzer *anAnalyzer);
    virtual ~xtnSgmlFlexLexer();

    virtual int yylex();
#if defined(_WIN32)
    virtual void LexerOutput(const char* buf, int size);
#endif
};

#endif		/* _XTN_SGML_FLEXLEXER_H_ */

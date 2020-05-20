#ifndef _XTN_CORE_ANALYZER_H_
#define _XTN_CORE_ANALYZER_H_
/**************************************************
* File: analyzer.h.
* Desc: Definition of the Core Document ML parser.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/08/22 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: analyzer.h,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1.1.1  2000/09/01 07:33:30  hugo
* Initial Entry
*
**************************************************/

#include <fstream>

#include <exportDefs.h>

class FlexLexer;


class xtnCoreDtdDefinition;
class xtnCoreDoc;
class xtnCoreDocRenderer;

class ClExp xtnCoreAnalyzer {
  public:
    enum xtnCoreToken {
	startTag, endTag, attribute, dataChar, pcDataChar, comment,
	literal, unqLiteralHack,
	name, nameToken
	, markupStart, markup, per
	, procInstrName, procInstr, itemEnd
	, nbrTokens
    };
    enum runFlags {
	silent= 1, debug= 2, lexDebug= 4
    };

  protected:
    FlexLexer *lexer;
    xtnCoreDtdDefinition *dtd;
    xtnCoreDoc *currentDoc;
    xtnCoreDocRenderer *renderDeleguate;
    unsigned int flags;

  public:
    xtnCoreAnalyzer();
    virtual ~xtnCoreAnalyzer();

    virtual xtnCoreDoc *createDoc(char *aName);
    virtual int parseDTD(std::istream *aStream, char *aName);
    virtual int parseDoc(std::istream *aStream, char *aName);
    virtual int parseConformentDoc(std::istream *aStream, char *aName);
    virtual void setFlags(unsigned int value);
    
    virtual int handle(unsigned int aToken, char *rawData);
    virtual xtnCoreDoc *getCurrentDoc();

    inline int doLexDebug() { return (flags & lexDebug) != 0; }
};

#endif	/* _XTN_CORE_ANALYZER_H_ */

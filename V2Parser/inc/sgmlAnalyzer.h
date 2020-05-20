#ifndef _SGMLANALYZER_H_
#define _SGMLANALYZER_H_
/**************************************************
* File: sgmlAnalyzer.h.
* Desc: Definition of the generic Sgml Document parser.
* Module: WAO : SgmlParser.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <fstream>

#include <akra/AkObject.h>

class FlexLexer;
class DtdDefinition;
class SgmlDoc;
class DocRenderer;

class SgmlAnalyzer : public AkObject {
  public:
    enum SgmlToken {
	startTag, endTag, attribute, dataChar, pcDataChar, comment,
	literal, unqLiteralHack,
	name, nameToken
	, markupStart, markup, per
	, procInstrName, procInstr, itemEnd
	, cDataStart, cDataEnd, fastEndTag        // ATTN-000123 [HD]: XML only !
	, nbrTokens
    };
    enum runFlags {
	silent= 1, debug= 2
    };

  protected:
    FlexLexer *lexer;
    DtdDefinition *dtd;
    SgmlDoc *currentDoc;
    DocRenderer *renderDeleguate;
    unsigned int flags;

  public:
    SgmlAnalyzer(void);

    virtual SgmlDoc *createDoc(char *aName);
    virtual int parseDTD(std::istream *aStream, char *aName);
    virtual int parseDoc(std::istream *aStream, char *aName);
    virtual int parseConformentDoc(std::istream *aStream, char *aName);
    virtual void setFlags(unsigned int value);
    
    virtual int handle(SgmlToken aToken, char *rawData);
    virtual SgmlDoc *getCurrentDoc(void);

};

#endif	/* _SGMLANALYZER_H_ */

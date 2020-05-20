#ifndef _HTMLANALYZER_H_
#define _HTMLANALYZER_H_
/**************************************************
* File: htmlAnalyzer.h.
* Desc: «desc».
* Module: «module».
* Rev: «rev».
**************************************************/

#include <akra/AkObject.h>
#include "sgmlAnalyzer.h"
#include "htmlDTD.h"


class HtmlAnalyzer : public SgmlAnalyzer {
  public:
    enum ParseState {
	initial, hasDocType, parseDoc
    };

  protected:
    ParseState state;

  public:
    HtmlAnalyzer(void);
    virtual int handle(SgmlToken aToken, char *rawData);

  protected:
    HtmlDTD::HtmlTags preProcessTag(char *rawData);
#if defined(OLDCODE)
    int pushStartTag(char *rawData);
    int pushEndTag(char *rawData);
    int defineAttribute(char *rawData);
    int setAttrValue(char *rawData);
    int scanData(char *rawData);
    int scanComment(char *rawData);
#endif	/* OLDCODE */
};


#endif		/* _HTMLANALYZER_H_ */

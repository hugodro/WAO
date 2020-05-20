#ifndef _XTN_HTML_ANALYZER_H_
#define _XTN_HTML_ANALYZER_H_
/**************************************************
* File: htAnalyzer.h.
* Desc: Definition of the HTML optimized parsing analyzer.
* $Date$
* Rev: 19 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
* Rev : 2000/09/02 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* Rev: 2000/11/30 : REV 2 : Hugo DesRosiers : Produced out of Hdml:hdAnalyzer.cpp.
* $Log$
**************************************************/

#include <coreml/sgAnalyzer.h>
#include "htDTD.h"


class ClExp xtnHtmlAnalyzer : public xtnSgmlAnalyzer {
  public:
    enum ParseState {
	initial, hasDocType, parseDoc
    };

  protected:
    ParseState state;

  public:
    xtnHtmlAnalyzer(void);
    virtual int handle(unsigned int aToken, char *rawData);

  protected:
    xtnHtmlDTD::HtmlTags preProcessTag(char *rawData);
};


#endif		/* _XTN_HTML_ANALYZER_H_ */

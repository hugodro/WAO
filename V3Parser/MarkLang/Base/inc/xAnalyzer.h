#ifndef _XTN_XML_ANALYZER_H_
#define _XTN_XML_ANALYZER_H_
/**************************************************
* File: analyzerXML.h.
* Desc: Definition of the XML Document ML parser.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/08/22 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: xAnalyzer.h,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1.1.1  2000/09/01 07:33:30  hugo
* Initial Entry
*
**************************************************/

#include <exportDefs.h>

#include "analyzer.h"


class ClExp xtnXmlAnalyzer : public xtnCoreAnalyzer {
  public:
    enum xtnXmlToken {
	cDataStart= xtnCoreAnalyzer::nbrTokens, cDataEnd, fastEndTag        // ATTN-000123 [HD]: XML only !
	, nbrXmlTokens
    };

  public:
    xtnXmlAnalyzer();
    virtual ~xtnXmlAnalyzer();
};

#endif	/* _XTN_XML_ANALYZER_H_ */

#ifndef _XTN_WML_ANALYZER_H_
#define _XTN_WML_ANALYZER_H_
/**************************************************
* File: wAnalyzer.h.
* Desc: Definition of the WML optimized parsing analyzer.
* $Date: 2000/09/20 03:37:34 $
* Rev: 19 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
* Rev : 2000/08/23 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: wAnalyzer.h,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
**************************************************/

#include <exportDefs.h>

#include <coreml/xAnalyzer.h>
#include "wDTD.h"


class ClExp xtnWmlAnalyzer : public xtnXmlAnalyzer {
  public:
    enum ParseState {
	initial, hasDocType, parseDoc
    };

  protected:
    ParseState state;

  public:
    xtnWmlAnalyzer(void);
    virtual int handle(unsigned int aToken, char *rawData);

  protected:
    xtnWmlDTD::WmlTags preProcessTag(char *rawData);
};


#endif		/* _XTN_WML_ANALYZER_H_ */

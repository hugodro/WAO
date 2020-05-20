#ifndef _WMLANALYZER_H_
#define _WMLANALYZER_H_
/**************************************************
* File: wmlAnalyzer.h.
* Desc: «desc».
* Module: «module».
* Rev: 19 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include "sgmlAnalyzer.h"
#include "wmlDTD.h"


class WmlAnalyzer : public SgmlAnalyzer {
  public:
    enum ParseState {
	initial, hasDocType, parseDoc
    };

  protected:
    ParseState state;

  public:
    WmlAnalyzer(void);
    virtual int handle(SgmlToken aToken, char *rawData);

  protected:
    WmlDTD::WmlTags preProcessTag(char *rawData);
};


#endif		/* _WMLANALYZER_H_ */

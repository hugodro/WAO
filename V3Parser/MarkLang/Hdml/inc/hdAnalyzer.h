#ifndef _XTN_WML_ANALYZER_H_
#define _XTN_WML_ANALYZER_H_
/**************************************************
* File: hdAnalyzer.h.
* Desc: Definition of the HDML optimized parsing analyzer.
* $Date: 2000/09/20 03:37:34 $
* Rev: 19 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
* Rev : 2000/09/02 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: hdAnalyzer.h,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1  2000/09/05 07:13:37  hugo
* Initial entry of real parsing/generating HDML support.
*
**************************************************/

#include <exportDefs.h>

#include <coreml/sgAnalyzer.h>
#include "hdDTD.h"


class ClExp xtnHdmlAnalyzer : public xtnSgmlAnalyzer {
  public:
    enum ParseState {
	initial, hasDocType, parseDoc
    };

  protected:
    ParseState state;

  public:
    xtnHdmlAnalyzer(void);
    virtual int handle(unsigned int aToken, char *rawData);

  protected:
    xtnHdmlDTD::HdmlTags preProcessTag(char *rawData);
};


#endif		/* _XTN_HDML_ANALYZER_H_ */

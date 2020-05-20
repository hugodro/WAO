#ifndef _XTN_SGML_ANALYZER_H_
#define _XTN_SGML_ANALYZER_H_
/**************************************************
* File: sgAnalyzer.h.
* Desc: Definition of the SGML Document ML parser.
* Rev: 2000/09/03 : REV 0 : Hugo DesRosiers : Creation.
* $Log: sgAnalyzer.h,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1.1.1  2000/09/20 03:26:47  hugo
* Initial entry
*
**************************************************/

#include "analyzer.h"


class ClExp xtnSgmlAnalyzer : public xtnCoreAnalyzer {
  public:
    xtnSgmlAnalyzer();
    virtual ~xtnSgmlAnalyzer();
};

#endif	/* _XTN_SGML_ANALYZER_H_ */

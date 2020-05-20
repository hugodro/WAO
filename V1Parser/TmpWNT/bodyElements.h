#ifndef _BODYELEMENTS_H_
#define _BODYELEMENTS_H_
/**************************************************
* File: bodyElements.h.
* Desc: Definition of the optimized version of the body elements of HTML 3.2.
* Module: WAO : SgmlParser.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "htmlElement.h"

class HHeading : public HtmlElement {
  protected:
    unsigned char level;

  public:
    HHeading(int anArg);
};

class HAddress : public HtmlElement {
  protected:
  public:
    HAddress();
};


#endif		/* _BODYELEMENTS_H_ */

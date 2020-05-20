#ifndef _XTN_BODYELEMENTS_H_
#define _XTN_BODYELEMENTS_H_
/**************************************************
* File: bodyElements.h.
* Desc: Definition of the optimized version of the body elements of HTML 3.2.
* $Date$
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/11/30 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
**************************************************/

#include "htElement.h"

class xtnHHeading : public xtnHtmlElement {
  protected:
    unsigned char level;

  public:
    xtnHHeading(int anArg);
};

class xtnHAddress : public xtnHtmlElement {
  protected:
  public:
    xtnHAddress();
};


#endif		/* _BODYELEMENTS_H_ */

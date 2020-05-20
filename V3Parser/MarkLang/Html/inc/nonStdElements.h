#ifndef _XTN_NONSTDELEMENTS_H_
#define _XTN_NONSTDELEMENTS_H_
/**************************************************
* File: nonStdElements.h.
* Desc: Definition of the optimized version of the special form elements of HTML 3.2.
* $Date$
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/11/30 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log$
**************************************************/

#include "htElement.h"


class xtnHSpan : public xtnHtmlElement {
  protected:
  public:
    xtnHSpan();
};


// TODO: Move this to the core package.
class xtnHPcData : public xtnHtmlElement {
    protected:
      char *data;

    public:
      xtnHPcData();
      virtual void setData(char *someData);
      virtual char *getData(void);
      virtual void mergeData(char *someData);
};


#endif		/* _XTN_NONSTDELEMENTS_H_ */

#ifndef _XTN_SFORMELEMENTS_H_
#define _XTN_SFORMELEMENTS_H_
/**************************************************
* File: sformElements.h.
* Desc: Definition of the optimized version of the special form elements of HTML 3.2.
* $Date$
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/11/30 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log$
**************************************************/

#include "htElement.h"


class xtnHInput : public xtnHtmlElement {
  protected:
  public:
    xtnHInput();
};


class xtnHSelect : public xtnHtmlElement {
  protected:
  public:
    xtnHSelect();
};


class xtnHTextArea : public xtnHtmlElement {
  protected:
  public:
    xtnHTextArea();
};

class xtnHOption : public xtnHtmlElement {
  protected:
  public:
    xtnHOption();
};


#endif		/* _XTN_SFORMELEMENTS_H_ */

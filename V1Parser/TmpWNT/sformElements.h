#ifndef _SFORMELEMENTS_H_
#define _SFORMELEMENTS_H_
/**************************************************
* File: sformElements.h.
* Desc: Definition of the optimized version of the special form elements of HTML 3.2.
* Module: WAO : SgmlParser.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "htmlElement.h"


class HInput : public HtmlElement {
  protected:
  public:
    HInput();
};


class HSelect : public HtmlElement {
  protected:
  public:
    HSelect();
};


class HTextArea : public HtmlElement {
  protected:
  public:
    HTextArea();
};

class HOption : public HtmlElement {
  protected:
  public:
    HOption();
};


#endif		/* _SFORMELEMENTS_H_ */

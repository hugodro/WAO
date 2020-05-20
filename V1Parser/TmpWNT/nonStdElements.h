#ifndef _NONSTDELEMENTS_H_
#define _NONSTDELEMENTS_H_
/**************************************************
* File: nonStdElements.h.
* Desc: Definition of the optimized version of the special form elements of HTML 3.2.
* Module: WAO : SgmlParser.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "htmlElement.h"


class HSpan : public HtmlElement {
  protected:
  public:
    HSpan();
};


class HPcData : public HtmlElement {
    protected:
      char *data;

    public:
      HPcData();
      virtual void setData(char *someData);
      virtual char *getData(void);
};


#endif		/* _NONSTDELEMENTS_H_ */

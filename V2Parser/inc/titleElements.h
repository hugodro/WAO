#ifndef _TITLEELEMENTS_H_
#define _TITLEELEMENTS_H_
/**************************************************
* File: titleElements.h.
* Desc: Definition of the optimized version of the title elements of HTML 3.2.
* Module: WAO : SgmlParser.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "htmlElement.h"


class HStyle : public HtmlElement {
  protected:
  public:
    HStyle();
};

class HScript : public HtmlElement {
  protected:
  public:
    HScript();
};

class HTitle : public HtmlElement {
  protected:
  public:
    HTitle();
};

class HIsIndex : public HtmlElement {
  protected:
  public:
    HIsIndex();
};

class HBase : public HtmlElement {
  protected:
  public:
    HBase();
};

class HMeta : public HtmlElement {
  protected:
  public:
    HMeta();
};

class HLink : public HtmlElement {
  protected:
  public:
    HLink();
};


#endif		/* _TITLEELEMENTS_H_ */

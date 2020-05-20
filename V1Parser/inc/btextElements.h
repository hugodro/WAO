#ifndef _BTEXTELEMENTS_H_
#define _BTEXTELEMENTS_H_
/**************************************************
* File: btextElements.h.
* Desc: Definition of the optimized version of the body text elements of HTML 3.2.
* Module: WAO : SgmlParser.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "htmlElement.h"


class HTeleType : public HtmlElement {
  protected:
  public:
    HTeleType();
};

class HItalic : public HtmlElement {
  protected:
  public:
    HItalic();
};

class HBold : public HtmlElement {
  protected:
  public:
    HBold();
};

class HUnderscore : public HtmlElement {
  protected:
  public:
    HUnderscore();
};

class HStrike : public HtmlElement {
  protected:
  public:
    HStrike();
};

class HBig : public HtmlElement {
  protected:
  public:
    HBig();
};

class HSmall : public HtmlElement {
  protected:
  public:
    HSmall();
};

class HSub : public HtmlElement {
  protected:
  public:
    HSub();
};

class HSup : public HtmlElement {
  protected:
  public:
    HSup();
};

class HEm : public HtmlElement {
  protected:
  public:
    HEm();
};

class HStrong : public HtmlElement {
  protected:
  public:
    HStrong();
};

class HDfn : public HtmlElement {
  protected:
  public:
    HDfn();
};

class HCode : public HtmlElement {
  protected:
  public:
    HCode();
};

class HSamp : public HtmlElement {
  protected:
  public:
    HSamp();
};

class HKbd : public HtmlElement {
  protected:
  public:
    HKbd();
};

class HVar : public HtmlElement {
  protected:
  public:
    HVar();
};

class HCite : public HtmlElement {
  protected:
  public:
    HCite();
};

class HAnchor : public HtmlElement {
  protected:
  public:
    HAnchor();
};

class HImg : public HtmlElement {
  protected:
  public:
    HImg();
};

class HApplet : public HtmlElement {
  protected:
  public:
    HApplet();
};

class HParam : public HtmlElement {
  protected:
  public:
    HParam();
};

class HFont : public HtmlElement {
  protected:
  public:
    HFont();
};

class HBaseFont : public HtmlElement {
  protected:
  public:
    HBaseFont();
};

class HMap : public HtmlElement {
  protected:
  public:
    HMap();
};

class HArea : public HtmlElement {
  protected:
  public:
    HArea();
};

class HBreak : public HtmlElement {
  protected:
  public:
    HBreak();
};


#endif		/* _BTEXTELEMENTS_H_ */

#ifndef _XTN_TITLEELEMENTS_H_
#define _XTN_TITLEELEMENTS_H_
/**************************************************
* File: titleElements.h.
* Desc: Definition of the optimized version of the title elements of HTML 3.2.
* $Date$
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/11/30 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log$
**************************************************/

#include "htElement.h"


class xtnHStyle : public xtnHtmlElement {
  protected:
  public:
    xtnHStyle();
};

class xtnHScript : public xtnHtmlElement {
  protected:
  public:
    xtnHScript();
};

class xtnHNoScript : public xtnHtmlElement {
  protected:
  public:
    xtnHNoScript();
};

class xtnHTitle : public xtnHtmlElement {
  protected:
  public:
    xtnHTitle();
};

class xtnHIsIndex : public xtnHtmlElement {
  protected:
  public:
    xtnHIsIndex();
};

class xtnHBase : public xtnHtmlElement {
  protected:
  public:
    xtnHBase();
};

class xtnHMeta : public xtnHtmlElement {
  protected:
  public:
    xtnHMeta();
};

class xtnHLink : public xtnHtmlElement {
  protected:
  public:
    xtnHLink();
};


class xtnHObject : public xtnHtmlElement {
  protected:
  public:
    xtnHObject();
};

class xtnHEmbed : public xtnHtmlElement {
  protected:
  public:
    xtnHEmbed();
};


#endif		/* _XTN_TITLEELEMENTS_H_ */

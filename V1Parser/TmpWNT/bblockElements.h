#ifndef _BBLOCKELEMENTS_H_
#define _BBLOCKELEMENTS_H_
/**************************************************
* File: bblockElements.h.
* Desc: Definition of the optimized version of the body block elements of HTML 3.2.
* Module: WAO : SgmlParser.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "htmlElement.h"


class HPara : public HtmlElement {
  protected:
  public:
    HPara();
};

class HUList : public HtmlElement {
  protected:
  public:
    HUList();
};

class HOList : public HtmlElement {
  protected:
  public:
   HOList ();
};

class HLiElement : public HtmlElement {
  protected:
  public:
   HLiElement ();
};

class HDefList : public HtmlElement {
  protected:
  public:
   HDefList ();
};

class HDefTerm : public HtmlElement {
  protected:
  public:
   HDefTerm ();
};

class HDefDef : public HtmlElement {
  protected:
  public:
    HDefDef();
};

class HPre : public HtmlElement {
  protected:
  public:
    HPre();
};

class HDiv : public HtmlElement {
  protected:
  public:
   HDiv ();
};

class HCenter : public HtmlElement {
  protected:
  public:
    HCenter();
};

class HBlockQuote : public HtmlElement {
  protected:
  public:
    HBlockQuote();
};

class HForm : public HtmlElement {
  protected:
  public:
    HForm();
};

class HHr : public HtmlElement {
  protected:
  public:
    HHr();
};

class HTable : public HtmlElement {
  protected:
  public:
    HTable();
};

class HCaption : public HtmlElement {
  protected:
  public:
    HCaption();
};

class HTableRow : public HtmlElement {
  protected:
  public:
    HTableRow();
};

class HTableHeader : public HtmlElement {
  protected:
  public:
    HTableHeader();
};

class HTableData : public HtmlElement {
  protected:
  public:
   HTableData ();
};

class HDir : public HtmlElement {
  protected:
  public:
    HDir();
};

class HMenu : public HtmlElement {
  protected:
  public:
    HMenu();
};

class HXmp : public HtmlElement {
  protected:
  public:
    HXmp();
};

class HListing : public HtmlElement {
  protected:
  public:
    HListing();
};

class HPlainText : public HtmlElement {
  protected:
  public:
    HPlainText();
};


#endif		/* _BBLOCKELEMENTS_H_ */

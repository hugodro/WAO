#ifndef _XTN_BBLOCKELEMENTS_H_
#define _XTN_BBLOCKELEMENTS_H_
/**************************************************
* File: bblockElements.h.
* Desc: Definition of the optimized version of the body block elements of HTML 3.2.
* $Date$
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* REV: 2000/11/30 : REV 1 : Hugo DesRosiers : Recoded in Extenta context.
* $Log$
**************************************************/

#include "htElement.h"


class xtnHPara : public xtnHtmlElement {
  protected:
  public:
    xtnHPara();
};

class xtnHUList : public xtnHtmlElement {
  protected:
  public:
    xtnHUList();
};

class xtnHOList : public xtnHtmlElement {
  protected:
  public:
   xtnHOList();
};

class xtnHLiElement : public xtnHtmlElement {
  protected:
  public:
   xtnHLiElement();
};

class xtnHDefList : public xtnHtmlElement {
  protected:
  public:
   xtnHDefList();
};

class xtnHDefTerm : public xtnHtmlElement {
  protected:
  public:
   xtnHDefTerm();
};

class xtnHDefDef : public xtnHtmlElement {
  protected:
  public:
    xtnHDefDef();
};

class xtnHPre : public xtnHtmlElement {
  protected:
  public:
    xtnHPre();
};

class xtnHDiv : public xtnHtmlElement {
  protected:
  public:
   xtnHDiv();
};

class xtnHCenter : public xtnHtmlElement {
  protected:
  public:
    xtnHCenter();
};

class xtnHBlockQuote : public xtnHtmlElement {
  protected:
  public:
    xtnHBlockQuote();
};

class xtnHForm : public xtnHtmlElement {
  protected:
  public:
    xtnHForm();
};

class xtnHHr : public xtnHtmlElement {
  protected:
  public:
    xtnHHr();
};

class xtnHTable : public xtnHtmlElement {
  protected:
  public:
    xtnHTable();
};

class xtnHCaption : public xtnHtmlElement {
  protected:
  public:
    xtnHCaption();
};

class xtnHTableRow : public xtnHtmlElement {
  protected:
  public:
    xtnHTableRow();
};

class xtnHTableHeader : public xtnHtmlElement {
  protected:
  public:
    xtnHTableHeader();
};

class xtnHTableData : public xtnHtmlElement {
  protected:
  public:
   xtnHTableData ();
};

class xtnHDir : public xtnHtmlElement {
  protected:
  public:
    xtnHDir();
};

class xtnHMenu : public xtnHtmlElement {
  protected:
  public:
    xtnHMenu();
};

class xtnHXmp : public xtnHtmlElement {
  protected:
  public:
    xtnHXmp();
};

class xtnHListing : public xtnHtmlElement {
  protected:
  public:
    xtnHListing();
};

class xtnHPlainText : public xtnHtmlElement {
  protected:
  public:
    xtnHPlainText();
};


#endif		/* _XTN_BBLOCKELEMENTS_H_ */

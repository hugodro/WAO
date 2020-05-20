#ifndef _ALL_WML_ELEMENTS_H_
#define _ALL_WML_ELEMENTS_H_
/**************************************************
* File: allWElements.h.
* Desc: Definition of the optimized version of all elements of WML 1.1.
* $Date: 2000/09/20 03:37:34 $
* Rev: 19 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/08/23 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: allWElements.h,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
**************************************************/

#include "wElement.h"


class xtnWAccess : public xtnWmlElement {
  protected:
  public:
    xtnWAccess();
};


class xtnWAnchor : public xtnWmlElement {
  protected:
  public:
    xtnWAnchor();
};


class xtnWAnchorMin : public xtnWmlElement {
  protected:
  public:
    xtnWAnchorMin();
};


class xtnWBig : public xtnWmlElement {
  protected:
  public:
    xtnWBig();
};


class xtnWBold : public xtnWmlElement {
  protected:
  public:
    xtnWBold();
};


class xtnWBreak : public xtnWmlElement {
  protected:
  public:
    xtnWBreak();
};


class xtnWCard : public xtnWmlElement {
  protected:
  public:
    xtnWCard();
};


class xtnWDo : public xtnWmlElement {
  protected:
  public:
    xtnWDo();
};


class xtnWEm : public xtnWmlElement {
  protected:
  public:
    xtnWEm();
};


class xtnWFieldSet : public xtnWmlElement {
  protected:
  public:
    xtnWFieldSet();
};


class xtnWGo : public xtnWmlElement {
  protected:
  public:
    xtnWGo();
};


class xtnWHead : public xtnWmlElement {
  protected:
  public:
    xtnWHead();
};


class xtnWImg : public xtnWmlElement {
  protected:
  public:
    xtnWImg();
};


class xtnWInput : public xtnWmlElement {
  protected:
  public:
    xtnWInput();
};


class xtnWItalic : public xtnWmlElement {
  protected:
  public:
    xtnWItalic();
};


class xtnWMeta : public xtnWmlElement {
  protected:
  public:
    xtnWMeta();
};


class xtnWNoop : public xtnWmlElement {
  protected:
  public:
    xtnWNoop();
};


class xtnWOnEvent : public xtnWmlElement {
  protected:
  public:
    xtnWOnEvent();
};


class xtnWOptGroup : public xtnWmlElement {
  protected:
  public:
    xtnWOptGroup();
};


class xtnWOption : public xtnWmlElement {
  protected:
  public:
    xtnWOption();
};


class xtnWPara : public xtnWmlElement {
  protected:
  public:
    xtnWPara();
};


class xtnWPostField : public xtnWmlElement {
  protected:
  public:
    xtnWPostField();
};


class xtnWPrev : public xtnWmlElement {
  protected:
  public:
    xtnWPrev();
};


class xtnWRefresh : public xtnWmlElement {
  protected:
  public:
    xtnWRefresh();
};


class xtnWSelect : public xtnWmlElement {
  protected:
  public:
    xtnWSelect();
};


class xtnWSetVar : public xtnWmlElement {
  protected:
  public:
    xtnWSetVar();
};


class xtnWSmall : public xtnWmlElement {
  protected:
  public:
    xtnWSmall();
};


class xtnWStrong : public xtnWmlElement {
  protected:
  public:
    xtnWStrong();
};


class xtnWTable : public xtnWmlElement {
  protected:
  public:
    xtnWTable();
};


class xtnWTableData : public xtnWmlElement {
  protected:
  public:
    xtnWTableData();
};


class xtnWTableRow : public xtnWmlElement {
  protected:
  public:
    xtnWTableRow();
};


class xtnWTemplate : public xtnWmlElement {
  protected:
  public:
    xtnWTemplate();
};


class xtnWTimer : public xtnWmlElement {
  protected:
  public:
    xtnWTimer();
};


class xtnWUnderscore : public xtnWmlElement {
  protected:
  public:
    xtnWUnderscore();
};


class xtnWWml : public xtnWmlElement {
  protected:
  public:
    xtnWWml();
};


// ATTN-000124 [HD]: This and the HTML version should be unified and
// implemented as a direct xtnCoreElement subclass.
class xtnWPcData : public xtnWmlElement {
  protected:
    char *data;

  public:
    xtnWPcData();
    virtual ~xtnWPcData();

    void setData(char *someData);

    inline char *getData() { return data; }
};


// ATTN-000124 [HD]: This and CommentElement in topElements.h should be unified and
// implemented as a direct xtnCoreElement subclass.
class xtnWComment : public xtnWmlElement {
  protected:
    char *data;

  public:
    xtnWComment(char *someData);
    virtual ~xtnWComment();

    inline char *getData() { return data; }
};


#endif        /*  _ALL_WML_ELEMENTS_H_ */

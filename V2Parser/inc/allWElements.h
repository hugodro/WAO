#ifndef _ALL_WML_ELEMENTS_H_
#define _ALL_WML_ELEMENTS_H_
/**************************************************
* File: allWElements.h.
* Desc: Definition of the optimized version of all elements of WML 1.1.
* Module: WAO : SgmlParser.
* Rev: 19 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "wmlElement.h"


class WAccess : public WmlElement {
  protected:
  public:
    WAccess(void);
};


class WAnchor : public WmlElement {
  protected:
  public:
    WAnchor(void);
};


class WAnchorMin : public WmlElement {
  protected:
  public:
    WAnchorMin(void);
};


class WBig : public WmlElement {
  protected:
  public:
    WBig(void);
};


class WBold : public WmlElement {
  protected:
  public:
    WBold(void);
};


class WBreak : public WmlElement {
  protected:
  public:
    WBreak(void);
};


class WCard : public WmlElement {
  protected:
  public:
    WCard(void);
};


class WDo : public WmlElement {
  protected:
  public:
    WDo(void);
};


class WEm : public WmlElement {
  protected:
  public:
    WEm(void);
};


class WFieldSet : public WmlElement {
  protected:
  public:
    WFieldSet(void);
};


class WGo : public WmlElement {
  protected:
  public:
    WGo(void);
};


class WHead : public WmlElement {
  protected:
  public:
    WHead(void);
};


class WImg : public WmlElement {
  protected:
  public:
    WImg(void);
};


class WInput : public WmlElement {
  protected:
  public:
    WInput(void);
};


class WItalic : public WmlElement {
  protected:
  public:
    WItalic(void);
};


class WMeta : public WmlElement {
  protected:
  public:
    WMeta(void);
};


class WNoop : public WmlElement {
  protected:
  public:
    WNoop(void);
};


class WOnEvent : public WmlElement {
  protected:
  public:
    WOnEvent(void);
};


class WOptGroup : public WmlElement {
  protected:
  public:
    WOptGroup(void);
};


class WOption : public WmlElement {
  protected:
  public:
    WOption(void);
};


class WPara : public WmlElement {
  protected:
  public:
    WPara(void);
};


class WPostField : public WmlElement {
  protected:
  public:
    WPostField(void);
};


class WPrev : public WmlElement {
  protected:
  public:
    WPrev(void);
};


class WRefresh : public WmlElement {
  protected:
  public:
    WRefresh(void);
};


class WSelect : public WmlElement {
  protected:
  public:
    WSelect(void);
};


class WSetVar : public WmlElement {
  protected:
  public:
    WSetVar(void);
};


class WSmall : public WmlElement {
  protected:
  public:
    WSmall(void);
};


class WStrong : public WmlElement {
  protected:
  public:
    WStrong(void);
};


class WTable : public WmlElement {
  protected:
  public:
    WTable(void);
};


class WTableData : public WmlElement {
  protected:
  public:
    WTableData(void);
};


class WTableRow : public WmlElement {
  protected:
  public:
    WTableRow(void);
};


class WTemplate : public WmlElement {
  protected:
  public:
    WTemplate(void);
};


class WTimer : public WmlElement {
  protected:
  public:
    WTimer(void);
};


class WUnderscore : public WmlElement {
  protected:
  public:
    WUnderscore(void);
};


class WWml : public WmlElement {
  protected:
  public:
    WWml(void);
};


// ATTN-000124 [HD]: This and the HTML version should be unified and
// implemented as a direct SgmlElement subclass.
class WPcData : public WmlElement {
  protected:
    char *data;

  public:
    WPcData(void);
    void setData(char *someData);
};


// ATTN-000124 [HD]: This and CommentElement in topElements.h should be unified and
// implemented as a direct SgmlElement subclass.
class WComment : public WmlElement {
  protected:
    char *data;

  public:
    WComment(char *someData);
    inline char *getData(void) { return data; }
};


#endif        /*  _ALL_WML_ELEMENTS_H_ */

#ifndef _ALL_HDML_ELEMENTS_H_
#define _ALL_HDML_ELEMENTS_H_
/**************************************************
* File: allHdElements.h.
* Desc: Definition of the optimized version of all elements of HDML 2.0.
* Rev: 29 mai 2000 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/09/02 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: allHdElements.h,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1  2000/09/05 07:13:37  hugo
* Initial entry of real parsing/generating HDML support.
*
**************************************************/

#include "hdElement.h"

class xtnHdAction : public xtnHdmlElement {
  protected:
  public:
    xtnHdAction();
};

class xtnHdB : public xtnHdmlElement {
  protected:
  public:
    xtnHdB();
};

class xtnHdBr : public xtnHdmlElement {
  protected:
  public:
    xtnHdBr();
};

class xtnHdCe : public xtnHdmlElement {
  protected:
  public:
    xtnHdCe();
};

class xtnHdCenter : public xtnHdmlElement {
  protected:
  public:
    xtnHdCenter();
};

class xtnHdChoice : public xtnHdmlElement {
  protected:
  public:
    xtnHdChoice();
};

class xtnHdDeck : public xtnHdmlElement {
  protected:
  public:
    xtnHdDeck();
};

class xtnHdDisplay : public xtnHdmlElement {
  protected:
  public:
    xtnHdDisplay();
};

class xtnHdEntry : public xtnHdmlElement {
  protected:
  public:
    xtnHdEntry();
};

class xtnHdI : public xtnHdmlElement {
  protected:
  public:
    xtnHdI();
};

class xtnHdImg : public xtnHdmlElement {
  protected:
  public:
    xtnHdImg();
};

class xtnHdLine : public xtnHdmlElement {
  protected:
  public:
    xtnHdLine();
};

class xtnHdNoDisplay : public xtnHdmlElement {
  protected:
  public:
    xtnHdNoDisplay();
};

class xtnHdRight : public xtnHdmlElement {
  protected:
  public:
    xtnHdRight();
};

class xtnHdTab : public xtnHdmlElement {
  protected:
  public:
    xtnHdTab();
};

class xtnHdWrap : public xtnHdmlElement {
  protected:
  public:
    xtnHdWrap();
};

// ATTN-000124 [HD]: The HTML, WML and this version should be unified and
// implemented as a direct SgmlElement subclass.
class xtnHdPcData : public xtnHdmlElement {
  protected:
    char *data;

  public:
    xtnHdPcData();
    virtual ~xtnHdPcData();

    void setData(char *someData);

    inline char *getData() { return data; }
};


// ATTN-000124 [HD]: This and CommentElement in topElements.h should be unified and
// implemented as a direct SgmlElement subclass.
class xtnHdComment : public xtnHdmlElement {
  protected:
    char *data;

  public:
    xtnHdComment(char *someData);
    virtual ~xtnHdComment();

    inline char *getData() { return data; }
};


#endif        /*  _ALL_HDML_ELEMENTS_H_ */

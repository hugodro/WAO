#ifndef _ALL_HDML_ELEMENTS_H_
#define _ALL_HDML_ELEMENTS_H_
/**************************************************
* File: allWElements.h.
* Desc: Definition of the optimized version of all elements of HDML 2.0.
* Module: WAO : SgmlParser.
* Rev: 29 mai 2000 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "hdmlElement.h"

class HdAction : public HdmlElement {
    protected:
    public:
    HdAction(void);
};

class HdB : public HdmlElement {
    protected:
    public:
    HdB(void);
};

class HdBr : public HdmlElement {
    protected:
    public:
    HdBr(void);
};

class HdCe : public HdmlElement {
    protected:
    public:
    HdCe(void);
};

class HdCenter : public HdmlElement {
    protected:
    public:
    HdCenter(void);
};

class HdChoice : public HdmlElement {
    protected:
    public:
    HdChoice(void);
};

class HdDeck : public HdmlElement {
    protected:
    public:
    HdDeck(void);
};

class HdDisplay : public HdmlElement {
    protected:
    public:
    HdDisplay(void);
};

class HdEntry : public HdmlElement {
    protected:
    public:
    HdEntry(void);
};

class HdI : public HdmlElement {
    protected:
    public:
    HdI(void);
};

class HdImg : public HdmlElement {
    protected:
    public:
    HdImg(void);
};

class HdLine : public HdmlElement {
    protected:
    public:
    HdLine(void);
};

class HdNoDisplay : public HdmlElement {
    protected:
    public:
    HdNoDisplay(void);
};

class HdRight : public HdmlElement {
    protected:
    public:
    HdRight(void);
};

class HdTab : public HdmlElement {
    protected:
    public:
    HdTab(void);
};

class HdWrap : public HdmlElement {
  protected:
  public:
    HdWrap(void);
}

// ATTN-000124 [HD]: The HTML, WML and this version should be unified and
// implemented as a direct SgmlElement subclass.
class HdPcData : public HdmlElement {
  protected:
    char *data;

  public:
    HdPcData(void);
    void setData(char *someData);
};


// ATTN-000124 [HD]: This and CommentElement in topElements.h should be unified and
// implemented as a direct SgmlElement subclass.
class HdComment : public HdmlElement {
  protected:
    char *data;

  public:
    HdComment(char *someData);
    inline char *getData(void) { return data; }
};


#endif        /*  _ALL_HDML_ELEMENTS_H_ */

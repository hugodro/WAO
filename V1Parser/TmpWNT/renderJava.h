#ifndef _RENDERJAVA_H_
#define _RENDERJAVA_H_
/**************************************************
* File: renderJava.h.
* Desc: Definition of the Html-to-Java spit engine.
* Module: WAO : SgmlParser.
* Rev: 24 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include "htmlDTD.h"
#include "sgmlRenderer.h"

class ofstream;


class NameContainer : public AkObject {
    friend class JavaRenderer;
  protected:
    char *name;
    NameContainer *previous;
    unsigned int index;

  public:
    NameContainer(char *aName, NameContainer *parent);
    ~NameContainer(void);
};


class JavaRenderer : public SgmlRenderer {
  protected:
    static char *elementClassName[HtmlDTD::numOfElements+6];

  protected:
    NameContainer *nameStack;
    ostream *outStream;
    unsigned int usage[HtmlDTD::numOfElements+6];
    char *scratchPad;

  public:
    JavaRenderer(ostream *output);
    virtual ~JavaRenderer(void);
    virtual void renderDoc(SgmlDoc *aDoc);
    virtual void renderStartOf(SgmlElement *anElement);
    virtual void renderEndOf(SgmlElement *anElement);
};


#endif	/*  _RENDERJAVA_H_ */

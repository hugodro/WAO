#ifndef _RENDERHTML_H_
#define _RENDERHTML_H_
/**************************************************
* File: renderHtml.h.
* Desc: Definition of the Html-to-Html (!) spit engine.
* Module: WAO : SgmlParser.
* Rev: 24 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include "htmlDTD.h"
#include "sgmlRenderer.h"

class ofstream;


class HtmlRenderer : public SgmlRenderer {
  protected:
    static char *tagNames[HtmlDTD::numOfElements];

  protected:
    ostream *outStream;

  public:
    HtmlRenderer(ostream *output);
    virtual ~HtmlRenderer(void);
    virtual void renderDoc(SgmlDoc *aDoc);
    virtual void renderStartOf(SgmlElement *anElement);
    virtual void renderEndOf(SgmlElement *anElement);
};


#endif	/*  _RENDERHTML_H_ */

#ifndef _RENDERWML_H_
#define _RENDERWML_H_
/**************************************************
* File: renderWml.h.
* Desc: Definition of the Wml-to-Wml (!) spit engine.
* Module: WAO : SgmlParser.
* Rev: 24 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include "wmlDTD.h"
#include "sgmlRenderer.h"

class ofstream;


class WmlRenderer : public SgmlRenderer {
  protected:
    static char *tagNames[WmlDTD::numOfElements];

  protected:
    ostream *outStream;

  public:
    WmlRenderer(ostream *output);
    virtual ~WmlRenderer(void);
    virtual void renderDoc(SgmlDoc *aDoc);
    virtual void renderStartOf(SgmlElement *anElement);
    virtual void renderEndOf(SgmlElement *anElement);
};


#endif	/*  _RENDERWML_H_ */

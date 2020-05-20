#ifndef _XTN_HTML_RENDER_H_
#define _XTN_HTML_RENDER_H_
/**************************************************
* File: htRender.h.
* Desc: Definition of the HTML rendering engine.
* $Date$
* Rev: 2000/09/02 : REV 1 : Hugo DesRosiers : Creation.
* $Log$
**************************************************/

#include <fstream>

#include <exportDefs.h>

#include <coreml/renderer.h>
#include "htDTD.h"

class xtnCoreDoc;

class ClExp xtnHtmlRenderer : public xtnCoreRenderer {
  protected:
    std::ostream *outStream;

  public:
    xtnHtmlRenderer(std::ostream *output);
    virtual ~xtnHtmlRenderer(void);
    virtual void renderDoc(xtnCoreDoc *aDoc);
    virtual void renderStartOf(xtnCoreElement *anElement);
    virtual void renderEndOf(xtnCoreElement *anElement);
};


#endif	/* _XTN_HTML_RENDER_H_ */

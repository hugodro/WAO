#ifndef _XTN_HDML_RENDER_H_
#define _XTN_HDML_RENDER_H_
/**************************************************
* File: wRender.h.
* Desc: Definition of the Hdml rendering engine.
* $Date: 2000/09/20 03:37:34 $
* Rev: 2000/09/02 : REV 1 : Hugo DesRosiers : Creation.
* $Log: hdRender.h,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1  2000/09/05 07:13:37  hugo
* Initial entry of real parsing/generating HDML support.
*
**************************************************/

#include <exportDefs.h>

#if defined(_WIN32)
using std::ostream;
#endif


#include <coreml/renderer.h>
#include "hdDTD.h"

#if !defined(_WIN32)
class ostream;
#endif
class xtnCoreDoc;

class ClExp xtnHdmlRenderer : public xtnCoreRenderer {
  protected:
    static char *tagNames[xtnHdmlDTD::numOfElements];

  protected:
    ostream *outStream;

  public:
    xtnHdmlRenderer(ostream *output);
    virtual ~xtnHdmlRenderer(void);
    virtual void renderDoc(xtnCoreDoc *aDoc);
    virtual void renderStartOf(xtnCoreElement *anElement);
    virtual void renderEndOf(xtnCoreElement *anElement);
};


#endif	/* _XTN_HDML_RENDER_H_ */

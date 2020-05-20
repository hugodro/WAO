#ifndef _XTN_WML_RENDER_H_
#define _XTN_WML_RENDER_H_
/**************************************************
* File: wRender.h.
* Desc: Definition of the Wml rendering engine.
* $Date: 2000/09/20 03:37:34 $
* Rev: 24 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/08/25 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: wRender.h,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
**************************************************/

#include <exportDefs.h>

#include <iostream>

#include <coreml/renderer.h>
#include "wDTD.h"


class xtnCoreDoc;

class ClExp xtnWmlRenderer : public xtnCoreRenderer {
  protected:
    static char *tagNames[xtnWmlDTD::numOfElements];

  protected:
    std::ostream *outStream;

  public:
    xtnWmlRenderer(std::ostream *output);
    virtual ~xtnWmlRenderer(void);
    virtual void renderDoc(xtnCoreDoc *aDoc);
    virtual void renderStartOf(xtnCoreElement *anElement);
    virtual void renderEndOf(xtnCoreElement *anElement);
};


#endif	/* _XTN_WML_RENDER_H_ */

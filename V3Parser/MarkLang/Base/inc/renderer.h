#ifndef _CORE_ML_RENDERER_H_
#define _CORE_ML_RENDERER_H_
/**************************************************
* File: renderer.h.
* Desc: Definition of the generic ML Renderer interface.
* $Date: 2000/09/20 03:37:34 $
* Rev: 24 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/08/22 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log*
**************************************************/

#include <exportDefs.h>

class xtnCoreDoc;
class xtnCoreElement;
class xtnCoreElementList;

class ClExp xtnCoreRenderer {
  public:
    virtual void renderDoc(xtnCoreDoc *aDoc);
    virtual void render(xtnCoreElement *anElement);
    virtual void renderStartOf(xtnCoreElement *anElement);
    virtual void renderElements(xtnCoreElement *anElement, xtnCoreElementList *subElements);
    virtual void renderEndOf(xtnCoreElement *anElement);
};


#endif	/* _CORE_ML_RENDERER_H_ */



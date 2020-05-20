#ifndef _SGMLRENDERER_H_
#define _SGMLRENDERER_H_
/**************************************************
* File: sgmlRenderer.h.
* Desc: Definition of the generic Sgml Renderer interface.
* Module: WAO : SgmlParser.
* Rev: 24 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>

class SgmlDoc;
class SgmlElement;
class SgmlElementList;

class SgmlRenderer : public AkObject {
  public:
    virtual void renderDoc(SgmlDoc *aDoc);
    virtual void render(SgmlElement *anElement);
    virtual void renderStartOf(SgmlElement *anElement);
    virtual void renderElements(SgmlElement *anElement, SgmlElementList *subElements);
    virtual void renderEndOf(SgmlElement *anElement);
};


#endif	/*  _SGMLRENDERER_H_ */


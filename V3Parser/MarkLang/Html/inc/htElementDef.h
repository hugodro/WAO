#ifndef _XTN_HDML_ELEMENT_DEFS_H_
#define _XTN_HDML_ELEMENT_DEFS_H_
/**************************************************
* File: htElementDef.h.
* Desc: Definition of the HTML Element Definition class.
* $Date$
* Rev: 29 mai 2000 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/09/02 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* Rev: 2000/11/30 : REV 2: Hugo DesRosiers : Wrote from Hdml/hdElementDef.h.
* $Log$
**************************************************/

#include <coreml/elementDef.h>
#include <coreml/sgElementDef.h>

#include "htDTD.h"

/************************************
* Class: xtnHtmlElementDef.
* SuperClass: xtnCoreElementDef.
* Desc: Equivalent of an !ELEMENT definition of (our version of)
*          the HTML DTD.
************************************/

class xtnHtmlElementDef : public xtnSgmlElementDef {
    friend class xtnHtmlDTD;

  protected:
    xtnHtmlDTD::HtmlTags tag;

  public:
    xtnHtmlElementDef(char *aName, unsigned int startFlag, unsigned int endFlag);

    virtual bool canInclude(xtnHtmlDTD::HtmlTags aTag);
    inline xtnHtmlDTD::HtmlTags getTag() { return tag; }
};


#endif    /* _XTN_HTML_ELEMENT_DEFS_H_ */

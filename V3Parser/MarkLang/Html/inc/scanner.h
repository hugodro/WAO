#ifndef _AKRA_HTML_SCANNER_H_
#define _AKRA_HTML_SCANNER_H_
/**************************************************
* File: scanner.h.
* Desc: Definition of the HTML scanning engine.
* $Date$
* Rev: 2005/02/03 : REV 1 : Hugo DesRosiers : Creation.
* $Log$
**************************************************/

// TODO: Make it part of a proper CoreScanner < SgScanner hierarchy.

#include "htDTD.h"

class xtnHtmlDoc;

class HtScanner {
 protected:
  xtnHtmlElement *cursor;
  xtnHtmlDoc *document;

 public:
  HtScanner(xtnHtmlDoc *aDoc);
  virtual ~HtScanner();

  virtual xtnHtmlElement *searchFor(xtnHtmlDTD::HtmlTags aTag);
  virtual xtnHtmlElement *searchForAt(xtnHtmlDTD::HtmlTags aTag, xtnHtmlElement *anElement, bool onlyChildren= false);
  virtual xtnHtmlElement *searchForAfter(xtnHtmlDTD::HtmlTags aTag, xtnHtmlElement *anElement, xtnHtmlElement *boundary= NULL);

  void inline reset() { cursor= 0; }
};


#endif

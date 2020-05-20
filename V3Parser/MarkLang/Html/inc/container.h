#ifndef _HTML_ELEMENT_CONTAINER_H_
#define _HTML_ELEMENT_CONTAINER_H_
/*******************************************
* File: container.h.
* Desc: Definition of the HtEleContainer class.
* $Date$
* Rev: 2000/08/23 : REV 1 : Hugo DesRosiers : Creation.
* Rev: 2000/11/30 : REV 2 : Hugo DesRosiers : Updated from Hdml/container.h.
* $Log$
**************************************************/


class xtnHtmlElement;

class xtnHtEleContainer {
  protected:
    xtnHtEleContainer *prev, *next;
    xtnHtmlElement *content;

  public:
    xtnHtEleContainer(xtnHtmlElement *aContent, xtnHtEleContainer *aPred);

    inline xtnHtmlElement *getContent(void) { return content; }
    inline xtnHtEleContainer *getPrevious(void) { return prev; }
    inline xtnHtEleContainer *getNext(void) { return next; }

};

#endif	/* _HTML_ELEMENT_CONTAINER_H_ */

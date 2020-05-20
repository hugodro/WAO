#ifndef _WML_ELEMENT_CONTAINER_H_
#define _WML_ELEMENT_CONTAINER_H_
/*******************************************
* File: container.h.
* Desc: Definition of the WEleContainer class.
* $Date: 2000/09/20 03:37:34 $
* Rev: 25 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/08/23 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: container.h,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
**************************************************/


class xtnWmlElement;

class xtnWEleContainer {
  protected:
    xtnWEleContainer *prev, *next;
    xtnWmlElement *content;

  public:
    xtnWEleContainer(xtnWmlElement *aContent, xtnWEleContainer *aPred);

    inline xtnWmlElement *getContent(void) { return content; }
    inline xtnWEleContainer *getPrevious(void) { return prev; }
    inline xtnWEleContainer *getNext(void) { return next; }

};

#endif	/* _WML_ELEMENT_CONTAINER_H_ */

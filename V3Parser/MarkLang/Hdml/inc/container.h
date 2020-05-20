#ifndef _HDML_ELEMENT_CONTAINER_H_
#define _HDML_ELEMENT_CONTAINER_H_
/*******************************************
* File: container.h.
* Desc: Definition of the HdEleContainer class.
* $Date: 2000/09/20 03:37:34 $
* Rev: 2000/08/23 : REV 1 : Hugo DesRosiers : Creation.
* $Log: container.h,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1  2000/09/05 07:13:37  hugo
* Initial entry of real parsing/generating HDML support.
*
**************************************************/


class xtnHdmlElement;

class xtnHdEleContainer {
  protected:
    xtnHdEleContainer *prev, *next;
    xtnHdmlElement *content;

  public:
    xtnHdEleContainer(xtnHdmlElement *aContent, xtnHdEleContainer *aPred);

    inline xtnHdmlElement *getContent(void) { return content; }
    inline xtnHdEleContainer *getPrevious(void) { return prev; }
    inline xtnHdEleContainer *getNext(void) { return next; }

};

#endif	/* _HDML_ELEMENT_CONTAINER_H_ */

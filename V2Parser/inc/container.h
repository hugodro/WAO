#ifndef _WML_ELEMENT_CONTAINER_H_
#define _WML_ELEMENT_CONTAINER_H_
/*******************************************
* File: container.h.
* Desc: Definition of the WEleContainer class.
* Module: WAO : SgmlParser.
* Rev: 25 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/


#include <akra/AkObject.h>

class WmlElement;

class WEleContainer : public AkObject
{
  protected:
    WEleContainer *prev, *next;
    WmlElement *content;

  public:
    WEleContainer(WmlElement *aContent, WEleContainer *aPred);

    inline WmlElement *getContent(void) { return content; }
    inline WEleContainer *getPrevious(void) { return prev; }
    inline WEleContainer *getNext(void) { return next; }

};

#endif	/* _WML_ELEMENT_CONTAINER_H_ */

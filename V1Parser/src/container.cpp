/*******************************************
* File: container.cpp.
* Desc: Implementation of the WEleContainer class.
* Module: WAO : SgmlParser.
* Rev: 25 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/


#include "container.h"

#if !defined(NULL)
#define	NULL	(0L)
#endif


WEleContainer::WEleContainer(WmlElement *aContent, WEleContainer *aPred)
{
    content= aContent;
    if (aPred != NULL) aPred->next= this;
    prev= aPred;
    next= NULL;
}



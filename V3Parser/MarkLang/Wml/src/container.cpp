/*******************************************
* File: container.cpp.
* Desc: Implementation of the WEleContainer class.
* $Date: 2000/09/20 03:37:34 $
* Rev: 25 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/08/24 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: container.cpp,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
**************************************************/

#include <globDefs.h>
#include "container.h"

xtnWEleContainer::xtnWEleContainer(xtnWmlElement *aContent, xtnWEleContainer *aPred)
{
    prev= aPred;
    if (prev != NULL) prev->next= this;
    next= NULL;
    content= aContent;
}


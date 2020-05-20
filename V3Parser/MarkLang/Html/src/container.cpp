/*******************************************
* File: container.cpp.
* Desc: Implementation of the HtEleContainer class.
* $Date$
* Rev: 2000/09/03 : REV 1 : Hugo DesRosiers : Creation.
* Rev: 2000/11/30 : REV 2 : Hugo DesRosiers : Updated from Hdml/container.cpp.
* $Log$
**************************************************/

#include <globDefs.h>

#include "container.h"


// TODO-000903 [HD]: Merge with WML version and put in the Base library.

xtnHtEleContainer::xtnHtEleContainer(xtnHtmlElement *aContent, xtnHtEleContainer *aPred)
{
    prev= aPred;
    if (prev != NULL) prev->next= this;
    next= NULL;
    content= aContent;
}


/*******************************************
* File: container.cpp.
* Desc: Implementation of the HdEleContainer class.
* $Date: 2000/09/20 03:37:34 $
* Rev: 2000/09/03 : REV 1 : Hugo DesRosiers : Creation.
* $Log: container.cpp,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1  2000/09/05 07:13:40  hugo
* Initial entry of real parsing/generating HDML support.
*
**************************************************/

#include <globDefs.h>

#include "container.h"


// TODO-000903 [HD]: Merge with WML version and put in the Base library.

xtnHdEleContainer::xtnHdEleContainer(xtnHdmlElement *aContent, xtnHdEleContainer *aPred)
{
    prev= aPred;
    if (prev != NULL) prev->next= this;
    next= NULL;
    content= aContent;
}


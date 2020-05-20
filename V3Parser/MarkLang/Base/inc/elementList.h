#ifndef _XTN_CORE_ELEMENT_LIST_H_
#define _XTN_CORE_ELEMENT_LIST_H_
/**************************************************
* File: elementList.h.
* Desc: Definition of the xtnCoreElementList class.
* Rev: 22 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/08/22 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: elementList.h,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1.1.1  2000/09/01 07:33:30  hugo
* Initial Entry
*
**************************************************/

#include <exportDefs.h>

#include "lists.h"

class xtnCoreElement;
class xtnCoreAttribute;

class ClExp xtnCoreElementList : public xtnGenericList {
  protected:
  public:
    virtual bool addObject(xtnCoreElement *object);
    virtual xtnCoreElement *objectAt(unsigned int position);
 };


class ClExp xtnCoreAttributeList : public xtnGenericList {
  protected:
  public:
    xtnCoreAttributeList(unsigned int initSize);
    virtual bool addObject(xtnCoreAttribute *object);
    virtual xtnCoreAttribute *objectAt(unsigned int position);
 };



#endif		/* _SGML_ELEMENT_LIST_H_ */

#ifndef _SGML_ELEMENT_LIST_H_
#define _SGML_ELEMENT_LIST_H_
/**************************************************
* File: elementList.h.
* Desc: Definition of the SgmlElementList class.
* Module: WAO : SgmlParser.
* Rev: 22 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "lists.h"

class SgmlElement;
class SgmlAttribute;

class SgmlElementList : public GenericList {
  protected:
  public:
    virtual boolean addObject(SgmlElement *object);
    virtual SgmlElement *objectAt(unsigned int position);
 };


class SgmlAttributeList : public GenericList {
  protected:
  public:
    SgmlAttributeList(unsigned int initSize);
    virtual boolean addObject(SgmlAttribute *object);
    virtual SgmlAttribute *objectAt(unsigned int position);
 };



#endif		/* _SGML_ELEMENT_LIST_H_ */

#ifndef _LIBRARIAN_DATA_OBJECT_H_
#define _LIBRARIAN_DATA_OBJECT_H_
/**************************************************
* File: dbObject.h.
* Desc: Definition of the basic db persistant object model.
* Module: AkraLog : WAO.
* Rev: 8 decembre 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>

class WAssociationTable;
class WDataEngine;


class DataObject : public AkObject {
  protected:
  public:
    virtual void cloneFromDB(WAssociationTable *assocTable, WDataEngine *anEngine, void *data)= 0;
};


class ArrayDO : public AkObject {
  protected:
    unsigned int nbrInside;
    unsigned int arraySize;
    void **values;

  public:
    ArrayDO(void);
    ArrayDO(unsigned int aSize);
    ~ArrayDO(void);
    void addObject(void *anObject);
    void *objectAt(unsigned int aPos);
    unsigned int count(void);
};


#endif		/* _LIBRARIAN_DATA_OBJECT_H_ */

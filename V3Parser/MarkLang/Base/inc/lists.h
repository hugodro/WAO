#ifndef _XTN_GENERIC_LISTS_H_
#define _XTN_GENERIC_LISTS_H_
/**************************************************
* File: lists.h.
* Desc: Contains the definitions of the different lists used in the
*    parsing process.
* $Date: 2000/09/20 03:37:34 $
* Rev: 4 juin 1996 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 6 mars 1997 : REV 0.1 : Hugo DesRosiers: MOD-MSC: ajoute 'public' a toutes les derivations de Generic.
* Rev: 2000/08/22 : REV 1: Hugo DesRosiers : Rewrote within Extenta context.
* $Log: lists.h,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1.1.1  2000/09/01 07:33:30  hugo
* Initial Entry
*
**************************************************/

#include <exportDefs.h>

class ClExp xtnGenericList {
  protected:
    unsigned int nbrElements;
    unsigned int maxElements;
    void **elements;

  public:
    xtnGenericList(unsigned int initSize);
    xtnGenericList(void);
    virtual ~xtnGenericList(void);

    virtual void init(unsigned int initSize);
    virtual unsigned int count(void);
    virtual bool addObject(void *object);
    virtual bool removeObject(void *object);
    virtual bool removeObjectAt(unsigned int position);
    virtual bool removeLastObject(void);
    virtual void *voidObjectAt(unsigned int position);
    virtual void *lastObject(void);
    virtual void removeAll(void);
 };


#endif		/* _XTN_GENERIC_LISTS_H_ */

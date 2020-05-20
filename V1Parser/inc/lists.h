#ifndef _LISTS_H_
#define _LISTS_H_
/**************************************************
* File: lists.h.
* Desc: Contains the definitions of the different lists used in the compilation process.
* Module: AkraLog : JavaComp.
* Rev: 4 juin 1996 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 6 mars 1997 : REV 0.1 : Hugo DesRosiers: MOD-MSC: ajoute 'public' a toutes les derivations de Generic.
**************************************************/

// ATTENTION: Extract of the real file.


#include <akra/AkObject.h>
#include <akra/portableDefs.h>

class GenericList : public AkObject {
  protected:
    unsigned int nbrElements;
    unsigned int maxElements;
    void **elements;

  public:
    GenericList(unsigned int initSize);
    GenericList(void);
    virtual ~GenericList(void);

    virtual void init(unsigned int initSize);
    virtual unsigned int count(void);
    virtual boolean addObject(void *object);
    virtual boolean removeObject(void *object);
    virtual boolean removeObjectAt(unsigned int position);
    virtual boolean removeLastObject(void);
    virtual void *voidObjectAt(unsigned int position);
    virtual void *lastObject(void);
    virtual void removeAll(void);
 };


#endif		/* _LISTS_H_ */

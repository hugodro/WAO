#ifndef _WAOLINK_H_
#define _WAOLINK_H_
/**************************************************
* File: waoLink.h.
* Desc: Definition of the WaoLink class.
* Module: Wao : ApacheSupport.
* Rev: 26 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include <akra/portableDefs.h>


class JVMachine;
class ClassFile;
class JVInstance;
class JVVariable;
struct request_rec;

class WaoLink : public AkObject {
  protected:	// Class variables.
    static JVVariable *dualField;
    static boolean mustFetchDict;

  public:	// Class methods.
    static boolean fetchDictionary(JVMachine *aMachine, ClassFile *aClass);

  protected:	// Instance variables.
    JVInstance *javaEquiv;
    request_rec *requestContext;

  public:		// Instance methods.
    WaoLink(JVInstance *anInstance, JVMachine *aMachine);
    virtual void setRequestContext(request_rec *r);
    virtual void defineHeader(char *aString);
    virtual void puts(char *aString);

    JVInstance *get_this(void);
    void set_dual(void *thisValue);
    WaoLink *get_dual(void);
};


#endif	/* _WAOLINK_H_ */

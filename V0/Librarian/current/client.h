#ifndef _LIBRARIANCLIENT_H_
#define _LIBRARIANCLIENT_H_
/**************************************************
* File: client.h.
* Desc: Definition of the WClient class.
* Module: WAO : Librarian.
* Rev: 26 juin 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include <akra/portableDefs.h>

class WClient : public AkObject {
  protected:	// Instance variables.
    unsigned int type;

  public:		// Instance methods.
};


#endif		/* _LIBRARIANCLIENT_H_ */

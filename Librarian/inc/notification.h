#ifndef _NOTIFICATION_PORT_H_
#define _NOTIFICATION_PORT_H_
/**************************************************
* File: notification.h.
* Desc: Definition of the AkNotificationPort class.
* Module: AkraLog : WAO.
* Rev: 24 juin 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include <akra/portableDefs.h>

class AkCommCenter;


class AkNotificationPort : public AkObject {
  public:
    enum Situations {
	newClient, msgReceived, msgSent,
	channelClosed, mapFull
    };

  protected:	// Instance variables.
    AkNotificationPort *next;

  public:		// Instance methods.
    AkNotificationPort(void);
    virtual ~AkNotificationPort(void);
    void linkTo(AkNotificationPort *aPort);
    AkNotificationPort *getNext(void);
    virtual bool wants(AkNotificationPort::Situations aSituation);
    virtual bool beNotifiedOf(AkCommCenter *sender, AkNotificationPort::Situations aSituation, void *argument);
};


#endif		/* _NOTIFICATION_PORT_H_ */
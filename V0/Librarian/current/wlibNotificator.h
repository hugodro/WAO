#ifndef _LIBRARIAN_NOTIFICATOR_H_
#define _LIBRARIAN_NOTIFICATOR_H_
/**************************************************
* File: wlibNotificator.h.
* Desc: Definition of the WLibNotificator class.
* Module: AkraLog : WAO.
* Rev: 25 juin 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "notification.h"

class WaoLibrarian;
class AkCommCenter;
class AkMessage;
class AkRequest;


class WIncomingNotificator : public AkNotificationPort  {
  protected:	// Instance variables.
    WaoLibrarian *owner;
    AkNotificationPort *msgsPort;

  public:		// Instance methods.
    WIncomingNotificator(WaoLibrarian *theOwner);
    virtual ~WIncomingNotificator(void);
    virtual bool wants(AkNotificationPort::Situations aSituation);
    virtual bool beNotifiedOf(AkCommCenter *sender, AkNotificationPort::Situations aSituation, void *argument);
    virtual void setMessagePort(AkNotificationPort *aPort);
};


class WPeerNotificator : public AkNotificationPort  {
  protected:	// Instance variables.
    WaoLibrarian *owner;

  public:		// Instance methods.
    WPeerNotificator(WaoLibrarian *theOwner);
    virtual ~WPeerNotificator(void);
    virtual bool wants(AkNotificationPort::Situations aSituation);
    virtual bool beNotifiedOf(AkCommCenter *sender, AkNotificationPort::Situations aSituation, void *argument);
    virtual AkRequest *buildRequestFrom(AkMessage *aMessage);
};


#endif		/* _LIBRARIAN_NOTIFICATOR_H_ */
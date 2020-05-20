/**************************************************
* File: notification.cc.
* Desc: Implementation of the AkNotificationPort class.
* Module: AkraLog : WAO.
* Rev: 24 juin 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "notification.h"


AkNotificationPort::AkNotificationPort(void)
{
    next= NULL;
}


AkNotificationPort::~AkNotificationPort(void)
{
// TODO.
}


void AkNotificationPort::linkTo(AkNotificationPort *aPort)
{
    next= aPort;
}


AkNotificationPort *AkNotificationPort::getNext(void)
{
    return next;
}


bool AkNotificationPort::wants(AkNotificationPort::Situations aSituation)
{
	// By default, a notification port is not interested in anything.
	// NOTE-980625 [HD]: Maybe this should be an abstract method.
    return false;
}


bool AkNotificationPort::beNotifiedOf(AkCommCenter *sender, AkNotificationPort::Situations aSituation, void *argument)
{
    // By default, a notification port does nothing with a notification.
    // NOTE-980625 [HD]: Maybe this should be an abstract method.
    return false;
}


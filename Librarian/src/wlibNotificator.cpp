/**************************************************
* File: wlibNotificator.cc.
* Desc: Implementation of the WIncomingNotificator class.
* Module: AkraLog : WAO.
* Rev: 25 juin 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "socketChannel.h"
#include "commCenter.h"
#include "librarian.h"
#include "wlibNotificator.h"

WIncomingNotificator::WIncomingNotificator(WaoLibrarian *theOwner)
{
    owner= theOwner;
}


WIncomingNotificator::~WIncomingNotificator(void)
{
// TODO.
}


bool WIncomingNotificator::wants(AkNotificationPort::Situations aSituation)
{
    switch(aSituation) {
	case newClient:
	    return true;
	default:
	    return false;
    }
}


bool WIncomingNotificator::beNotifiedOf(AkCommCenter *sender, AkNotificationPort::Situations aSituation, void *argument)
{
    unsigned int channelID;
    bool result= false;

    switch(aSituation) {
	case newClient:
	    channelID= ((AkSocketChannel *)argument)->getPrivateID();
	    sender->assignNotificationPort(channelID, msgsPort);
	    result= owner->addClient(channelID);
	    break;
	case msgReceived:
	    break;
	default:
	    break;
    }

    return result;
}

void WIncomingNotificator::setMessagePort(AkNotificationPort *aPort)
{
    msgsPort= aPort;
}


/**************************************************
* Implementation: WPeerNotificator.
**************************************************/


WPeerNotificator::WPeerNotificator(WaoLibrarian *theOwner)
{
    owner= theOwner;
}


WPeerNotificator::~WPeerNotificator(void)
{
// TODO.
}


bool WPeerNotificator::wants(AkNotificationPort::Situations aSituation)
{
    switch(aSituation) {
	case newClient:
	case msgReceived:
	    return true;
	default:
	    return false;
    }
}


bool WPeerNotificator::beNotifiedOf(AkCommCenter *sender, AkNotificationPort::Situations aSituation, void *argument)
{
    AkSocketChannel *channel;
    AkMessage *message;
    AkRequest *newRequest;
    unsigned int channelID;
    bool result= false;

    switch(aSituation) {
	case msgReceived:
	    channel= (AkSocketChannel *)argument;
	    message= channel->fetchMessage();
	    while (message != NULL) {
		if ((newRequest= buildRequestFrom(message)) != NULL) {
		    owner->addClientRequest(channel->getPrivateID(), newRequest);
		}
		channel->releaseMessage(message);
		message= channel->fetchMessage();
	    }
	    result= true;
	    break;
	case channelClosed:
	    channelID= ((AkSocketChannel *)argument)->getPrivateID();
	    result= owner->removeClient(channelID);
	    break;
	default:
	    break;
    }

    return result;
}


AkRequest *WPeerNotificator::buildRequestFrom(AkMessage *aMessage)
{
// TODO: Compose a request from a given message.
    return NULL;		// TMPTMP.
}



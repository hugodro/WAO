/**************************************************
* File: commCenter.cc.
* Desc: Implementation of the AkCommCenter class.
* Module: AkraLog : WAO.
* Rev: 24 juin 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

// DEBUG:
#include <iostream.h>

#if defined(_WIN32)
#include <sys/types.h>
#include <winsock.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/errno.h>
#if !defined(__linux__)
#include <libc.h>
#endif
#if defined(__linux__)
#include <string.h>
#include <stdio.h>			// For perror.
#endif
#endif
#include "socketChannel.h"
#include "notification.h"
#include "message.h"
#include "commCenter.h"


/**************************************************
* Implementation: AkCommCenter.
**************************************************/

AkMessage *AkCommCenter::newMessage(void)
{
    return new AkMessage();		// TMPTMP !
}


void AkCommCenter::releaseMessage(AkMessage *aMessage)
{
    delete aMessage;			// TMPTMP.
}


AkCommCenter::AkCommCenter(void)
{
    inPorts= NULL;
    nbrInPorts= 0;
    peeredPorts= NULL;
    nbrPeeredPorts= 0;
    delegates= new AkNotificationPort *[channelMapSize << 5];
    channelMap= new unsigned int[channelMapSize];
    memset(channelMap, 0, sizeof(unsigned int) * channelMapSize);
    FD_ZERO((&selectors[0]));
    FD_ZERO((&selectors[1]));
    maxSockID= 0;
    runningModal= false;
}


AkCommCenter::~AkCommCenter(void)
{
    if (nbrPeeredPorts > 0) {
	AkSocketChannel *nextChannel;

	while (peeredPorts != NULL) {
	    nextChannel= peeredPorts->getNext();
	    delete peeredPorts;
	    peeredPorts= nextChannel;
	}
    }
    if (nbrInPorts > 0) {
	AkSocketChannel *nextChannel;

	while (inPorts != NULL) {
	    nextChannel= inPorts->getNext();
	    delete inPorts;
	    inPorts= nextChannel;
	}
    }
}


bool AkCommCenter::addListenPort(int port, AkNotificationPort *notifier)
{
    AkSocketChannel *newChannel;

	// Test first if the channel table is full.
    if ((nbrInPorts + nbrPeeredPorts) == (channelMapSize << 5)) {
	return false;		// Warning: quick exit.
    }

    newChannel= new AkSocketChannel();
    newChannel->setNonBlocking();
    newChannel->connectToOperator(port, 5);

    if (newChannel->isConnected()) {
	int tmpID;

	newChannel->linkTo(inPorts);
	inPorts= newChannel;
	nbrInPorts++;

	    // Warning: assignMapIndex can return 0x0FFFF is no place in table.
	    // It is assumed that the entry test is a garantee of the consistency of the table !
	tmpID= assignMapIndex();
	newChannel->setPrivateID(tmpID);
	delegates[tmpID]= notifier;

	tmpID= newChannel->getSystemID();
	FD_SET(tmpID, (&selectors[0]));
	if (tmpID > maxSockID) maxSockID= tmpID;
	return true;
    }
    else {
	delete newChannel;
	return false;
    }
}


int AkCommCenter::addConnectionTo(char *host, int port, AkNotificationPort *notifier)
{
    AkSocketChannel *newChannel;

	// Test first if the channel table is full.
    if ((nbrInPorts + nbrPeeredPorts) == (channelMapSize << 5)) {
	return false;		// Warning: quick exit.
    }

    newChannel= new AkSocketChannel(host, port, 5);

    if (newChannel->isConnected()) {
	int tmpID;

	newChannel->setNonBlocking();
	newChannel->linkTo(peeredPorts);
	peeredPorts= newChannel;
	nbrPeeredPorts++;
	    // Warning: assignMapIndex can return 0x0FFFF is no place in table.
	    // It is assumed that the entry test is a garantee of the consistency of the table !
	tmpID= assignMapIndex();
	newChannel->setPrivateID(tmpID);
	delegates[tmpID]= notifier;

	tmpID= newChannel->getSystemID();
	FD_SET(tmpID, (&selectors[0]));
	if (tmpID > maxSockID) maxSockID= tmpID;
	return tmpID;
    }
    else {
	delete newChannel;
	return -1;
    }
}


void AkCommCenter::runModal(void)
{
    AkSocketChannel *sockCursor, *newcommers, *firstCommer;
    AkSocketChannel *tmpSock, *deathList;
    struct timeval timeout;
    fd_set indic[3], *inIndicators, *outIndicators, *otherIndicators;
    int signalCount;
    unsigned int nbrNewCommers;

// TODO: Run modal loop, accepting new connection, receiving and sending messages on existing one.
    inIndicators= &indic[0];
    outIndicators= &indic[1];
    otherIndicators= &indic[2];

    runningModal= true;		// Controlled externally.

    deathList= firstCommer= newcommers= NULL;
    nbrNewCommers= 0;
    while (runningModal) {
	memcpy(inIndicators, &selectors[0], sizeof(fd_set));
	memcpy(outIndicators, &selectors[1], sizeof(fd_set));

	    // Set timeout every time, since it might be modified by the select call.
	timeout.tv_sec= 3600;		// We look around every hour.
	timeout.tv_usec= 0;

	signalCount= select(maxSockID+1, inIndicators, outIndicators, NULL, &timeout);
	if (signalCount > 0) {
	    if (nbrInPorts > 0) {
		sockCursor= inPorts;
		while (sockCursor != NULL) {
		    if (FD_ISSET(sockCursor->getSystemID(), inIndicators)) {
			struct sockaddr visitorAddress;
			int sockID;
			unsigned int addrLng= sizeof(visitorAddress);

			// Must create a new connection.
			sockID= accept(sockCursor->getSystemID(), (struct sockaddr *)&visitorAddress, &addrLng);
			if (sockID > -1) {
			    AkNotificationPort *delegate;
			    AkSocketChannel *newChannel;
			    unsigned short tmpID;

			    delegate= delegates[sockCursor->getPrivateID()];
			    if ((tmpID= assignMapIndex()) != 0x0FFFF) {
				newChannel= new AkSocketChannel(sockID);
				newChannel->setPrivateID(tmpID);
				if (delegate != NULL) {
				    if (delegate->beNotifiedOf(this, AkNotificationPort::newClient, newChannel)) {
					if (firstCommer == NULL) firstCommer= newChannel;
					newChannel->linkTo(newcommers);
					newcommers= newChannel;
					nbrNewCommers++;
				    }
				    else {
					    // New client is refused.
					releaseMapIndex(tmpID);
					delete newChannel;
				    }
				}
				else {
					// No delegate means no entry accepted yet on that port.
				    releaseMapIndex(tmpID);
				    delete newChannel;
				}
			    }
			    else {	// Channel map table is full.
				if (delegate != NULL) {
				    delegate->beNotifiedOf(this, AkNotificationPort::mapFull, sockCursor);
				}
			    }
			}
			else {
			    int errorCode;
			    extern int h_errno;
				// Error.
			    errorCode= AkSocketChannel::getSysErrorCode();
			    cout << "Error: " << errorCode << ", " << h_errno << "\n";
			    perror(NULL);
			}
			signalCount--;
		    }
		    sockCursor= sockCursor->getNext();
		}
	    }
		// Take care of the 'out' queue.
	    if (nbrPeeredPorts > 0) {
		sockCursor= peeredPorts;
		while (sockCursor != NULL) {
		    if (FD_ISSET(sockCursor->getSystemID(), inIndicators)) {
			AkNotificationPort *delegate;
			AkSocketChannel *newChannel;
			int status;

			status= sockCursor->getNewMsg();
			if ((delegate= delegates[sockCursor->getPrivateID()]) != NULL) {
			    switch(status) {
				case -2:
				    // TODO: Got a weird error.
				    break;
				case -1:
				    // TODO: Got a 'msg too big' error.
				    break;
				case 0:
				    if (!delegate->beNotifiedOf(this, AkNotificationPort::msgReceived, sockCursor)) {
					// TODO: Handle the refusal of a msgReceived request.
				    }
				    break;
				case 1:
				    delegate->beNotifiedOf(this, AkNotificationPort::channelClosed, sockCursor);
				    tmpSock= sockCursor;
				    if (sockCursor == peeredPorts) {
					if ((peeredPorts= sockCursor->getNext()) != NULL) {
					    peeredPorts->resetPrev();
					}
					sockCursor= peeredPorts;
				    }
				    else {
					sockCursor= sockCursor->getNext();
					tmpSock->getPrev()->linkTo(sockCursor);
				    }
				    tmpSock->linkTo(deathList);
				    deathList= tmpSock;
				    nbrPeeredPorts--;
				    break;
			    }
			    if (status == 1) continue;	// Warning: short-circuit is caused by socket death.
			}
			else {	// No delegate to handle the socket, that is very annoying.
			    switch(status) {
				case 0:
				case 1:
				    // TODO: Put the socket on the death list.
				    break;
			    }
			}
			signalCount--;
		    }
			// Attn: this may not happen, when a socket death occurs (the loop is short-circuited).
		    sockCursor= sockCursor->getNext();
		}
	    }
		// Link the new channels to the 'out' queue.
	    if (newcommers != NULL) {
		firstCommer->linkTo(peeredPorts);
		peeredPorts= newcommers;
		nbrPeeredPorts+= nbrNewCommers;
		firstCommer= newcommers= NULL;
		nbrNewCommers= 0;
		recalcMaxID();
	    }
	}
	else {
#if defined(__linux__)
	    signalCount= errno;  // Linux returns -1 on select, and error in errno.
#endif
	    if (signalCount == EINTR) {	// Select was interrupted.
		// TODO.
	    }
	}

	    // Last stage: the death list is emptied.
	if (deathList != NULL) {
	     do {
		tmpSock= deathList->getNext();
		releaseMapIndex(deathList->getPrivateID());
		delete deathList;
		deathList= tmpSock;
	    } while (deathList != NULL);
	    recalcMaxID();
	}
    }

}


bool AkCommCenter::sendMessage(AkMessage *aMessage)
{
// TODO: Add the message for delivery.
    return false;
}


void AkCommCenter::assignNotificationPort(unsigned short aChannel, AkNotificationPort *aPort)
{
    delegates[aChannel]= aPort;
}


void AkCommCenter::shutdown(void)
{
    runningModal= false;
}


void AkCommCenter::recalcMaxID(void)
{
    AkSocketChannel *tmpChannel;
    int tmpID;

    maxSockID= 0;
    FD_ZERO((&selectors[0]));
    FD_ZERO((&selectors[1]));

    if (nbrInPorts > 0) {
	tmpChannel= inPorts;
	while (tmpChannel != NULL) {
	    tmpID= tmpChannel->getSystemID();
	    FD_SET(tmpID, (&selectors[0]));
	    if (tmpID > maxSockID) maxSockID= tmpID;
	    tmpChannel= tmpChannel->getNext();
	}
    }
    if (nbrPeeredPorts > 0) {
	tmpChannel= peeredPorts;
	while (tmpChannel != NULL) {
	    tmpID= tmpChannel->getSystemID();
	    FD_SET(tmpID, (&selectors[0]));
// TODO: Decide when to use: FD_SET(tmpID, (&selectors[1]));
	    if (tmpID > maxSockID) maxSockID= tmpID;
	    tmpChannel= tmpChannel->getNext();
	}
    }
}


unsigned short AkCommCenter::assignMapIndex(void)
{
    unsigned int *cursor= channelMap;
    unsigned short index= 0x0FFFF;		// Return 0x0FFFF if no entry found.

    // Warning: this expects 'unsigned int' type to be 32 bits wide.
    do {
	if (*cursor != 0x0FFFFFFFF) {	// Browse for a whole.
	    unsigned int i= 0;

	    if ((*cursor & 0x0FFFF) != 0x0FFFF) {	// Look at low word.
		if ((*cursor & 0x0FF) != 0xFF) {	// Look at low byte.
		    for (; i < 8; i++) {
			if ((*cursor & (1 << i)) == 0) {
			    index= i;
			    break;
			}
		    }
		}
		else {		// Look at high byte.
		    for (; i < 8; i++) {
			if ((*cursor & (0x0100 << i)) == 0) {
			    index= 8 + i;
			    break;
			}
		    }
		}
	    }
	    else {		// Look at high word.
		if ((*cursor & 0x000FF0000) != 0x00FF0000) {	// Look at low byte.
		    for (; i < 8; i++) {
			if ((*cursor & (0x010000 << i)) == 0) {
			    index= 16 + i;
			    break;
			}
		    }		    
		}
		else {	// Look at high byte.
		    for (; i < 8; i++) {
			if ((*cursor & (0x01000000 << i)) == 0) {
			    index= 24 + i;
			    break;
			}
		    }		    
		}
	    }

		// Found a whole, add the cursor offset and get out of the scan loop.
	    *cursor|= (1 << index);		// Lock the bit.
	    index+= (cursor - channelMap) << 5;
	    break;
	}
	cursor++;
    } while (cursor < channelMap + (channelMapSize << 5));

    return index;
}


void AkCommCenter::releaseMapIndex(unsigned short anIndex)
{
    unsigned int tmpDisp= anIndex >> 5;
    if (tmpDisp < channelMapSize) {
	channelMap[tmpDisp]&= ~(1 << (anIndex % 32));
    }
}



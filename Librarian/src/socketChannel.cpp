/**************************************************
* File: socketChannel.cc.
* Desc: Implementation of the AkSocketPort class (and tempo. AkCommPort).
* Module: AkraLog : WAO.
* Rev: 24 juin 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#if defined(_WIN32)
#include <sys/types.h>
#include <winsock.h>
#include <io.h>		// ATTN: Using old style of 'io' include.
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#if !defined(__linux__)
#include <libc.h>
#endif
#include <sys/time.h>
#if defined(__linux__)
#include <unistd.h>
#endif
#endif
#include <memory.h>
#include <fcntl.h>
#include "message.h"
#include "commCenter.h"
#include "socketChannel.h"


/**************************************************
* Implementation: AkSocketChannel.
**************************************************/

void AkSocketChannel::socketSleep(unsigned int milliSecs)
{
    struct timeval timeout;

    timeout.tv_sec= milliSecs / 1000;
    timeout.tv_usec= (milliSecs % 1000) * 1000 ;

    select(0, 0, 0, 0, &timeout);
}


int AkSocketChannel::getSysErrorCode(void)
{
#if defined(NeXT)
    return cthread_errno();
#elif defined(_WIN32)
    return WSAGetLastError();
#else
    return h_errno;
#endif
}


AkSocketChannel::AkSocketChannel(void)
{
    prev= next= NULL;
    socketFD= socket(PF_INET, SOCK_STREAM, 0);
    flags= noConnection;
    privateID= 0;
    readSoFar= 0;
    currentMessage= msgsHead= msgsTail= NULL;
}


AkSocketChannel::AkSocketChannel(int aSocketID)
{
    prev= next= NULL;
    socketFD= aSocketID;
    flags= connected;	// Assume that it is connected.
    privateID= 0;
    readSoFar= 0;
    currentMessage= msgsHead= msgsTail= NULL;
}


AkSocketChannel::AkSocketChannel(char *hostName, int port, unsigned int nbrRetries)
{
    prev= next= NULL;
    flags= noConnection;
    if ((socketFD= socket(PF_INET, SOCK_STREAM, 0)) > -1) {
	connectToHost(hostName, port, nbrRetries);
    }
    privateID= 0;
    readSoFar= 0;
    currentMessage= msgsHead= msgsTail= NULL;
}


AkSocketChannel::~AkSocketChannel(void)
{
    if ((flags & connected) != 0) {
	close(socketFD);
    }
}


void AkSocketChannel::linkTo(AkSocketChannel *aChannel)
{
    next= aChannel;
    if (aChannel != NULL) aChannel->prev= this;
}


AkSocketChannel *AkSocketChannel::getNext(void)
{
    return next;
}


AkSocketChannel *AkSocketChannel::getPrev(void)
{
    return prev;
}


void AkSocketChannel::resetPrev(void)
{
    prev= NULL;
}


bool AkSocketChannel::isConnected(void)
{
    return ((flags & connected) != 0);
}


bool AkSocketChannel::connectToHost(char *hostName, int port, unsigned int nbrRetries)
{
    struct sockaddr_in destination;
    struct hostent *hostInfo= NULL;


    if (socketFD > -1) {
	int errorCode= 0;

	if (hostName == NULL) {
	    destination.sin_family= AF_INET;
	    destination.sin_port= htons(port);
#if defined(NeXT)
	    destination.sin_addr.S_un.S_addr= INADDR_ANY;
#else
	    destination.sin_addr.s_addr= INADDR_ANY;
#endif
	}
	else {
	    flags= (Flags)(flags | refused);	// Expect the worst.
	    for (unsigned int i= 0; i < nbrRetries; i++) {
		if ((hostInfo= gethostbyname(hostName)) == NULL) {
		    if (getSysErrorCode() != TRY_AGAIN) {
			break;
		    }
		}
		else {
		    flags= (Flags)(flags & ~refused);
		    break;
		}
		socketSleep(200);	// Give some time before retrying.
	    }
	    if ((flags & refused) == 0) {
		memset(&destination, 0, sizeof(destination));
		memcpy(&destination.sin_addr, hostInfo->h_addr, hostInfo->h_length);
		destination.sin_family= hostInfo->h_addrtype;
		destination.sin_port= htons(port);
	    }
	    else return false;		// Warning: quick exit.
	}
	if (connect(socketFD, (struct sockaddr *)&destination, sizeof(destination)) != 0) {
	    flags= (Flags)(flags | refused);
	}
	else {
	    flags= (Flags)(flags | connected);
	    return true;		// Warning: quick exit.
	}
    }

    return false;		// If we get here, the connection didn't succeed.
}


bool AkSocketChannel::connectToOperator(int port, unsigned int queueLength)
{
    struct sockaddr_in address;
    int errorCode;

    address.sin_family= AF_INET;
    address.sin_port= htons(port);
#if defined(NeXT)
    address.sin_addr.S_un.S_addr= INADDR_ANY;
#else
    address.sin_addr.s_addr= INADDR_ANY;
#endif

    errorCode= bind(socketFD, (struct sockaddr *)&address, sizeof(address));
    if (errorCode == 0) {	// Could not bind the socket.
	flags= (Flags) (flags | inward | connected);
	return (listen(socketFD, queueLength) == 0);
    }

    return false;		// If we get here, the listening didn't work.
}


void AkSocketChannel::setNonBlocking(void)
{
#if !defined(_WIN32)
    fcntl(socketFD, F_SETFL, FNDELAY);
#else
// TODO.
#endif
}


bool AkSocketChannel::isNonBlocking(void)
{
#if !defined(_WIN32)
    return ((fcntl(socketFD, F_GETFL, 0) & FNDELAY) != 0);
#else
// TODO.
    return false;		// TMPTMP.
#endif
}


int AkSocketChannel::getSystemID(void)
{
    return socketFD;
}


int AkSocketChannel::getNewMsg(void)
{
    int lengthReceived;
    unsigned char tmpBuffer[4096], *dataPtr;

    lengthReceived= recv(socketFD, tmpBuffer, 4096, 0);
    if (lengthReceived == 0) {
// TMPTMP: Un message vide veut dire que le socket a ferme a l'autre bout.
	flags= (Flags)((flags & ~stateMask)| disconnected);
	close(socketFD);
	return 1;		// Warning: quick exit.
    }
    else {
	unsigned int status;

    	dataPtr= tmpBuffer;
	do {
	    if (currentMessage == NULL) {
		// Start a new message.
		currentMessage= AkCommCenter::newMessage();
		status= currentMessage->extract(dataPtr, lengthReceived, 0);
	    }
	    else {	// Continue reading a unfinished message.
		status= currentMessage->extract(dataPtr, lengthReceived, readSoFar);
	    }
	    switch(status) {
		case 0x0FFFFFFFF:	// All data was taken, still need more.
		    readSoFar= lengthReceived;
		    lengthReceived= 0;
		    break;
		case 0x0FFFFFFFE:	// Error, message body too long.
		    return -2;	// Warning: quick exit.
		    break;
		case 0x0FFFFFFFD:	// Error, something is wrong in message.
		    return -3;	// Warning: quick exit.
		    break;
		default:		// Message was read, some data (maybe 0) is left-over.
		    if (msgsHead == NULL) {
			msgsHead= currentMessage;
		    }
		    else {
			msgsTail->next= currentMessage;
		    }
		    msgsTail= currentMessage;
		    currentMessage= NULL;
		    dataPtr+= (lengthReceived - status);
		    lengthReceived= status;
		    readSoFar= 0;
		    break;
	    }
	} while (lengthReceived > 0);
    }
    return 0;
}


void AkSocketChannel::setPrivateID(unsigned short anID)
{
    privateID= anID;
}


unsigned short AkSocketChannel::getPrivateID(void)
{
    return privateID;
}


AkMessage *AkSocketChannel::fetchMessage(void)
{
    if (msgsHead != NULL) {
	AkMessage *result;

	result= msgsHead;
	if (msgsHead == msgsTail) msgsTail= NULL;
	msgsHead= msgsHead->next;
	result->next= NULL;
	return result;
    }
    return NULL;
}


void AkSocketChannel::releaseMessage(AkMessage *aMessage)
{
    AkCommCenter::releaseMessage(aMessage);
}


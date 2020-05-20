/**************************************************
* File: httpSession.cc.
* Desc: Implementation of the HttpSession class.
* Module: AkraLog : WebFetcher.
* Rev: 4 septembre 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

// DEBUG:
#include <iostream>

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
#endif
#include <memory.h>
#include <fcntl.h>
#include "response.h"
#include "delegate.h"
#include "request.h"
#include "httpSession.h"


#if !defined(NeXT)
extern int errno;
#endif

void HttpSession::socketSleep(unsigned int milliSecs)
{
    struct timeval timeout;

    timeout.tv_sec= milliSecs / 1000;
    timeout.tv_usec= (milliSecs % 1000) * 1000 ;

    select(0, 0, 0, 0, &timeout);
}


int HttpSession::getSysErrorCode(void)
{
#if defined(NeXT)
    return cthread_errno();
#else
    return errno;
#endif
}


HttpSession::HttpSession(DataDelegate *aDelegate)
{
    flags= noConnection;
    if ((socketFD= socket(PF_INET, SOCK_STREAM, 0)) > -1) {
    }
    readSoFar= 0;
    delegate= aDelegate;
}


bool HttpSession::connectToHost(char *hostName, int port, unsigned int nbrRetries)
{
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
		destination.sin_port= htons((u_short)port);
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



bool HttpSession::open(char *aHost, unsigned int aPort)
{
    return connectToHost(aHost, aPort, 5);
}


bool HttpSession::reopen(void)
{
    flags= noConnection;
    if ((socketFD= socket(PF_INET, SOCK_STREAM, 0)) > -1) {
	if (connect(socketFD, (struct sockaddr *)&destination, sizeof(destination)) != 0) {
	    flags= (Flags)(flags | refused);
	}
	else {
	    flags= (Flags)(flags | connected);
	    return true;		// Warning: quick exit.
	}
    }
    readSoFar= 0;
    return false;
}


bool HttpSession::execute(HttpRequest *request)
{
    bool result= false;

    switch(request->getType()) {
              case HttpRequest::connectRq:
              case HttpRequest::deleteRq:
              case HttpRequest::extensionRq:
	    cerr << "@ERR [HttpSession.execute]: request not implemented.\n";
	    break;
	case HttpRequest::getRq:
	    if (request->emitOn(this)) {
		result= receiveAnswer();
	    }
	    break;
              case HttpRequest::headRq:
              case HttpRequest::postRq:
              case HttpRequest::putRq:
              case HttpRequest::optionsRq:
              case HttpRequest::traceRq:
	    cerr << "@ERR [HttpSession.execute]: request not implemented.\n";
	    break;
              default:
	    cerr << "@ERR [HttpSession.execute]: unknown request.\n";
	    break;
    }

    return result;
}


HttpSession::Flags HttpSession::getStatus(void)
{
    return (Flags)(flags & stateMask);
}


bool HttpSession::emitRequest(HttpRequest *request)
{
    unsigned int msgLength;
    int lengthSent;
    char tmpBuffer[4096], *command;

    if ((command= request->getCommand()) != NULL) {
	msgLength= strlen(command);
	memcpy(tmpBuffer, command, msgLength);
	tmpBuffer[msgLength++]= '\r';
	tmpBuffer[msgLength++]= '\n';

	if ((lengthSent= send(socketFD, tmpBuffer, msgLength, 0)) != msgLength) {
	    // TODO: Add more recup logic.
	    return false;
	}
    }
    return true;
}


#define BUFFER_SIZE	4096

bool HttpSession::receiveAnswer(void)
{
    HttpResponse *currentResponse= NULL;
    int lengthReceived, scanPos, bufferOffset= 0;
    int opResult= -1;  // -2 (read error), -1 (nothing done), 0 (read but not closed), 1 (read and closed).
    char tmpBuffer[BUFFER_SIZE];
    State state= start;
    bool result= true;

    beginReception();

    do {
	if ((lengthReceived= recv(socketFD, tmpBuffer + bufferOffset, BUFFER_SIZE - bufferOffset, 0)) < 1) {
	    // Socket a ferme (0) ou est en etat special, comme blocked (neg).
	    if (lengthReceived == 0) {
		opResult= 1;
	    }
	    else {
		opResult= -2;
	    }
	    close(socketFD);
	    break;
	}
	else {	// Il y a du data a lire.
	    unsigned int tmpScan;
	    char *aChar;
	    bool foundRecord= false;

	    scanPos= 0;
	    opResult= 0;
	    while (scanPos < lengthReceived) {
		aChar= tmpBuffer + bufferOffset + scanPos;
		switch (state) {
		    case start:
			tmpScan=  0;
			do {
			    if (*(aChar + tmpScan) == '\r') {
				if (*(aChar + tmpScan + 1) == '\n') {    // ATTN: Va crasher si tmpScan == lengthReceived - 1.
				    foundRecord= true;
				    break;
				}
			    }
			    else tmpScan++;
			} while ((tmpScan + scanPos) < lengthReceived);
			if (foundRecord) {
			    if ((*aChar == 'H') && (*(aChar + 1) == 'T')    // ATTN: Va crasher s'il reste moins de 5 char dans tmpBuffer.
				    && (*(aChar + 2) == 'T') && (*(aChar + 3) == 'P') && (*(aChar + 4) == '/')) {
				aChar+= 5;
				state= readHeader;
				currentResponse= new HttpResponse(aChar);
			    }
			    scanPos+= tmpScan + 2;
			}
			else {
				// TODO: Gerer la situation sans paquet.
			}
			break;
		    case readHeader:
			tmpScan=  0;
			do {
			    if (*(aChar + tmpScan) == '\r') {
				if (*(aChar + tmpScan + 1) == '\n') {    // ATTN: Va crasher si tmpScan == lengthReceived - 1.
				    foundRecord= true;
				    break;
				}
			    }
			    else tmpScan++;
			} while ((tmpScan + scanPos) < lengthReceived);
			if (foundRecord) {
			    if (tmpScan == 0) {
				state= readContent;
				handleHeader(currentResponse);
				scanPos+= 2;
			    }
			    else {
				// TODO: Gerer le record trouve.
				currentResponse->addRecord(tmpBuffer + bufferOffset + scanPos, tmpScan);
				scanPos+= tmpScan + 2;
			    }
			}
			else {
			    // TODO: Gerer la situation sans paquet.
			}
			break;
		    case readContent:
			handleContent(currentResponse, tmpBuffer + bufferOffset + scanPos, lengthReceived - scanPos);
			scanPos= lengthReceived;
			break;
		}
	    }
	}
    } while (1);

    endReception(currentResponse, opResult);

    if (currentResponse != NULL) {
	if (currentResponse->isAutoDel())
	    delete currentResponse;
    }
    return result;
}


bool HttpSession::beginReception(void)
{
    if (delegate != NULL) return delegate->beginReception(this);
    else return true;
}


bool HttpSession::handleHeader(HttpResponse *response)
{
    if (delegate != NULL) return delegate->noticeHeader(this, response);
    else return true;
}


bool HttpSession::handleContent(HttpResponse *response, char *data, unsigned int dataLength)
{
    response->addContent(data, dataLength);
    if (delegate != NULL) return delegate->noticeContent(this, response, data, dataLength);
    else return true;
}


bool HttpSession::endReception(HttpResponse *response, int aStatus)
{
    if (delegate != NULL) return delegate->endReception(this, response, aStatus);
    else return true;
}


void HttpSession::setDelegate(DataDelegate *aDelegate)
{
    delegate= aDelegate;
}


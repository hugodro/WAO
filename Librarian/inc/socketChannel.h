#ifndef _AKCOMMPORT_H_
#define _AKCOMMPORT_H_
/**************************************************
* File: socketChannel.h.
* Desc: Definition of the AkSocketPort class (and tempo. AkCommPort).
* Module: AkraLog : WAO.
* Rev: 24 juin 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include <akra/portableDefs.h>


class AkMessage;


/********************************************************
* Class: AkCommPort.
* Desc: Virtual class that will be the root to all comm. channels.
* NOTE-980624 [HD]: It will be filled up based on the experience of AkSocketChannel.
* Class variables:
* Instance variables:
* Super-Class: AkObject.
* Module: AkraLog : WAO.
********************************************************/

class AkCommPort : public AkObject {
  protected:	// Instance variables.
  public:		// Instance methods.
};


/********************************************************
* Class: AkSocketChannel.
* Desc: Concrete communication port, using TCP/IP sockets.
* NOTE-980624 [HD]: Same file for now, will have to be moved to another file.
* Class variables: none.
* Instance variables:
*	prev : [AkSocketChannel *] previous element in implicit linked list.
*	next : [AkSocketChannel *] next element in implicit linked list.
*	socketFD : [int] system-level file descriptor of the socket.
*	privateID : [unsigned short] internal ID of the comm port.
*	flags : [Flags] states of the comm port.
*	readSoFar : [unsigned int] amount of bytes read in the current incoming message. 
*	currentMessage : [AkMessage *] current message being received over socket.
*	msgsHead : [AkMessage *] head of linked list of AkMessage received since last purge.
*	msgsTail : [AkMessage *] tail of linked list of AkMessage received since last purge.
* Super-Class: AkCommPort.
* Module: AkraLog : WAO.
********************************************************/

class AkSocketChannel : public AkCommPort {
  public:
    enum Flags {
	    // Kind (bit 0-1):
	stream= 0x00, seqStream= 0x01, dgram= 0x02
	, kindMask= 0x03,
	    // Activity (bit 2):
	outward= 0x00, inward= 0x04
	, activityMask= 0x04,
	    // State (bit 3-6):
	noConnection= 0x00, connected= 0x08, gotData= 0x018,
	disconnected= 0x020, refused= 0x040
	, stateMask= 0x078
    };

  public:		// Class Methods.
    static void socketSleep(unsigned int milliSecs);
    static int getSysErrorCode(void);

  protected:	// Instance variables.
    AkSocketChannel *prev, *next;	// Channels are implicitly linkable.
    int socketFD;
    unsigned short privateID;
    Flags flags;
    unsigned int readSoFar;
    AkMessage *currentMessage;
    AkMessage *msgsHead;
    AkMessage *msgsTail;

  public:		// Instance methods.
    AkSocketChannel(void);				// Create an unconnected channel.
    AkSocketChannel(int aSocketID);		// Create channel with existing system socket.
    AkSocketChannel(char *hostName, int port, unsigned int nbrRetries);    // Fast creation of outward socket.
    virtual ~AkSocketChannel(void);		// Destroy channel, close system socket if necessary.
    virtual void linkTo(AkSocketChannel *aChannel);	// Add a channel as next element of implicit linked list.
    virtual AkSocketChannel *getNext(void);		// Get next element in implicit linked list.
    virtual AkSocketChannel *getPrev(void);		// Get previous element in implicit linked list.
    virtual void resetPrev(void);				// Forget last element in implicit linked list (previous element itself is not modified). 
    virtual bool isConnected(void);				// Assert that system socket is connected to peer.
    virtual bool connectToHost(char *hostName, int port, unsigned int nbrRetries);	// Build a system-level connection to a given host, on given port.
    virtual bool connectToOperator(int port, unsigned int queueLength);	// Build a system-level connection as a port of entry for remote channels to connect to.
    virtual void setNonBlocking(void);			// Make the channel non-blocking.
    virtual bool isNonBlocking(void);			// Assert that the channel is non-blocking.
    virtual int getSystemID(void);				// Get the system socket file descriptor.
    virtual int getNewMsg(void);				// Perform a system read to try to extract a new message.
    virtual void setPrivateID(unsigned short anID);	// Define the internal ID for the channel.
    virtual unsigned short getPrivateID(void);	// Get the internal ID for the channel.
    virtual AkMessage *fetchMessage(void);		// Extract the first message on the queue.
    virtual void releaseMessage(AkMessage *aMessage);	// Indicate that the message is no longer useful, and can be discarded.

/* TODO:
    virtual void setBlocking(void);	// Make the socket blocking.
*/

};


#endif		/* _AKCOMMPORT_H_ */

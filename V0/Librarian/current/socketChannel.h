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
    AkSocketChannel(void);
    AkSocketChannel(int aSocketID);
    AkSocketChannel(char *hostName, int port, unsigned int nbrRetries);    // Fast creation of outward socket.
    virtual ~AkSocketChannel(void);
    virtual void linkTo(AkSocketChannel *aChannel);
    virtual AkSocketChannel *getNext(void);
    virtual AkSocketChannel *getPrev(void);
    virtual void resetPrev(void);
    virtual bool isConnected(void);
    virtual bool connectToHost(char *hostName, int port, unsigned int nbrRetries);
    virtual bool connectToOperator(int port, unsigned int queueLength);
    virtual void setNonBlocking(void);
    virtual bool isNonBlocking(void);
    virtual int getSystemID(void);
    virtual int getNewMsg(void);
    virtual void setPrivateID(unsigned short anID);
    virtual unsigned short getPrivateID(void);
    virtual AkMessage *fetchMessage(void);
    virtual void releaseMessage(AkMessage *aMessage);

/* TODO:
    virtual void setBlocking(void);	// Make the socket blocking.
*/

};


#endif		/* _AKCOMMPORT_H_ */

#ifndef _AKCOMMCENTER_H_
#define _AKCOMMCENTER_H_
/**************************************************
* File: commCenter.h.
* Desc: Definition of the AkCommCenter class.
* Module: AkraLog : WAO.
* Rev: 24 juin 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <sys/types.h>		// For fd_set.

#include <akra/AkObject.h>
#include <akra/portableDefs.h>


class AkSocketChannel;
class AkMessage;
class AkNotificationPort;


class AkCommCenter : public AkObject {
  public:
    enum Constants {
	channelMapSize= 32	// There 32 times that much entries in the delegate table.
    };

  public:		// Class methods.
    static AkMessage *newMessage(void);
    static void releaseMessage(AkMessage *aMessage);

  protected:		// Instance variables.
    AkSocketChannel *inPorts;
    unsigned int nbrInPorts;
    AkSocketChannel *peeredPorts;
    unsigned int nbrPeeredPorts;
    AkNotificationPort **delegates;	// Each channel has a delegate.
    unsigned int *channelMap;
	// Socket stuff for select, might go somewhere else.
    fd_set selectors[3];
    int maxSockID;
    bool runningModal;

  public:
    AkCommCenter(void);
    virtual ~AkCommCenter(void);
    virtual bool addListenPort(int port, AkNotificationPort *notifier);
    virtual int addConnectionTo(char *host, int port, AkNotificationPort *notifier);    // Return a ID to the connection if it was successful.
    virtual void runModal(void);
    virtual bool sendMessage(AkMessage *aMessage);
    virtual void assignNotificationPort(unsigned short aChannel, AkNotificationPort *aPort);
    virtual void shutdown(void);
    virtual unsigned short assignMapIndex(void);
    virtual void releaseMapIndex(unsigned short anIndex);

	// Socket stuff for select, might go somewhere else.
    virtual void recalcMaxID(void);
};


#endif		/* _AKCOMMCENTER_H_ */

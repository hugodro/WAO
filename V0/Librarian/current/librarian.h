#ifndef _LIBRARIAN_WAO_H_
#define _LIBRARIAN_WAO_H_
/**************************************************
* File: librarian.h.
* Desc: Definition of the WaoLibrarian class.
* Module: AkraLog : WAO.
* Rev: 19 juin 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include <akra/portableDefs.h>


class JScripter;
class WLibStatistics;
class AkCommCenter;
class WLibNotificator;
class WClient;
class WIncomingNotificator;
class WPeerNotificator;
class AkRequest;


class WaoLibrarian : public AkObject {
  public:
    enum StatusFlags {
	notReady, configured, initialized, running,
	stopped
    };
    enum Constants {
	clientTableSize= 1024
    };

  protected:	// Instance variables.
    JScripter *jScripter;
    AkCommCenter *commCenter;
    WIncomingNotificator *incomingDoor;
    WPeerNotificator *peerDoor;
    WClient **clients;		// Normal clients.
    WClient **vips;		// Priviliedge clients.
    // Informations generales.
    StatusFlags status;

  public:		// Instance methods.
    WaoLibrarian(void);
    virtual ~WaoLibrarian(void);
    virtual bool setOption(unsigned int option, void *value);    // Set the value of an option (false -> no such option).
    virtual void configure(void);		// Configure all components of Librarian.
    virtual int initialize(void);			// Initialize Librarian just before launching.
    virtual int run(void);
    virtual WLibStatistics *getRunStats(void);    // Return the statistics of a run session.
    virtual bool stop(void);			// Stop receiving new requests.
    virtual bool restart(void);			// Restart receiving requests.
    virtual void terminate(void);			// Ends operations.
    virtual bool addClient(unsigned int aPortID);
    virtual void addClientRequest(unsigned int aclientID, AkRequest *aRequest);
    virtual bool removeClient(unsigned int aPortID);
};


#endif		/* _LIBRARIAN_WAO_H_ */

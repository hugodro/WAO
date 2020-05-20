/**************************************************
* File: librarian.cc.
* Desc: Implementation of the WaoLibrarian class.
* Module: AkraLog : WAO.
* Rev: 24 juin 1998 : REV 0 : Hugo DesRosiers.
**************************************************/

#include "commCenter.h"
#include "wlibNotificator.h"
#include "client.h"
#include "librarian.h"


WaoLibrarian::WaoLibrarian(void)
{
    jScripter= NULL;
    commCenter= NULL;
    incomingDoor= NULL;
    peerDoor= NULL;

// TODO: Initialisation des infos generales.
    status= notReady;
}


WaoLibrarian::~WaoLibrarian(void)
{
    if (commCenter != NULL) delete commCenter;
    if (incomingDoor != NULL) delete incomingDoor;
    if (peerDoor != NULL) delete peerDoor;
// TODO:    if (jScripter != NULL) delete jScripter;
}


bool WaoLibrarian::setOption(unsigned int option, void *value)
{
    return true;
}

    
void WaoLibrarian::configure(void)
{
// TODO: take options and do whatever with them.

    commCenter= new AkCommCenter();
}

		
int WaoLibrarian::initialize(void)
{
    int errorCode= 0;

// TODO: setup everything for running, according to configuration.

    incomingDoor= new WIncomingNotificator(this);
    peerDoor= new WPeerNotificator(this);
    incomingDoor->setMessagePort(peerDoor);

    clients= new WClient*[clientTableSize];

	// TMP: Use port 9999.
    if (!commCenter->addListenPort(9999, incomingDoor)) errorCode= -1;

    return errorCode;
}

			
int WaoLibrarian::run(void)
{
    int runCode= 0;

// TODO: Main run loop.
    commCenter->runModal();

    return runCode;
}


WLibStatistics *WaoLibrarian::getRunStats(void)
{
// TODO: Gather statistics and put them in a WLibStatistics.
    return NULL;
}

    
bool WaoLibrarian::stop(void)
{

// TODO: Try to stop (non-terminally) the librarian, return success of operation.
    return true;
}

			
bool WaoLibrarian::restart(void)
{

// TODO: Try to restart the librarian after a stop, return success of operation.
    return true;
}

			
void WaoLibrarian::terminate(void)
{
// TODO: Shut down the librarian.  It MUST always work, since the librarian will
// get annihilated by a superior entity if it doesn't.

    if (commCenter != NULL) {
	commCenter->shutdown();
    }
}


bool WaoLibrarian::addClient(unsigned int aPortID)
{
    bool result= false;

    if (aPortID < clientTableSize) {
	if (clients[aPortID] == NULL) {
	    clients[aPortID]= new WClient();
	    result= true;
	}
    }
    return result;
}


void WaoLibrarian::addClientRequest(unsigned int aclientID, AkRequest *aRequest)
{
// TODO: Handle the request toward the client.
}


bool WaoLibrarian::removeClient(unsigned int aPortID)
{
    bool result= false;

    if (aPortID < clientTableSize) {
	if (clients[aPortID] != NULL) {
	    delete clients[aPortID];
	    clients[aPortID]= NULL;
	    result= true;
	}
    }
    return result;
}



/**************************************************
* File: main.cc.
* Desc: Implementation of librarian basic launch code.
* Module: AkraLog : WAO.
* Rev: 19 juin 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <iostream.h>
#include <signal.h>
#include "librarian.h"


/*** Functions defined in this module. ***/
void shutDown(int);
bool parseOptions(char **, unsigned int);


/*** Global variables defined in this module. ***/

static WaoLibrarian *librarian= NULL;
static int mode= 0;		// Modes: 1=> serveur, 2=> client.


main(int argc, char **argv)
{
    int returnCode;
    bool didRun= false;

    // Parse options.
    if (parseOptions(argv, argc)) {
	exit(0);
    }

    if (mode == 1) {
	signal(SIGINT, shutDown);
	signal(SIGHUP, shutDown);
    
	librarian= new WaoLibrarian();
    
	// Set Librarian options.
	librarian->configure();
    
	    // Bootstrap.
	if ((returnCode= librarian->initialize()) > -1) {
	    didRun= true;
	    returnCode= librarian->run();
	}
	else {
	    // Do error management.
	    cout << "Could not initialize the Librarian.\n";
	} 
	if (didRun) {
	    WLibStatistics *stats; 
		// Clean up run session.
	    stats= librarian->getRunStats();
	    delete librarian;
	    returnCode= 0;
	}
    }
    else if (mode == 2) {
	// Fait le client.
    }
    exit(returnCode);
}


void shutDown(int signalArg)
{
    if (librarian != NULL) librarian->terminate();
}


bool parseOptions(char **options, unsigned int nbrElements)
{
    unsigned int i;
    bool result= true;

    mode= 1;		// Par defaut, on fait le mode serveur.

    for (i= 0; i < nbrElements; i++) {
	if (options[i][0] == '-') {
	    if (options[i][1] == 'c') {
		mode= 2;		// Passe en mode test client.
	    }
	}
    }

    return result;
}


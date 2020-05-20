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
void testMySql(void);


/*** Global variables defined in this module. ***/

static WaoLibrarian *librarian= NULL;

main(int argc, char **argv)
{
    int returnCode;
    bool didRun= false;

    // Parse options.

    signal(SIGINT, shutDown);
    signal(SIGHUP, shutDown);


    librarian= new WaoLibrarian();

// TODO-991012 [HD]:
/*
    testMySql();
*/

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

    exit(returnCode);
}


void shutDown(int signalArg)
{
    if (librarian != NULL) librarian->terminate();
}


#include "mySqlSupport.h"
#include "logisinDO.h"

void testMySql(void)
{
    WConnectDictionary *connectDefs;
    MySqlWEngine *myEngine;
    EntityTable *internalUsers;
    ArrayDO *users;
    

/* TODO-991012 [HD]:
    internalUsers= new EntityTable("utilisateur", "InternalUsers", UtilisateurInterne::generateur);
    internalUsers->addProperty("uid", PropertyField::dtInteger);
    internalUsers->addProperty("appName", PropertyField::dtVarchar);
    internalUsers->addProperty("passwd", PropertyField::dtVarchar);
    internalUsers->addProperty("firstName", PropertyField::dtVarchar);
    internalUsers->addProperty("lastName", PropertyField::dtVarchar);
    internalUsers->addProperty("lastAccess", PropertyField::dtVarchar);
    internalUsers->addProperty("logCount", PropertyField::dtInteger);
    internalUsers->addProperty("rights", PropertyField::dtVarchar);
    internalUsers->addProperty("email", PropertyField::dtVarchar);
    internalUsers->addProperty("fileID", PropertyField::dtChar);
    internalUsers->addProperty("fileCount", PropertyField::dtInteger);
*/

    connectDefs= new WConnectDictionary();

    connectDefs->add("host", "serveur");
    connectDefs->add("user", "hugo");
    connectDefs->add("database", "LogisinV1R0");

    myEngine= new MySqlWEngine();
    myEngine->setConnectDict(connectDefs);
    myEngine->connect();

    users= myEngine->fetchAll(internalUsers);

    myEngine->disconnect();
}



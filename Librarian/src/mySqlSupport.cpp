/**************************************************
* File: mysqlSupport.cc.
* Desc: Implementation of the MySQL engine support.
* Module: AkraLog : WAO.
* Rev: 8 decembre 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <mysql.h>
#include <iostream.h>
#if defined(__linux__)
#include <stdlib.h>
#endif
#include "dbObject.h"
#include "mySqlSupport.h"

#if !defined(NULL)
#define NULL	(0L)
#endif


/**************************************************
* Implementation: WSqlEngine.
**************************************************/

MySqlWEngine::MySqlWEngine(void)
{
    session= (MYSQL *)calloc(1, sizeof(MYSQL));
}


MySqlWEngine::~MySqlWEngine(void)
{
    if (session != NULL) free(session);
}


int MySqlWEngine::connect(void)
{
    char *host, *user, *password, *database;

    if (connectDict == NULL) return -2;

    host= (char *)connectDict->get("host");
    user= (char *)connectDict->get("user");
    password= (char *)connectDict->get("password");
    database= (char *)connectDict->get("database");

#if defined(MYSQL_3_22)
    if (mysql_real_connect(session, host, user, password, NULL, MYSQL_PORT, NULL, 0) != NULL) {
#else
    if (mysql_real_connect(session, host, user, password, MYSQL_PORT, NULL, 0) != NULL) {
#endif
	if (database != NULL) {
	    if (mysql_select_db(session, database) < 0) {
		return -4;
	    }
	}
    }
    else return -3;
}


bool MySqlWEngine::disconnect(void)
{
    mysql_close(session);

    return true;			// It always succeed.
}


int  MySqlWEngine::execute(char *aStatement, Operation anOp)
{
    int resultCode;

    switch (anOp) {
	case opSelect:
	    resultCode= mysql_query(session, aStatement);
	    if (resultCode != 0) {
		resultCode= -1;		// Query failed.
	    }
	    break;

	case opCreate:
	case opUpdate:
	case opDelete:
		// TODO:
	    resultCode= -2;		// Not implemented yet.
	    break;
    }

    return resultCode;
}


int  MySqlWEngine::extractData(EntityTable *anEntity, ArrayDO *resultSet)
{
    MYSQL_RES *cmdResult;
    MYSQL_ROW aRow;
    int resultCode;

    if ((cmdResult= mysql_use_result(session)) != NULL) {
	MYSQL_FIELD **fieldDesc;
	int j, replyWidth;

	replyWidth= mysql_num_fields(cmdResult);
	fieldDesc= new MYSQL_FIELD*[replyWidth];
	for (j= 0; j < replyWidth; j++) {
	    fieldDesc[j]= mysql_fetch_field(cmdResult);
	}
	WAssociationTable *assocTable= new WAssociationTable(anEntity->propertyCount());

	if (anEntity->propertyCount() > 0) {
	    PropertyField *curseur;
	    curseur= anEntity->getProperties();
	    do {
		for (j= 0; j < replyWidth; j++) {
		    if (strcmp(fieldDesc[j]->name, curseur->getName()) == 0) {
/* TODO-991012 [HD]:
			assocTable.bind(curseur, fieldDesc, j);
*/
			break;
		    }
		}
		curseur= curseur->getNext();
	    } while (curseur != NULL);
	}
	else {
	    // TODO: Handle the case with no property specified (select-star).
	}

	if ((aRow= mysql_fetch_row(cmdResult)) != NULL) {
	    DataObject *newInstance;

	    do {
		// TODO: Doit batir un UID selon aRow et assocTable.
		newInstance= anEntity->getInstance(0);
		newInstance->cloneFromDB(assocTable, this, aRow);
		resultSet->addObject(newInstance);

		aRow= mysql_fetch_row(cmdResult);
	    } while (aRow != NULL);
	    resultCode= 0;	// No error.
	}
	else resultCode= -1;    // Error: no data returned.

	delete assocTable;
	delete[] fieldDesc;
	mysql_free_result(cmdResult);
    }
    else resultCode= -2;	// Can't access query result.
}


int MySqlWEngine::fetchValue(WAssocElement *which, void *data, void *destination)
{
    unsigned int offset;

// RENDU ICI-990128:
/*
    offset= which->getOffset();
    switch((MYSQL_FIELD *)which->privateDesc()
*/    
}



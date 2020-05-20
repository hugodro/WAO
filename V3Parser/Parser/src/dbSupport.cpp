#include <stdlib.h>
#include <arpa/inet.h>
#include <string>

#include <libpq/libpq-fs.h>

#include "dbSupport.h"


/***************************************************
* Implementation: PostgresChannel.
****************************************************/

PostgresChannel::PostgresChannel(const char *connString)
{
  if (connString != NULL) {
    unsigned int tmpLng;
    tmpLng= strlen(connString) + 1;
    connDict= new char[tmpLng];
    memcpy(connDict, connString, tmpLng);
  }
  else
    connDict= NULL;
  connection= NULL;
}


PostgresChannel::~PostgresChannel()
{
  delete[] connDict;
}

bool PostgresChannel::connect()
{
  if (connDict != NULL)
    connection= PQconnectdb(connDict);
  return (connection != NULL);
}


void PostgresChannel::disconnect()
{
  if (connection != NULL)
    PQfinish(connection);
}


DBResult *PostgresChannel::exec(const char *aStmt)
{
  PgResult *result;

  if ((connection != NULL) && (aStmt != NULL)) {
    result= new PgResult(PQexec(connection, aStmt));
  }
  else
    //TODO: replace by exception throwing.
    result= 0;
  return result;
}


int PostgresChannel::status()
{
  return PQstatus(connection);
}


int PostgresChannel::openBlob(int anID)
{
  return lo_open(connection, anID, INV_READ);
}


int PostgresChannel::readFromBlob(int aFD, char *aBuffer, size_t aLen)
{
  return lo_read(connection, aFD, aBuffer, aLen);
}


int PostgresChannel::closeBlob(int aFD)
{
  return lo_close(connection, aFD);
}


/***************************************************
* Implementation: PostgresChannel.
****************************************************/

PgResult::PgResult(PGresult *aRez)
{
  lowLevel= aRez;
}


PgResult::~PgResult()
{
  PQclear(lowLevel);
}


bool PgResult::isOk()
{
 return (PQresultStatus(lowLevel) == PGRES_COMMAND_OK) || (PQresultStatus(lowLevel) == PGRES_TUPLES_OK);
}


int PgResult::getNbrFields()
{
  return PQnfields(lowLevel);
}


int PgResult::getNbrRows()
{
  return PQntuples(lowLevel);
}


unsigned int PgResult::getFieldPosOf(char *aLabel)
{
  return PQfnumber(lowLevel, aLabel);
}


void PgResult::fieldAsInt(unsigned int rowIndex, unsigned int offset, int &receiver)
{
  if (rowIndex < PQntuples(lowLevel)) {
    char *tmpVal;

    tmpVal= PQgetvalue(lowLevel, rowIndex, offset);
    receiver= atoi(tmpVal);
  }
  //TODO: throw exception on no-more-rows.
}


void PgResult::fieldAsChar(unsigned int rowIndex, unsigned int offset, char *receiver, unsigned int maxLength)
{
  if (rowIndex < PQntuples(lowLevel)) {
    unsigned int cpyLength;
    char *tmpPtr;

    tmpPtr= PQgetvalue(lowLevel, rowIndex, offset);
    cpyLength=  maxLength-1 < PQgetlength(lowLevel, rowIndex, offset) ? maxLength-1 : PQgetlength(lowLevel, rowIndex, offset);
    memcpy(receiver, tmpPtr, cpyLength);
    receiver[cpyLength+1]= '\0';
  }
  //TODO: throw exception on no-more-rows or length-excess.
}



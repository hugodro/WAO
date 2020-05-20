#ifndef _X_AKRALOG_DBSUPPORTSQL_H_
#define _X_AKRALOG_DBSUPPORTSQL_H_

#include <libpq-fe.h>

class DBChannel;
class DBResult;


/***************************************************
* Definition: DBChannel.
****************************************************/

class DBChannel {
 public:
  virtual bool connect() = 0;
  virtual void disconnect() = 0;
  virtual DBResult *exec(const char *aStmt) = 0;
  virtual int status() = 0;
};


/****************************
* Class: PostgresChannel.
****************************/

class PostgresChannel : public DBChannel {
 protected:
  PGconn *connection;
  char *connDict;

 public:
  PostgresChannel(const char *connString);
  virtual ~PostgresChannel();
  virtual bool connect();
  virtual void disconnect();
  virtual DBResult *exec(const char *aStmt);
  virtual int status();
  virtual int openBlob(int anID);
  virtual int readFromBlob(int aFD, char *aBuffer, size_t aLen);
  virtual int closeBlob(int aFD);
};


/****************************
* Class: DBResult.
****************************/

class DBResult {
 public:
  virtual bool isOk()= 0;
  virtual int getNbrFields()= 0;
  virtual int getNbrRows()= 0;
  virtual unsigned int getFieldPosOf(char *aLabel)= 0;
  virtual void fieldAsInt(unsigned int rowIndex, unsigned int offset, int &receiver)= 0;
  virtual void fieldAsChar(unsigned int rowIndex, unsigned int offset, char *receiver, unsigned int maxLength)= 0;
};


/****************************
* Class: PgResult.
****************************/

class PgResult : public DBResult {
 protected: 
  PGresult *lowLevel;

 public:
  PgResult(PGresult *aRez);
  virtual ~PgResult();
  virtual bool isOk();
  virtual int getNbrFields();
  virtual int getNbrRows();
  virtual unsigned int getFieldPosOf(char *aLabel);
  virtual void fieldAsInt(unsigned int rowIndex, unsigned int offset, int &receiver);
  virtual void fieldAsChar(unsigned int rowIndex, unsigned int offset, char *receiver, unsigned int maxLength); 
};


#endif  /* _X_AKRALOG_DBSUPPORTSQL_H_ */

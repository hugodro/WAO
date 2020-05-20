#ifndef _MYSQL_ENGINE_H_
#define _MYSQL_ENGINE_H_
/**************************************************
* File: mySqlSupport.h.
* Desc: Definition of the generic SQL engine support.
* Module: AkraLog : WAO.
* Rev: 8 decembre 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "sqlEngine.h"


typedef struct st_mysql MYSQL;


class MySqlWEngine : public WDataEngine {
  protected:
    MYSQL *session;

  protected:
    virtual int execute(char *aStatement, Operation anOp);
    virtual int extractData(EntityTable *anEntity, ArrayDO *resultSet);

  public:
    MySqlWEngine(void);
    ~MySqlWEngine(void);
    virtual int connect(void);
    virtual bool disconnect(void);

    virtual int fetchValue(WAssocElement *which, void *data, void *destination);
};


#endif		/* _MYSQL_ENGINE_H_ */

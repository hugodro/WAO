#ifndef _LIBRARIAN_SQL_ENGINE_H_
#define _LIBRARIAN_SQL_ENGINE_H_
/**************************************************
* File: sqlEngine.h.
* Desc: Definition of the generic SQL engine support.
* Module: AkraLog : WAO.
* Rev: 8 decembre 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>


class SqlStatement;
class DataObject;
class ArrayDO;
class AkHashManager;

typedef DataObject *(*InstanceGenerator)(void);
typedef DataObject *(*InstanceFiller)(void *, void *);


class WConnectDictionary : public AkObject {
  protected:
    unsigned int nbrKeys;
    unsigned int arraySize;
    char **keys;
    void **values;

  public:
    WConnectDictionary(void);
    virtual ~WConnectDictionary(void);
    virtual void add(char *key, void *value);
    virtual void *get(char *key);
};


class PropertyField : public AkObject {
    friend class EntityTable;
  public:
    enum DataType {
	dtInteger, dtVarchar, dtBool, dtDateTime, dtMoney, dtFloat
      , dtChar
    };

  protected:
    PropertyField *next;
    char *name;
    DataType type;

  public:
    PropertyField(char *aName, DataType aType);
    ~PropertyField(void);
    char *getName(void);
    PropertyField *getNext(void);
};


class EntityTable : public AkObject {
  protected:
    EntityTable *next;
    char *tableName;
    char *name;
    AkHashManager *uniqueStore;
    PropertyField *fields;
    unsigned int nbrFields;
    InstanceGenerator generator;

  protected:
    virtual DataObject *newInstance(void);
    virtual bool addInstance(DataObject *anObject);

  public:
    EntityTable(void);
    EntityTable(char *aName, char *aTableName, InstanceGenerator aGenerator);
    virtual ~EntityTable(void);
    EntityTable *getNext(void);
    void linkTo(EntityTable *anEntity);
    char *getTableName(void);
    unsigned int propertyCount(void);
    PropertyField *getProperties(void);
    virtual void addProperty(char *aName, PropertyField::DataType aType);
    virtual DataObject *getInstance(unsigned int aUID);
    virtual DataObject *getFromStore(unsigned int aUID);
    virtual void forgetInstance(unsigned int aUID);
    virtual unsigned int propsAsSelectList(char *buffer);
};


class WAssocElement : public AkObject {
    friend class WAssociationTable;

  protected:
    PropertyField *property;
    void *privateDescriptor;
    unsigned int index;

  public:
};


class WAssociationTable : public AkObject {
  protected:
    unsigned int tableSize;
    unsigned int currentPos;
    WAssocElement *associations;

  public:
    WAssociationTable(unsigned int aSize);
    ~WAssociationTable(void);
    virtual void bind(PropertyField *aField, void *aDescriptor, unsigned int anOffset);
    virtual WAssocElement *getPropAssoc(char *aName);
};


class WDataEngine : public AkObject {
  public:
    enum Operation {
	opSelect, opCreate, opUpdate, opDelete
    };

  protected:
    WConnectDictionary *connectDict;
    EntityTable *entities;
 
  protected:
    virtual int execute(char *aStatement, Operation anOp);
    virtual int extractData(EntityTable *anEntity, ArrayDO *resultSet);

  public:
    WDataEngine(void);
    ~WDataEngine(void);
    virtual void setConnectDict(WConnectDictionary *aDict);
    virtual int connect(void);
    virtual bool disconnect(void);

    virtual void addEntity(EntityTable *anEntity);
    virtual ArrayDO *fetchAll(EntityTable *anEntity);
    virtual ArrayDO *fetchWhere(EntityTable *anEntity, char *whereClause);
    virtual int fetchValue(WAssocElement *which, void *data, void *destination)= 0;
};


#endif		/* _LIBRARIAN_SQL_ENGINE_H_ */

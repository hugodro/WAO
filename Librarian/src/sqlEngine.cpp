/**************************************************
* File: sqlEngine.cc.
* Desc: Implementation of the generic SQL engine support.
* Module: AkraLog : WAO.
* Rev: 8 decembre 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "dbObject.h"
#include "sqlEngine.h"

#if !defined(NULL)
#define NULL	(0L)
#endif


/**************************************************
* Implementation: WConnectDictionary.
**************************************************/

WConnectDictionary::WConnectDictionary(void)
{
    nbrKeys= 0;
    arraySize= 32;
    keys= new char*[arraySize];
    values= new void *[arraySize];
}


WConnectDictionary::~WConnectDictionary(void)
{
    delete[] keys;
    delete[] values;
}


void WConnectDictionary::add(char *key, void *value)
{
    if (nbrKeys < arraySize) {
	keys[nbrKeys]= key;
	values[nbrKeys++]= value;
    }
    else {
	char **tmpKeys= keys;
	void **tmpValues= values;
	unsigned int tmpSize= arraySize;

	arraySize+= 32;
	keys= new char*[arraySize];
	values= new void *[arraySize];
	for (unsigned int i= 0; i < tmpSize; i++) {
	    keys[i]= tmpKeys[i];
	    values[i]= tmpValues[i];
	}
	delete[] tmpKeys;
	delete[] tmpValues;
    }
}


void *WConnectDictionary::get(char *key)
{
    unsigned int i;

    i= 0;
    while (i < nbrKeys) {
	if (strcmp(keys[i], key) == 0) return values[i];        // Warning: quick exit.
	i++;
    }

    return NULL;
}


/**************************************************
* Implementation: PropertyField.
**************************************************/

PropertyField::PropertyField(char *aName, DataType aType)
{
    unsigned int tmpLength;

    tmpLength= strlen(aName)+1;
    name= new char[tmpLength];
    memcpy(name, aName, tmpLength * sizeof(char));
    type= aType;
}


PropertyField::~PropertyField(void)
{
    if (name != NULL) delete[] name;
}

char *PropertyField::getName(void)
{
    return name;
}


PropertyField *PropertyField::getNext(void)
{
    return next;
}


/**************************************************
* Implementation: EntityTable.
**************************************************/
EntityTable::EntityTable(void)
{
    next= NULL;
    tableName= NULL;
    uniqueStore= NULL;
    fields= NULL;
    generator= NULL;
    nbrFields= 0;
}


EntityTable::EntityTable(char *aName, char *aTableName, InstanceGenerator aGenerator)
{
    unsigned int tmpLength;

    next= NULL;

    tmpLength= strlen(aName)+1;
    name= new char[tmpLength];
    memcpy(name, aName, tmpLength * sizeof(char));

    tmpLength= strlen(aTableName)+1;
    tableName= new char[tmpLength];
    memcpy(tableName, aTableName, tmpLength * sizeof(char));

    generator= aGenerator;
    uniqueStore= NULL;
    fields= NULL;
    nbrFields= 0;
}


EntityTable::~EntityTable(void)
{
    if (name != NULL) delete[] name;
    if (tableName != NULL) delete[] tableName;
// TODO:    if (instances != NULL) delete instances;
}


EntityTable *EntityTable::getNext(void)
{
    return next;
}


void EntityTable::linkTo(EntityTable *anEntity)
{
    next= anEntity;
}


char *EntityTable::getTableName(void)
{
    return tableName;
}


unsigned int EntityTable::propertyCount(void)
{
    return nbrFields;
}


PropertyField *EntityTable::getProperties(void)
{
    return fields;
}


void EntityTable::addProperty(char *aName, PropertyField::DataType aType)
{
    PropertyField *newProp;

    newProp= new PropertyField(aName, aType);
    if (fields == NULL) {
	fields= newProp;
    }
    else {
	PropertyField *tmpProp= fields;

	while (tmpProp->next != NULL) tmpProp= tmpProp->next;
	tmpProp->next= newProp;
    }
    nbrFields++;
}


DataObject *EntityTable::newInstance(void)
{
    return generator();
}


bool EntityTable::addInstance(DataObject *anObject)
{
// TODO.
    return false;
}


DataObject *EntityTable::getInstance(unsigned int aUID)
{
    DataObject *result;

    if ((result= getFromStore(aUID)) == NULL) {
	result= newInstance();
	addInstance(result);
    }
    return result;
}


DataObject *EntityTable::getFromStore(unsigned int aUID)
{
    DataObject *result= NULL;

// TODO.
    return result;
}


void EntityTable::forgetInstance(unsigned int aUID)
{
// TODO.
}


unsigned int EntityTable::propsAsSelectList(char *buffer)
{
    if (fields == NULL) {
	buffer[0]= '*';
	return 1;
    }
    else {
	PropertyField *curseur;
	unsigned int tmpLength, totalLength= 0;

	curseur= fields;
	do {
		tmpLength= strlen(curseur->name);
		memcpy(buffer, curseur->name, tmpLength * sizeof(char));
		if (curseur->next != NULL) {
		    buffer[tmpLength++]= ',';
		    buffer+= tmpLength;
		}
		totalLength+= tmpLength;
		curseur= curseur->next;
	} while (curseur != NULL);
	return totalLength;
    }
}


/**************************************************
* Implementation: WAssocElement.
**************************************************/


/**************************************************
* Implementation: WAssociationTable.
**************************************************/

WAssociationTable::WAssociationTable(unsigned int aSize)
{
    tableSize= aSize;
    currentPos= 0;
    associations= new WAssocElement[tableSize];
}


WAssociationTable::~WAssociationTable(void)
{
    if (associations != NULL) delete[] associations;
}


void WAssociationTable::bind(PropertyField *aField, void *aDescriptor, unsigned int anOffset)
{
    if (currentPos < tableSize) {
	associations[currentPos].property= aField;
	associations[currentPos].privateDescriptor= aDescriptor;
	associations[currentPos++].index= anOffset;
    }
}


WAssocElement *WAssociationTable::getPropAssoc(char *aName)
{
    for (unsigned int i= 0; i < currentPos; i++) {
	if (strcmp(associations[i].property->getName(), aName) == 0) {
	    return &associations[i];
	}
    }

    return NULL;
}


/**************************************************
* Implementation: WDataEngine.
**************************************************/

WDataEngine::WDataEngine(void)
{
    connectDict= NULL;
    entities= NULL;
}


WDataEngine::~WDataEngine(void)
{
    if (connectDict != NULL) delete connectDict;
    if (entities != NULL) {
	EntityTable *tmpEntity;
	while (entities != NULL) {
	    tmpEntity= entities->getNext();
	    delete entities;
	    entities= tmpEntity;
	}
    }
}


void WDataEngine::setConnectDict(WConnectDictionary *aDict)
{
    if (connectDict != NULL) delete connectDict;
    connectDict= aDict;
}


int WDataEngine::connect(void)
{
    return -1;
}


bool WDataEngine::disconnect(void)
{
    return false;
}


void WDataEngine::addEntity(EntityTable *anEntity)
{
    anEntity->linkTo(entities);
    entities= anEntity;
}


ArrayDO *WDataEngine::fetchAll(EntityTable *anEntity)
{
    ArrayDO *result= NULL;
    unsigned int textLength;
    char tmpBuffer[1024];

	// 1- build statement.
    strcpy(tmpBuffer, "select ");
    textLength= 7;
    textLength+= anEntity->propsAsSelectList(tmpBuffer + textLength);
    strcpy(tmpBuffer + textLength, " from ");
    textLength+= 6;
    strcpy(tmpBuffer + textLength, anEntity->getTableName());

	// 2- execute statement.
    if (execute(tmpBuffer, opSelect) == 0) {
	// 3- extract the information.
	result= new ArrayDO();
	extractData(anEntity, result);
    }
    return result;
}


ArrayDO *WDataEngine::fetchWhere(EntityTable *anEntity, char *whereClause)
{
    // TODO.
}


int  WDataEngine::execute(char *aStatement, Operation anOp)
{
    return -2;		// Not implemented.
}


int  WDataEngine::extractData(EntityTable *anEntity, ArrayDO *resultSet)
{
    return -2;		// Not implemented.
}
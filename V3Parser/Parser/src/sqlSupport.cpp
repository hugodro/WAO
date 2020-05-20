#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "commonData.h"
#include "sqlSupport.h"

/***************************************
* Implementation: InsertStmtSql.
****************************************/

InsertStmtSql::InsertStmtSql(char *aTable)
{
  unsigned int strLng;

  strLng= strlen(aTable);
  tableName= new char[strLng];
  memcpy(tableName, aTable, strLng);

  flatVersion= 0;

  fields= tailFields= 0;
}


InsertStmtSql::~InsertStmtSql()
{
  while (fields != 0) {
    tailFields= fields->getNext();
    delete fields;
    fields= tailFields;
  }
  delete[] flatVersion;
  delete[] tableName;
}


void InsertStmtSql::addField(InsertField *aField)
{
  if (fields == 0) {
    fields= aField;
  }
  else {
    tailFields->linkTo(aField);
  }
  tailFields= aField;
}


void InsertStmtSql::addFieldStr(char *aField, char *aValue)
{
  if ((aValue != 0) && (*aValue != '\0')) {
    unsigned int strLng;
    char *tmpPtr, *aCursor, *bCursor;

    strLng= strlen(aValue) * 3;
    tmpPtr= new char[strLng];
    aCursor= aValue;
    bCursor= tmpPtr;
    while (*aCursor != '\0') {
      if (*aCursor == '\'') {
        if (*(aCursor-1) != '\\')
          *bCursor++= '\\';
      }
      *bCursor++= *aCursor++;
    }
    *bCursor= '\0';
    addField(new StringInsertField(aField, tmpPtr));
    delete[] tmpPtr;
  }
  else {
    addField(new NullValueField(aField));
  }
}


void InsertStmtSql::addFieldNbr(char *aField, long long aValue)
{
  addField(new IntInsertField(aField, aValue));
}


void InsertStmtSql::addFieldNbr(char *aField, long long aValue, int aDecimal)
{
  double value;

  if (aDecimal != 0) {
    unsigned int logValue, logPower;

    logValue= (aDecimal < 0) ? -aDecimal : aDecimal;
    logPower= 1;
    while (logValue > 0) {
      logValue/= 10;
      logPower*= 10;
    }
    aValue= aValue * logPower + aDecimal;
    value= ((double)aValue) / (double)logPower;
  }
  else {
    value= (double)aValue;
  }
  addField(new DoubleInsertField(aField, value));
}


void InsertStmtSql::addFieldDate(char *aField, SimpleDate *aDate)
{
  if (aDate != 0) {
    if (aDate->getDay() == 0) {
      addField(new NullValueField(aField));
    }
    else {
      addField(new DateInsertField(aField, aDate->asText()));
    }
  }
  else {
    addField(new NullValueField(aField));
  }
}


char *InsertStmtSql::render()
{
  InsertField *cursor;
  unsigned int tmpLng;
  char resultString[8192];

  strcpy(resultString, "insert into ");
  strcat(resultString, tableName);
  strcat(resultString, " (");

  cursor= fields;
  while (cursor != 0) {
    strcat(resultString, cursor->getName());
    cursor= cursor->getNext();
    if (cursor != 0)
      strcat(resultString, ", ");
  }

  strcat(resultString, ") values (");

  cursor= fields;
  while (cursor != 0) {
    strcat(resultString, cursor->asText());
    cursor= cursor->getNext();
    if (cursor != 0)
      strcat(resultString, ", ");
  }

  strcat(resultString, ")");

  tmpLng= strlen(resultString) + 1;
  flatVersion= new char[tmpLng];
  memcpy(flatVersion, resultString, tmpLng);
  return flatVersion;
}


InsertField::InsertField(unsigned int aType, char *aName)
{
  next= 0;
  subtype= aType;
  if ((aName != 0) && (*aName != '\0')) {
    unsigned int strLng;
    strLng= strlen(aName) +1;
    name= new char[strLng];
    memcpy(name, aName, strLng);
  }
  else
    name= 0;
}


InsertField::~InsertField()
{
  delete[] name;
}



NullValueField::NullValueField(char *aField)
  : InsertField(StmtSql::nullT, aField)
{

}


char *NullValueField::asText()
{
  return "null";
}



IntInsertField::IntInsertField(char *aField, long long aValue)
  : InsertField(StmtSql::intT, aField)
{
  value= aValue;
  sprintf(flatValue, "%lld", value);
}


char *IntInsertField::asText()
{
  return flatValue;
}


DoubleInsertField::DoubleInsertField(char *aField, double aValue)
  : InsertField(StmtSql::doubleT, aField)
{
  value= aValue;
  sprintf(flatValue, "%f", value);
}


char *DoubleInsertField::asText()
{
  return flatValue;
}


DateInsertField::DateInsertField(char *aField, char *aDate)
  : InsertField(StmtSql::dateT, aField)
{
//TODO: suck in the date.
  value[0]= '\'';
  strcpy(value+1, aDate);
  strcat(value, "\'");
}


char *DateInsertField::asText()
{
  return value;
}


StringInsertField::StringInsertField(char *aField, char *aValue)
  : InsertField(StmtSql::stringT, aField)
{
  if ((aValue != 0) && (*aValue != '\0')) {
    unsigned int strLng;

    strLng= strlen(aValue);
    value= new char[strLng+3];
    value[0]= '\'';
    memcpy(value+1, aValue, strLng);
    value[strLng+1]= '\'';
    value[strLng+2]= '\0';
  }
  else
    value= 0;
}


StringInsertField::~StringInsertField()
{
  delete[] value;
}


char *StringInsertField::asText()
{
  return value;
}



#ifndef _X_AKRALOG_SQLSUPPORT_H_
#define _X_AKRALOG_SQLSUPPORT_H_

class SimpleDate;

class StmtSql {
 public:
  enum DataTypes {
    intT, doubleT, stringT, dateT, nullT
  };
};


class InsertField {
 protected:
  InsertField *next;
  unsigned int subtype;
  char *name;

 public:
  InsertField(unsigned int aType, char *aName);
  virtual ~InsertField();
  virtual char *asText()= 0;

  inline InsertField *getNext() { return next; }
  inline void linkTo(InsertField *aField) { next= aField; }
  inline char *getName() { return name; }
};


class NullValueField : public InsertField {
 public:
  NullValueField(char *aField);
  virtual char *asText();
};


class IntInsertField : public InsertField {
 protected:
  long long value;
  char flatValue[64];

 public:
  IntInsertField(char *aField, long long aValue);
  virtual char *asText();
};


class DoubleInsertField : public InsertField {
 protected:
  double value;
  char flatValue[64];

 public:
  DoubleInsertField(char *aField, double aValue);
  virtual char *asText();
};


class DateInsertField : public InsertField {
 protected:
  char value[13];

 public:
  DateInsertField(char *aField, char *aDate);
  virtual char *asText();
};


class StringInsertField : public InsertField {
 protected:
  char *value;

 public:
  StringInsertField(char *aField, char *aValue);
  virtual ~StringInsertField();
  virtual char *asText();
};


class InsertStmtSql : public StmtSql {
 protected:
  InsertField *fields, *tailFields;
  char *tableName;
  char *flatVersion;

 public:
  InsertStmtSql(char *aTable);
  virtual ~InsertStmtSql();

  virtual void addFieldStr(char *aField, char *aValue);
  virtual void addFieldNbr(char *aField, long long aValue);
  virtual void addFieldNbr(char *aField, long long aValue, int aDecimal);
  virtual void addFieldDate(char *aField, SimpleDate *aDate);

  virtual void addField(InsertField *aField);
  virtual char *render();
};


#endif /* _X_AKRALOG_SQLSUPPORT_H_ */

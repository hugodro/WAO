#ifndef _X_AKRALOG_COMMONDATA_H_
#define _X_AKRALOG_COMMONDATA_H_

class CurrencyValue {
 protected:
  unsigned long long value;
  unsigned int decimal;
  char currency[80];
  bool negativity;
  char *textBuffer;

 public:
  CurrencyValue(char *aString);
  virtual ~CurrencyValue();

  virtual void makeIntoBigNumber(char *someText, unsigned long long &value, unsigned int &decimal);
  virtual char *asText();
  virtual long long getNumber();
  virtual int getDecimal();

  inline char *getCurrency() { return currency; }
  inline bool isNegative() { return negativity; }
};


class SimpleDate {
 protected:
  unsigned int fields[3];
  char *textBuffer;

 public:
  SimpleDate(char *aString);
  virtual ~SimpleDate();
  virtual char *asText();
  inline unsigned int getDay() { return fields[0]; }
};

#endif /* _X_AKRALOG_COMMONDATA_H_ */

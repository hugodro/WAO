#ifndef _X_AKRALOG_HKEXTRADEINFO_H_
#define _X_AKRALOG_HKEXTRADEINFO_H_

#include "extractor.h"

class HkTradeExtract : public Extract {
 public:
  enum Tags {
    dateTimeT, companyT, priceT, netChangeT, bidT, askT, peT
  };

 protected:
  unsigned int dateTime[6];  // 0..5: DD/MM/YYYY HH:MM:SS.
  unsigned int nominalPrice;
  int netChange;
  unsigned int bid;
  unsigned int ask;
  unsigned int pe;
  unsigned int extremas[2];
  unsigned int previousClose;
  unsigned int volume;
  unsigned int turnOver;
  unsigned int code;
  char *cpyName;

 public:
  HkTradeExtract();
  virtual ~HkTradeExtract();
  virtual void load(int aTag, char *someText);
  virtual char *findDate(char *someText);
  virtual char *findTime(char *someText);
  virtual char *findCompanyName(char *someText);
  virtual int findInteger(char *someText);
  virtual void postProcess();

};


class HkTrader : public Extractor {
 protected:
  virtual Extract *allocExtract();

 public:
  virtual Extract *extract(std::istream *aStream, char *aCode);
};

#endif /* _X_AKRALOG_HKEXTRADEINFO_H_ */

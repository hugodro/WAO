#ifndef _X_AKRALOG_HKEXPROFILEINFO_H_
#define _X_AKRALOG_HKEXPROFILEINFO_H_

#include "extractor.h"

class xtnHtmlElement;
class HtScanner;
class CurrencyValue;
class SimpleDate;

class Detail {
 protected:
  Detail *next;
  char *content;

 public:
  Detail(char *aString);
  virtual ~Detail();

  inline char *getText() { return content; }
  inline Detail *getNext() { return next; }
  inline void linkTo(Detail *aDetail) { next= aDetail; }
};


class Dividend {
 protected:
  Dividend *next;
  SimpleDate *exDate;
  SimpleDate *financialYE;
  SimpleDate *bc[2];
  Detail *hDetail, *tDetail;
  char *textBuffer;
  bool gotData;

 public:
  Dividend();
  virtual ~Dividend();
  virtual void setExDate(char *aString);
  virtual void addDetails(char *aString);
  virtual void setYearEnd(char *aString);
  virtual void setBCDate(char *aString);
  virtual void output();

  inline void linkTo(Dividend *aDiv) { next= aDiv; }
  inline Dividend *getNext() { return next; }
};


class HkProfileExtract : public Extract {
 public:
  enum Tags {
    nicknameT, securityNameT, activitiesT, chairmanT, officeT, incorPlaceT
    , bizClassT, registrarT, listingT, tradingCurrT, authSharesT
    , issuedSharesT, parValueT, boardLotT, capitalT
    , yearEndT, netValueT, netProfitT, epsT, updatedOnT
    , entitlementT, dateEntT, detailsEntT, yearEndEntT, bcDateEntT
    , issueAsOfT
  };
  enum Types {
    shareT, warrantT, bondT, fundT
  };

 protected:
  char *cpyNickname;
  unsigned int code;
  char *securityName;
  char *activities;
  char *chairman;
  char *officeAddress;
  char *placeIncorporated;
  char *registrar;
  char *businessClass;
  SimpleDate *listingDate;
  char tradingCurr[80];
  unsigned long long authShares;
  unsigned long long issuedShares;
  SimpleDate *issuedUpdate;
  CurrencyValue *parValue;
  unsigned int boardLot;
  CurrencyValue *marketCap;
  SimpleDate *yearEnd;
  CurrencyValue *netAssetValue;
  CurrencyValue *netProfit;
  CurrencyValue *earningPerShare;
  SimpleDate *updatedOn;
  Dividend *headList, *tailList;
  unsigned int subType;

 public:
  HkProfileExtract();
  virtual ~HkProfileExtract();
  virtual void load(int aTag, char *someText);
  virtual char *findCompanyName(char *someText);
  virtual int findInteger(char *someText);
  virtual void postProcess();
  // String operations:
  virtual char *cleanup(char *someText);
  virtual char *ltrim(char *someText);
  virtual void rtrim(char *someText);
  virtual void ampConvert(char *someText);
  virtual char *cloneString(char *aString);
  virtual void makeIntoDate(char *aString, unsigned int *fields);
  virtual void makeIntoBigInt(char *aString, unsigned long long &value);

  inline char *nullFilter(char *aString) { return ((aString == 0) || (*aString == '\0')) ? (char *)"null" : aString; }
  inline void setSubType(unsigned int aType) { subType= aType; }
};


class HkProfiler : public Extractor {
 protected:
  Extract *products;

 protected:
  virtual Extract *allocExtract();

 public:
  virtual Extract *extract(std::istream *aStream, char *aCode);

  // Grammar:
  virtual xtnHtmlElement *companyScrape(HtScanner *scanner, xtnHtmlElement *tCursor);
  virtual xtnHtmlElement *financialsScrape(HtScanner *scanner, xtnHtmlElement *tCursor);
  virtual xtnHtmlElement *dividendsScrape(HtScanner *scanner, xtnHtmlElement *tRow);
  virtual xtnHtmlElement *warrantScrape(HtScanner *scanner, xtnHtmlElement *tRow);
  virtual xtnHtmlElement *fundScrape(HtScanner *scanner, xtnHtmlElement *tRow);

};


#endif /* _X_AKRALOG_HKEXPROFILEINFO_H_ */

#ifndef _X_AKRALOG_LANDSCAPEGEN_H_
#define _X_AKRALOG_LANDSCAPEGEN_H_

#include <sys/time.h>

#include <list>
#include <sstream>

#include "extractor.h"
#include "pageOfRows.h"


class xtnHtmlElement;
class xtnHtmlAttribute;
class xtnHPcData;
class DBChannel;
class HtScanner;
class PageLS;

/***************************************************
* Definition: LandScoper.
****************************************************/

class LandScoper : public Extractor {
 protected:
  HtScanner *scanner;
  DBChannel *dbLink;
  std::string connDict;
  bool useDB;

 public:
  LandScoper();

  virtual ~LandScoper();
  virtual void setDbDict(char *aHost, char *aDb, char *aUser, char *aPwd);
  virtual void connect();
  virtual void fetchWork();
  virtual void doWork();
  virtual void disconnect();
  virtual void readFile(char *aFileName);
  virtual PageLS *analyzePage(HtScanner *scanner);
};


/***************************************************
* Definition: ItemDB.
****************************************************/

class ItemDB {
 protected:
  unsigned int uid;
};


/***************************************************
* Definition: District.
****************************************************/

class District : ItemDB {
};


/***************************************************
* Definition: Building.
****************************************************/

class Building : ItemDB {
};


/***************************************************
* Definition: Address.
****************************************************/

class Address : ItemDB {
};


/***************************************************
* Definition: SaleLS.
****************************************************/

class SaleLS : public Extract {
 protected:
  std::list<xtnHtmlElement *>columns;
  std::string date;
  District *district;
  Building *building;
  Address *address;
  int area;
  int price;

 public:
  SaleLS();
  virtual ~SaleLS();
};


/***************************************************
* Definition: PageLS.
****************************************************/

class PageLS : public Extract {
 public:

 protected:
  xtnHtmlElement *firstAnchor;
  std::list<SaleLS *> sales;
  unsigned int totalNbrSales;

 public:
  PageLS();
  virtual ~PageLS();
  inline void setAnchor(xtnHtmlElement *anElement) { firstAnchor= anElement; }
};


#endif  /* _X_AKRALOG_LANDSCAPEGEN_H_ */

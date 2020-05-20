#ifndef _X_AKRALOG_GOHOMEHK_H_
#define _X_AKRALOG_GOHOMEHK_H_

#include "extractor.h"
#include "pageOfRows.h"

#include <list>

class xtnHtmlElement;
class xtnHtmlAttribute;
class xtnHPcData;
class xtnHTableRow;
class HtScanner;

class ProductHD;

/***************************************************
* Definition: GoHomeHk.
****************************************************/


class GoHomeHk : public Extractor {
 protected:
  bool useDB;

 public:
  virtual Extract *extract(std::istream *aStream, char *aCode);
  inline void doSerialization() { useDB= true; }

 protected:
  virtual Extract *transactionXtr(HtScanner *scanner);

};


/***************************************************
* Definition: TransactionDetails.
****************************************************/

class TransactionDetails : public ItemRow {
 protected:
  xtnHPcData *modelInfo;
  xtnHPcData *price;

 public:
  TransactionDetails(HtScanner *scanner, xtnHTableRow *aRow);
};


#endif  /* _X_AKRALOG_GOHOMEHK_H_ */

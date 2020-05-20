#ifndef _X_AKRALOG_PAGEOFROWS_H_
#define _X_AKRALOG_PAGEOFROWS_H_

#include "extractor.h"

/***************************************************
* Definition: ItemRow.
****************************************************/

class ItemRow {
 protected:
  ItemRow *next;
};

/***************************************************
* Definition: PageContent.
****************************************************/

class PageContent : public Extract {
 protected:
  ItemRow *items;

 public:
  PageContent();
  inline void setProducts(ItemRow *aList) { items= aList; }
};

#endif  /* _X_AKRALOG_PAGEOFROWS_H_ */

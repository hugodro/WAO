#include <iostream>

#include <coreml/elementList.h>
#include <html/bblockElements.h>
#include <html/htAnalyzer.h>
#include <html/htDoc.h>
#include <html/scanner.h>
#include <html/nonStdElements.h>

#include "problem.h"
#include "goHomeHk.h"


Extract *GoHomeHk::extract(std::istream *aStream, char *aCode)
{
  Extract *extract;
  extract= Extractor::extract(aStream, aCode);

  if (theDoc == NULL)
    return NULL;  // Warning: quick exit.

  HtScanner *scanner;
  xtnHtmlElement *tDiv, *curDiv;
  xtnCoreAttribute *attrib;
  Extract *result;

  scanner= new HtScanner(theDoc);
  useDB= false;

  result= transactionXtr(scanner);

  return result;
}


Extract *GoHomeHk::transactionXtr(HtScanner *scanner)
{
  xtnHtmlElement *cursor, *tmpCur, *baseTable;
  xtnCoreAttribute *attrib;
  PageContent *result;
  TransactionDetails *trans;
  char *value;
  bool hasRows= false;

  result= new PageContent();

  cursor= scanner->searchFor(xtnHtmlDTD::tSpan);
  while ((cursor != NULL) && !hasRows) {
    if ((attrib= cursor->getAttribute("class")) != NULL) {
      if ((value= ((xtnHtmlAttribute *)attrib)->getValue()) != NULL) {
        if ((hasRows= (strcmp(value, "\"subtitle\"") == 0)))
          break;    
      }
    }
    if ((tmpCur= scanner->searchForAt(xtnHtmlDTD::tSpan, cursor, true)) == NULL)
      cursor= scanner->searchForAfter(xtnHtmlDTD::tSpan, cursor);
    else
      cursor= tmpCur;
  }

  if (hasRows) {
    baseTable= scanner->searchForAfter(xtnHtmlDTD::tTable, cursor);
    if (baseTable != NULL) {
      cursor= scanner->searchForAt(xtnHtmlDTD::tTr, baseTable, true);
      while (cursor != NULL) {
        //TODO: extract data.
        std::cout << "@DBG [GoHomeHk.transactionXtr] found a tr at: " << cursor->getStartPos() << "\n";
        // Check if we are at header row (if skip if so).
        if ((attrib= cursor->getAttribute("class")) != NULL) {
          if ((value= ((xtnHtmlAttribute *)attrib)->getValue()) != NULL) {
            if ((hasRows= (strcmp(value, "\"subheader\"") == 0)))
              cursor= scanner->searchForAfter(xtnHtmlDTD::tTr, cursor, baseTable);
              continue;
          }
        }
        tmpCur= scanner->searchForAt(xtnHtmlDTD::tTd, cursor, true);
        if ((attrib= tmpCur->getAttribute("class")) != NULL) {
          if ((value= ((xtnHtmlAttribute *)attrib)->getValue()) != NULL) {
            if (strcmp(value, "\"td_set\"") == 0) {
              trans= new TransactionDetails(scanner, (xtnHTableRow *)cursor);
            }
            else
              break;
          }
        }
        cursor= scanner->searchForAfter(xtnHtmlDTD::tTr, cursor, baseTable);
      }
    }

  }
  return result;
}


TransactionDetails::TransactionDetails(HtScanner *scanner, xtnHTableRow *aRow) {
  xtnHtmlElement *cursor, *anchor;
  unsigned int position;

  cursor= scanner->searchForAt(xtnHtmlDTD::tTd, aRow, true);
  position= 0;

  while (cursor != NULL) {
    xtnHPcData *text;
    if ((text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, cursor, true)) != NULL) {
      switch(position) {
        case 0: // Inst. Date.
          std::cout << "@DBG [TransactionDetails.constr]: inst date: " << text->getData() << ".\n";
          break;
        case 1: // Estate Building.
          if ((anchor= scanner->searchForAfter(xtnHtmlDTD::tA, text, cursor)) != NULL) {
            if ((text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, anchor, true)) != NULL) {
            std::cout << "@DBG [TransactionDetails.constr]: Estate Building: " << text->getData() << ".\n";
            }
          }
          break;
        case 2: // Block.
          if ((anchor= scanner->searchForAfter(xtnHtmlDTD::tA, text, cursor)) != NULL) {
            if ((text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, anchor, true)) != NULL) {
            std::cout << "@DBG [TransactionDetails.constr]: Block: " << text->getData() << ".\n";
            }
          }
          break;
        case 3: // Floor.
          std::cout << "@DBG [TransactionDetails.constr]: Floor: " << text->getData() << ".\n";
          break;
        case 5: // Price(M).
          std::cout << "@DBG [TransactionDetails.constr]: Price: " << text->getData() << ".\n";
          break;
        case 6: // Net Size.
          std::cout << "@DBG [TransactionDetails.constr]: Net Size: " << text->getData() << ".\n";
          break;
        case 7: // Size.
          std::cout << "@DBG [TransactionDetails.constr]: Size: " << text->getData() << ".\n";
          break;
        case 9: // Price/sq.ft.
          std::cout << "@DBG [TransactionDetails.constr]: Price/sq.ft: " << text->getData() << ".\n";
          break;
        case 10: // Built Year.
          std::cout << "@DBG [TransactionDetails.constr]: Built Year: " << text->getData() << ".\n";
          break;
        case 11: // Type.
          std::cout << "@DBG [TransactionDetails.constr]: Type: " << text->getData() << ".\n";
          break;
        default:
          if ((position != 4) && (position != 8))
            std::cout << "@DBG [TransactionDetails.constr]: unknown: " << text->getData() << ".\n";
          break;
      }
    }
    position++;
    cursor= scanner->searchForAfter(xtnHtmlDTD::tTd, cursor, aRow);
  }
}

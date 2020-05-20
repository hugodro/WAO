#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>

#include <iostream>

#include <coreml/elementList.h>
#include <html/htAnalyzer.h>
#include <html/htDoc.h>
#include <html/scanner.h>
#include <html/nonStdElements.h>

#include "problem.h"
#include "dbSupport.h"
#include "landScope.h"


/***************************************************
* Implementation: PageLS.
****************************************************/
PageLS::PageLS()
 : Extract(1)
{
  firstAnchor= 0;
  totalNbrSales= 0;
}


PageLS::~PageLS()
{
}

  
/***************************************************
* Implementation: LandScoper.
****************************************************/

LandScoper::LandScoper()
{
  useDB= false;
  dbLink= 0;
}


LandScoper::~LandScoper()
{
  delete dbLink;
}


void LandScoper::setDbDict(char *aHost, char *aDb, char *aUser, char *aPwd)
{
  if (useDB) {
    connDict= "host=";
    connDict+= aHost;
    connDict+= " user= ";
    connDict+= aUser;
    connDict+= " dbname=";
    connDict+= aDb;
    connDict+= " password=";
    connDict+= aPwd;
  }
}


void LandScoper::connect()
{
  if (useDB) {
    dbLink= new PostgresChannel(connDict.c_str());
    dbLink->connect();
  }
/*TODO: throw an error if the db is not available.
  if (dbLink->status() != 0) {
  }
*/
}


void LandScoper::fetchWork()
{
// TODO.
}


void LandScoper::doWork()
{
  if (useDB) {
    //TODO.
  }
  else {
    if (theDoc != 0) {
      scanner= new HtScanner(theDoc);
      analyzePage(scanner);
    }
    else {
      // TODO: throw an exception.
    }
  }
}


void LandScoper::disconnect()
{
  if (useDB) {
    dbLink->disconnect();
  }
}


void LandScoper::readFile(char *aFileName)
{
  std::istream *inputStream;

  inputStream= new std::ifstream(aFileName, std::ios::in | std::ios::binary);
  Extractor::extract(inputStream, aFileName);
}


PageLS *LandScoper::analyzePage(HtScanner *scanner) {
  PageLS *result;
  xtnHtmlElement *cursor, *tmpCur;
  xtnCoreAttribute *attrib;
  bool keepPage= false;

  result= new PageLS();
  cursor= scanner->searchFor(xtnHtmlDTD::tTable);
  while (cursor != 0) {
    if ((attrib= cursor->getAttribute("id")) != 0) {
      char *value;

      value= ((xtnHtmlAttribute *)attrib)->getValue();
      if (strcmp(value, "\"listing\"") == 0) {
        xtnHtmlElement *trCur;
        bool isFirst= true;

        // Scan all rows: skip first, extract sale info from subsequent.
        trCur= scanner->searchForAt(xtnHtmlDTD::tTr, cursor, true);
        while (trCur != 0) {
          if (!isFirst) {
            xtnHtmlElement *tdCur, *brCur;
            xtnHPcData *pcCursor;
            unsigned int pos= 0;

            tdCur= scanner->searchForAt(xtnHtmlDTD::tTd, trCur, true);
            while (tdCur != 0) {
              switch(pos) {
                case 0:  // Date.
                  if ((pcCursor= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, tdCur, true)) != 0) {
                      std::cout << "0:[" << pcCursor->getData() << "] ";
                  }
                  break;
                case 1:  // District.
                  if ((pcCursor= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, tdCur, true)) != 0) {
                      std::cout << "1:[" << pcCursor->getData() << "] ";
                  }
                  break;
                case 2:  // Building.
                  if ((pcCursor= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, tdCur, true)) != 0) {
                      std::cout << "2:[" << pcCursor->getData() << "] ";
                  }
                  break;
                case 3:  // Address.
                    // Here we need to iterate over the <br>.
                  if ((pcCursor= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, tdCur, true)) != 0) {
                      std::cout << "3:[" << pcCursor->getData();
                  }
                  brCur= (xtnHPcData *)scanner->searchForAfter(xtnHtmlDTD::tBr, pcCursor, tdCur);
                  while (brCur != 0) {
                    if ((pcCursor= (xtnHPcData *)scanner->searchForAfter(xtnHtmlDTD::tPcdata, brCur, tdCur)) != 0) {
                        std::cout << "||" << pcCursor->getData() << "";
                    }
                    brCur= (xtnHPcData *)scanner->searchForAfter(xtnHtmlDTD::tBr, brCur, tdCur);
                  }
                  std::cout << "] ";
                  break;
                case 4:  // Area.
                  if ((pcCursor= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, tdCur, true)) != 0) {
                      std::cout << "4:[" << pcCursor->getData() << "] ";
                  }
                  break;
                case 5:  // Price.
                  if ((pcCursor= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, tdCur, true)) != 0) {
                      std::cout << "5:[" << pcCursor->getData() << "]\n";
                  }
                  // Note: the $/sq.ft is after the <br>.
                  break;
              }
              pos++;
              tdCur= scanner->searchForAfter(xtnHtmlDTD::tTd, tdCur, trCur);
            }
          }
          else {
            isFirst= false;
            keepPage= true;
          }
          trCur= scanner->searchForAfter(xtnHtmlDTD::tTr, trCur, cursor);
        }

      }
    }

    if ((tmpCur= scanner->searchForAt(xtnHtmlDTD::tTable, cursor, true)) == 0)
      cursor= scanner->searchForAfter(xtnHtmlDTD::tTable, cursor);
    else
      cursor= tmpCur;
  }

  if (keepPage)
    return result;
  else {
    delete result;
    return 0;
  }
}


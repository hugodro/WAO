#include <iostream>

#include <coreml/elementList.h>
#include <html/htAnalyzer.h>
#include <html/htDoc.h>
#include <html/scanner.h>
#include <html/nonStdElements.h>

#include "problem.h"
#include "hkTrader.h"


/***************************************
* Implementation: HkTradeExtract.
****************************************/

// Expected data:
// "\r\n\t          Last Updated: 11/10/2007 &nbsp; 08:01:00 HKT\r\n        \t  "
// "\r\n\t          ESPRIT HOLDINGS (330  )\r\n        \t  "
// "128.4", "0", "0", "0", "\r\n27.17  \r\n\t"


HkTradeExtract::HkTradeExtract()
 : Extract(1) {
  dateTime[0]= dateTime[1]= dateTime[2]= dateTime[3]= dateTime[4]= dateTime[5]= 0;
  nominalPrice= 0;
  pe= 0;
  code= 0;
  cpyName= 0;
}


HkTradeExtract::~HkTradeExtract() {
  delete[] cpyName;
}

void HkTradeExtract::load(int aTag, char *someText)
{
  // TODO: Add error handling management.
  // Jump the padding characters.
  do {
    if ((*someText != '\r') && (*someText != '\n') && (*someText != ' ') && (*someText != '\t')) {
      break;
    }
    someText++;
  } while (someText != '\0');

  switch(aTag) {
    case dateTimeT:
      someText= findDate(someText);
      if (someText != 0) {
        someText= findTime(someText);
      }
      break;
    case companyT:
      findCompanyName(someText);
      break;
    case priceT:
      nominalPrice= findInteger(someText);
      break;
    case netChangeT:
      netChange= findInteger(someText);
      break;
    case bidT:
      bid= findInteger(someText);
      break;
    case askT:
      ask= findInteger(someText);
      break;
    case peT:
      pe= findInteger(someText);
      break;
  }
}

char *HkTradeExtract::findDate(char *someText)
{
  //TODO: Use a better scanning system than this!
  //TODO: Handle errors in text.

  do {
   if (isdigit(*someText)) break;
   someText++;
  } while (*someText != '\0');

  if (*someText == '\0') return 0;

  // Day:
  if (isdigit(*(someText+1))) {
    dateTime[0]= (unsigned int)(*someText - 0x030) * 10 + (unsigned int)(*(someText+1) - 0x030);
    someText+= 3;
  }
  else {
    dateTime[0]= (unsigned int)(*someText - 0x030);
    someText+= 2;
  }

  // Month:
  if (isdigit(*(someText+1))) {
    dateTime[1]= (unsigned int)(*someText - 0x030) * 10 + (unsigned int)(*(someText+1) - 0x030);
    someText+= 3;
  }
  else {
    dateTime[1]= (unsigned int)(*someText - 0x030);
    someText+= 2;
  }

  // Year:
  unsigned int nbrDigits= 0, multiplier= 1;

  if (isdigit(*someText)) {
    nbrDigits++;
    if (isdigit(*(someText+1))) {
      nbrDigits++;
      if (isdigit(*(someText+2))) {
        nbrDigits++;
        if (isdigit(*(someText+3))) {
          nbrDigits++;
        }
      }
    }
  }

  for (unsigned int i= 1; i < nbrDigits; i++)
    multiplier*= 10;

  for (unsigned int i= nbrDigits; i > 0; i--) {
    dateTime[2]+= (unsigned int)(*someText - 0x030) * multiplier;
    someText++;
    multiplier/= 10;
  }

  return someText;
}


char *HkTradeExtract::findTime(char *someText)
{
  do {
   if (isdigit(*someText)) break;
   someText++;
  } while (*someText != '\0');

  if (*someText == '\0') return 0;

  // Hour:
  if (isdigit(*(someText+1))) {
    dateTime[3]= (unsigned int)(*someText - 0x030) * 10 + (unsigned int)(*(someText+1) - 0x030);
    someText+= 3;
  }
  else {
    dateTime[3]= (unsigned int)(*someText - 0x030);
    someText+= 2;
  }

  // Minute:
  if (isdigit(*(someText+1))) {
    dateTime[4]= (unsigned int)(*someText - 0x030) * 10 + (unsigned int)(*(someText+1) - 0x030);
    someText+= 3;
  }
  else {
    dateTime[4]= (unsigned int)(*someText - 0x030);
    someText+= 2;
  }

  // Second:
  if (isdigit(*(someText+1))) {
    dateTime[5]= (unsigned int)(*someText - 0x030) * 10 + (unsigned int)(*(someText+1) - 0x030);
    someText+= 3;
  }
  else {
    dateTime[5]= (unsigned int)(*someText - 0x030);
    someText+= 2;
  }
}


char *HkTradeExtract::findCompanyName(char *someText)
{
  unsigned int lng, nbrApos;
  char *endings[2];

  endings[0]= someText;
  do {
    if (*someText == '(') {
      break;
    }
    someText++;
  } while (someText != '\0');
  endings[1]= someText;

  lng= endings[1] - endings[0];
  nbrApos= 0;

  for (char *scanner= endings[0]; scanner < endings[1]; scanner++) {
    if (*scanner == '\'')
      nbrApos++;
  }

  lng+= nbrApos;
  cpyName= new char[lng];
  if (nbrApos == 0) {
    memcpy(cpyName, endings[0], lng-1);
  }
  else {
    char *scanner, *cursor;

    for (scanner= endings[0], cursor= cpyName; scanner < endings[1];) {
      if (*scanner == '\'')
        *cursor++= '\\';
      *cursor++= *scanner++;
    }
  }
  cpyName[lng-1]= '\0';
  code= findInteger(endings[1]+1)/100;
  return endings[1]+1;
}


int HkTradeExtract::findInteger(char *someText)
{
  float tmpFloat;
  int result= 0;

  sscanf(someText, "%f", &tmpFloat);
  result= (int)(1000 * tmpFloat);
  if ((result % 10) > 4) result+= 10;
  result/= 10;
  return result;
}


void HkTradeExtract::postProcess()
{
  std::cout << "insert into dtim.hktradeinfo (code, moment, cName, price, pe) values ("
    << code << ", '"
    << dateTime[2] << "/" << dateTime[1] << "/" << dateTime[0] << " "
    << dateTime[3] << ":" << dateTime[4] << ":" << dateTime[5] << "', '"
    << cpyName << "', "
    << nominalPrice << ".0/100.0, " << pe << ".0/100.0);\n";
}


/***************************************
* Implementation: HkTrader.
****************************************/

Extract *HkTrader::allocExtract()
{
  return new HkTradeExtract();
}


Extract *HkTrader::extract(std::istream *aStream, char *aCode)
{
  HkTradeExtract *extract;

  extract= (HkTradeExtract *)Extractor::extract(aStream, aCode);

  if (theDoc != NULL) {
    HtScanner *scanner;
    xtnHtmlElement *bodyCur, *tRow, *tCursor;
    xtnHPcData *text;

    scanner= new HtScanner(theDoc);

    // TODO: Add error handling management.

    bodyCur= scanner->searchFor(xtnHtmlDTD::tTable);
    if (bodyCur == NULL) throw new ParseProblem("no table found");
    bodyCur= scanner->searchForAt(xtnHtmlDTD::tTable, bodyCur, true);
    if (bodyCur == NULL) throw new ParseProblem("no sub-table found");
    tRow= scanner->searchForAt(xtnHtmlDTD::tTr, bodyCur, true);
    if (tRow == NULL) throw new ParseProblem("no row in sub-table");
    tRow= scanner->searchForAfter(xtnHtmlDTD::tTr, tRow);
    if (tRow == NULL) throw new ParseProblem("no 2nd row in sub-table");
    tRow= scanner->searchForAfter(xtnHtmlDTD::tTr, tRow);
    if (tRow == NULL) throw new ParseProblem("no 3rd row in sub-table");

    // Find font:
    tCursor= scanner->searchForAt(xtnHtmlDTD::tFont, tRow);
    if (tCursor == NULL) throw new ParseProblem("no font found");
    // Extract date/time.
    text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, tCursor, true);
    // std::cerr << "@DBG [] xval\"" << text->getData() << "\".\n";
    extract->load(HkTradeExtract::dateTimeT, text->getData());

    // Jump 2 tr to stock name:
    tRow= scanner->searchForAfter(xtnHtmlDTD::tTr, tCursor);
    tRow= scanner->searchForAfter(xtnHtmlDTD::tTr, tRow);
    tCursor= scanner->searchForAt(xtnHtmlDTD::tFont, tRow);
    text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, tCursor, true);
    // std::cerr << "@DBG [] xval\"" << text->getData() << "\".\n";
    extract->load(HkTradeExtract::companyT, text->getData());


    // Jump 3 tr to price/bid/pe array of columns.
    tRow= scanner->searchForAfter(xtnHtmlDTD::tTr, tRow);
    tRow= scanner->searchForAfter(xtnHtmlDTD::tTr, tRow);
    tRow= scanner->searchForAfter(xtnHtmlDTD::tTr, tRow);
    // Extract 6 values.
    tCursor= scanner->searchForAt(xtnHtmlDTD::tFont, tRow);
    text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, tCursor, true);
    // std::cerr << "@DBG [] xval\"" << text->getData() << "\".\n";
    extract->load(HkTradeExtract::priceT, text->getData());

    tCursor= scanner->searchForAfter(xtnHtmlDTD::tFont, tCursor);
    text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, tCursor, true);
    // std::cerr << "@DBG [] xval\"" << text->getData() << "\".\n";
    extract->load(HkTradeExtract::netChangeT, text->getData());

    tCursor= scanner->searchForAfter(xtnHtmlDTD::tFont, tCursor);
    text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, tCursor, true);
    // std::cerr << "@DBG [] xval\"" << text->getData() << "\".\n";

    tCursor= scanner->searchForAfter(xtnHtmlDTD::tFont, tCursor);
    text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, tCursor, true);
    // std::cerr << "@DBG [] xval\"" << text->getData() << "\".\n";
    extract->load(HkTradeExtract::bidT, text->getData());

    tCursor= scanner->searchForAfter(xtnHtmlDTD::tFont, tCursor);
    text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, tCursor, true);
    // std::cerr << "@DBG [] xval\"" << text->getData() << "\".\n";
    extract->load(HkTradeExtract::askT, text->getData());

    tCursor= scanner->searchForAfter(xtnHtmlDTD::tFont, tCursor);
    text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, tCursor, true);
    // std::cerr << "@DBG [] xval\"" << text->getData() << "\".\n";
    extract->load(HkTradeExtract::peT, text->getData());

    // Jump 3 tr to high/low/volume array of columns.
    tRow= scanner->searchForAfter(xtnHtmlDTD::tTr, tRow);
    tRow= scanner->searchForAfter(xtnHtmlDTD::tTr, tRow);
    tRow= scanner->searchForAfter(xtnHtmlDTD::tTr, tRow);
    // Extract 6 values.
    tCursor= scanner->searchForAt(xtnHtmlDTD::tFont, tRow);
    text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, tCursor, true);
    // std::cerr << "@DBG [] xval\"" << text->getData() << "\".\n";
    tCursor= scanner->searchForAfter(xtnHtmlDTD::tFont, tCursor);
    text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, tCursor, true);
    // std::cerr << "@DBG [] xval\"" << text->getData() << "\".\n";
    tCursor= scanner->searchForAfter(xtnHtmlDTD::tFont, tCursor);
    text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, tCursor, true);
    // std::cerr << "@DBG [] xval\"" << text->getData() << "\".\n";
    tCursor= scanner->searchForAfter(xtnHtmlDTD::tFont, tCursor);
    text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, tCursor, true);
    // std::cerr << "@DBG [] xval\"" << text->getData() << "\".\n";
    tCursor= scanner->searchForAfter(xtnHtmlDTD::tFont, tCursor);
    text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, tCursor, true);
    // std::cerr << "@DBG [] xval\"" << text->getData() << "\".\n";
    tCursor= scanner->searchForAfter(xtnHtmlDTD::tFont, tCursor);
    text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, tCursor, true);
    // std::cerr << "@DBG [] xval\"" << text->getData() << "\".\n";
  }
  return extract;
}

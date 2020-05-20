#include <stdlib.h>

#include <iostream>

#include <coreml/elementList.h>
#include <html/htAnalyzer.h>
#include <html/htDoc.h>
#include <html/scanner.h>
#include <html/nonStdElements.h>

#include "problem.h"
#include "commonData.h"
#include "sqlSupport.h"
#include "hkProfile.h"


/***************************************
* Implementation: Detail.
****************************************/
Detail::Detail(char *aString)
{
  next= 0;
  if (aString != 0) {
    if (*aString != '\0') {
      unsigned int tmpLng;

      tmpLng= strlen(aString) + 1;
      content= new char[tmpLng];
      memcpy(content, aString, tmpLng);
    }
    else
      content= 0;
  }
  else
    content= 0;
}


Detail::~Detail()
{
  delete[] content;
}


/***************************************
* Implementation: Dividend.
****************************************/
Dividend::Dividend()
{
  next= 0;
  exDate= 0;
  financialYE= 0;
  bc[0]= bc[1]= 0;
  hDetail= tDetail= 0;
  gotData= 0;
  textBuffer= 0;
  gotData= false;
}


Dividend::~Dividend()
{
  delete exDate;
  delete financialYE;
  delete bc[0];
  delete bc[1];
  while (hDetail != 0) {
    tDetail= hDetail->getNext();
    delete hDetail;
    hDetail= tDetail;
  }

  delete[] textBuffer;
}


void Dividend::setExDate(char *aString)
{
  if (aString != 0) {
    if (*aString != '\0') {
      if (isdigit(*aString)) {
        exDate= new SimpleDate(aString);
        gotData= true;
      }
    }
  }
}



void Dividend::addDetails(char *aString)
{
  Detail *newObj;

  newObj= new Detail(aString);
  if (hDetail == 0) {
    hDetail= newObj;
  }
  else {
    tDetail->linkTo(newObj);
  }
  tDetail= newObj;
}



void Dividend::setYearEnd(char *aString)
{
  if (aString != 0) {
    if (*aString != '\0') {
      if (isdigit(*aString)) {
        financialYE= new SimpleDate(aString);
        gotData= true;
      }
    }
  }
}



void Dividend::setBCDate(char *aString)
{
  if (aString != 0) {
    if (*aString != '\0') {
      char *tmpPtr;

      tmpPtr= strchr(aString, '-');
      if (isdigit(*aString)) {
        bc[0]= new SimpleDate(aString);
        gotData= true;
      }
      if (tmpPtr != 0) {
        if (isdigit(*(tmpPtr+2))) {
          bc[1]= new SimpleDate(aString);
        }
      }
    }
  }
}


void Dividend::output()
{
  if (!gotData) return;
  std::cout << "@DBG [Dividend.asText] -----------------------\n";

  if (exDate != 0)
    std::cout << "@DBG [Dividend.asText] exDate: " << exDate->asText() << ".\n";
  Detail *cursor;
  cursor= hDetail;
  while (cursor != 0) {
    if (cursor->getText() == 0)
      break;
    std::cout << "@DBG [Dividend.asText] detail: " << cursor->getText() << ".\n";
    cursor= cursor->getNext();
  }
  if (financialYE != 0)
    std::cout << "@DBG [Dividend.asText] year end: " << financialYE->asText() << ".\n";
  if (bc[0] != 0)
    std::cout << "@DBG [Dividend.asText] begin: " << bc[0]->asText() << ".\n";
  if (bc[1] != 0)
    std::cout << "@DBG [Dividend.asText] close: " << bc[1]->asText() << ".\n";
}


/***************************************
* Implementation: HkProfileExtract.
****************************************/


HkProfileExtract::HkProfileExtract()\
 : Extract(1)
{
  cpyNickname= 0;
  securityName= 0;
  activities= 0;
  chairman= 0;
  officeAddress= 0;
  placeIncorporated= 0;
  registrar= 0;
  businessClass= 0;
  headList= tailList= 0;
}


HkProfileExtract::~HkProfileExtract()
{
  delete[] cpyNickname;
  delete[] securityName;
  delete[] activities;
  delete[] chairman;
  delete[] officeAddress;
  delete[] placeIncorporated;
  delete[] registrar;
  delete[] businessClass;

  while (headList != 0) {
    tailList= headList->getNext();
    delete headList;
    headList= tailList;
  }
}


void HkProfileExtract::load(int aTag, char *someText)
{

  someText= cleanup(someText);

#if defined(SPIT_LOADED_TXT)
  std::cout << "@DBG [HkProfileExtract::load] tag " << aTag << " txt: |" << ((someText == 0) ? "<nil>" : someText) << "|\n";
#endif

  switch(aTag) {
    case nicknameT:
      findCompanyName(someText);
      break;
    case securityNameT:
      securityName= cloneString(someText);
      break;
    case activitiesT:
      activities= cloneString(someText);
      break;
    case chairmanT:
      chairman= cloneString(someText);
      break;
    case officeT:
      if ((someText != 0) && (*someText != '\0')) {
        if (officeAddress == 0) {
          officeAddress= cloneString(someText);
        }
        else {
          unsigned int strLng;
          char *tmpPtr;
  
          strLng= strlen(someText) + strlen(officeAddress) + 2;
          tmpPtr= new char[strLng];
          strcpy(tmpPtr, officeAddress);
          strcat(tmpPtr, "\n");
          strcat(tmpPtr, someText);
          delete[] officeAddress;
          officeAddress= tmpPtr;
        }
      }
      break;
    case incorPlaceT:
      placeIncorporated= cloneString(someText);
      break;
    case bizClassT:
      businessClass= cloneString(someText);
      break;
    case registrarT:
      registrar= cloneString(someText); 
      break;
    case listingT:
      listingDate= new SimpleDate(someText);
      break;
    case tradingCurrT:
      strcpy(tradingCurr, someText);
      break;
    case authSharesT:
      makeIntoBigInt(someText, authShares);
      break;
    case issuedSharesT:
      makeIntoBigInt(someText, issuedShares);
      break;
    case issueAsOfT:
      issuedUpdate= new SimpleDate(someText);
      break;
    case parValueT:
      parValue= new CurrencyValue(someText);
      break;
    case boardLotT:
      boardLot= atoi(someText);
      break;
    case capitalT:
      marketCap= new CurrencyValue(someText);
      break;
    case yearEndT:
      yearEnd= new SimpleDate(someText);
      break;
    case netValueT:
      netAssetValue= new CurrencyValue(someText);
      break;
    case netProfitT:
      netProfit= new CurrencyValue(someText);
      break;
    case epsT:
      earningPerShare= new CurrencyValue(someText);
      break;
    case updatedOnT:
      updatedOn= new SimpleDate(someText);
      break;
    case entitlementT: {
      Dividend *dividend;
      
      dividend= new Dividend();
      if (headList == 0) {
        headList= dividend;
      }
      else {
        tailList->linkTo(dividend);
      }
      tailList= dividend;
      } break;
    case dateEntT:
      tailList->setExDate(someText);
      break;
    case detailsEntT:
      tailList->addDetails(someText);
      break;
    case yearEndEntT:
      tailList->setYearEnd(someText);
      break;
    case bcDateEntT:
      tailList->setBCDate(someText);
      break;
  };
}


char *HkProfileExtract::findCompanyName(char *someText)
{
  unsigned int lng, nbrApos;
  char *endings[2], *tmpPtr;

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

  cpyNickname= new char[lng];
  memcpy(cpyNickname, endings[0], lng-1);
  cpyNickname[lng-1]= '\0';

  tmpPtr= strrchr(endings[1], '(');
  if (tmpPtr != 0) {
    code= findInteger(tmpPtr+1)/100;
  }
  return endings[1]+1;
}


int HkProfileExtract::findInteger(char *someText)
{
  float tmpFloat;
  int result= 0;

  sscanf(someText, "%f", &tmpFloat);
  result= (int)(1000 * tmpFloat);
  if ((result % 10) > 4) result+= 10;
  result/= 10;
  return result;
}


void HkProfileExtract::postProcess()
{
  if (subType == shareT) {
#if defined(DEBUG_OUTPUT)
    std::cout << "@DBG [HkProfileExtract.postProcess] ****************************************\n";
    std::cout << "@DBG [HkProfileExtract.output] nick: " << cpyNickname << ", code: " << code << ".\n";
    std::cout << "@DBG [HkProfileExtract.output] cpy name: " << nullFilter(securityName) << ".\n";
    std::cout << "@DBG [HkProfileExtract.output] activities: " << nullFilter(activities) << ".\n";
    std::cout << "@DBG [HkProfileExtract.output] chairman: " << nullFilter(chairman) << ".\n";
    std::cout << "@DBG [HkProfileExtract.output] officeAddress: " << nullFilter(officeAddress) << ".\n";
    std::cout << "@DBG [HkProfileExtract.output] place Inc: " << nullFilter(placeIncorporated) << ".\n";
    std::cout << "@DBG [HkProfileExtract.output] registrar: " << nullFilter(registrar) << ".\n";
    std::cout << "@DBG [HkProfileExtract.output] bizClass: " << nullFilter(businessClass) << ".\n";
    std::cout << "@DBG [HkProfileExtract.output] listing date: " << listingDate->asText() << ".\n";
    std::cout << "@DBG [HkProfileExtract.output] tradeCurr: " << tradingCurr << ".\n";
    std::cout << "@DBG [HkProfileExtract.output] auth shares: " << authShares << ".\n";
    std::cout << "@DBG [HkProfileExtract.output] issued shares: " << issuedShares << ".\n";
    std::cout << "@DBG [HkProfileExtract.output] issuedUpdate: " << issuedUpdate->asText() << ".\n";
  
    std::cout << "@DBG [HkProfileExtract.output] parValue: " << parValue->asText() << ".\n";
    std::cout << "@DBG [HkProfileExtract.output] boardLot: " << boardLot << ".\n";
    std::cout << "@DBG [HkProfileExtract.output] marketCap: " << marketCap->asText() << ".\n";
    std::cout << "@DBG [HkProfileExtract.output] yearEnd: " << yearEnd->asText() << ".\n";
    std::cout << "@DBG [HkProfileExtract.output] netAssetValue: " << netAssetValue->asText() << ".\n";
    std::cout << "@DBG [HkProfileExtract.output] netProfit: " << netProfit->asText() << ".\n";
    std::cout << "@DBG [HkProfileExtract.output] earningPerShare: " << earningPerShare->asText() << ".\n";
    std::cout << "@DBG [HkProfileExtract.output] updatedOn: " << updatedOn->asText() << ".\n";
#endif

    InsertStmtSql *query;
    query= new InsertStmtSql("dtim.hkprofileinfo");
    query->addFieldStr("nickname", cpyNickname);
    query->addFieldNbr("code", code);

    query->addFieldStr("fullName", securityName);
    query->addFieldStr("activities", activities);
    query->addFieldStr("chairman", chairman);
    query->addFieldStr("officeAddress", officeAddress);
    query->addFieldStr("incorpPlace", placeIncorporated);
    query->addFieldStr("registrar", registrar);
    query->addFieldStr("bizClass", businessClass);
    query->addFieldDate("listedOn", listingDate);
    query->addFieldStr("tradeCurr", tradingCurr);
    query->addFieldNbr("authShares", authShares);
    query->addFieldNbr("issuedShares", issuedShares);
    query->addFieldDate("issuedAsOf", issuedUpdate);
  
    query->addFieldNbr("parValue", parValue->getNumber(), parValue->getDecimal());
    query->addFieldStr("pvCurrency", parValue->getCurrency());
    query->addFieldNbr("boardLot", boardLot);
    query->addFieldNbr("marketCap", marketCap->getNumber(), marketCap->getDecimal());
    query->addFieldStr("mcCurrency", marketCap->getCurrency());
    query->addFieldDate("yearEnd", yearEnd);
    query->addFieldNbr("netAssetValue", netAssetValue->getNumber(), netAssetValue->getDecimal());
    query->addFieldStr("navCurrency", netAssetValue->getCurrency());
    query->addFieldNbr("netProfit", netProfit->getNumber(), netProfit->getDecimal());
    query->addFieldStr("npCurrency", netProfit->getCurrency());
    query->addFieldNbr("earningPerShare", earningPerShare->getNumber(), earningPerShare->getDecimal());
    query->addFieldStr("epsCurrency", earningPerShare->getCurrency());
    query->addFieldDate("updatedOn", updatedOn);

    std::cout << query->render() << ";\n";

#if defined(DEBUG_OUTPUT)
    Dividend *cursor;
    cursor= headList;
    while (cursor != 0) {
      cursor->output();
      cursor= cursor->getNext();
    }
    std::cout << "@DBG [HkProfileExtract.output] ****************************************\n";
#endif
  }
  else {
    std::cout << "-- TODO: [" << code << ", " << cpyNickname << "] type " << subType << ".\n";
  }
}


char *HkProfileExtract::cleanup(char *someText) {
  someText= ltrim(someText);

  if (someText != 0) {
    ampConvert(someText);
    rtrim(someText);
  }

  return someText;
}


char *HkProfileExtract::ltrim(char *someText)
{
  while (someText != '\0') {
    if ((*someText != '\r') && (*someText != '\n') && (*someText != ' ') && (*someText != '\t')) {
      break;
    }
    someText++;
  };

  return someText;
}


void HkProfileExtract::rtrim(char *someText)
{
  char *cursor;

  if (*someText == '\0') return;

  for (cursor= someText; *cursor != '\0'; cursor++);
  cursor--;
  while (((*cursor == ' ') || (*cursor == '\r') || (*cursor == '\n') || (*cursor == '\t')) && (cursor > someText)) {
    cursor--;
  }
  if (cursor == someText) {
    *cursor= '\0';
  }
  else {
    if (*cursor != '\0') {
      *(cursor+1)= '\0';
    }
  }
}


void HkProfileExtract::ampConvert(char *someText)
{
  char *cursor, *cpyDest, *ampPos;
  unsigned int scanMode= 0;

  cursor= cpyDest= someText;

  while (*cursor != '\0') {
    switch(scanMode) {
      case 0:
        if (*cursor == '&') {
          scanMode= 1;
          ampPos= cursor;
        }
        else {
          *cpyDest++= *cursor;
        }
        break;

      case 1:
        if (!isalpha(*cursor)) {
         scanMode= 0;
         if (*cursor == ';') {
            //TODO: check what is between ampPos & cursor, remplace *cpyDest with the proper char.
            //ATTN: For now we assume we have it a &nbsp;
            *cpyDest++= ' ';
          }
          else {
            for (; ampPos <= cursor;) {
              *cpyDest++= *ampPos++;
            }
          }
        }
        break;
    }

    cursor++;
  }

  //TODO: Take care of case where sentence ends with a &[!;]+.
  // Put the padding in any case:
  *cpyDest= '\0';
}


char *HkProfileExtract::cloneString(char *aString)
{
  char *result= 0;

  if (aString != 0) {
    if (*aString != '\0') {
      unsigned int length;

      length= strlen(aString) + 1;
      result= new char[length];
      memcpy(result, aString, length);
    }
  }

  return result;
}


void HkProfileExtract::makeIntoDate(char *aString, unsigned int *fields)
{
  //TODO: Use a better scanning system than this!
  //TODO: Handle errors in text.

  do {
   if (isdigit(*aString)) break;
   aString++;
  } while (*aString != '\0');

  if (*aString == '\0') return;

  // Day:
  if (isdigit(*(aString+1))) {
    fields[0]= (unsigned int)(*aString - 0x030) * 10 + (unsigned int)(*(aString+1) - 0x030);
    aString+= 3;
  }
  else {
    fields[0]= (unsigned int)(*aString - 0x030);
    aString+= 2;
  }

  // Month:
  if (isdigit(*(aString+1))) {
    fields[1]= (unsigned int)(*aString - 0x030) * 10 + (unsigned int)(*(aString+1) - 0x030);
    aString+= 3;
  }
  else {
    fields[1]= (unsigned int)(*aString - 0x030);
    aString+= 2;
  }

  // Year:
  unsigned int nbrDigits= 0, multiplier= 1;

  if (isdigit(*aString)) {
    nbrDigits++;
    if (isdigit(*(aString+1))) {
      nbrDigits++;
      if (isdigit(*(aString+2))) {
        nbrDigits++;
        if (isdigit(*(aString+3))) {
          nbrDigits++;
        }
      }
    }
  }

  for (unsigned int i= 1; i < nbrDigits; i++)
    multiplier*= 10;

  for (unsigned int i= nbrDigits; i > 0; i--) {
    fields[2]+= (unsigned int)(*aString - 0x030) * multiplier;
    aString++;
    multiplier/= 10;
  }
}


void HkProfileExtract::makeIntoBigInt(char *someText, unsigned long long &value)
{
  if (someText == 0) {
    value= 0;
    return;
  }

  char *aCursor, *bCursor;

  aCursor= bCursor= someText;
  while (*aCursor != '\0') {
    if (*aCursor != ',') {
      if (!isdigit(*aCursor))
        break;
      else
        *bCursor++= *aCursor;
    }
    aCursor++;
  }

  *bCursor= '\0';
  value= strtoll(someText, 0, 10);
}


/***************************************
* Implementation: HkProfiler.
****************************************/


Extract *HkProfiler::allocExtract()
{
  return new HkProfileExtract();
}


Extract *HkProfiler::extract(std::istream *aStream, char *aCode)
{
  HkProfileExtract *extract;

  products= extract= (HkProfileExtract *)Extractor::extract(aStream, aCode);

  if (theDoc != NULL) {
    HtScanner *scanner;
    xtnHtmlElement *bodyCur, *tRow, *tCursor;
    xtnHPcData *text;
    char *label;
    bool warrantMode= false;

    scanner= new HtScanner(theDoc);

    // TODO: Add error handling management.

    bodyCur= scanner->searchFor(xtnHtmlDTD::tTable);
    if (bodyCur == NULL) throw new ParseProblem("no main table found");
    bodyCur= scanner->searchForAt(xtnHtmlDTD::tTable, bodyCur, true);
    if (bodyCur == NULL) throw new ParseProblem("no sub-table found");

    // Data is on second row:
    tRow= scanner->searchForAt(xtnHtmlDTD::tTr, bodyCur, true);
    if (tRow == NULL) throw new ParseProblem("1st row of sub-table not found");
    tRow= scanner->searchForAfter(xtnHtmlDTD::tTr, tRow);
    if (tRow == NULL) throw new ParseProblem("2nd row of sub-table not found");

    // Find font that contains company short name/code:
    tCursor= scanner->searchForAt(xtnHtmlDTD::tFont, tRow);
    if (tCursor == NULL) throw new ParseProblem("font in row not found");
    text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, tCursor, true);
    extract->load(HkProfileExtract::nicknameT, text->getData());
    // std::cerr << "@DBG [] xval\"" << text->getData() << "\".\n";

    tCursor= scanner->searchForAfter(xtnHtmlDTD::tFont, tCursor);
    if (tCursor == NULL) throw new ParseProblem("font in company row not found");
    xtnHtmlElement *mark= tCursor;
    tCursor= scanner->searchForAfter(xtnHtmlDTD::tFont, tCursor);
    if (tCursor == NULL) throw new ParseProblem("2nd font in company row not found");
    tCursor= scanner->searchForAfter(xtnHtmlDTD::tFont, tCursor);
    if (tCursor == NULL) throw new ParseProblem("3rd font in company row not found");
    text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, tCursor, true);
    if ((label= text->getData()) != 0) {
      label= extract->cleanup(label);
      if (strcmp(label, "Description:") == 0) {
        // Eg: warrant: 00831; bond: 01012.
        warrantScrape(scanner, mark);
      }
      else if (strcmp(label, "Fund Manager:") == 0) {
        // Eg: 00820.
        fundScrape(scanner, mark);
      }
      else {
        tCursor= companyScrape(scanner, mark);
        tCursor= financialsScrape(scanner, tCursor);
        tCursor= dividendsScrape(scanner, tCursor);
      }
    }
  }
  return extract;
}


xtnHtmlElement *HkProfiler::companyScrape(HtScanner *scanner, xtnHtmlElement *tCursor)
{
  xtnHPcData *text;
  unsigned int firstSeq[]= { HkProfileExtract::securityNameT, HkProfileExtract::activitiesT, HkProfileExtract::chairmanT, HkProfileExtract::officeT, HkProfileExtract::incorPlaceT
    , HkProfileExtract::bizClassT, HkProfileExtract::registrarT, HkProfileExtract::listingT, HkProfileExtract::tradingCurrT, HkProfileExtract::authSharesT
    , HkProfileExtract::issuedSharesT, HkProfileExtract::parValueT, HkProfileExtract::boardLotT, HkProfileExtract::capitalT };


  HkProfileExtract *extract;
  extract= (HkProfileExtract *)products;
  extract->setSubType(HkProfileExtract::shareT);

  for (unsigned int i= 0; i < 14; i++) {
    if (i > 0)
      tCursor= scanner->searchForAfter(xtnHtmlDTD::tFont, tCursor);
    if (tCursor == NULL) throw new ParseProblem("1st font in company row not found");
    tCursor= scanner->searchForAfter(xtnHtmlDTD::tFont, tCursor);
    if (tCursor == NULL) throw new ParseProblem("2nd font in company row not found");
    text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, tCursor, true);
    extract->load(firstSeq[i], text->getData());
    // std::cerr << "@DBG [] xval\"" << text->getData() << "\".\n";

    switch (firstSeq[i]) {
      case HkProfileExtract::issuedSharesT:
        text= (xtnHPcData *)scanner->searchForAfter(xtnHtmlDTD::tPcdata, text);
        extract->load(HkProfileExtract::issueAsOfT, text->getData());
        // std::cerr << "@DBG [] xval\"" << text->getData() << "\".\n";
        break;

      case HkProfileExtract::officeT: {
        xtnHtmlElement *brCur= scanner->searchForAfter(xtnHtmlDTD::tBr, text, tCursor);
        while (brCur != 0) {
          text= (xtnHPcData *)scanner->searchForAfter(xtnHtmlDTD::tPcdata, brCur, tCursor);
          extract->load(HkProfileExtract::officeT, text->getData());
          // std::cerr << "@DBG [] xval\"" << text->getData() << "\".\n";
    
          brCur= scanner->searchForAfter(xtnHtmlDTD::tBr, brCur, tCursor);
        }
        } break;
    }
  }

  return tCursor;
}


xtnHtmlElement *HkProfiler::financialsScrape(HtScanner *scanner, xtnHtmlElement *tCursor)
{
  xtnHPcData *text;
  unsigned int secondSeq[]= { HkProfileExtract::yearEndT, HkProfileExtract::netValueT, HkProfileExtract::netProfitT, HkProfileExtract::epsT, HkProfileExtract::updatedOnT };

  HkProfileExtract *extract;
  extract= (HkProfileExtract *)products;

  // Financial Information:
  tCursor= scanner->searchForAfter(xtnHtmlDTD::tFont, tCursor);
  if (tCursor != NULL) {
    for (unsigned int i= 0; i < 5; i++) {
      tCursor= scanner->searchForAfter(xtnHtmlDTD::tFont, tCursor);
      if (tCursor == NULL) throw new ParseProblem("1st font in iter financial not found");
      tCursor= scanner->searchForAfter(xtnHtmlDTD::tFont, tCursor);
      if (tCursor == NULL) throw new ParseProblem("2nd font in iter financial not found");
      text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, tCursor, true);
      extract->load(secondSeq[i], text->getData());
      // std::cerr << "@DBG [] xval\"" << text->getData() << "\".\n";
    }
  }

  return tCursor;
}


xtnHtmlElement *HkProfiler::dividendsScrape(HtScanner *scanner, xtnHtmlElement *tRow)
{
  xtnHtmlElement *bodyCur;
  xtnHPcData *text;
  unsigned int passNbr= 0;
  char *label;

  HkProfileExtract *extract;
  extract= (HkProfileExtract *)products;

  // Follow thru to Entitlement table:
  bodyCur= scanner->searchForAfter(xtnHtmlDTD::tTable, tRow);
  if (bodyCur == NULL) throw new ParseProblem("row for entitlement not found");
  
  // Data starts on fourth row (3 rows + 1 wrongly embedded, by HTML 4 it is a new row):
  tRow= scanner->searchForAt(xtnHtmlDTD::tTr, bodyCur, true);
  if (tRow == 0) throw new ParseProblem("1st row of entitlement not found");
  tRow= scanner->searchForAfter(xtnHtmlDTD::tTr, tRow);
  if (tRow == 0) throw new ParseProblem("2nd row of entitlement not found");
  tRow= scanner->searchForAfter(xtnHtmlDTD::tTr, tRow);
  if (tRow == 0) throw new ParseProblem("3rd row of entitlement not found");
  tRow= scanner->searchForAfter(xtnHtmlDTD::tTr, tRow);
  if (tRow == 0) throw new ParseProblem("4th row of entitlement not found");
  

  while (tRow != 0) {
    xtnHtmlElement *brCur, *tCursor;

    extract->load(HkProfileExtract::entitlementT, 0);
    // Ex-date:
    tCursor= scanner->searchForAt(xtnHtmlDTD::tFont, tRow, true);
    if (tCursor == NULL) {
      // It is a 'nil' block, eg 00825.
      return 0;
    }
    text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, tCursor, true);
    if ((label == text->getData()) != 0) {
      if (strcmp(label, "nil") == 0) {
        // It is a 'nil' block, eg 00825.
        break;
      }
      else
        extract->load(HkProfileExtract::dateEntT, label);
    }
    // std::cerr << "@DBG [] xval\"" << text->getData() << "\".\n";

    // Details:
    tCursor= scanner->searchForAfter(xtnHtmlDTD::tFont, tCursor);
    if (tCursor == NULL) throw new ParseProblem("font in date row not found");
    text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, tCursor, true);
    extract->load(HkProfileExtract::detailsEntT, text->getData());
    // std::cerr << "@DBG [] xval\"" << text->getData() << "\".\n";

    brCur= scanner->searchForAfter(xtnHtmlDTD::tBr, text, tCursor);
    while (brCur != 0) {
      text= (xtnHPcData *)scanner->searchForAfter(xtnHtmlDTD::tPcdata, brCur, tCursor);
      extract->load(HkProfileExtract::detailsEntT, text->getData());
      // std::cerr << "@DBG [] xval\"" << text->getData() << "\".\n";

      brCur= scanner->searchForAfter(xtnHtmlDTD::tBr, brCur, tCursor);
    }

    // Financial year end:
    tCursor= scanner->searchForAfter(xtnHtmlDTD::tFont, tCursor);
    if (tCursor == NULL) throw new ParseProblem("font for financial year end not found");
    text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, tCursor, true);
    extract->load(HkProfileExtract::yearEndEntT, text->getData());
    // std::cerr << "@DBG [] xval\"" << text->getData() << "\".\n";

    // B/C date:
    tCursor= scanner->searchForAfter(xtnHtmlDTD::tFont, tCursor);
    if (tCursor == NULL) throw new ParseProblem("font for b/c date not found");
    text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, tCursor, true);
    extract->load(HkProfileExtract::bcDateEntT, text->getData());
    // std::cerr << "@DBG [] xval\"" << text->getData() << "\".\n";

    tRow= scanner->searchForAfter(xtnHtmlDTD::tTr, tRow, bodyCur);
    if (tRow != 0)
      tRow= scanner->searchForAfter(xtnHtmlDTD::tTr, tRow, bodyCur);

    passNbr++;
  }

  return tRow;
}


xtnHtmlElement *HkProfiler::warrantScrape(HtScanner *scanner, xtnHtmlElement *tRow)
{
  // For now, bonds are also typed as warrant.  Need to find the "subscription rights per unit" in warrant vs "date raised" in bond to differentiate.
  // Bond fields: Company/Securities Name, Description, Amount Outstanding, Board Lot Nominal, Date Raised, Maturity Date, Interest (%), Payable (Month/Day), Listing Date, Trading Currency, Last Updated.
  // Warrant fields: Company/Securities Name, Description, Amount Outstanding, Board Lot, Subscription Rights per Unit, Subscription price/Strike price, Subscription Ratio, Subscription Period, Underlying Stock Code, Listing Date, Trading Currency, Last Updated.

  HkProfileExtract *extract;
  extract= (HkProfileExtract *)products;
  extract->setSubType(HkProfileExtract::warrantT);
  return 0;
}


xtnHtmlElement *HkProfiler::fundScrape(HtScanner *scanner, xtnHtmlElement *tRow)
{
  HkProfileExtract *extract;
  extract= (HkProfileExtract *)products;
  extract->setSubType(HkProfileExtract::fundT);
  return 0;
}



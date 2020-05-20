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
#include "homeDepot.h"


/***************************************************
* Implementation: HomeDepoter.
****************************************************/

HomeDepoter::HomeDepoter(unsigned int aKind)
{
  dbLink= 0;
  parseKind= aKind;
}


HomeDepoter::~HomeDepoter()
{
  delete dbLink;
}


void HomeDepoter::setDbDict(char *aHost, char *aDb, char *aUser, char *aPwd)
{
  connDict= "host=";
  connDict+= aHost;
  connDict+= " user= ";
  connDict+= aUser;
  connDict+= " dbname=";
  connDict+= aDb;
  connDict+= " password=";
  connDict+= aPwd;
}


void HomeDepoter::connect()
{
  dbLink= new PostgresChannel(connDict.c_str());
  dbLink->connect();

/*TODO: throw an error if the db is not available.
  if (dbLink->status() != 0) {
  }
*/
}


void HomeDepoter::disconnect()
{
  dbLink->disconnect();
}


void HomeDepoter::fetchWork()
{
  DBResult *opRez;
  int uid, outputFK;
  char selectStmt[1024];

  sprintf(selectStmt, "select a.uid, a.outputfk, a.enteredon from di.parserequest a left outer join di.parsejob b on a.uid=b.requestfk where a.kind=%d and b.requestfk is null limit 200", parseKind);
  opRez= dbLink->exec(selectStmt);
  if (opRez->isOk()) {
    for (unsigned int i= 0; i < opRez->getNbrRows(); i++) {
      opRez->fieldAsInt(i, 0, uid);
      opRez->fieldAsInt(i, 1, outputFK);
      requests.push_back(new ParseRequest(uid, outputFK));
    }
  }
  delete opRez;

  std::list<ParseRequest *>::iterator cursor;
  int blobID, jobID, blobSize, httpCode, areaID, propertyID;

  for (cursor= requests.begin(); cursor != requests.end(); cursor++) {
    ParseRequest *request= *cursor;

    sprintf(selectStmt, "select %s from %s where uid=%d"
      , "a.jobfk, a.size, a.agedat, a.httpcode, a.blobid"
      , "di.fetchoutput a"
      , request->getOutputID());
    opRez= dbLink->exec(selectStmt);
    if (opRez->isOk()) {
      unsigned int blobPos;
      if (opRez->getNbrRows() == 1) {
        opRez->fieldAsInt(0, opRez->getFieldPosOf("blobid"), blobID);
        opRez->fieldAsInt(0, opRez->getFieldPosOf("jobfk"), jobID);
        opRez->fieldAsInt(0, opRez->getFieldPosOf("size"), blobSize);
        opRez->fieldAsInt(0, opRez->getFieldPosOf("httpcode"), httpCode);
        request->setBlobDetails(blobID, blobSize, httpCode);
      }
      else {
        //TODO: throw an exception.
      }
    }
    delete opRez;
    if (request->isGood()) {
      sprintf(selectStmt, "select %s from %s where a.kind=%d and b.uid=%d"
        , "a.sourcefk, c.propertyfk, a.actualurl"
        , "di.fetchjob b join di.fetchrequest a on b.requestfk=a.uid join di.sitearea c on a.sourcefk=c.uid"
        , parseKind, jobID);
      opRez= dbLink->exec(selectStmt);
      if (opRez->isOk()) {
        char actualUrl[2048];

        opRez->fieldAsInt(0, opRez->getFieldPosOf("sourcefk"), areaID);
        opRez->fieldAsInt(0, opRez->getFieldPosOf("propertyfk"), propertyID);
        opRez->fieldAsChar(0, 2, actualUrl, 2048);
        request->setSiteInfo(areaID, propertyID, actualUrl);
      }
      delete opRez;
    }
  }
}


void HomeDepoter::doWork()
{
  std::list<ParseRequest *>::iterator cursor;

  for (cursor= requests.begin(); cursor != requests.end(); cursor++) {
    ParseRequest *request= *cursor;
    if (request->isGood()) {
      writeTrace(request);
      hdExtractor= new PageHDExtractor(parseKind);

      try {
        loadContent(request);
        parse(request);
        postProcess(request);
      }
      catch (ParseProblem *anError) {
        //TODO: Handle exceptions.
      }

      delete hdExtractor;
    }
    updateTrace(request);
    offload(request);
  }
}


void HomeDepoter::loadContent(ParseRequest *aRequest)
{
  DBResult *opRez;
  int invFD;

  opRez= dbLink->exec("begin transaction");
  delete opRez;

  size_t bufLength= 1024 * 128, lengthRead;
  char *blobBuffer= new char[bufLength];

  invFD= ((PostgresChannel *)dbLink)->openBlob(aRequest->getBlobID());

  do {
    lengthRead= ((PostgresChannel *)dbLink)->readFromBlob(invFD, blobBuffer, bufLength-1);
    blobBuffer[lengthRead]= '\0';
    aRequest->accumulate(blobBuffer, lengthRead);
    // accuBuffer.write(blobBuffer, lengthRead);
  } while (lengthRead == (bufLength-1));

  aRequest->getContent()->seekp(0);
  delete[] blobBuffer;

  ((PostgresChannel *)dbLink)->closeBlob(invFD);
  opRez= dbLink->exec("end transaction");
  delete opRez;

#if defined(DO_DEBUG)
  std::ofstream dbgFile("/tmp/t.html");
  const char *dbgChar= aRequest->getContent()->str().c_str();
  dbgFile.write(dbgChar, strlen(dbgChar));
  dbgFile.close();
#endif

}


void HomeDepoter::parse(ParseRequest *aRequest)
{
  PageHD *result;

  aRequest->startWatch();
  result= (PageHD *)hdExtractor->extract(aRequest->getContent(), "void");
  aRequest->setParseOutput(result);
  aRequest->stopWatch();
}


void HomeDepoter::postProcess(ParseRequest *aRequest)
{
  PageHD *page;

// go through all categories, write site-area if not already there,
// add fetch request for its content.
  if ((page= aRequest->getPage()) != 0) {
    page->setSiteInfo(aRequest->getSiteArea(), aRequest->getProperty());
    page->setUrlPrefix(aRequest->getUrl());

    switch (page->getKind()) {
      case PageHD::cateProduct: {
        // write a fetch request for every next page of products (48 items per page).
        // write the info about the items contained in the current page.
        // Navigation?Ntk=AllProps&Ntx=mode%2bmatchallpartial&Ns=P_Topseller_Sort%7c1&N=10000003+90401+500270&No=24&rpp=12
        DBResult *opRez;
        unsigned int nbrPages;
        char insertStmt[2048];

        if (page->getTotalProdNbr() > 12) {
          nbrPages= page->getTotalProdNbr() / 48;
          if (nbrPages * 48 < page->getTotalProdNbr()) nbrPages++;
    
          for (unsigned int i= 0; i < nbrPages; i++) {
            sprintf(insertStmt, "insert into di.FetchRequest (sourcefk, kind, actualurl) values (%d, 2, '%s&No=%d&rpp=48')"
              , aRequest->getSiteArea(), aRequest->getUrl().c_str(), i * 48);
            opRez= dbLink->exec(insertStmt);
            if (!opRez->isOk()) {
            }
            delete opRez;
          }
        }
        break; }
    }
    page->describeInto(dbLink);

  } 
}


void HomeDepoter::offload(ParseRequest *aRequest)
{
  delete aRequest;
  //ATTN: Anything else to do??
}


void HomeDepoter::writeTrace(ParseRequest *aRequest)
{
  DBResult *opRez1, *opRez2;
  char insertStmt[250];

  sprintf(insertStmt, "insert into %s (%s) values (%d, %d)"
    , "di.parsejob"
    , "requestfk, status"
    , aRequest->getUid(), 1);
  opRez1= dbLink->exec(insertStmt);
  if (opRez1->isOk()) {
    opRez2= dbLink->exec("select lastval()");
    if (opRez2->isOk()) {
      int lastID;
      opRez2->fieldAsInt(0, 0, lastID);
      aRequest->setJobID(lastID);
    }
    delete opRez2;
  }
  delete opRez1;
}


void HomeDepoter::updateTrace(ParseRequest *aRequest)
{
  DBResult *opRez;
  char updateStmt[250];

  sprintf(updateStmt, "update %s set status=2, duration=%d where uid=%d"
    , "di.parsejob"
    , aRequest->getDuration()
    , aRequest->getJobID());
  opRez= dbLink->exec(updateStmt);
  if (!opRez->isOk()) {
    //TODO: throw an exception.
  }
  delete opRez;
}


/***************************************************
* Implementation: PageHDExtractor.
****************************************************/

PageHDExtractor::PageHDExtractor(unsigned int aKind)
 : Extractor()
{
  scanner= 0;
  parseKind= aKind;
}


PageHDExtractor::~PageHDExtractor()
{
  delete scanner;
}


Extract *PageHDExtractor::extract(std::istream *aStream, char *aCode)
{
  Extract *extract;

  extract= Extractor::extract(aStream, aCode);

  if (theDoc == NULL)
    return NULL;  // Warning: quick exit.

  xtnHtmlElement *tDiv, *curDiv;
  xtnCoreAttribute *attrib;
  PageHD *result;

  scanner= new HtScanner(theDoc);

  result= inspect_A(scanner);
  if (result != 0) {
    inspect_B(scanner, result);
    result->analyze(scanner);
  }

  return result;
}


PageHD *PageHDExtractor::inspect_A(HtScanner *scanner) {
  xtnHtmlElement *cursor, *tmpCur;
  xtnCoreAttribute *attrib;
  PageHD *result;
  char *location= 0;
  bool stillSearching= true;

  // First, locate the lu{id: "breadcrumb-nav"} that contains the presentation
  //  of the category path, made of li[href[<category name>]] ">" ...
  cursor= scanner->searchFor(xtnHtmlDTD::tUl);
  while ((cursor != 0) && stillSearching) {
    if ((attrib= cursor->getAttribute("id")) != 0) {
      char *value;

      value= ((xtnHtmlAttribute *)attrib)->getValue();
      if (strcmp(value, "\"breadcrumb-nav\"") == 0) {
        xtnHtmlElement *liCur, *nextLi, *aCur;
        xtnHPcData *pcCursor;
        std::list<xtnHPcData *> pathNames;

        if ((liCur= scanner->searchForAt(xtnHtmlDTD::tLi, cursor, true)) != 0) {  // Found "You are here:", scan the path of categories.
          /* Syntax:
             find li as target immediately within lu a where a.id = 'breadcrumb-nav' and li is last {
               find first a immediately within target 
             }
          */
          nextLi= liCur= scanner->searchForAfter(xtnHtmlDTD::tLi, liCur, cursor);
          std::list<PathEntry *> path;
 
          while (nextLi != 0) {
            liCur= nextLi;
            if ((aCur= scanner->searchForAt(xtnHtmlDTD::tA, liCur, true)) != 0) {
               char *value= 0;

              if ((attrib= aCur->getAttribute("href")) != 0) {                
                value= ((xtnHtmlAttribute *)attrib)->getValue();
              }
              if ((pcCursor= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, aCur, true)) != 0) {
                path.push_back(new PathEntry(pcCursor, value));
              }
            }
            nextLi= scanner->searchForAfter(xtnHtmlDTD::tLi, liCur, cursor);
          }
          if (liCur != 0) {
            if ((aCur= scanner->searchForAt(xtnHtmlDTD::tA, liCur, true)) != 0) {
              xtnHPcData *pcCursor;
              if ((pcCursor= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, aCur, true)) != 0) {
                result= new PageHD(path, cursor);
                if (parseKind == 2) {
                  result->setKind(PageHD::nextProduct);
                }
              }
            }
          }
        }
        stillSearching= false;
      }
    }
    if ((tmpCur= scanner->searchForAt(xtnHtmlDTD::tUl, cursor, true)) == 0)
      cursor= scanner->searchForAfter(xtnHtmlDTD::tUl, cursor);
    else
      cursor= tmpCur;
  }

  return result;
}


void PageHDExtractor::inspect_B(HtScanner *scanner, PageHD *aPage)
{
  xtnHtmlElement *cursor, *tmpCur;

    /* Horizontal navigation menu:
      div(id:"nav-cover")
      + ul(id: "main-nav")
    */

  // Handle the root page a bit differently:
  if (aPage->area()->match("HOME")) {
    aPage->setKind(PageHD::home);
  }
  else {
    xtnHtmlElement *cursor, *tmpCur;
    xtnCoreAttribute *aAttrib, *bAttrib;
    bool kindUnfound= true;

    // Other pages are either top-category/promo or category/product matrix pages, which are either first page (interested in categories and product matrix) or following pages (only interested in product matrix).
    cursor= scanner->searchFor(xtnHtmlDTD::tSpan);
    while (cursor != 0) {

      if (((aAttrib= cursor->getAttribute("class")) != 0) && ((bAttrib= cursor->getAttribute("id")) != 0)) {
        if ((strcmp(((xtnHtmlAttribute *)aAttrib)->getValue(), "\"total-results\"") == 0) && (strcmp(((xtnHtmlAttribute *)bAttrib)->getValue(), "\"Products_Link\"") == 0)) {
          aPage->linkProductAt(cursor);
          if ((cursor= scanner->searchForAt(xtnHtmlDTD::tB, cursor, true)) != 0) {
            if ((cursor= scanner->searchForAt(xtnHtmlDTD::tPcdata, cursor, true)) != 0) {
              char *value;

              if ((value= ((xtnHPcData *)cursor)->getData()) != 0) {
                aPage->setTotalProdNbr(atoi(value));
              }
            }
          }
          kindUnfound= false;
          break;
        }
      }
      cursor= scanner->searchForAfter(xtnHtmlDTD::tSpan, cursor);
    }
    if (kindUnfound) {
      aPage->setKind(PageHD::catePromo);
    }
  }

  /* Find div(id: "side")
        ?+ div(id: "side-online", class="tab-content")
        + * dl {
          + dt { PcData(<category-title> | "Category") }
          + * dd { a(href=<url>){ PcData([ ]*.* ?([0-9]+)) } }
  */
  /*
    url to fetch 48 products, starting from number 12 (base 1):
http://www.homedepot.com/webapp/wcs/stores/servlet/Navigation?Ntk=AllProps&Ntx=mode%252bmatchallpartial&N=10000003%2B90401%2B503405&Ns=P_Topseller_Sort%257c1&recordCompareList=&langId=-1&storeId=10051&catalogId=10053&style=A&No=12&rpp=48
  */
}


bool PageHDExtractor::productPageCheck(HtScanner *scanner)
{
  xtnHtmlElement *cursor, *tmpCur;
  xtnCoreAttribute *attrib;

  cursor= scanner->searchFor(xtnHtmlDTD::tDiv);
  while (cursor != NULL) {
    if ((attrib= cursor->getAttribute("class")) != NULL) {
      char *value;

      value= ((xtnHtmlAttribute *)attrib)->getValue();
      if (strcmp(value, "\"wps-fragment\"") == 0) {
        return false;
      }
      else if (strcmp(value, "\"product\"") == 0) {
        return true;
      }
    }
    if ((tmpCur= scanner->searchForAt(xtnHtmlDTD::tDiv, cursor, true)) == NULL)
      cursor= scanner->searchForAfter(xtnHtmlDTD::tDiv, cursor);
    else
      cursor= tmpCur;
  }
  return false;
}


Extract *PageHDExtractor::productsXtr(HtScanner *scanner)
{
  xtnHtmlElement *cursor, *tmpCur;
  xtnHtmlElement *topHolder= NULL;
  xtnCoreAttribute *attrib;
  Extract *result= NULL;
  std::list<ProductHD *> products;
  char *hrefValue;

  cursor= scanner->searchFor(xtnHtmlDTD::tDiv);
  while (cursor != NULL) {
    if ((attrib= cursor->getAttribute("class")) != NULL) {
      char *value;
      value= ((xtnHtmlAttribute *)attrib)->getValue();
      if (strcmp(value, "\"product\"") == 0) {
        ProductHD *newProd;
        newProd= new ProductHD(cursor);
        products.push_back(newProd);
      }
    }
    if ((tmpCur= scanner->searchForAt(xtnHtmlDTD::tDiv, cursor, true)) == NULL)
      cursor= scanner->searchForAfter(xtnHtmlDTD::tDiv, cursor);
    else
      cursor= tmpCur;
  }

  return result;
}


Extract *PageHDExtractor::categoriesXtr(HtScanner *scanner)
{
  Extract *result= NULL;

  std::cout << "@DBG [HomeDepot.categoriesXtr] category page.\n";

  return result;
}


/*********************************************
* Implementation: ParseRequest.
*********************************************/

ParseRequest::ParseRequest(int anID, int anOutputID)
{
  uid= anID;
  outputID= anOutputID;
  jobID= 0;
  blobID= 0;
  blobSize= 0;
  httpReplyCode= 0;
  superArea= 0;
  blobContent= 0;
  result= 0;
  start.tv_sec= end.tv_sec= 0;
  start.tv_usec= end.tv_usec= 0;
}


ParseRequest::~ParseRequest()
{
  delete blobContent;
  delete result;
}


void ParseRequest::accumulate(char *aBuffer, size_t aLength)
{
  if (blobContent == 0)
    blobContent= new std::stringstream(aBuffer, std::ios_base::in | std::ios_base::out | std::ios_base::binary | std::ios_base::app);
  else
    blobContent->write(aBuffer, aLength);
  std::cout << "[ParseRequest.accumulate] request " << uid << "; blob " << blobID << " tellp: " << blobContent->tellp() << ".\n";
}


bool ParseRequest::isGood()
{
  return (httpReplyCode / 200 == 1);
}


void ParseRequest::startWatch()
{
  gettimeofday(&start, 0);
}


void ParseRequest::stopWatch()
{
  gettimeofday(&end, 0);
}


unsigned int ParseRequest::getDuration()
{
  time_t secs;
  suseconds_t microsecs;
  secs= end.tv_sec - start.tv_sec;
  if (start.tv_usec > end.tv_usec) {
    secs--;
    microsecs= 1000000 - start.tv_usec + end.tv_usec;
  }
  else {
    microsecs= end.tv_usec - start.tv_usec;
  }
  return (secs * 1000 + microsecs / 1000);
}


/*********************************************
* Implementation: PageHD.
*********************************************/

PageHD::PageHD(std::list<PathEntry *> &aPath, xtnHtmlElement *anchor)
  : Extract(1)
{
  pagePath.assign(aPath.begin(), aPath.end());
  firstAnchor= anchor;
  productHook= 0;
  propertyID= parentID= areaID= 0;
  kind= unknown;
  totalNbrProducts= 0;
}


PageHD::~PageHD()
{
  for (std::list<CategoryHD *>::iterator catCur= categories.begin(); catCur != categories.end(); catCur++) {
    delete *catCur;
  }

  for (std::list<PathEntry *>::iterator pathCur= pagePath.begin(); pathCur != pagePath.end(); pathCur++) {
    delete *pathCur;
  }
}


PathEntry *PageHD::area()
{
  if (pagePath.size() > 0) {
    return pagePath.back();
  }
  else
    return 0;
}


void PageHD::analyze(HtScanner *scanner)
{
  switch(kind) {
    case PageHD::home:
      homeExtractor(scanner);
      break;
    case PageHD::catePromo:
      categoryExtractor(scanner);
      categorySimplification();
      break;
    case PageHD::cateProduct:
      categoryExtractor(scanner);
      productExtractor(scanner);
      categorySimplification();
      break;
    case PageHD::nextProduct:
      productExtractor(scanner);
      break;
    default:
      //TODO: signal unimplemented functionality.
      break;
  }
}


void PageHD::homeExtractor(HtScanner *scanner)
{
  xtnHtmlElement *cursor, *tmpCur;
  xtnCoreAttribute *attrib;

  /* Horizontal navigation menu:
    div(id:"nav-cover")
    + ul(id: "main-nav")
  */
  cursor= scanner->searchForAfter(xtnHtmlDTD::tDiv, firstAnchor);

  while (cursor != 0) {
    if ((attrib= cursor->getAttribute("id")) != 0) {
      char *value;

      value= ((xtnHtmlAttribute *)attrib)->getValue();
      if (strcmp(value, "\"side\"") == 0) {
        xtnHtmlElement *onlineCur;

        onlineCur= scanner->searchForAt(xtnHtmlDTD::tDiv, cursor, true);
        while (onlineCur != 0) {
          if ((attrib= onlineCur->getAttribute("id")) != 0) {
            char *value;
      
            value= ((xtnHtmlAttribute *)attrib)->getValue();
            if (strcmp(value, "\"side-online\"") == 0) {
              xtnHtmlElement *dlCur, *dtCur, *ddCur;

              dlCur= scanner->searchForAt(xtnHtmlDTD::tDl, onlineCur, true);
              while (dlCur != 0) {
                xtnHtmlElement *anchor;
                xtnHPcData *label;
                CategoryHD *newCat;

                if ((dtCur= scanner->searchForAt(xtnHtmlDTD::tDt, dlCur, true)) != 0) {                 
                  if ((anchor= scanner->searchForAt(xtnHtmlDTD::tA, dtCur, true)) != 0) {
                    char *value= 0;

                    if ((attrib= anchor->getAttribute("href")) != 0) {                
                      value= ((xtnHtmlAttribute *)attrib)->getValue();
                    }
                    label= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, anchor, true);
                    if ((value != 0) && (label != 0)) {
                      newCat= new CategoryHD(label, value);
                      categories.push_back(newCat);
                      // DBG: std::cout << "[inspect_B] seeing top-cat " << label->getData() << " : " << value << ".\n";
                      ddCur= scanner->searchForAfter(xtnHtmlDTD::tDd, dtCur, dlCur);
                      while (ddCur != 0) {
                        if ((anchor= scanner->searchForAt(xtnHtmlDTD::tA, ddCur, true)) != 0) {
                          if ((attrib= anchor->getAttribute("href")) != 0) {                
                            value= ((xtnHtmlAttribute *)attrib)->getValue();
                          }
                          label= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, anchor, true);
                          if ((value != 0) && (label != 0)) {
                            // DBG: std::cout << "[inspect_B] seeing sub-cat " << label->getData() << ".\n";
                            newCat->addSubCat(label, value);
                          }
                        }
                        ddCur= scanner->searchForAfter(xtnHtmlDTD::tDd, ddCur, dlCur);
                      }

                    }
                  }
                }

                dlCur= scanner->searchForAfter(xtnHtmlDTD::tDl, dlCur, onlineCur);
              }
              break;
            }
          }
          if ((tmpCur= scanner->searchForAt(xtnHtmlDTD::tDiv, onlineCur, true)) == 0)
            onlineCur= scanner->searchForAfter(xtnHtmlDTD::tDiv, onlineCur, cursor);
          else
            onlineCur= tmpCur;
        }
      }
    }
    if ((tmpCur= scanner->searchForAt(xtnHtmlDTD::tDiv, cursor, true)) == 0)
      cursor= scanner->searchForAfter(xtnHtmlDTD::tDiv, cursor);
    else
      cursor= tmpCur;
  }
}


void PageHD::categoryExtractor(HtScanner *scanner)
{
  xtnHtmlElement *cursor, *tmpCur;
  xtnCoreAttribute *attrib;
  bool stillSearching= true;

  /* Horizontal navigation menu:
    div(id:"nav-cover")
    + ul(id: "main-nav")
  */
  cursor= scanner->searchForAfter(xtnHtmlDTD::tDiv, firstAnchor);

  while ((cursor != 0) && stillSearching) {
    if ((attrib= cursor->getAttribute("id")) != 0) {
      char *value;

      value= ((xtnHtmlAttribute *)attrib)->getValue();
      if (strcmp(value, "\"side\"") == 0) {
        xtnHtmlElement *onlineCur;

        onlineCur= scanner->searchForAt(xtnHtmlDTD::tDiv, cursor, true);
        while ((onlineCur != 0) && stillSearching) {
          if ((attrib= onlineCur->getAttribute("id")) != 0) {
            char *value;
      
            value= ((xtnHtmlAttribute *)attrib)->getValue();
            if (strcmp(value, "\"side-online\"") == 0) {
              xtnHtmlElement *dlCur, *dtCur, *ddCur;

              dlCur= scanner->searchForAt(xtnHtmlDTD::tDl, onlineCur, true);
              while (dlCur != 0) {
                xtnHtmlElement *anchor;
                xtnHPcData *label;
                CategoryHD *newCat;

                if ((dtCur= scanner->searchForAt(xtnHtmlDTD::tDt, dlCur, true)) != 0) {                 
                  if ((label= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, dtCur, true)) == 0)
                    continue; //ATTN: Skip the current dl if the dt doesn't have a label.
                  newCat= new CategoryHD(label, 0);
                  categories.push_back(newCat);
                  ddCur= scanner->searchForAfter(xtnHtmlDTD::tDd, dtCur, dlCur);
                  while (ddCur != 0) {
                    if ((anchor= scanner->searchForAt(xtnHtmlDTD::tA, ddCur, true)) != 0) {
                      if ((attrib= anchor->getAttribute("href")) != 0) {                
                        value= ((xtnHtmlAttribute *)attrib)->getValue();
                      }
                      label= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, anchor, true);
                      if ((value != 0) && (label != 0)) {
                        // DBG: std::cout << "[inspect_B] seeing sub-cat " << label->getData() << ".\n";
                        newCat->addSubCat(label, value);
                      }
                    }
                    ddCur= scanner->searchForAfter(xtnHtmlDTD::tDd, ddCur, dlCur);
                  }
                }
                dlCur= scanner->searchForAfter(xtnHtmlDTD::tDl, dlCur, onlineCur);
              }
              stillSearching= false;
            }
          }
          if ((tmpCur= scanner->searchForAt(xtnHtmlDTD::tDiv, onlineCur, true)) == 0)
            onlineCur= scanner->searchForAfter(xtnHtmlDTD::tDiv, onlineCur, cursor);
          else
            onlineCur= tmpCur;
        }
      }
    }
    if ((tmpCur= scanner->searchForAt(xtnHtmlDTD::tDiv, cursor, true)) == 0)
      cursor= scanner->searchForAfter(xtnHtmlDTD::tDiv, cursor);
    else
      cursor= tmpCur;
  }
}


void PageHD::productExtractor(HtScanner *scanner)
{
  xtnHtmlElement *cursor, *tmpCur, *prodsEle, *prodRowEle, *productEle;
  xtnCoreAttribute *attrib;
  char *hrefValue;
  char *value;

  cursor= scanner->searchForAfter(xtnHtmlDTD::tDiv, productHook);
  while (cursor != 0) {
    if ((attrib= cursor->getAttribute("id")) != 0) {
      value= ((xtnHtmlAttribute *)attrib)->getValue();
      if (strcmp(value, "\"products\"") == 0) {
        prodsEle= cursor;

        cursor= scanner->searchForAt(xtnHtmlDTD::tDiv, prodsEle, true);
        while (cursor != 0) {
          if ((attrib= cursor->getAttribute("class")) != 0) {
            value= ((xtnHtmlAttribute *)attrib)->getValue();
            if (strcmp(value, "\"product-row\"") == 0) {
              prodRowEle= cursor;

              cursor= scanner->searchForAt(xtnHtmlDTD::tDiv, prodRowEle, true);
              while (cursor != 0) {
                if ((attrib= cursor->getAttribute("class")) != 0) {
                  value= ((xtnHtmlAttribute *)attrib)->getValue();
                  if (strcmp(value, "\"product\"") == 0) {
                    ProductHD *newProd;
                    //TODO: extract all the information properly:
                    newProd= new ProductHD(cursor);
                    newProd->locateElements(scanner);
                    products.push_back(newProd);
                  }
                }
                cursor= scanner->searchForAfter(xtnHtmlDTD::tDiv, cursor, prodRowEle);
              }
              cursor= prodRowEle;
            }
          }
          cursor= scanner->searchForAfter(xtnHtmlDTD::tDiv, cursor, prodsEle);
        }
        break;
      }
    }
    if ((tmpCur= scanner->searchForAt(xtnHtmlDTD::tDiv, cursor, true)) == 0)
      cursor= scanner->searchForAfter(xtnHtmlDTD::tDiv, cursor);
    else
      cursor= tmpCur;
  }
}


void PageHD::categorySimplification()
{
  std::list<CategoryHD *>::iterator cursor;

  if (kind == catePromo) {
    for (cursor= categories.begin(); cursor != categories.end(); cursor++) {
      CategoryHD *category= *cursor;

      //ATTN: Non-main-nav tree categories are DD without ID;
      // while 'more ways to shop' have id='more-ways-to-shop'.
      if (pagePath.back()->match(category->getLabel())) {
        category->setKind(CategoryHD::namedNode);
        category->setSubKind(CategoryHD::namedNode);
      }
      else if (category->nameMatch("Category")) {
        category->setKind(CategoryHD::anonymousNode);
        category->setSubKind(CategoryHD::innerNode);
      }
    }
  }
  else {
    for (cursor= categories.begin(); cursor != categories.end(); cursor++) {
      CategoryHD *category= *cursor;

      if (category->nameMatch("Category")) {
        category->setKind(CategoryHD::anonymousNode);
      }
    }
  }
}


void PageHD::describeInto(DBChannel *dbConn)
{
  std::list<CategoryHD *>::iterator catCursor;
  std::list<ProductHD *>::iterator prodCursor;
  int pathLeafID, parentLeafID;

  if (kind != home) {
    loadAreaSet(dbConn);
    std::list<PathEntry *>::reverse_iterator revCur;
    if ((revCur= pagePath.rbegin()) != pagePath.rend()) {
      pathLeafID= (*revCur)->getUid();
      revCur++;
      if (revCur != pagePath.rend()) {
        parentLeafID= (*revCur)->getUid();
      }
    }   
  }
  else
    pathLeafID= parentID;

  switch(kind) {
    case home:
    case catePromo:
      for (catCursor= categories.begin(); catCursor != categories.end(); catCursor++) {
        CategoryHD *category= *catCursor;
    
        if (category->isActive()) {
          category->serializeInto(dbConn, prefix, pathLeafID, parentLeafID, propertyID);
        }
      }
      break;

    case cateProduct:
      if (totalNbrProducts < 13) {
        for (prodCursor= products.begin(); prodCursor != products.end(); prodCursor++) {
          ProductHD *item= *prodCursor;

          item->serialize(dbConn, propertyID, areaID);
        }
      }
      break;

    case nextProduct:
      // write the info about the items contained in the current page.
      for (prodCursor= products.begin(); prodCursor != products.end(); prodCursor++) {
        ProductHD *item= *prodCursor;
   
        item->serialize(dbConn, propertyID, areaID);
      }
      break;

    default:
      //TODO: raise exception on unknown kind of page.
      break;
  }

}


void PageHD::linkProductAt(xtnHtmlElement *aCursor)
{
  if (kind == unknown)
    kind= cateProduct;
  productHook= aCursor;
}


void PageHD::loadAreaSet(DBChannel *dbConn)
{
  DBResult *opRez;
  char aStmt[2048];
  int containingID, newUid;
  std::list<PathEntry *>::iterator cursor;
  bool mustCreateArea= true, skipCat= false;

  for (newUid= 0, cursor= pagePath.begin(); cursor != pagePath.end(); cursor++) {
    PathEntry *entry= *cursor;

    parentID= newUid;
    if (entry->match("HOME")) {
      sprintf(aStmt, "select uid, url from di.SiteArea where propertyfk=%d and parent=0 and label = 'Front Page'", propertyID);
    }
    else {
      sprintf(aStmt, "select uid, url from di.SiteArea where propertyfk=%d and parent=%d and label = '%s'", propertyID, containingID, entry->getLabel().c_str());
    }

    mustCreateArea= true;
    opRez= dbConn->exec(aStmt);
    if (opRez->isOk()) {
      if (opRez->getNbrRows() > 0) {
        //ATTN: For now we match anything.
        mustCreateArea= false;

        opRez->fieldAsInt(0, 0, newUid);
        entry->setUid(newUid);
        if (opRez->getNbrRows() == 1) {
          // Anything to do?
        }
        else {
          //TODO: throw exception.
        }
      }
    }
    delete opRez;

    if (mustCreateArea)
      break;
    containingID= newUid;
  }

  if (mustCreateArea) {
    //BUG: if cursor == path:"HOME", then we must do a special insert.
    for (; cursor != pagePath.end(); cursor++) {
      PathEntry *entry= *cursor;

      parentID= containingID;
      entry->serializeInto(dbConn, containingID, propertyID);
      containingID= entry->getUid();
    }    
  }
}


void PageHD::setUrlPrefix(const std::string &aUrl)
{
  size_t aPos;

  if ((aPos= aUrl.rfind('/')) != std::string::npos) {
    prefix= aUrl.substr(0, aPos);
  }
}


/*********************************************
* Implementation: CategoryHD.
*********************************************/

CategoryHD::CategoryHD(xtnHPcData *aStr,  char *aRef)
{
  std::string tmpString;
  int startPos, endPos;

  if (aRef != 0) {
    url= aRef;
    startPos= 0;
    // Remove attribute quotes from the url:
    if (url[0] == '"')
      url.erase(0, 1);
    if (url[url.length() - 1] == '"')
      url.erase(url.length()-1, 1);
    do {
      if ((startPos= url.find("&amp;", startPos)) != std::string::npos) {
        url.erase(startPos+1, 4);
        startPos++;
      }
      else
        break;
    } while (true);
  }

  tmpString= aStr->getData();
  startPos= tmpString.find_first_not_of(" \n\t");
  endPos= tmpString.find_last_not_of(" \n\t");
  label= tmpString.substr(startPos, (endPos - startPos + 1));
  startPos= 0;
  do {
    if ((startPos= label.find("&amp;", startPos)) != std::string::npos) {
      label.erase(startPos + 1, 4);
      startPos++;
    }
    else
      break;
  } while (true);
  // Remove the trailing "(<count>)" info in some category names.
  if (label[label.size()-1] == ')') {
    if (isdigit(label[label.size()-2])) {
      endPos= label.find_last_of('(');
      startPos= label.find_last_not_of(" \n\t", endPos-1);
      label.erase(startPos + 1);
    }
  }
  kind= inactive;
}


CategoryHD::~CategoryHD()
{
  std::list<CategoryHD *>::iterator cursor;

  for (cursor= subCats.begin(); cursor != subCats.end(); cursor++) {
    delete *cursor;
  }
}


void CategoryHD::serializeInto(DBChannel *dbConn, std::string &prefix, int aParent, int aTopID, int aProperty)
{
  DBResult *opRez;
  char aStmt[2048];
  int areaID= 0;
  bool mustCreateArea= true, skipCat= false;

  switch(kind) {
    case namedNode:
    case innerNode:
      if (kind == namedNode) {
        sprintf(aStmt, "select uid, url from di.SiteArea where parent=%d and propertyfk=%d and label = '%s'", aTopID, aProperty, label.c_str());
      }
      else if (kind == innerNode) {
        sprintf(aStmt, "select uid, url from di.SiteArea where parent=%d and propertyfk=%d and label = '%s'", aParent, aProperty, label.c_str());
      }
      opRez= dbConn->exec(aStmt);
      if (opRez->isOk()) {
        if (opRez->getNbrRows() > 0) {
          mustCreateArea= false;
          opRez->fieldAsInt(0, 0, areaID);
          if (opRez->getNbrRows() == 1) {
            char existingUrl[2048];
    
            opRez->fieldAsChar(0, 1, existingUrl, 2048);
            skipCat= url.compare(existingUrl) == 0;
          }
          else {
            //TODO: throw exception.
          }
        }
      }
      delete opRez;

      if (mustCreateArea) {
        char fullUrl[2048];
        if (url[0] == '/') {
          if (kind == namedNode) {
            sprintf(aStmt, "insert into di.SiteArea (parent, propertyfk, label, url) values (%d, %d, '%s', '%s')"
            , aTopID, aProperty, label.c_str(), url.c_str());
          }
          else if (kind == innerNode) {
            sprintf(aStmt, "insert into di.SiteArea (parent, propertyfk, label, url) values (%d, %d, '%s', '%s')"
            , aParent, aProperty, label.c_str(), url.c_str());
          }
        }
        else {
          if (kind == namedNode) {
            sprintf(aStmt, "insert into di.SiteArea (parent, propertyfk, label, url) values (%d, %d, '%s', '%s/%s')"
            , aTopID, aProperty, label.c_str(), prefix.c_str(), url.c_str());
          }
          else {
            sprintf(aStmt, "insert into di.SiteArea (parent, propertyfk, label, url) values (%d, %d, '%s', '%s/%s')"
            , aParent, aProperty, label.c_str(), prefix.c_str(), url.c_str());
          }
        }
        opRez= dbConn->exec(aStmt);
        if (opRez->isOk()) {
          DBResult *lastValRez;
    
          lastValRez= dbConn->exec("select lastval()");
          if (lastValRez->isOk()) {
            if (lastValRez->getNbrRows() == 1) {
              lastValRez->fieldAsInt(0, 0, areaID);
            }
            else {
              //TODO: Throw exception.
            }
          }
          delete lastValRez;
        }
        delete opRez;
      }
      if (areaID == 0)
        return;
    
      if (url.size() > 0) {
        if (url[0] == '/') {
          sprintf(aStmt, "insert into di.FetchRequest (sourcefk, kind, actualurl) values (%d, 1, '%s')", areaID, url.c_str());
        }
        else {
          sprintf(aStmt, "insert into di.FetchRequest (sourcefk, kind, actualurl) values (%d, 1, '%s/%s')", areaID, prefix.c_str(), url.c_str());
        }
        opRez= dbConn->exec(aStmt);
        if (opRez->isOk()) {
          //ATTN: what to do?
        }
        else {
          //TODO: throw exception.
        }
        delete opRez;
      }
      break;

    case anonymousNode:
      areaID= aParent;
      aParent= aTopID;
      break;

    default:
      break;
  }
  //TODO: Use exception in the code above to do away with this situation.

  if (areaID != 0) {
    std::list<CategoryHD *>::iterator cursor;
    for (cursor= subCats.begin(); cursor != subCats.end(); cursor++) {
      CategoryHD *category= *cursor;
      category->serializeInto(dbConn, prefix, areaID, aParent, aProperty);
    }
  }
}


void CategoryHD::addSubCat(xtnHPcData *aLabel, char *aRef)
{
  CategoryHD *newCat;
  newCat= new CategoryHD(aLabel, aRef);
  subCats.push_back(newCat);
}


bool CategoryHD::nameMatch(char *aLabel)
{
  return strcasecmp(label.c_str(), aLabel) == 0;
}


void CategoryHD::setSubKind(int aKind)
{
  std::list<CategoryHD *>::iterator cursor;

  for (cursor= subCats.begin(); cursor != subCats.end(); cursor++) {
    CategoryHD *category= *cursor;
    category->setKind(aKind);
  }
}


/*********************************************
* Implementation: ProductHD.
*********************************************/

ProductHD::ProductHD(xtnHtmlElement *aHolder)
{
  holder= aHolder;
}

void ProductHD::locateElements(HtScanner *scanner)
{
  xtnHPcData *pcData;
  xtnHtmlElement *cursor;
  xtnHtmlElement *details;
  xtnHtmlAttribute *attrib;

/*
div.product {
    a href=<full path> onclick=<js(rel path)> {
      img #product-img src=<full path> alt=<prod name>
    }
    div.details {
      p.product-name {
        a href=<full path> onclick=<js(rel path)> {
          <brand> BR <product name>
        }
        p.model-number {
          model <label>
        }
        div.prices {
          p.price {
            <price>
          }
          span {
            a href=<full path> {
              <rebate text>
            }_a
          }_span
        }_div.prices
      }_p.product-name
      div.actions {
      }_div.actions
    }_a
}_div.product
*/
  
  // std::cout << "@DBG [ProductHD.locateElements] begin.\n";

  // Image reference:
  if ((cursor= scanner->searchForAt(xtnHtmlDTD::tImg, holder)) != NULL) {
    if (cursor->attributeMatch("class", "\"product-img\"") || ((xtnHtmlElement *)cursor->getParent())->attributeMatch("class", "\"product-img-link\"")) {
      attrib= (xtnHtmlAttribute *)cursor->getAttribute("src");
      if (attrib != 0) {
        imageUrl= attrib->getValue();
      }
    }
    else 
      throw new ParseProblem("incorrect class for image", cursor);
  }
  else
    throw new ParseProblem("missing image in product");


  // Link to details and official product label:
  if ((details= scanner->searchForAfter(xtnHtmlDTD::tA, cursor, holder)) != NULL) {
    attrib= (xtnHtmlAttribute *)details->getAttribute("href");
    if (attrib != 0) {
      detailUrl= attrib->getValue();
    }

    xtnCoreElementList *subElements;
    xtnHtmlElement *anEle;
    bool passBrand;

    passBrand= false;
    subElements= details->getSubElements();
    for (unsigned int i= 0; i < subElements->count(); i++) {
      anEle= (xtnHtmlElement *)subElements->objectAt(i);
      if (anEle->getTag() == xtnHtmlDTD::tBr) {
        passBrand= true;
        continue;
      }
      if (anEle->getTag() == xtnHtmlDTD::tPcdata) {
        if (passBrand) {
          name+= ((xtnHPcData *)anEle)->getData();
        }
        else {
          brand+= ((xtnHPcData *)anEle)->getData();
        }
      }
    }
  }
  else
    throw new ParseProblem("details link missing in product");

  // Model number:
  if ((cursor= scanner->searchForAfter(xtnHtmlDTD::tP, details, holder)) != NULL) {
    if (cursor->attributeMatch("class", "\"model-number\"")) {
      pcData= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, cursor, true);
      model= pcData->getData();
    }
    else
      throw new ParseProblem("incorrect class for model number");
  }
  else
    throw new ParseProblem("model number missing in product");

  // Price:
  if ((cursor= scanner->searchForAfter(xtnHtmlDTD::tP, cursor, holder)) != NULL) {
    if (cursor->attributeMatch("class", "\"price\"") || cursor->attributeMatch("class", "\"price-strike\"")) {
      pcData= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, cursor, true);
      price= pcData->getData();
    }
    else
      throw new ParseProblem("incorrect class for price");
  }
  else
    throw new ParseProblem("price missing in product");

  // std::cout << "@DBG [ProductHD.locateElements] end.\n";
}


void ProductHD::serialize(DBChannel *dbChannel, int catalogID, int categoryID)
{
  DBResult *opRez;
  std::string tmpString;
  size_t startPos, endPos;

  if (imageUrl[0] == '"')
    imageUrl.erase(0, 1);
  if (imageUrl[imageUrl.length() - 1] == '"')
    imageUrl.erase(imageUrl.length()-1, 1);
  startPos= 0;
  do {
    if ((startPos= imageUrl.find("&amp;", startPos)) != std::string::npos) {
      imageUrl.erase(startPos+1, 4);
      startPos++;
    }
    else
      break;
  } while (true);

  if (detailUrl[0] == '"')
    detailUrl.erase(0, 1);
  if (detailUrl[detailUrl.length() - 1] == '"')
    detailUrl.erase(detailUrl.length()-1, 1);
  startPos= 0;
  do {
    if ((startPos= detailUrl.find("&amp;", startPos)) != std::string::npos) {
      detailUrl.erase(startPos+1, 4);
      startPos++;
    }
    else
      break;
  } while (true);
  if ((startPos= detailUrl.find("http://www.homedepot.com")) != std::string::npos) {
    detailUrl.erase(startPos, 24);
  }
  
  if (brand.size() > 0) {
    tmpString= brand;
    startPos= tmpString.find_first_not_of(" \r\n\t");
    endPos= tmpString.find_last_not_of(" \r\n\t");
/* Necessary?
    if (startPos == std::string::npos)
      startPos= 0;
    if (endPos == std::string::npos)
      endPos= tmpString.size()-1;
*/
    brand= tmpString.substr(startPos, (endPos - startPos + 1));
    startPos= 0;
    do {
      if ((startPos= brand.find("&amp;", startPos)) != std::string::npos) {
        brand.erase(startPos + 1, 4);
        startPos++;
      }
      else
        break;
    } while (true);
  }

  tmpString= name;
  startPos= tmpString.find_first_not_of(" \r\n\t");
  endPos= tmpString.find_last_not_of(" \r\n\t");
  name= tmpString.substr(startPos, (endPos - startPos + 1));
  startPos= 0;
  do {
    if ((startPos= name.find("&amp;", startPos)) != std::string::npos) {
      name.erase(startPos + 1, 4);
      startPos++;
    }
    else
      break;
  } while (true);

  tmpString= model;
  startPos= tmpString.find_first_not_of(" \r\n\t");
  endPos= tmpString.find_last_not_of(" \r\n\t");
  if ((startPos != std::string::npos) && (endPos != std::string::npos)) {
    model= tmpString.substr(startPos, (endPos - startPos + 1));
  }
  startPos= 0;
  do {
    if ((startPos= model.find("&amp;", startPos)) != std::string::npos) {
      model.erase(startPos + 1, 4);
      startPos++;
    }
    else
      break;
  } while (true);
  if ((startPos= model.find("Model ")) != std::string::npos) {
    model.erase(startPos, 6);
  }

  // Skip dollar sign.
  tmpString= price;
  startPos= tmpString.find_first_not_of(" \r\n\t");
  endPos= tmpString.find_last_not_of(" \r\n\t");
  price= tmpString.substr(startPos, (endPos - startPos + 1));
  price= price.erase(0, 1);
  // Remove commas.
  startPos= price.find(',');
  while (startPos != std::string::npos) {
    price.erase(startPos, 1);
    startPos= price.find(',', startPos - 1);
  }

  char sqlStmt[4096];
  int itemID= 0;
  std::string tmpBrand= brand;
  std::string tmpName= name;

  startPos= tmpBrand.find("'");
  while (startPos != std::string::npos) {
    tmpBrand.insert(startPos, "\\");
    startPos= tmpBrand.find("'", startPos + 2);
  }
  startPos= tmpName.find("'");
  while (startPos != std::string::npos) {
    tmpName.insert(startPos, "\\");
    startPos= tmpName.find("'", startPos + 2);
  }

  sprintf(sqlStmt, "insert into di.CatalogItemWP (catalogFK, directUrl, brand, label) values (%d, '%s', '%s', '%s')", catalogID, detailUrl.c_str(), tmpBrand.c_str(), tmpName.c_str());

  opRez= dbChannel->exec(sqlStmt);
  if (opRez->isOk()) {
    DBResult *lastValRez;

    lastValRez= dbChannel->exec("select lastval()");
    if (lastValRez->isOk()) {
      if (lastValRez->getNbrRows() == 1) {
        lastValRez->fieldAsInt(0, 0, itemID);
      }
      else {
        //TODO: Throw exception.
        std::cout << "@ERR[ProductHD.serialize] can't get lastval (sql: " << sqlStmt << ").\n";
      }
    }
    delete lastValRez;
  }
  else {
    //TODO: Throw exception.
    std::cout << "@ERR[ProductHD.serialize] new item didn't insert (sql: " << sqlStmt << ").\n";
  }
  delete opRez;

/* DBG:
  std::cout << "[ProductHD.serialize] " << sqlStmt << "\n";
*/

  sprintf(sqlStmt, "insert into di.HomeDepotExtra (itemFK, model) values (%d, '%s')", itemID, model.c_str());
  opRez= dbChannel->exec(sqlStmt);
  if (!opRez->isOk()) {
    //TODO: Throw exception.
    std::cout << "@ERR[ProductHD.serialize] sql failed (sql: " << sqlStmt << ").\n";
  }
  delete opRez;
  sprintf(sqlStmt, "insert into di.PricingCI (itemFK, amount) values (%d, '%s')", itemID, price.c_str());
  opRez= dbChannel->exec(sqlStmt);
  if (!opRez->isOk()) {
    //TODO: Throw exception.
    std::cout << "@ERR[ProductHD.serialize] sql failed (sql: " << sqlStmt << ").\n";
  }
  delete opRez;

  sprintf(sqlStmt, "insert into di.CategoryMapCI (itemFK, tagFK) values (%d, %d)", itemID, categoryID);
  opRez= dbChannel->exec(sqlStmt);
  if (!opRez->isOk()) {
    //TODO: Throw exception.
    std::cout << "@ERR[ProductHD.serialize] sql failed (sql: " << sqlStmt << ").\n";
  }
  delete opRez;

  sprintf(sqlStmt, "insert into di.FetchRequest (sourceFK, actualUrl, httpType, kind) values (%d, '%s', 1, 3)"
    , itemID, detailUrl.c_str());
  opRez= dbChannel->exec(sqlStmt);
  if (!opRez->isOk()) {
    //TODO: Throw exception.
    std::cout << "@ERR[ProductHD.serialize] sql failed (sql: " << sqlStmt << ").\n";
  }
  delete opRez;

  sprintf(sqlStmt, "insert into di.FetchRequest (sourceFK, actualUrl, httpType, kind) values (%d, '%s', 1, 4)"
    , itemID, imageUrl.c_str());
  opRez= dbChannel->exec(sqlStmt);
  if (!opRez->isOk()) {
    //TODO: Throw exception.
    std::cout << "@ERR[ProductHD.serialize] sql failed (sql: " << sqlStmt << ").\n";
  }
  delete opRez;
}


/***************************************************
* Implementation: PathEntry.
****************************************************/

PathEntry::PathEntry(xtnHPcData *aLabel, char *aUrl)
{
  std::string tmpString;
  int startPos, endPos;

  if (aUrl != 0) {
    url= aUrl;
    startPos= 0;
    // Remove attribute quotes from the url:
    if (url[0] == '"')
      url.erase(0, 1);
    if (url[url.length() - 1] == '"')
      url.erase(url.length()-1, 1);
    do {
      if ((startPos= url.find("&amp;", startPos)) != std::string::npos) {
        url.erase(startPos+1, 4);
        startPos++;
      }
      else
        break;
    } while (true);
  }

  tmpString= aLabel->getData();
  startPos= tmpString.find_first_not_of(" \n\t");
  endPos= tmpString.find_last_not_of(" \n\t");
  label= tmpString.substr(startPos, (endPos - startPos + 1));
  startPos= 0;
  do {
    if ((startPos= label.find("&amp;", startPos)) != std::string::npos) {
      label.erase(startPos + 1, 4);
      startPos++;
    }
    else
      break;
  } while (true);
}


bool PathEntry::match(char *aLabel)
{
  return label.compare(aLabel) == 0;
}


bool PathEntry::match(const std::string &aLabel)
{
  return label.compare(aLabel) == 0;
}


void PathEntry::serializeInto(DBChannel *dbConn, int aParent, int aProperty)
{
  DBResult *opRez;
  char aStmt[2048];

  sprintf(aStmt, "insert into di.SiteArea (parent, propertyfk, label, url) values (%d, %d, '%s', '%s')"
    , aParent, aProperty, label.c_str(), url.c_str());
  opRez= dbConn->exec(aStmt);
  if (opRez->isOk()) {
    DBResult *lastValRez;

    lastValRez= dbConn->exec("select lastval()");
    if (lastValRez->isOk()) {
      if (lastValRez->getNbrRows() == 1) {
        lastValRez->fieldAsInt(0, 0, uid);
      }
      else {
        //TODO: Throw exception.
      }
    }
    delete lastValRez;
  }
  delete opRez;
}


#ifndef _X_AKRALOG_HOMEDEPOTGEN_H_
#define _X_AKRALOG_HOMEDEPOTGEN_H_

#include <sys/time.h>

#include <list>
#include <sstream>

#include "extractor.h"
#include "pageOfRows.h"

class ProductHD;
class xtnHtmlElement;
class xtnHtmlAttribute;
class xtnHPcData;
class DBChannel;
class ParseRequest;
class PageHD;
class CategoryHD;
class ProductHD;
class ItemRow;
class HtScanner;
class PathEntry;
class PageHDExtractor;


/***************************************************
* Definition: HomeDepoter.
****************************************************/

class HomeDepoter : public Extractor {
 protected:
  DBChannel *dbLink;
  std::string connDict;
  std::list<ParseRequest *> requests;
  PageHDExtractor *hdExtractor;
  unsigned int parseKind;

 public:
  HomeDepoter(unsigned int aKind);
  virtual ~HomeDepoter();
  virtual void setDbDict(char *aHost, char *aDb, char *aUser, char *aPwd);
  virtual void connect();
  virtual void fetchWork();
  virtual void doWork();
  virtual void disconnect();

 protected:
  virtual void loadContent(ParseRequest *aRequest);
  virtual void parse(ParseRequest *aRequest);
  virtual void postProcess(ParseRequest *aRequest);
  virtual void offload(ParseRequest *aRequest);
  virtual void writeTrace(ParseRequest *aRequest);
  virtual void updateTrace(ParseRequest *aRequest);
};


/***************************************************
* Definition: PageHDExtractor.
****************************************************/

class PageHDExtractor : public Extractor {
 protected:
  HtScanner *scanner;
  unsigned int parseKind;

 public:
  PageHDExtractor(unsigned int aKind);
  virtual ~PageHDExtractor();

  virtual Extract *extract(std::istream *aStream, char *aCode);
  virtual PageHD *inspect_A(HtScanner *scanner);
  virtual void inspect_B(HtScanner *scanner, PageHD *aPage);
  virtual bool productPageCheck(HtScanner *scanner);
  virtual Extract *productsXtr(HtScanner *scanner);
  virtual Extract *categoriesXtr(HtScanner *scanner);
};


/***************************************************
* Definition: ParseRequest.
****************************************************/

class ParseRequest {
 protected:
  std::stringstream *blobContent;  // blob content
  PageHD *result;   // parse result.
  struct timeval start, end;   // Timing info; gettimeofday(struct timeval *tv, struct timezone *tz).
  std::string requestedUrl;
  int uid;    // parsejob id.
  int jobID;  // parsejob id.
  int outputID, blobID, blobSize, httpReplyCode;  // fetchoutput info.
  int superArea, webProperty;    // siteare id, property id.

 public:
  ParseRequest(int anID, int anOutputID);
  virtual ~ParseRequest();
  virtual void accumulate(char *aBuffer, size_t aLength);
  virtual bool isGood();
  virtual void startWatch();
  virtual void stopWatch();
  virtual unsigned int getDuration();

  inline void setBlobDetails(int anID, int aSize, int aRezCode)
    { blobID= anID; blobSize= aSize; httpReplyCode= aRezCode; }
  inline void setSiteInfo(int anID, int aPropID, char *aUrl) { superArea= anID; webProperty= aPropID; requestedUrl= aUrl; }
  inline void setParseOutput(PageHD *anOutput) { result= anOutput; }
  inline std::stringstream *getContent() { return blobContent; }
  inline void setJobID(int anID) { jobID= anID; }
  inline int getUid() { return uid; }
  inline int getOutputID() { return outputID; }
  inline int getJobID() { return jobID; }
  inline PageHD *getPage() { return result; }
  inline int getSiteArea() { return superArea; }
  inline int getBlobID() { return blobID; }
  inline int getProperty() { return webProperty; }
  inline std::string getUrl() { return requestedUrl; }
};


/***************************************************
* Definition: PageHD.
****************************************************/

class PageHD : public Extract {
 public:
  enum Kind { home, catePromo, cateProduct, nextProduct, unknown };

 protected:
  std::list<PathEntry *> pagePath;
  xtnHtmlElement *firstAnchor;
  std::list<CategoryHD *> categories;
  std::list<ProductHD *> products;
  xtnHtmlElement *productHook;
  unsigned int totalNbrProducts;
  int propertyID, parentID, areaID;
  unsigned int kind;
  std::string prefix;

 public:
  PageHD(std::list<PathEntry *> &aPath, xtnHtmlElement *anchor);
  virtual ~PageHD();

  virtual void analyze(HtScanner *scanner);
  virtual void describeInto(DBChannel *dbConn);
  virtual PathEntry *area();
  virtual void linkProductAt(xtnHtmlElement *aCursor);    // ATTN: move to protected when logic of HomeDepoter::inspect_B is migrated to PageHD.
  virtual void setUrlPrefix(const std::string &aUrl);
  

 protected:
  virtual void homeExtractor(HtScanner *scanner);
  virtual void categoryExtractor(HtScanner *scanner);
  virtual void productExtractor(HtScanner *scanner);
  virtual void categorySimplification();
  virtual void loadAreaSet(DBChannel *dbConn);

 public:
  inline xtnHtmlElement *getFirstAnchor() { return firstAnchor; }
  inline void addCategory(CategoryHD *aCat) { categories.push_back(aCat); }
  inline void setSiteInfo(int anID, int aPropID) { areaID= anID; propertyID= aPropID; }
  inline int getAreaID() { return areaID; }
  inline int getPropertyID() { return propertyID; }
  inline void setKind(unsigned int aKind) { kind= aKind; }
  inline void setTotalProdNbr(unsigned int aValue) { totalNbrProducts= aValue; }
  inline unsigned int getKind() { return kind; }
  inline unsigned int getTotalProdNbr() { return totalNbrProducts; }
  inline unsigned int nbrProductsExtracted() { return products.size(); }
};


/***************************************************
* Definition: CategoryHD.
****************************************************/

class CategoryHD {
 public:
  enum Kinds { inactive, namedNode, innerNode, anonymousNode, refineSet };

 protected:
  std::string url;  // url must be cleaned of html encoding.
  std::string label; // label must be cleaned up.
  std::list<CategoryHD *> subCats;
  int kind;

// Example of aRef: "/webapp/wcs/stores/servlet/Navigation?Ntk=AllProps&amp;N=10000003+90401+501170&amp;storeId=10051&amp;catalogId=10053&amp;langId=-1&amp;cs=501170&amp;cm_sp=Navigation-_-Homepage-_-LeftNav-_-Outdoors"
// Example of label:  Tools &amp; Hardware .

 public:
   CategoryHD(xtnHPcData *aStr,  char *aRef);
   virtual ~CategoryHD();
   virtual void serializeInto(DBChannel *dbConn, std::string &prefix, int aParent, int aTopID, int aProperty);
   virtual void addSubCat(xtnHPcData *aLabel, char *aRef);
   virtual bool nameMatch(char *aLabel);
   virtual void setSubKind(int aKind);

   inline unsigned int getNbrSubCats() { return subCats.size(); }
   inline void setKind(int aKind) { kind= aKind; }
   inline bool isActive() { return kind != inactive; }
   inline std::string getLabel() { return label; }
};


/***************************************************
* Definition: ProductHD.
****************************************************/

class ProductHD : public ItemRow {
  xtnHtmlElement *holder;
  std::string imageUrl;
  std::string detailUrl;
  std::string brand;
  std::string name;
  std::string model;
  std::string price;
  
 public:
   ProductHD(xtnHtmlElement *aHolder);
   virtual void locateElements(HtScanner *scanner);
   virtual void serialize(DBChannel *dbChannel, int catalogID, int categoryID);
};


/***************************************************
* Definition: PathEntry.
****************************************************/

class PathEntry {
 protected:
  std::string label;
  std::string url;
  int uid;

 public:
  PathEntry(xtnHPcData *aLabel, char *aUrl= 0);
  virtual bool match(char *aLabel);
  virtual bool match(const std::string &aLabel);
  virtual void serializeInto(DBChannel *dbConn, int aParent, int aProperty);

  inline void setUid(int anID) { uid= anID; }
  inline std::string getLabel() { return label; }
  inline int getUid() { return uid; }
};



#endif  /* _X_AKRALOG_HOMEDEPOTGEN_H_ */

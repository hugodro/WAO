#ifndef _X_AKRALOG_EXTRACTOR_H_
#define _X_AKRALOG_EXTRACTOR_H_

#include <fstream>


class xtnCoreAnalyzer;
class xtnHtmlDoc;


class Extract {
 protected:
  Extract *next;
  unsigned int type;
  unsigned int status;

 public:
  Extract(unsigned int aType);
  virtual ~Extract();

  virtual void postProcess();

  inline unsigned int getType() { return type; }
  inline void setStatus(unsigned int anInt) { status= anInt; }
  inline unsigned int getStatus() { return status; }
  inline void linkTo(Extract *anExtract) { next= anExtract; }
  inline Extract *getNext() { return next; }
};


class Extractor {
 protected:
  xtnCoreAnalyzer *htAnalyzer;
  xtnHtmlDoc *theDoc;
  unsigned int runFlags;

 protected:
  virtual Extract *allocExtract();

 public:
  Extractor();
  virtual ~Extractor();

  virtual Extract *extract(std::istream *aStream, char *aCode);

  inline xtnHtmlDoc *getDoc() { return theDoc; }
};

#endif /* _X_AKRALOG_EXTRACTOR_H_ */

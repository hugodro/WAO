#ifndef _X_AKRALOG_GOOGALIZER_H_
#define _X_AKRALOG_GOOGALIZER_H_

#include "extractor.h"

class GoogleExtract : public Extract {
 protected:
  char *url;
  char *msg;
  char *desc;

 public:
  GoogleExtract();
  virtual ~GoogleExtract();
  virtual void setUrl(char *aString);
  virtual void setMessage(char *aString);
  virtual void setDescription(char *aString);
  inline char *getUrl() { return url; }
  inline char *getMessage() { return msg; }
  inline char *getDescription() { return desc; }
};


class Googalizer : public Extractor {
 protected:
  virtual Extract *allocExtract();

 public:
  virtual Extract *extract(std::istream *aStream, char *aCode);
};

#endif /* _X_AKRALOG_GOOGALIZER_H_ */

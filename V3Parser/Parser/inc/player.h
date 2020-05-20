#ifndef _X_AKRALOG_PLAYERACTOR_H_
#define _X_AKRALOG_PLAYERACTOR_H_

#include "extractor.h"

class Playeractor : public Extractor {

 public:
  virtual Extract *extract(std::istream *aStream, char *aCode);
};

#endif /* _X_AKRALOG_PLAYERACTOR_H_ */

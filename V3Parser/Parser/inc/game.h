#ifndef _X_AKRALOGGAMORACTOR_H_
#define _X_AKRALOGGAMORACTOR_H_

#include "extractor.h"

class Gamoractor : public Extractor {

 public:
  virtual Extract *extract(std::istream *aStream, char *aCode);
};

#endif /* _X_AKRALOGGAMORACTOR_H_ */

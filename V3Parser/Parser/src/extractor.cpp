
#include <html/htAnalyzer.h>
#include <html/htDoc.h>

#include "extractor.h"

/***************************************
* Implementation: Extract.
****************************************/

Extract::Extract(unsigned int aType) {
  type= aType;
}


Extract::~Extract() {
// NOTE: Anything to do?
}

void Extract::postProcess() {
  // By default, we do nothing.
}

/***************************************
* Implementation: Extractor.
****************************************/

Extractor::Extractor()
{
  htAnalyzer= NULL;
  theDoc= NULL;
  runFlags= 0;
}


Extractor::~Extractor()
{
  delete htAnalyzer;
  delete theDoc;
}


Extract *Extractor::allocExtract()
{
  return new Extract(0);
}


Extract *Extractor::extract(std::istream *aStream, char *aCode)
{
  Extract *result;
  unsigned int opRez;

  htAnalyzer= new xtnHtmlAnalyzer();

  htAnalyzer->setFlags(1);
  opRez= htAnalyzer->parseConformentDoc(aStream, "aTest2");
  theDoc= (xtnHtmlDoc *)htAnalyzer->getCurrentDoc();
  result= allocExtract();

  result->setStatus(opRez);
  return result;
}

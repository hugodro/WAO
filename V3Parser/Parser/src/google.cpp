#include <iostream>

#include <coreml/elementList.h>
#include <html/htAnalyzer.h>
#include <html/htDoc.h>
#include <html/scanner.h>
#include <html/nonStdElements.h>

#include "google.h"


/***************************************
* Implementation: GoogleExtract.
****************************************/

GoogleExtract::GoogleExtract()
 : Extract(1) {
  url= msg= desc= 0;
}


GoogleExtract::~GoogleExtract() {
  delete[] desc;
  delete[] msg;
  delete[] url;
}


void GoogleExtract::setUrl(char *aString) {
  if (aString != 0) {
    unsigned int tmpLng;

    delete[] url;
    tmpLng= strlen(aString) + 1;
    url= new char[tmpLng];
    memcpy(url, aString, tmpLng);
  }
}


void GoogleExtract::setMessage(char *aString) {
  if (aString != 0) {
    unsigned int tmpLng;

    delete[] msg;
    tmpLng= strlen(aString) + 1;
    msg= new char[tmpLng];
    memcpy(msg, aString, tmpLng);
  }
}


void GoogleExtract::setDescription(char *aString) {
  if (aString != 0) {
    unsigned int tmpLng;

    delete[] desc;
    tmpLng= strlen(aString) + 1;
    desc= new char[tmpLng];
    memcpy(desc, aString, tmpLng);
  }
}

/***************************************
* Implementation: Googalizer.
****************************************/

Extract *Googalizer::allocExtract()
{
  return new GoogleExtract();
}


Extract *Googalizer::extract(std::istream *aStream, char *aCode)
{
  GoogleExtract *resultHead, *cResult;

  resultHead= cResult= (GoogleExtract *)Extractor::extract(aStream, aCode);

  if (theDoc != NULL) {
    HtScanner *scanner;
    xtnHtmlElement *div, *para, *cursor, *table;
    xtnHPcData *text;
    xtnCoreAttribute *attrib;
    char *mainURL;
    bool gotARow, gotDescText;

    scanner= new HtScanner(theDoc);

    if ((div= scanner->searchFor(xtnHtmlDTD::tDiv)) != NULL) {  // start of row of answers.
      para= scanner->searchForAt(xtnHtmlDTD::tP, div);
      while (para != NULL) {
          // Format: each result is a block of tP[class="g"] {tA}, tTable { } , tPcData {0}.
        gotARow= false;
        table= NULL;
        if ((attrib= para->getAttribute("class")) != NULL) {
          gotARow= strcmp(((xtnHtmlAttribute *)attrib)->getValue(), "g") == 0;
        }
        if (gotARow) {
          xtnHtmlElement *c2;
          char textBuffer[8192];  // A dynamically growable text buffer would be better here.

          if ((cursor= scanner->searchForAt(xtnHtmlDTD::tA, para)) != NULL) {
            if ((attrib= cursor->getAttribute("href")) != NULL) {
              cResult->setUrl(((xtnHtmlAttribute *)attrib)->getValue());
            }

            textBuffer[0]= '\0';
            c2= scanner->searchForAt(xtnHtmlDTD::tPcdata, cursor);
            do {
              // ATTN: This will blow if there is more than 8191 chars in the message.
              if (((xtnHPcData *)c2)->getData() != NULL)
                strcat(textBuffer, ((xtnHPcData *)c2)->getData()); 
            } while ((c2= scanner->searchForAfter(xtnHtmlDTD::tPcdata, c2, cursor)) != NULL);

            if (textBuffer[0] != '\0')
              cResult->setMessage(textBuffer);
          }
          if ((cursor= scanner->searchForAfter(xtnHtmlDTD::tTd, cursor)) != NULL) {
            c2= (xtnHtmlElement *)cursor->getParent();
            while (c2 != NULL) {
              if (c2->getTag() == xtnHtmlDTD::tTable) {
                table= c2;
                break;
              }
              else
                c2= (xtnHtmlElement *)c2->getParent();
            }

            gotDescText= false;
            if ((attrib= cursor->getAttribute("class")) != NULL) {
              gotDescText= strcmp(((xtnHtmlAttribute *)attrib)->getValue(), "j") == 0;
            }
            if (gotDescText) {
              xtnHtmlElement *fonts[2];

              // TODO: check for existence of fonts[0..1].
              fonts[0]= scanner->searchForAt(xtnHtmlDTD::tFont, cursor);
              fonts[1]= scanner->searchForAt(xtnHtmlDTD::tFont, fonts[0], true);

              textBuffer[0]= '\0';
              c2= scanner->searchForAt(xtnHtmlDTD::tPcdata, fonts[0]);
              do {
                if (((xtnHPcData *)c2)->getData() != NULL)
                  strcat(textBuffer, ((xtnHPcData *)c2)->getData());
              } while ((c2= scanner->searchForAfter(xtnHtmlDTD::tPcdata, c2, fonts[1])) != NULL);
              if (textBuffer[0] != '\0')
                cResult->setDescription(textBuffer);

            }
          }
        } // gotARow
        if (table != NULL) {
          if ((para= scanner->searchForAfter(xtnHtmlDTD::tP, table, div)) != NULL) {
            GoogleExtract *nextExtract;

            nextExtract= (GoogleExtract *)allocExtract();
            cResult->linkTo(nextExtract);
            cResult= nextExtract;
          }
        }
        else
          para= NULL;
      } // para loop.
    } // target == tDiv


  }  // theDoc exists.

  return resultHead;
}

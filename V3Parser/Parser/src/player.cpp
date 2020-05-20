
#include <iostream>

#include <coreml/elementList.h>
#include <html/htAnalyzer.h>
#include <html/htDoc.h>
#include <html/scanner.h>
#include <html/nonStdElements.h>

#include "player.h"


Extract *Playeractor::extract(std::istream *aStream, char *aCode)
{
  Extract *result;

  result= Extractor::extract(aStream, aCode);

  if (theDoc != NULL) {
    HtScanner *scanner;
    xtnHtmlElement *target, *cursor, *anchor;
    xtnHPcData *text;
    bool notFound;

    scanner= new HtScanner(theDoc);

    // Locate and extract number/name/team.
    notFound= true;
    target= scanner->searchFor(xtnHtmlDTD::tTd);
    do {
      if (notFound) {
        if ((cursor= scanner->searchForAfter(xtnHtmlDTD::tTable, target)) != NULL) {
          anchor= cursor;
          if ((target= scanner->searchForAt(xtnHtmlDTD::tTd, cursor)) != NULL) {
            if ((text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, target)) != NULL) {
              char *tmpString;

              tmpString= text->getData();
              if (strstr(tmpString, "# ") != NULL) {
                std::cout << "player: " << aCode << "; " << tmpString << "\n";
                notFound= false;

                if ((cursor= scanner->searchForAfter(xtnHtmlDTD::tA, target)) != NULL) {
                  xtnCoreAttributeList *attribs;
                  attribs= cursor->getAttributes();
                  for (unsigned int i= 0; i < attribs->count(); i++) {
                    if (strcmp(((xtnHtmlAttribute *)attribs->objectAt(i))->getName(), "href") == 0) {
                      std::cout << "team:" << ((xtnHtmlAttribute *)attribs->objectAt(i))->getValue() << "\n";
                      break;
                    }
                  }
                }

              }
            }
          }
        }
      }
    }
    while ((cursor != NULL) && notFound);

    if (!notFound) {
      // Extract mini-bio.
      if ((cursor= scanner->searchForAfter(xtnHtmlDTD::tTr, target)) != NULL) {
        if ((cursor= scanner->searchForAt(xtnHtmlDTD::tTd, cursor)) != NULL) {
          if ((target= scanner->searchForAfter(xtnHtmlDTD::tTd, cursor)) != NULL) {
            if ((text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, target)) != NULL) {
              do {
                char *tmpString;

                tmpString= text->getData();
                std::cout << tmpString << "\n";
                text= (xtnHPcData *)scanner->searchForAfter(xtnHtmlDTD::tPcdata, text, target);
              } while (text != NULL);
            }
          }
        }
      }

      target= anchor;
      if ((cursor= scanner->searchForAfter(xtnHtmlDTD::tTable, target)) != NULL) {
        if ((cursor= scanner->searchForAfter(xtnHtmlDTD::tTable, cursor)) != NULL) {
          xtnHtmlElement *subTable;

          do {
            subTable= cursor;
            if ((cursor= scanner->searchForAt(xtnHtmlDTD::tTd, cursor)) != NULL) {
              if ((text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, cursor)) != NULL) {
                char *tmpString;

                tmpString= text->getData();
                std::cout << "stat: " << tmpString << "\n";

                if ((target= scanner->searchForAfter(xtnHtmlDTD::tTable, cursor)) != NULL) {
                  if ((cursor= scanner->searchForAt(xtnHtmlDTD::tTr, target)) != NULL) {
                    do {
                      if ((cursor= scanner->searchForAfter(xtnHtmlDTD::tTr, cursor, target)) != NULL) {
                        xtnHtmlElement *c2;

                        if ((c2= scanner->searchForAt(xtnHtmlDTD::tTd, cursor)) != NULL) {
                          std::cout << "row: ";
                          do {
                            if ((text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, c2)) != NULL) {
                              std::cout << text->getData();
                            }
                            if ((c2= scanner->searchForAfter(xtnHtmlDTD::tTd, c2, cursor)) != NULL)
                              std::cout << ", ";
                          } while (c2 != NULL);
                          std::cout << "\n";
                        }
                      }
                    } while (cursor != NULL);
                  }
                }
              }
            }
            cursor= scanner->searchForAfter(xtnHtmlDTD::tTable, subTable, anchor);
          } while (cursor != NULL);
        }
      }
    }
  }

  return result;
}

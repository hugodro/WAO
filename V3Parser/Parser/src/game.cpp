#include <iostream>

#include <coreml/elementList.h>
#include <html/htAnalyzer.h>
#include <html/htDoc.h>
#include <html/scanner.h>
#include <html/nonStdElements.h>

#include "game.h"


Extract *Gamoractor::extract(std::istream *aStream, char *aCode)
{
  Extract *result;

  result= Extractor::extract(aStream, aCode);

  if (theDoc != NULL) {
    HtScanner *scanner;
    xtnHtmlElement *target, *cursor, *anchor;
    xtnHPcData *text;
    bool notFound;

    scanner= new HtScanner(theDoc);

    // Locate the first Quarter element.
    notFound= true;
    if ((target= scanner->searchFor(xtnHtmlDTD::tA)) != NULL) {
      do {
        if ((text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, target)) != NULL) {
          char *tmpString;

          tmpString= text->getData();
          if ((strcmp(tmpString, "Team Stats") == 0) || (strcmp(tmpString, "Game Stats") == 0)) {
            notFound= false;
            break;
          }
        }
        target= scanner->searchForAfter(xtnHtmlDTD::tA, target);
      } while (target != NULL);

      if (!notFound) {
        // Get game ID.
        xtnCoreAttributeList *attribs;
        attribs= target->getAttributes();
        for (unsigned int i= 0; i < attribs->count(); i++) {
          if (strcmp(((xtnHtmlAttribute *)attribs->objectAt(i))->getName(), "href") == 0) {
            std::cout << "game:" << ((xtnHtmlAttribute *)attribs->objectAt(i))->getValue() << "\n";
            break;
          }
        }

        // Run through rows.
        target= scanner->searchForAfter(xtnHtmlDTD::tTable, target);
        if ((anchor= scanner->searchForAfter(xtnHtmlDTD::tTable, target)) != NULL) {
          notFound= true;

          if ((text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, anchor)) != NULL) {
            do {
              if (strcmp(text->getData(), "First Quarter") == 0) {
                notFound= false;
                break;
              }
              text= (xtnHPcData *)scanner->searchForAfter(xtnHtmlDTD::tPcdata, text, anchor);
            } while (text != NULL);

            if (!notFound) {
              xtnHtmlElement *td[2];

              cursor= scanner->searchForAfter(xtnHtmlDTD::tTr, text, anchor);
              do {
                td[0]= scanner->searchForAt(xtnHtmlDTD::tTd, cursor);
                td[1]= scanner->searchForAfter(xtnHtmlDTD::tTd, td[0], cursor);
                if (td[1] == NULL) {
                  if ((text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, td[0])) != NULL) {
                    bool gotHeader= false;

                    attribs= td[0]->getAttributes();
                    for (unsigned int i= 0; i < attribs->count(); i++) {
                      if (strcmp(((xtnHtmlAttribute *)attribs->objectAt(i))->getName(), "class") == 0) {
                        if ((strcmp(((xtnHtmlAttribute *)attribs->objectAt(i))->getValue(), "home") == 0) || (strcmp(((xtnHtmlAttribute *)attribs->objectAt(i))->getValue(), "away") == 0)) {
                          std::cout << "context: " << text->getData() << "\n";
                          gotHeader= true;
                        }
                        else if (strcmp(((xtnHtmlAttribute *)attribs->objectAt(i))->getValue(), "bg3") == 0) {
                          std::cout << "tlEvent: " << text->getData() << "\n";
                          gotHeader= true;
                        }
                        if (gotHeader)
                          break;
                      }
                    }
                    if (!gotHeader) {
                      std::cout << "info: " << text->getData() << "\n";
                    }
                  }
                }
                else {
                  // Row with 2 columns.
                  if ((text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, td[0])) != NULL) {
                    std::cout << "event: " << text->getData() << "[[";
                  }
                  if ((text= (xtnHPcData *)scanner->searchForAt(xtnHtmlDTD::tPcdata, td[1])) != NULL) {
                    std::cout << text->getData() << "]]\n";
                  }
                }
                cursor= scanner->searchForAfter(xtnHtmlDTD::tTr, cursor, anchor);
              } while (cursor != NULL);
            }

          }
        }
      }
    }
  }

  return result;
}

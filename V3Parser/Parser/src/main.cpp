#include <unistd.h>

#include <iostream>
#include <fstream>

#include <html/htRender.h>
#include <html/htDoc.h>

#include "problem.h"
#include "game.h"
#include "player.h"
#include "google.h"
#include "hkTrader.h"
#include "hkProfile.h"
#include "homeDepot.h"
#include "goHomeHk.h"

main(int argc, char **argv)
{
  std::istream *inputStream;
  std::ofstream *outputStream;
  char **filesInNames;
  unsigned int parseType;

  filesInNames= new char*[1];
  parseType= 6;

  if (argc > 1) {
    Extractor *ractor;
    Extract *extracts;
    xtnHtmlRenderer *renderer;
    unsigned int option;

    do {
      option= getopt(argc, argv, "p:");
      switch(option) {
        case 'p':
          parseType= atoi(optarg);
          break;
      }
    } while (option != -1);

    filesInNames[0]= argv[argc-1];

    inputStream= new std::ifstream(filesInNames[0], std::ios::in | std::ios::binary);

    switch(parseType) {
      case 1:
        ractor= new Playeractor();
        break;
      case 2:
        ractor= new Gamoractor();
        break;
      case 3:
        ractor= new Googalizer();
        break;
      case 4:
        ractor= new HkTrader();
        break;
      case 5:
        ractor= new HkProfiler();
        break;
      case 6:
        ractor= new HomeDepoter();
        break;
      case 7:
        ractor= new GoHomeHk();
        break;
    }

    try {
      if ((extracts= ractor->extract(inputStream, filesInNames[0])) != NULL) {
        extracts->postProcess();
      }
    }
    catch (ParseProblem *aProb) {
      std::cerr << aProb->what() << "\n";
    }

#if defined(CONSTRUCT_OUTPUT)
    char ouchName[80]= "/tmp/";
    strcat(ouchName, filesInNames[0]);

    outputStream= new std::ofstream(ouchName, std::ios::out | std::ios::binary);

    renderer= new xtnHtmlRenderer(outputStream);
    renderer->renderDoc(ractor->getDoc());
    outputStream->close();
#endif

  }
}


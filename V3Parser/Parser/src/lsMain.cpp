#include <unistd.h>
#include <iostream>


#include "problem.h"
#include "landScope.h"

main(int argc, char **argv)
{
  LandScoper *ractor;
  unsigned int fetchKind= 2;

  if (argc > 1) {
    //TODO: take fetchKind from the argv.
  }

  ractor= new LandScoper();
  ractor->setDbDict("chodov", "realestate", "hugo", "hugo");

  try {
    ractor->connect();
    ractor->fetchWork();
    ractor->readFile(argv[argc-1]);
    ractor->doWork();
    ractor->disconnect();
  }
  catch (ParseProblem *aProb) {
    std::cerr << aProb->what() << "\n";
  }
}


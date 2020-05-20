#include <unistd.h>
#include <iostream>


#include "problem.h"
#include "homeDepot.h"

main(int argc, char **argv)
{
  HomeDepoter *ractor;
  unsigned int fetchKind= 2;

  if (argc > 1) {
    //TODO: take fetchKind from the argv.
  }

  ractor= new HomeDepoter(fetchKind);
  ractor->setDbDict("chodov", "tupspace", "tupsone", "onetups");

  try {
    ractor->connect();
    ractor->fetchWork();
    ractor->doWork();
    ractor->disconnect();

  }
  catch (ParseProblem *aProb) {
    std::cerr << aProb->what() << "\n";
  }
}



#include <html/nonStdElements.h>

#include "problem.h"

ParseProblem::ParseProblem(char *aNote, xtnHtmlElement *aPos)
 : std::runtime_error("ParseProblem"),
 internalNote(aNote)
{
  location= aPos;
}


ParseProblem::~ParseProblem() throw ()
{}

const char *ParseProblem::what()  const throw ()
{
  std::string message;

  if (location != 0) {
    char tmpString[32];

    sprintf(tmpString, "(%d, %d)", location->getStartPos(), location->getEndPos());
    message.append(tmpString);
  }

  message.append(std::runtime_error::what());
  message.append(": ");
  message.append(internalNote);
  return message.c_str(); 
}


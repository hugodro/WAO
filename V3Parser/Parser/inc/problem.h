#ifndef __H_AKRALOG_EXCEPTIONMGMNT_H_
#define __H_AKRALOG_EXCEPTIONMGMNT_H_

#include <stdexcept>

class xtnHtmlElement;

class ParseProblem : std::runtime_error {
 protected:
  std::string internalNote;
  xtnHtmlElement *location;

 public:
  ParseProblem(char *aNote, xtnHtmlElement *aPos= 0);
  virtual ~ParseProblem() throw ();
  virtual const char * what() const throw ();
};


#endif /* __H_AKRALOG_EXCEPTIONMGMNT_H_ */

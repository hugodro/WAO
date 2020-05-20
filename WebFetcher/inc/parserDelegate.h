#ifndef _PARSER_DELEGATE_H_
#define _PARSER_DELEGATE_H_ 
/**************************************************
* File: parserDelegate.h.
* Desc: Definition of the ParserDelegate class.
* Module: AkraLog : WebFetcher.
* Rev: 26 mars 2000 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "delegate.h"


class ParserDelegate : public DataDelegate {
  protected:	// Instance variables.

  public:		// Instance methods.
    ParserDelegate(void);
    virtual ~ParserDelegate(void);

    virtual bool beginReception(HttpSession *aSession);
    virtual bool noticeHeader(HttpSession *aSession, HttpResponse *aResponse);
    virtual bool noticeContent(HttpSession *aSession, HttpResponse *aResponse, char *data, unsigned int dataLength);
    virtual bool endReception(HttpSession *aSession, HttpResponse *aResponse, int aStatus);
};

#endif		/*  _PARSER_DELEGATE_H_ */

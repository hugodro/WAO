#ifndef _FILE_DELEGATE_H_
#define _FILE_DELEGATE_H_
/**************************************************
* File: fileDelegate.h.
* Desc: Definition of the FileDelegate class.
* Module: AkraLog : WebFetcher.
* Rev: 6 septembre 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "delegate.h"

class ofstream;


class FileDelegate : public DataDelegate {
  protected:	// Instance variables.
    ofstream *output;
    char *fileName;

  public:		// Instance methods.
    FileDelegate(void);
    virtual ~FileDelegate(void);

    virtual void fileOn(char *aName);
    virtual bool beginReception(HttpSession *aSession);
    virtual bool noticeHeader(HttpSession *aSession, HttpResponse *aResponse);
    virtual bool noticeContent(HttpSession *aSession, HttpResponse *aResponse, char *data, unsigned int dataLength);
    virtual bool endReception(HttpSession *aSession, HttpResponse *aResponse, int aStatus);
};

#endif		/* _FILE_DELEGATE_H_ */

#ifndef _DATA_DELEGATE_H_
#define _DATA_DELEGATE_H_
/**************************************************
* File: delegate.h.
* Desc: Definition of the DataDelegate class.
* Module: AkraLog : WebFetcher.
* Rev: 6 septembre 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include <akra/portableDefs.h>


class HttpSession;
class HttpResponse;


class DataDelegate : public AkObject {
  protected:	// Instance variables.

  public:		// Instance methods.
    DataDelegate(void);
    virtual ~DataDelegate(void);

    virtual bool beginReception(HttpSession *aSession)= 0;
    virtual bool noticeHeader(HttpSession *aSession, HttpResponse *aResponse)= 0;
    virtual bool noticeContent(HttpSession *aSession, HttpResponse *aResponse, char *data, unsigned int dataLength)= 0;
    virtual bool endReception(HttpSession *aSession, HttpResponse *aResponse, int aStatus)= 0;
};

#endif		/* _DATA_DELEGATE_H_ */

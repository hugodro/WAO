#ifndef _HTTP_RESPONSE_H_
#define _HTTP_RESPONSE_H_
/**************************************************
* File: reponse.h.
* Desc: Definition of the HttpResponse and HttpRecord class.
* Module: AkraLog : WebFetcher.
* Rev: 6 septembre 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include <akra/portableDefs.h>


class HttpRecord : public AkObject {
    friend class HttpResponse;
  protected:
    HttpRecord *next;
    unsigned int size;
    char *content;

  public:
    HttpRecord(char *dataText, unsigned int dataLength);
    virtual ~HttpRecord(void);
};


class HttpResponse : public AkObject {
  public:
    enum Flags {
	autoDel= 1
    };

  protected:	// Instance variables.
    HttpRecord *records, *lastRecord;
    unsigned int majorVersion, minorVersion;
    unsigned int type;
    unsigned int nbrRecords;
    Flags flags;
    char *content;

  public:
    HttpResponse(char *aCode);
    virtual ~HttpResponse();
    virtual void addRecord(char *textData, unsigned int length);
    virtual void addContent(char *textData, unsigned int length);

    inline bool isAutoDel(void) { return ((flags & autoDel) != 0); }
};


#endif		/* _HTTP_RESPONSE_H_ */

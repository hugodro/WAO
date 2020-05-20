#ifndef _HTTP_REQUEST_H_
#define _HTTP_REQUEST_H_
/**************************************************
* File: request.h.
* Desc: Definition of the HttpRequest class.
* Module: AkraLog : WebFetcher.
* Rev: 6 novembre 1999 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include <akra/portableDefs.h>

class HttpSession;


class HttpRequest : public AkObject {
  public:
    enum Kind {
      connectRq
      , deleteRq, extensionRq
      , getRq, headRq
      , postRq, putRq
      , optionsRq
      , traceRq
    };
  protected:
    unsigned int cmdLength;
    unsigned int majorVersion, minorVersion;
    char *command;
    Kind kind;
    bool prepared;

  public:
    HttpRequest(Kind aKind);
    virtual ~HttpRequest(void);

    virtual void prepare(void);
    virtual bool emitOn(HttpSession *aSession);

    inline char *getCommand(void) { return command; }
    inline Kind getType(void) { return kind; }
};


class HttpGetRequest : public HttpRequest {
  protected:
    char *uri;

  public:
    HttpGetRequest(char *aURI);
    ~HttpGetRequest(void);

    virtual void prepare(void);

    inline char *getURI(void) { return uri; }
};

#endif        /* _HTTP_REQUEST_H_ */

#ifndef _HTTPSESSION_H_
#define _HTTPSESSION_H_
/**************************************************
* File: httpSession.h.
* Desc: Definition of the HttpSession class.
* Module: Utils : WebFetcher .
* Rev: 9 mai 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include <akra/portableDefs.h>

#include <sys/socket.h>
#include <netinet/in.h>

class DataDelegate;
class HttpResponse;
class FieldTable;
class HttpRequest;


// A HttpSession is in charge of doing requests and response processing.
// Requests are the typical 'get, put, post, ...'.
// Responses are the typical 'data-type length data'.

// Things to implement:
// - HTTP-date.
// - Character set: charset = token.
// - Content coding: content-coding = token.
// - Transfer coding.
// - Media type.


class HttpSession : public AkObject {
  public:
    enum Action {
	get, put
    };
    enum State {
	start, readHeader, readContent
    };
    enum Flags {
	    // Kind (bit 0-1):
	stream= 0x00, seqStream= 0x01, dgram= 0x02
	, kindMask= 0x03,
	    // Activity (bit 2):
	outward= 0x00, inward= 0x04
	, activityMask= 0x04,
	    // State (bit 3-6):
	noConnection= 0x00, connected= 0x08, gotData= 0x018,
	disconnected= 0x020, refused= 0x040
	, stateMask= 0x078
    };

  public:		// Class methods.
    static void socketSleep(unsigned int milliSecs);
    static int getSysErrorCode(void);

  protected:		// Instance variables.
    Flags flags;
    int socketFD;
    struct sockaddr_in destination;
    int status;
    unsigned int readSoFar;
    char *hostName;
    char *pageName;
    DataDelegate *delegate;
    FieldTable *fields;	// The field values that are sent as part of a HTTP request.

  protected:	// Instance methods.
    virtual bool connectToHost(char *hostName, int port, unsigned int nbrRetries);

  public:		// Instance methods.
    HttpSession(DataDelegate *aDelegate);

    virtual bool open(char *aHost, unsigned int aPort);
    virtual bool reopen(void);
    virtual bool execute(HttpRequest *request);
    virtual Flags getStatus(void);
    virtual bool emitRequest(HttpRequest *request);
    virtual bool receiveAnswer(void);
    virtual bool beginReception(void);
    virtual bool handleHeader(HttpResponse *response);
    virtual bool handleContent(HttpResponse *response, char *data, unsigned int dataLength);
    virtual bool endReception(HttpResponse *response, int aStatus);
    virtual void setDelegate(DataDelegate *aDelegate);
};


#endif		/* _HTTPSESSION_H_ */

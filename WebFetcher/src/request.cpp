/**************************************************
* File: request.cc.
* Desc: Implementation of the HttpRequest class.
* Module: AkraLog : WebFetcher.
* Rev: 25 mars 2000 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "httpSession.h"
#include "request.h"


/*************************************************
* Implementation: HttpRequest.
 *************************************************/

HttpRequest::HttpRequest(Kind aKind)
{
    command= NULL;
    cmdLength= 0;
    kind= aKind;
    majorVersion= 1;
    minorVersion= 0;
    prepared= false;
}


HttpRequest::~HttpRequest(void)
{
    if (command != NULL) delete[] command;
}


void HttpRequest::prepare(void)
{
    // By default, nothing goes on here...
    prepared= true;
}


bool HttpRequest::emitOn(HttpSession *aSession)
{
    bool result= false;

    // TMP:
    if (!prepared) prepare();
    result= aSession->emitRequest(this);

    return result;
}


/*************************************************
* Implementation: HttpGetRequest.
 *************************************************/

HttpGetRequest::HttpGetRequest(char *aURI)
  : HttpRequest(HttpRequest::getRq)
{
    if (aURI != NULL) {
        unsigned int length= strlen(aURI)+1;
        uri= new char[length];
        memcpy(uri, aURI, length);
    }
    else
        uri= NULL;
}


HttpGetRequest::~HttpGetRequest(void)
{
    if (uri != NULL) delete[] uri;
}

void HttpGetRequest::prepare(void)
{
    unsigned int uriLng;

    if (command != NULL) delete[] command;

    cmdLength= 4 + (uriLng= strlen(uri)) + 12;
    command= new char[cmdLength];
    strcpy(command, "GET ");
    strcpy(command+4, uri);
    sprintf(command + 4 + uriLng, " HTTP/%d.%d\r\n", majorVersion, minorVersion);
    prepared= true;
}

/**************************************************
* File: reponse.cc.
* Desc: Implementation of the HttpResponse and HttpRecord class.
* Module: AkraLog : WebFetcher.
* Rev: 6 septembre 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

// DEBUG:
#include <iostream>

#include "response.h"

/**************************************************
* Implementation: HttpRecord.
**************************************************/

HttpRecord::HttpRecord(char *dataText, unsigned int dataLength)
{
    content= new char[(size= dataLength+1)];
    memcpy(content, dataText, dataLength * sizeof(char));
    content[dataLength]= '\0';
    next= NULL;
}


HttpRecord::~HttpRecord(void)
{
    delete content;
}


/**************************************************
* Implementation: HttpResponse.
**************************************************/

HttpResponse::HttpResponse(char *data)
{
    records= lastRecord= NULL;
    // ATTN-000326 [HD]: Extract the version major and minor numbers correctly.
    majorVersion= data[0] - 48;
    minorVersion= data[1] - 48;
    data+= 4;
    type= (data[4] - 48) * 100 + (data[5] - 48) * 10 + (data[6] - 48);
    nbrRecords= 0;
    flags= autoDel;
}


HttpResponse::~HttpResponse(void)
{
    HttpRecord *cursor;
    if (records != NULL) {
	lastRecord= records;
	do {
	    cursor= lastRecord->next;
	    delete lastRecord;
	    lastRecord= cursor;
	} while (lastRecord != NULL);
    }
}


void HttpResponse::addRecord(char *textData, unsigned int length)
{
    HttpRecord *newRecord= new HttpRecord(textData, length);

    if (records == NULL) {
	records= newRecord;
    }
    else {
	lastRecord->next= newRecord;
    }
    lastRecord= newRecord;
    nbrRecords++;
}


void HttpResponse::addContent(char *textData, unsigned int length)
{
    // TODO.
}


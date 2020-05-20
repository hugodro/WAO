/*******************************************
 * File: documents.cpp.
 * Desc: Implementation of the xtnHBDoc and xtnMLDoc class.
 * History: 2000/05/12 : REV 0 : [HD] : Creation.
******************************************/

#include <iostream>
#include <fstream>
#if defined(_WIN32)
using namespace std;
#endif

#include "documents.h"


/***********************************************************
* Implementation: xtnHBDoc.
***********************************************************/

xtnHBDoc::xtnHBDoc(void)
{
    next= NULL;
    contentData= NULL;
    contentLength= 0;
    useCount= 0;
    cacheable= true;
}


xtnHBDoc::xtnHBDoc(char *someData, unsigned int length)
{
    next= NULL;
    if (someData != NULL) {
	contentLength= length;
	if (length > 0) {
	    contentData= new char[contentLength];
	    memcpy(contentData, someData, contentLength);
	}
	else {
	    contentData= NULL;
	    contentLength= 0;
	}
    }
    useCount= 0;
    cacheable= true;
}


xtnHBDoc::~xtnHBDoc(void)
{
    delete[] contentData;
}


unsigned int xtnHBDoc::getClass(void)
{
    return 0;
}


bool xtnHBDoc::loadFromFile(char *fileName)
{
    ifstream *aStream;
    bool result= false;

#if defined(_WIN32)
    aStream= new ifstream(fileName, ios::in | ios::binary);
#else
    aStream= new ifstream(fileName, ios::in);
#endif

    if (aStream->good()) {
	aStream->seekg(0, ios::end);
	contentLength= aStream->tellg();
	if ((contentLength > 0) && (contentLength < maxDocSize)) {
	    aStream->seekg(0, ios::beg);
	    contentData= new char[contentLength];
	    aStream->read(contentData, contentLength);
	    result= true;
	}
	else
	    contentLength= 0;
    }
    delete aStream;

    return result;
}


unsigned int xtnHBDoc::spitInto(char *aBuffer, unsigned int maxLength)
{
    unsigned int writtenLng;

    if (contentLength > 0) {
	writtenLng= (contentLength < maxLength) ? contentLength : maxLength;
	memcpy(aBuffer, contentData, writtenLng);
    }
    else
	writtenLng= 0;

    return writtenLng;
}


/***********************************************************
* Implementation: xtnMLDoc.
***********************************************************/


xtnMLDoc::xtnMLDoc(void)
  : xtnHBDoc()
{
}


xtnMLDoc::xtnMLDoc(char *someData, unsigned int length)
  : xtnHBDoc(someData, length)
{
}


unsigned int xtnMLDoc::getClass(void)
{
    return 1;
}




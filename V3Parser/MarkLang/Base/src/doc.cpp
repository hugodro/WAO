/**************************************************
* File: doc.cc.
* Desc: Definition of the core ML Document.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/08/22 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: doc.cpp,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1.1.1  2000/09/01 07:33:30  hugo
* Initial Entry
*
**************************************************/

#include <string>
#include <time.h>

#include "doc.h"


xtnCoreDoc::xtnCoreDoc(char *aName)
{
    if (aName != NULL) {
	sourceName= new char[strlen(aName)+1];
	strcpy(sourceName, aName);
    }
    dateParsed= NULL;
}


xtnCoreDoc::~xtnCoreDoc(void)
{
    if (dateParsed != NULL) delete[] dateParsed;
    if (sourceName != NULL) delete[] sourceName;
}


char *xtnCoreDoc::getDateParsed(void)
{
    return dateParsed;
}


char *xtnCoreDoc::getSourceName(void)
{
    return sourceName;
}


xtnCoreDtdDefinition *xtnCoreDoc::getDocType(void)
{
    return docType;
}


void xtnCoreDoc::initForParse(void)
{
    time_t now;
    unsigned int tmpLength;
    char tmpBuffer[256];

// TODO-000822 [HD]: Use the xtnTime literal.
    time(&now);
    strcpy(tmpBuffer, ctime(&now));
	// Ctime ends the string with lf/null, which is one char too much.
    dateParsed= new char[(tmpLength= strlen(tmpBuffer))];
    memcpy(dateParsed, tmpBuffer, tmpLength * sizeof(char));
    dateParsed[tmpLength-1]= '\0';
}


void xtnCoreDoc::treatComment(char *data)
{
    // By default, ignore comments.
}


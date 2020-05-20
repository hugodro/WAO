/**************************************************
* File: sgmlDoc.cc.
* Desc: Definition of the generic SGML document.
* Module: WAO : SgmlParser.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <string.h>
#include <time.h>

#include "sgmlDoc.h"

SgmlDoc::SgmlDoc(char *aName)
{
    if (aName != NULL) {
	sourceName= new char[strlen(aName)+1];
	strcpy(sourceName, aName);
    }
    dateParsed= NULL;
}


SgmlDoc::~SgmlDoc(void)
{
    if (dateParsed != NULL) delete[] dateParsed;
    if (sourceName != NULL) delete[] sourceName;
}


char *SgmlDoc::getDateParsed(void)
{
    return dateParsed;
}


char *SgmlDoc::getSourceName(void)
{
    return sourceName;
}


DtdDefinition *SgmlDoc::getDocType(void)
{
    return docType;
}


void SgmlDoc::initForParse(void)
{
    time_t now;
    unsigned int tmpLength;
    char tmpBuffer[256];

    time(&now);
    strcpy(tmpBuffer, ctime(&now));
	// Ctime ends the string with lf/null, which is one char too much.
    dateParsed= new char[(tmpLength= strlen(tmpBuffer))];
    memcpy(dateParsed, tmpBuffer, tmpLength * sizeof(char));
    dateParsed[tmpLength-1]= '\0';
}


void SgmlDoc::treatComment(char *data)
{
    // By default, ignore comments.
}


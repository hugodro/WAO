/**************************************************
* File: sgmlDoc.cc.
* Desc: Definition of the generic SGML document.
* Module: WAO : SgmlParser.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/
#if defined(_WIN32)
#include <string.h>
#endif
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
    // Set the time/date in dateParse.
}


void SgmlDoc::treatComment(char *data)
{
    // By default, ignore comments.
}


/**************************************************
* File: nonStdElements.cc.
* Desc: Implementation of the optimized version of the special form elements of HTML 3.2.
* Module: WAO : SgmlParser.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#if defined(_WIN32)
#include <string.h>
#endif
#include "nonStdElements.h"

HSpan::HSpan()
    : HtmlElement(HtmlDTD::tSpan)
{
}


/**************************************************
* Implementation: HPcData.
**************************************************/

HPcData::HPcData()
    : HtmlElement(HtmlDTD::tPcdata)
{
    data= NULL;
}


void HPcData::setData(char *someData)
{
    if (someData != NULL) {
	unsigned int dataLength= strlen(someData);
	data= new char[dataLength+1];
	memcpy(data, someData, dataLength);
	data[dataLength]= '\0';
    }
}


char *HPcData::getData(void)
{
    if (data != NULL) return data;
    else return "\0";
}


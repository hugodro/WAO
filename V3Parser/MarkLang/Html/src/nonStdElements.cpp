/**************************************************
* File: nonStdElements.cc.
* Desc: Implementation of the optimized version of the special form elements of HTML 3.2.
* $Date$
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/11/30 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log$
**************************************************/

#include <string>

#include <globDefs.h>

#include "nonStdElements.h"

xtnHSpan::xtnHSpan()
    : xtnHtmlElement(xtnHtmlDTD::tSpan)
{
}


/**************************************************
* Implementation: HPcData.
**************************************************/

xtnHPcData::xtnHPcData()
    : xtnHtmlElement(xtnHtmlDTD::tPcdata)
{
    data= NULL;
}


void xtnHPcData::setData(char *someData)
{
  if (someData != NULL) {
	unsigned int dataLength= strlen(someData);
	data= new char[dataLength+1];
	memcpy(data, someData, dataLength);
	data[dataLength]= '\0';
  }
}


char *xtnHPcData::getData(void)
{
    if (data != NULL) return data;
    else return "\0";
}


void xtnHPcData::mergeData(char *someData)
{
  if (someData != NULL) {
	unsigned int dataLength, offset;

    dataLength= strlen(someData);
    if (data == NULL) {
      offset= 0;
      data= new char[dataLength+1];
    }
    else {
      char *tmpBuf;

      offset= strlen(data);
      tmpBuf= data;
      data= new char[offset + dataLength + 1];
      memcpy(data, tmpBuf, offset);
      delete[] tmpBuf;
    }
	memcpy(data + offset, someData, dataLength);
	data[offset + dataLength]= '\0';
  }
}


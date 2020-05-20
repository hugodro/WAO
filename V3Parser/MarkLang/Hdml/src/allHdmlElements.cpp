/**************************************************
* File: allHdElements.cpp.
* Desc: Implementation of the optimized version of all elements of HDML 2.0.
* Module: WAO : SgmlParser.
* Rev: 29 mai 2000 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/09/02 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: allHdmlElements.cpp,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.2  2000/09/20 03:25:22  hugo
* Minor updates to the HDML rendering.
*
* Revision 1.1  2000/09/05 07:13:40  hugo
* Initial entry of real parsing/generating HDML support.
*
**************************************************/

#if defined(_WIN32)
#include <string>
#endif

#include <globDefs.h>

#include "allHdElements.h"

xtnHdAction::xtnHdAction()
  : xtnHdmlElement(xtnHdmlDTD::tAction)
{


}


xtnHdB::xtnHdB()
  : xtnHdmlElement(xtnHdmlDTD::tB)
{


}


xtnHdBr::xtnHdBr()
  : xtnHdmlElement(xtnHdmlDTD::tBr)
{


}


xtnHdCe::xtnHdCe()
  : xtnHdmlElement(xtnHdmlDTD::tCe)
{


}


xtnHdCenter::xtnHdCenter()
  : xtnHdmlElement(xtnHdmlDTD::tCenter)
{


}


xtnHdChoice::xtnHdChoice()
  : xtnHdmlElement(xtnHdmlDTD::tChoice)
{


}


xtnHdDeck::xtnHdDeck()
  : xtnHdmlElement(xtnHdmlDTD::tDeck)
{


}


xtnHdDisplay::xtnHdDisplay()
  : xtnHdmlElement(xtnHdmlDTD::tDisplay)
{


}


xtnHdEntry::xtnHdEntry()
  : xtnHdmlElement(xtnHdmlDTD::tEntry)
{


}


xtnHdI::xtnHdI()
  : xtnHdmlElement(xtnHdmlDTD::tI)
{


}


xtnHdImg::xtnHdImg()
  : xtnHdmlElement(xtnHdmlDTD::tImg)
{


}


xtnHdLine::xtnHdLine()
  : xtnHdmlElement(xtnHdmlDTD::tLine)
{


}


xtnHdNoDisplay::xtnHdNoDisplay()
  : xtnHdmlElement(xtnHdmlDTD::tNoDisplay)
{


}


xtnHdRight::xtnHdRight()
  : xtnHdmlElement(xtnHdmlDTD::tRight)
{


}


xtnHdTab::xtnHdTab()
  : xtnHdmlElement(xtnHdmlDTD::tTab)
{


}


xtnHdWrap::xtnHdWrap()
  : xtnHdmlElement(xtnHdmlDTD::tWrap)
{


}


xtnHdPcData::xtnHdPcData()
  : xtnHdmlElement(xtnHdmlDTD::tPcdata)
{
    data= NULL;
}


xtnHdPcData::~xtnHdPcData()
{
    delete[] data;
}


void xtnHdPcData::setData(char *someData)
{
    if (someData != NULL) {
	unsigned int tmpLength;
	tmpLength= strlen(someData) + 1;
	data= new char[tmpLength];
	memcpy(data, someData, tmpLength * sizeof(char));
    }
}


xtnHdComment::xtnHdComment(char *someData)
  : xtnHdmlElement(xtnHdmlDTD::tComment)
{
    if (someData != NULL) {
	unsigned int tmpLength;
	tmpLength= strlen(someData) + 1;
	data= new char[tmpLength];
	memcpy(data, someData, tmpLength * sizeof(char));
    }
    else
	data= NULL;
}


xtnHdComment::~xtnHdComment()
{
    delete[] data;
}

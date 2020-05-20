/**************************************************
* File: allWElements.cpp.
* Desc: Implementation of the optimized version of all elements of HDML 2.0.
* Module: WAO : SgmlParser.
* Rev: 29 mai 2000 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "hdmlElement.h"

HdAction::HdAction(void)
  : HdmlElement(HdmlDTD::tAction)
{


}


HdB::HdB(void)
  : HdmlElement(HdmlDTD::tB)
{


}


HdBr::HdBr(void)
  : HdmlElement(HdmlDTD::tBr)
{


}


HdCe::HdCe(void)
  : HdmlElement(HdmlDTD::tCe)
{


}


HdCenter::HdCenter(void)
  : HdmlElement(HdmlDTD::tCenter)
{


}


HdChoice::HdChoice(void)
  : HdmlElement(HdmlDTD::tChoice)
{


}


HdDeck::HdDeck(void)
  : HdmlElement(HdmlDTD::tDeck)
{


}


HdDisplay::HdDisplay(void)
  : HdmlElement(HdmlDTD::tDisplay)
{


}


HdEntry::HdEntry(void)
  : HdmlElement(HdmlDTD::tEntry)
{


}


HdI::HdI(void)
  : HdmlElement(HdmlDTD::tI)
{


}


HdImg::HdImg(void)
  : HdmlElement(HdmlDTD::tImg)
{


}


HdLine::HdLine(void)
  : HdmlElement(HdmlDTD::tLine)
{


}


HdNoDisplay::HdNoDisplay(void)
  : HdmlElement(HdmlDTD::tNoDisplay)
{


}


HdRight::HdRight(void)
  : HdmlElement(HdmlDTD::tRight)
{


}


HdTab::HdTab(void)
  : HdmlElement(HdmlDTD::tTab)
{


}


HdWrap::HdWrap(void)
  : HdmlElement(HdmlDTD::tWrap)
{


}


HdPcData::HdPcData(void)
  : HdmlElement(HdmlDTD::tPcData)
{


}


void HdPcData::setData(char *someData)
{

}


HdComment::HdComment(char *someData)
  : HdmlElement(HdmlDTD::tComment)
{


}




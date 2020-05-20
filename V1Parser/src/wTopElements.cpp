/**************************************************
* File: allWElements.cpp.
* Desc: Implementation of the optimized version of all elements of WML 1.1.
* Module: WAO : SgmlParser.
* Rev: 19 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "allWElements.h"


WAccess::WAccess(void)
  : WmlElement(WmlDTD::tAccess)
{
}


WAnchor::WAnchor(void)
  : WmlElement(WmlDTD::tAnchor)
{
}


WAnchorMin::WAnchorMin(void)
  : WmlElement(WmlDTD::tA)
{
}


WBig::WBig(void)
  : WmlElement(WmlDTD::tBig)
{
}


WBold::WBold(void)
  : WmlElement(WmlDTD::tB)
{
}


WBreak::WBreak(void)
  : WmlElement(WmlDTD::tBr)
{
}


WCard::WCard(void)
  : WmlElement(WmlDTD::tCard)
{
}


WDo::WDo(void)
  : WmlElement(WmlDTD::tDo)
{
}


WEm::WEm(void)
  : WmlElement(WmlDTD::tEm)
{
}


WFieldSet::WFieldSet(void)
  : WmlElement(WmlDTD::tFieldset)
{
}


WGo::WGo(void)
  : WmlElement(WmlDTD::tGo)
{
}


WHead::WHead(void)
  : WmlElement(WmlDTD::tHead)
{
}


WImg::WImg(void)
  : WmlElement(WmlDTD::tImg)
{
}


WInput::WInput(void)
  : WmlElement(WmlDTD::tInput)
{
}


WItalic::WItalic(void)
  : WmlElement(WmlDTD::tI)
{
}


WMeta::WMeta(void)
  : WmlElement(WmlDTD::tMeta)
{
}


WNoop::WNoop(void)
  : WmlElement(WmlDTD::tNoop)
{
}


WOnEvent::WOnEvent(void)
  : WmlElement(WmlDTD::tOnevent)
{
}


WOptGroup::WOptGroup(void)
  : WmlElement(WmlDTD::tOptgroup)
{
}


WOption::WOption(void)
  : WmlElement(WmlDTD::tOption)
{
}


WPara::WPara(void)
  : WmlElement(WmlDTD::tP)
{
}


WPostField::WPostField(void)
  : WmlElement(WmlDTD::tPostfield)
{
}


WPrev::WPrev(void)
  : WmlElement(WmlDTD::tPrev)
{
}


WRefresh::WRefresh(void)
  : WmlElement(WmlDTD::tRefresh)
{
}


WSelect::WSelect(void)
  : WmlElement(WmlDTD::tSelect)
{
}


WSetVar::WSetVar(void)
  : WmlElement(WmlDTD::tSetvar)
{
}


WSmall::WSmall(void)
  : WmlElement(WmlDTD::tSmall)
{
}


WStrong::WStrong(void)
  : WmlElement(WmlDTD::tStrong)
{
}


WTable::WTable(void)
  : WmlElement(WmlDTD::tTable)
{
}


WTableData::WTableData(void)
  : WmlElement(WmlDTD::tTd)
{
}


WTableRow::WTableRow(void)
  : WmlElement(WmlDTD::tTr)
{
}


WTemplate::WTemplate(void)
  : WmlElement(WmlDTD::tTemplate)
{
}


WTimer::WTimer(void)
  : WmlElement(WmlDTD::tTimer)
{
}


WUnderscore::WUnderscore(void)
  : WmlElement(WmlDTD::tU)
{
}


WWml::WWml(void)
  : WmlElement(WmlDTD::tWml)
{
}


WPcData::WPcData(void)
  : WmlElement(WmlDTD::tPcdata)
{
    data= NULL;
}


void WPcData::setData(char *someData)
{
    if (someData != NULL) {
	unsigned int tmpLength;
	tmpLength= strlen(someData) + 1;
	data= new char[tmpLength];
	memcpy(data, someData, tmpLength * sizeof(char));
    }
}


WComment::WComment(char *someData)
  : WmlElement(WmlDTD::tComment)
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


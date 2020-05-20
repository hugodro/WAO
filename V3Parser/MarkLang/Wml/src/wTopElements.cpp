/**************************************************
* File: allWElements.cpp.
* Desc: Implementation of the optimized version of all elements of WML 1.1.
* Rev: 19 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/08/22 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: wTopElements.cpp,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
**************************************************/

#if defined(_WIN32)
#include <string>
#else
#include <string.h>
#endif

#include <globDefs.h>

#include "allWElements.h"


xtnWAccess::xtnWAccess(void)
  : xtnWmlElement(xtnWmlDTD::tAccess)
{
}


xtnWAnchor::xtnWAnchor(void)
  : xtnWmlElement(xtnWmlDTD::tAnchor)
{
}


xtnWAnchorMin::xtnWAnchorMin(void)
  : xtnWmlElement(xtnWmlDTD::tA)
{
}


xtnWBig::xtnWBig(void)
  : xtnWmlElement(xtnWmlDTD::tBig)
{
}


xtnWBold::xtnWBold(void)
  : xtnWmlElement(xtnWmlDTD::tB)
{
}


xtnWBreak::xtnWBreak(void)
  : xtnWmlElement(xtnWmlDTD::tBr)
{
}


xtnWCard::xtnWCard(void)
  : xtnWmlElement(xtnWmlDTD::tCard)
{
}


xtnWDo::xtnWDo(void)
  : xtnWmlElement(xtnWmlDTD::tDo)
{
}


xtnWEm::xtnWEm(void)
  : xtnWmlElement(xtnWmlDTD::tEm)
{
}


xtnWFieldSet::xtnWFieldSet(void)
  : xtnWmlElement(xtnWmlDTD::tFieldset)
{
}


xtnWGo::xtnWGo(void)
  : xtnWmlElement(xtnWmlDTD::tGo)
{
}


xtnWHead::xtnWHead(void)
  : xtnWmlElement(xtnWmlDTD::tHead)
{
}


xtnWImg::xtnWImg(void)
  : xtnWmlElement(xtnWmlDTD::tImg)
{
}


xtnWInput::xtnWInput(void)
  : xtnWmlElement(xtnWmlDTD::tInput)
{
}


xtnWItalic::xtnWItalic(void)
  : xtnWmlElement(xtnWmlDTD::tI)
{
}


xtnWMeta::xtnWMeta(void)
  : xtnWmlElement(xtnWmlDTD::tMeta)
{
}


xtnWNoop::xtnWNoop(void)
  : xtnWmlElement(xtnWmlDTD::tNoop)
{
}


xtnWOnEvent::xtnWOnEvent(void)
  : xtnWmlElement(xtnWmlDTD::tOnevent)
{
}


xtnWOptGroup::xtnWOptGroup(void)
  : xtnWmlElement(xtnWmlDTD::tOptgroup)
{
}


xtnWOption::xtnWOption(void)
  : xtnWmlElement(xtnWmlDTD::tOption)
{
}


xtnWPara::xtnWPara(void)
  : xtnWmlElement(xtnWmlDTD::tP)
{
}


xtnWPostField::xtnWPostField(void)
  : xtnWmlElement(xtnWmlDTD::tPostfield)
{
}


xtnWPrev::xtnWPrev(void)
  : xtnWmlElement(xtnWmlDTD::tPrev)
{
}


xtnWRefresh::xtnWRefresh(void)
  : xtnWmlElement(xtnWmlDTD::tRefresh)
{
}


xtnWSelect::xtnWSelect(void)
  : xtnWmlElement(xtnWmlDTD::tSelect)
{
}


xtnWSetVar::xtnWSetVar(void)
  : xtnWmlElement(xtnWmlDTD::tSetvar)
{
}


xtnWSmall::xtnWSmall(void)
  : xtnWmlElement(xtnWmlDTD::tSmall)
{
}


xtnWStrong::xtnWStrong(void)
  : xtnWmlElement(xtnWmlDTD::tStrong)
{
}


xtnWTable::xtnWTable(void)
  : xtnWmlElement(xtnWmlDTD::tTable)
{
}


xtnWTableData::xtnWTableData(void)
  : xtnWmlElement(xtnWmlDTD::tTd)
{
}


xtnWTableRow::xtnWTableRow(void)
  : xtnWmlElement(xtnWmlDTD::tTr)
{
}


xtnWTemplate::xtnWTemplate(void)
  : xtnWmlElement(xtnWmlDTD::tTemplate)
{
}


xtnWTimer::xtnWTimer(void)
  : xtnWmlElement(xtnWmlDTD::tTimer)
{
}


xtnWUnderscore::xtnWUnderscore(void)
  : xtnWmlElement(xtnWmlDTD::tU)
{
}


xtnWWml::xtnWWml(void)
  : xtnWmlElement(xtnWmlDTD::tWml)
{
}


xtnWPcData::xtnWPcData(void)
  : xtnWmlElement(xtnWmlDTD::tPcdata)
{
    data= NULL;
}


xtnWPcData::~xtnWPcData(void)
{
    delete[] data;
}


void xtnWPcData::setData(char *someData)
{
    if (someData != NULL) {
	unsigned int tmpLength;
	tmpLength= strlen(someData) + 1;
	data= new char[tmpLength];
	memcpy(data, someData, tmpLength * sizeof(char));
    }
}


xtnWComment::xtnWComment(char *someData)
  : xtnWmlElement(xtnWmlDTD::tComment)
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


xtnWComment::~xtnWComment()
{
    delete[] data;
}

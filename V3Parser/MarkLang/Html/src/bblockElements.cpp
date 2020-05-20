/**************************************************
* File: bblockElements.cc.
* Desc: Implementation of the optimized version of the body block elements of HTML 3.2.
* $Date$
* Rev: 22 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/11/30 : REV 1 : Hugo DesRosiers : Rewrote for Extenta context.
* $Log$
**************************************************/

#include "htDTD.h"
#include "bblockElements.h"


xtnHPara::xtnHPara()
    : xtnHtmlElement(xtnHtmlDTD::tP)
{
}


xtnHUList::xtnHUList()
    : xtnHtmlElement(xtnHtmlDTD::tUl)
{
}


xtnHOList::xtnHOList()
    : xtnHtmlElement(xtnHtmlDTD::tOl)
{
}


xtnHLiElement::xtnHLiElement()
    : xtnHtmlElement(xtnHtmlDTD::tLi)
{
}


xtnHDefList::xtnHDefList()
    : xtnHtmlElement(xtnHtmlDTD::tDl)
{
}


xtnHDefTerm::xtnHDefTerm()
    : xtnHtmlElement(xtnHtmlDTD::tDt)
{
}


xtnHDefDef::xtnHDefDef()
    : xtnHtmlElement(xtnHtmlDTD::tDd)
{
}


xtnHPre::xtnHPre()
    : xtnHtmlElement(xtnHtmlDTD::tPre)
{
}


xtnHDiv::xtnHDiv()
    : xtnHtmlElement(xtnHtmlDTD::tDiv)
{
}


xtnHCenter::xtnHCenter()
    : xtnHtmlElement(xtnHtmlDTD::tCenter)
{
}


xtnHBlockQuote::xtnHBlockQuote()
    : xtnHtmlElement(xtnHtmlDTD::tBlockquote)
{
}


xtnHForm::xtnHForm()
    : xtnHtmlElement(xtnHtmlDTD::tForm)
{
}


xtnHHr::xtnHHr()
    : xtnHtmlElement(xtnHtmlDTD::tHr)
{
}


xtnHTable::xtnHTable()
    : xtnHtmlElement(xtnHtmlDTD::tTable)
{
}


xtnHCaption::xtnHCaption()
    : xtnHtmlElement(xtnHtmlDTD::tCaption)
{
}


xtnHTableRow::xtnHTableRow()
    : xtnHtmlElement(xtnHtmlDTD::tTr)
{
}


xtnHTableHeader::xtnHTableHeader()
    : xtnHtmlElement(xtnHtmlDTD::tTh)
{
}


xtnHTableData::xtnHTableData()
    : xtnHtmlElement(xtnHtmlDTD::tTd)
{
}


xtnHDir::xtnHDir()
    : xtnHtmlElement(xtnHtmlDTD::tDir)
{
}


xtnHMenu::xtnHMenu()
    : xtnHtmlElement(xtnHtmlDTD::tMenu)
{
}


xtnHXmp::xtnHXmp()
    : xtnHtmlElement(xtnHtmlDTD::tXmp)
{
}


xtnHListing::xtnHListing()
    : xtnHtmlElement(xtnHtmlDTD::tListing)
{
}


xtnHPlainText::xtnHPlainText()
    : xtnHtmlElement(xtnHtmlDTD::tPlaintext)
{
}



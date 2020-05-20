/**************************************************
* File: bblockElements.cc.
* Desc: Implementation of the optimized version of the body block elements of HTML 3.2.
* Module: WAO : SgmlParser.
* Rev: 22 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "bblockElements.h"


HPara::HPara()
    : HtmlElement(HtmlDTD::tP)
{
}


HUList::HUList()
    : HtmlElement(HtmlDTD::tUl)
{
}


HOList::HOList()
    : HtmlElement(HtmlDTD::tOl)
{
}


HLiElement::HLiElement()
    : HtmlElement(HtmlDTD::tLi)
{
}


HDefList::HDefList()
    : HtmlElement(HtmlDTD::tDl)
{
}


HDefTerm::HDefTerm()
    : HtmlElement(HtmlDTD::tDt)
{
}


HDefDef::HDefDef()
    : HtmlElement(HtmlDTD::tDd)
{
}


HPre::HPre()
    : HtmlElement(HtmlDTD::tPre)
{
}


HDiv::HDiv()
    : HtmlElement(HtmlDTD::tDiv)
{
}


HCenter::HCenter()
    : HtmlElement(HtmlDTD::tCenter)
{
}


HBlockQuote::HBlockQuote()
    : HtmlElement(HtmlDTD::tBlockquote)
{
}


HForm::HForm()
    : HtmlElement(HtmlDTD::tForm)
{
}


HHr::HHr()
    : HtmlElement(HtmlDTD::tHr)
{
}


HTable::HTable()
    : HtmlElement(HtmlDTD::tTable)
{
}


HCaption::HCaption()
    : HtmlElement(HtmlDTD::tCaption)
{
}


HTableRow::HTableRow()
    : HtmlElement(HtmlDTD::tTr)
{
}


HTableHeader::HTableHeader()
    : HtmlElement(HtmlDTD::tTh)
{
}


HTableData::HTableData()
    : HtmlElement(HtmlDTD::tTd)
{
}


HDir::HDir()
    : HtmlElement(HtmlDTD::tDir)
{
}


HMenu::HMenu()
    : HtmlElement(HtmlDTD::tMenu)
{
}


HXmp::HXmp()
    : HtmlElement(HtmlDTD::tXmp)
{
}


HListing::HListing()
    : HtmlElement(HtmlDTD::tListing)
{
}


HPlainText::HPlainText()
    : HtmlElement(HtmlDTD::tPlaintext)
{
}


HNoscript::HNoscript()
    : HtmlElement(HtmlDTD::tNoscript)
{
}



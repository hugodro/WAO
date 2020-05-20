/**************************************************
* File: titleElements.h.
* Desc: Definition of the optimized version of the title elements of HTML 3.2.
* Module: WAO : SgmlParser.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "titleElements.h"

HStyle::HStyle()
    : HtmlElement(HtmlDTD::tStyle)
{
}

HScript::HScript()
    : HtmlElement(HtmlDTD::tScript)
{
}

HTitle::HTitle()
    : HtmlElement(HtmlDTD::tTitle)
{
}

HIsIndex::HIsIndex()
    : HtmlElement(HtmlDTD::tIsindex)
{
}

HBase::HBase()
    : HtmlElement(HtmlDTD::tBase)
{
}

HMeta::HMeta()
    : HtmlElement(HtmlDTD::tMeta)
{
}

HLink::HLink()
    : HtmlElement(HtmlDTD::tLink)
{
}

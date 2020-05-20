/**************************************************
* File: btextElements.cc.
* Desc: Implementation of the optimized version of the body text elements of HTML 3.2.
* Module: WAO : SgmlParser.
* Rev: 23 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "btextElements.h"


HTeleType::HTeleType()
    : HtmlElement(HtmlDTD::tTt)
{
}

HItalic::HItalic()
    : HtmlElement(HtmlDTD::tI)
{
}

HBold::HBold()
    : HtmlElement(HtmlDTD::tB)
{
}

HUnderscore::HUnderscore()
    : HtmlElement(HtmlDTD::tU)
{
}

HStrike::HStrike()
    : HtmlElement(HtmlDTD::tStrike)
{
}

HBig::HBig()
    : HtmlElement(HtmlDTD::tBig)
{
}

HSmall::HSmall()
    : HtmlElement(HtmlDTD::tSmall)
{
}

HSub::HSub()
    : HtmlElement(HtmlDTD::tSub)
{
}

HSup::HSup()
    : HtmlElement(HtmlDTD::tSup)
{
}

HEm::HEm()
    : HtmlElement(HtmlDTD::tEm)
{
}

HStrong::HStrong()
    : HtmlElement(HtmlDTD::tStrong)
{
}

HDfn::HDfn()
    : HtmlElement(HtmlDTD::tDfn)
{
}

HCode::HCode()
    : HtmlElement(HtmlDTD::tCode)
{
}

HSamp::HSamp()
    : HtmlElement(HtmlDTD::tSamp)
{
}

HKbd::HKbd()
    : HtmlElement(HtmlDTD::tKbd)
{
}

HVar::HVar()
    : HtmlElement(HtmlDTD::tVar)
{
}

HCite::HCite()
    : HtmlElement(HtmlDTD::tCite)
{
}

HAnchor::HAnchor()
    : HtmlElement(HtmlDTD::tA)
{
}

HImg::HImg()
    : HtmlElement(HtmlDTD::tImg)
{
}

HApplet::HApplet()
    : HtmlElement(HtmlDTD::tApplet)
{
}

HParam::HParam()
    : HtmlElement(HtmlDTD::tParam)
{
}

HFont::HFont()
    : HtmlElement(HtmlDTD::tFont)
{
}

HBaseFont::HBaseFont()
    : HtmlElement(HtmlDTD::tBasefont)
{
}

HMap::HMap()
    : HtmlElement(HtmlDTD::tMap)
{
}

HArea::HArea()
    : HtmlElement(HtmlDTD::tArea)
{
}

HBreak::HBreak()
    : HtmlElement(HtmlDTD::tBr)
{
}

/**************************************************
* File: btextElements.cc.
* Desc: Implementation of the optimized version of the body text elements of HTML 3.2.
* $Date$
* Rev: 23 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/11/30 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log$
**************************************************/

#include "btextElements.h"


xtnHTeleType::xtnHTeleType()
    : xtnHtmlElement(xtnHtmlDTD::tTt)
{
}


xtnHItalic::xtnHItalic()
    : xtnHtmlElement(xtnHtmlDTD::tI)
{
}


xtnHBold::xtnHBold()
    : xtnHtmlElement(xtnHtmlDTD::tB)
{
}


xtnHUnderscore::xtnHUnderscore()
    : xtnHtmlElement(xtnHtmlDTD::tU)
{
}


xtnHStrike::xtnHStrike()
    : xtnHtmlElement(xtnHtmlDTD::tStrike)
{
}


xtnHBig::xtnHBig()
    : xtnHtmlElement(xtnHtmlDTD::tBig)
{
}


xtnHSmall::xtnHSmall()
    : xtnHtmlElement(xtnHtmlDTD::tSmall)
{
}


xtnHSub::xtnHSub()
    : xtnHtmlElement(xtnHtmlDTD::tSub)
{
}


xtnHSup::xtnHSup()
    : xtnHtmlElement(xtnHtmlDTD::tSup)
{
}


xtnHEm::xtnHEm()
    : xtnHtmlElement(xtnHtmlDTD::tEm)
{
}

xtnHStrong::xtnHStrong()
    : xtnHtmlElement(xtnHtmlDTD::tStrong)
{
}


xtnHDfn::xtnHDfn()
    : xtnHtmlElement(xtnHtmlDTD::tDfn)
{
}


xtnHCode::xtnHCode()
    : xtnHtmlElement(xtnHtmlDTD::tCode)
{
}


xtnHSamp::xtnHSamp()
    : xtnHtmlElement(xtnHtmlDTD::tSamp)
{
}


xtnHKbd::xtnHKbd()
    : xtnHtmlElement(xtnHtmlDTD::tKbd)
{
}


xtnHVar::xtnHVar()
    : xtnHtmlElement(xtnHtmlDTD::tVar)
{
}


xtnHCite::xtnHCite()
    : xtnHtmlElement(xtnHtmlDTD::tCite)
{
}


xtnHAnchor::xtnHAnchor()
    : xtnHtmlElement(xtnHtmlDTD::tA)
{
}


xtnHImg::xtnHImg()
    : xtnHtmlElement(xtnHtmlDTD::tImg)
{
}


xtnHApplet::xtnHApplet()
    : xtnHtmlElement(xtnHtmlDTD::tApplet)
{
}


xtnHParam::xtnHParam()
    : xtnHtmlElement(xtnHtmlDTD::tParam)
{
}


xtnHFont::xtnHFont()
    : xtnHtmlElement(xtnHtmlDTD::tFont)
{
}


xtnHBaseFont::xtnHBaseFont()
    : xtnHtmlElement(xtnHtmlDTD::tBasefont)
{
}


xtnHMap::xtnHMap()
    : xtnHtmlElement(xtnHtmlDTD::tMap)
{
}


xtnHArea::xtnHArea()
    : xtnHtmlElement(xtnHtmlDTD::tArea)
{
}


xtnHBreak::xtnHBreak()
    : xtnHtmlElement(xtnHtmlDTD::tBr)
{
}

/**************************************************
* File: titleElements.h.
* Desc: Definition of the optimized version of the title elements of HTML 3.2.
* $Date$
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/11/30 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log$
**************************************************/

#include "titleElements.h"

xtnHStyle::xtnHStyle()
    : xtnHtmlElement(xtnHtmlDTD::tStyle)
{
}

xtnHScript::xtnHScript()
    : xtnHtmlElement(xtnHtmlDTD::tScript)
{
}

xtnHNoScript::xtnHNoScript()
    : xtnHtmlElement(xtnHtmlDTD::tNoScript)
{
}

xtnHTitle::xtnHTitle()
    : xtnHtmlElement(xtnHtmlDTD::tTitle)
{
}

xtnHIsIndex::xtnHIsIndex()
    : xtnHtmlElement(xtnHtmlDTD::tIsindex)
{
}

xtnHBase::xtnHBase()
    : xtnHtmlElement(xtnHtmlDTD::tBase)
{
}

xtnHMeta::xtnHMeta()
    : xtnHtmlElement(xtnHtmlDTD::tMeta)
{
}

xtnHLink::xtnHLink()
    : xtnHtmlElement(xtnHtmlDTD::tLink)
{
}


xtnHObject::xtnHObject()
    : xtnHtmlElement(xtnHtmlDTD::tObject)
{
}

xtnHEmbed::xtnHEmbed()
    : xtnHtmlElement(xtnHtmlDTD::tEmbed)
{
}


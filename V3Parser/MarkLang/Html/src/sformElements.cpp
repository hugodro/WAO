/**************************************************
* File: sformElements.h.
* Desc: Definition of the optimized version of the special form elements of HTML 3.2.
* $Date$
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/11/30 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log$
**************************************************/

#include "sformElements.h"


xtnHInput::xtnHInput()
    : xtnHtmlElement(xtnHtmlDTD::tInput)
{
}


xtnHSelect::xtnHSelect()
    : xtnHtmlElement(xtnHtmlDTD::tSelect)
{
}


xtnHTextArea::xtnHTextArea()
    : xtnHtmlElement(xtnHtmlDTD::tTextarea)
{
}

xtnHOption::xtnHOption()
    : xtnHtmlElement(xtnHtmlDTD::tOption)
{
}


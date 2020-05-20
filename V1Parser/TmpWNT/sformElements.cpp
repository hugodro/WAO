/**************************************************
* File: sformElements.h.
* Desc: Definition of the optimized version of the special form elements of HTML 3.2.
* Module: WAO : SgmlParser.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "sformElements.h"


HInput::HInput()
    : HtmlElement(HtmlDTD::tInput)
{
}


HSelect::HSelect()
    : HtmlElement(HtmlDTD::tSelect)
{
}


HTextArea::HTextArea()
    : HtmlElement(HtmlDTD::tTextarea)
{
}

HOption::HOption()
    : HtmlElement(HtmlDTD::tOption)
{
}


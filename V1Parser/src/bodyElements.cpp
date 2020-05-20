/**************************************************
* File: bodyElements.cc.
* Desc: Implementation of the optimized version of the body elements of HTML 3.2.
* Module: WAO : SgmlParser.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "bodyElements.h"


HHeading::HHeading(int anArg)
{
    level= (unsigned char)anArg;
    switch(anArg) {
	case 1: type= HtmlDTD::tH1; break;
	case 2: type= HtmlDTD::tH2; break;
	case 3: type= HtmlDTD::tH3; break;
	case 4: type= HtmlDTD::tH4; break;
	case 5: type= HtmlDTD::tH5; break;
	case 6: type= HtmlDTD::tH6; break;
	default: type= HtmlDTD::tH1; break;
    }
}


HAddress::HAddress()
    : HtmlElement(HtmlDTD::tAddress)
{
}


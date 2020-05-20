/**************************************************
* File: bodyElements.cc.
* Desc: Implementation of the optimized version of the body elements of HTML 3.2.
* $Date$
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* $Log$
**************************************************/

#include "bodyElements.h"


xtnHHeading::xtnHHeading(int anArg)
{
    level= (unsigned char)anArg;
    switch(anArg) {
	case 1: type= xtnHtmlDTD::tH1; break;
	case 2: type= xtnHtmlDTD::tH2; break;
	case 3: type= xtnHtmlDTD::tH3; break;
	case 4: type= xtnHtmlDTD::tH4; break;
	case 5: type= xtnHtmlDTD::tH5; break;
	case 6: type= xtnHtmlDTD::tH6; break;
	default: type= xtnHtmlDTD::tH1; break;
    }
}


xtnHAddress::xtnHAddress()
    : xtnHtmlElement(xtnHtmlDTD::tAddress)
{
}


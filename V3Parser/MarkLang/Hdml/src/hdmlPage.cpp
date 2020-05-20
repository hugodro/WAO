/*******************************************
* File: hdmlPage.cpp.
* Desc: Implementation of the xtnHdmlPage class.
* History: 2000/05/13 : REV 0 : [HD] : Creation.
******************************************/

#include "hdmlPage.h"


xtnHdmlPage::xtnHdmlPage()
  : xtnMLDoc()
{
}


xtnHdmlPage::xtnHdmlPage(char *someData, unsigned int length)
  : xtnMLDoc(someData, length)
{
}


unsigned int xtnHdmlPage::getClass(void)
{
    return 2;
}


/*******************************************
* File: wmlPage.cpp.
* Desc: Implementation of the xtnWmlPage class.
* History: 2000/04/04 : REV 0 : [HD] : Creation.
******************************************/

#include "wmlPage.h"

xtnWmlPage::xtnWmlPage(void)
  : xtnMLDoc()
{

}


xtnWmlPage::xtnWmlPage(char *someData, unsigned int length)
  : xtnMLDoc(someData, length)
{
}

unsigned int xtnWmlPage::getClass(void)
{
    return 3;
}


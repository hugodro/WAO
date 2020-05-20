/*******************************************
* File: htmlPage.cpp.
* Desc: Implementation of the xtnHtmlPage class.
* $Date$
* History: 2000/05/13 : REV 0 : [HD] : Creation.
* $Log$
******************************************/

#include "htmlPage.h"


xtnHtmlPage::xtnHtmlPage(void)
  : xtnMLDoc()
{

}


xtnHtmlPage::xtnHtmlPage(char *someData, unsigned int length)
  : xtnMLDoc(someData, length)
{
}


unsigned int xtnHtmlPage::getClass(void)
{
    return 4;
}


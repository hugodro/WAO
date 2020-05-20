/**************************************************
* File: htDoc.cc.
* Desc: Implementation of the HTML conforment document.
* $Date$
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/11/30 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log$
**************************************************/

// TMPTMP: DEBUG
#include <iostream>

#include <globDefs.h>

#include "container.h"
#include "htElementDef.h"
#include "htElements.h"
#include "nonStdElements.h"
#include "htDoc.h"

#define NO_PREDEF_ELEMENT

xtnHtmlDoc::xtnHtmlDoc(char *aName, xtnHtmlDTD *aDtd)
    : xtnCoreDoc(aName)
{
    docType= aDtd;

#if defined(NO_PREDEF_ELEMENT)
    container= NULL;
    head= NULL;
    body= NULL;
#else
    container= new xtnHHtml();
    head= new xtnHHead();
    body= new xtnHBody();
    container->linkAsChild(head);
    container->linkAsChild(body);
#endif
    state= initial;
    currentElement= container;
    rootElements= tailRootElements= 0;
}


void xtnHtmlDoc::treatComment(char *data)
{
    xtnHtmlElementDef *eleDef;
    xtnHtComment *docElement= new xtnHtComment(data);

    if (currentElement != NULL) {
	eleDef= (xtnHtmlElementDef *)currentElement->getDefinition();
	if (eleDef->canInclude(xtnHtmlDTD::tComment)) {
	    currentElement->linkAsChild(docElement);
	}
	else {
	    xtnHtmlElement *tmpEle= (xtnHtmlElement *)currentElement->getParent();
	    while (tmpEle != NULL) {
		eleDef= (xtnHtmlElementDef *)tmpEle->getDefinition();
		if (eleDef->canInclude(xtnHtmlDTD::tComment)) {
		    tmpEle->linkAsChild(docElement);
		    currentElement= tmpEle;
		    break;
		}
		tmpEle= (xtnHtmlElement *)tmpEle->getParent();
	    }
	    if (tmpEle == NULL) {
		// ATTN: Will have to signal an internal error.
	    }
	}
    }
    else {
	currentElement= docElement;
    }
}


int xtnHtmlDoc::pushElement(xtnHtmlDTD::HtmlTags anElement)
{
    xtnHtmlElementDef *eleDef;
    xtnHtmlElement *newEle;
    int result= 0;
    	// Errors: -1 -> out of sync element.

    if (currentElement != NULL) {
	eleDef= (xtnHtmlElementDef *)currentElement->getDefinition();
	if (eleDef->canInclude(anElement)) {
	    newEle= ((xtnHtmlDTD *)docType)->instanciateType(anElement);
	    currentElement->linkAsChild(newEle);
	    currentElement= newEle;
	}
	else if (eleDef->endType() != xtnSgmlElementDef::mandatory) {
	    xtnHtmlElement *tmpEle= (xtnHtmlElement *)currentElement->getParent();
	    while (tmpEle != container) {
		eleDef= (xtnHtmlElementDef *)tmpEle->getDefinition();
		if (eleDef->canInclude(anElement)) {
		    newEle= ((xtnHtmlDTD *)docType)->instanciateType(anElement);
		    tmpEle->linkAsChild(newEle);
		    currentElement= newEle;
		    break;
		}
		else if (eleDef->endType() == xtnSgmlElementDef::mandatory) {
		    result= -1;
		    break;
		}
		tmpEle= (xtnHtmlElement *)tmpEle->getParent();
	    }
	}
	else {
	    result= -1;
	}
    }
    else {
	currentElement= ((xtnHtmlDTD *)docType)->instanciateType(anElement);
    }
    return result;
}


int xtnHtmlDoc::addAttribute(char *attrName, bool assignFlag)
{
    xtnHtmlElementDef *eleDef;
    xtnCoreAttrDef *attrDef;
    xtnHtmlAttribute *newAttrib;
    int result= -1;	// Errors: -1 -> no current element.
				// 	-2: no such attribute.

    if (currentElement != NULL) {
	eleDef= (xtnHtmlElementDef *)currentElement->getDefinition();
	if ((attrDef= (xtnCoreAttrDef *)eleDef->getAttribute(attrName)) != NULL) {
	    newAttrib= new xtnHtmlAttribute(attrDef);
	    currentElement->addAttribute(newAttrib);
	    if (assignFlag) {
		if (attrDef->isAssignable()) {
		    currentElement->toBeAssigned();
		}
	    }
	    result= 0;
	}
	else {
	    result= -2;
	}
    }

    return result;
}


int xtnHtmlDoc::addValue(ValueType aType, char *aValue)
{
//    xtnHtmlElementDef *eleDef;
//    xtnCoreAttrDef *attrDef;
//    HtmlAttribute *newAttrib;
    int result= -1;	// Errors: -1 -> no current element.
				// 	-2: no assigment awaiting.
    char *tmpChar= aValue;

    while (*tmpChar != '\0') tmpChar++;
    if (tmpChar > aValue) {
	tmpChar--;
	while ((*tmpChar == '\n') || (*tmpChar == '\r') || (*tmpChar == ' ') || (*tmpChar == '\t')) {
	    tmpChar--;
	    if (tmpChar == aValue) break;
	}
	tmpChar++;
	*tmpChar= '\0';
    }

    if (currentElement != NULL) {
	if (currentElement->expectsAssignment()) {
	    currentElement->assignAttribute(aType, aValue);
	    result= 0;
	}
	else {
	    result= -2;
	}
    }

    return result;
}


int xtnHtmlDoc::addData(char *someData, unsigned int lineNbr)
{
  xtnHtmlElementDef *eleDef;
  xtnHtmlElement *newEle;
  int result= 0;	// Errors: -1 -> out of sync element.

  if (currentElement != NULL) {
    eleDef= (xtnHtmlElementDef *)currentElement->getDefinition();
    if (eleDef->getTag() == xtnHtmlDTD::tPcdata) {
      ((xtnHPcData *)currentElement)->mergeData(someData);
      currentElement->setEndPos(lineNbr);
    }
    else if (eleDef->canInclude(xtnHtmlDTD::tPcdata)) {
      newEle= ((xtnHtmlDTD *)docType)->instanciateType(xtnHtmlDTD::tPcdata);
      newEle->setStartPos(lineNbr);
      ((xtnHPcData *)newEle)->setData(someData);
      currentElement->linkAsChild(newEle);
      currentElement= newEle;
    }
    else if (eleDef->endType() != xtnSgmlElementDef::mandatory) {
      xtnHtmlElement *tmpEle= (xtnHtmlElement *)currentElement->getParent();
      while ((tmpEle != NULL) && (tmpEle != container)) {
        eleDef= (xtnHtmlElementDef *)tmpEle->getDefinition();
        if (eleDef->canInclude(xtnHtmlDTD::tPcdata)) {
          newEle= ((xtnHtmlDTD *)docType)->instanciateType(xtnHtmlDTD::tPcdata);
          ((xtnHPcData *)newEle)->setData(someData);
          tmpEle->linkAsChild(newEle);
          currentElement= newEle;
          break;
        }
        else if (eleDef->endType() == xtnSgmlElementDef::mandatory) {
          result= -1;
          break;
        }
        tmpEle= (xtnHtmlElement *)tmpEle->getParent();
      }
      if (tmpEle == NULL) {
        newEle= ((xtnHtmlDTD *)docType)->instanciateType(xtnHtmlDTD::tPcdata);
        newEle->setStartPos(lineNbr);
        ((xtnHPcData *)newEle)->setData(someData);
        currentElement->linkAsChild(newEle);
      }
	}
	else {
      result= -1;
	}
  }
  else {
	currentElement= ((xtnHtmlDTD *)docType)->instanciateType(xtnHtmlDTD::tPcdata);
    addRootElement(currentElement);
  }

  return result;
}


int xtnHtmlDoc::popElement(xtnHtmlDTD::HtmlTags anElement)
{
    xtnHtmlElementDef *eleDef;

    int result= -1;	// Errrors: -1 -> no element to pop.
				//	-2 -> element can not have an end tag.
				//	-3 -> trying to mid-pop an ele. with manda. end tag.
// ATTN: Must check if the close tag is ok with the stack.
    if (currentElement != NULL) {
	if (currentElement->getTag() == anElement) {
	    eleDef= (xtnHtmlElementDef *)currentElement->getDefinition();
	    if (eleDef->endType() == xtnSgmlElementDef::illegal) {
		result= -2;
	    }
	    else {
		currentElement= (xtnHtmlElement *)currentElement->getParent();
	    }
	}
	else {
	    xtnHtmlElement *tmpEle= currentElement;
	    while (tmpEle != container) {
		eleDef= (xtnHtmlElementDef *)tmpEle->getDefinition();
		if (tmpEle != currentElement) {
		    if (tmpEle->getTag() == anElement) {
			if (eleDef->endType() == xtnSgmlElementDef::illegal) {
			    result= -2;
			}
			else {
			    currentElement= (xtnHtmlElement *)tmpEle->getParent();
			}
			break;
		    }
		}
		if (eleDef->endType() == xtnSgmlElementDef::mandatory) {
		    result= -3;
		    break;
		}
		tmpEle= (xtnHtmlElement *)tmpEle->getParent();
	    }
	}
    }
    return result;
}


xtnHtmlDoc::State xtnHtmlDoc::getState(void)
{
    return state;
}


void xtnHtmlDoc::setState(State aState)
{
    state= aState;
    if (state == inHead) {
	container->linkAsChild(head);
	currentElement= head;
    }
    else if (state == inBody) {
	container->linkAsChild(body);
	currentElement= body;
    }
}


void xtnHtmlDoc::gotHeadStart(void)
{
    head->startTagged();
}


void xtnHtmlDoc::gotHeadEnd(void)
{
    head->endTagged();
}


void xtnHtmlDoc::gotBodyStart(void)
{
    body->startTagged();
}


void xtnHtmlDoc::gotBodyEnd(void)
{
    body->endTagged();
}


xtnHtmlElement *xtnHtmlDoc::getContainer(void)
{
    return container;
}


char *xtnHtmlDoc::getTitle(void)
{
    return head->getTitle();
}


xtnHBody *xtnHtmlDoc::getBody(void)
{
    return body;
}


int xtnHtmlDoc::startElement(xtnHtmlDTD::HtmlTags anElement, unsigned int linePos)
{
  xtnHtmlElement *nvoElement;
  int result= 0;

#if defined(NO_PREDEF_ELEMENT)
  nvoElement= ((xtnHtmlDTD *)docType)->instanciateType(anElement);
#else
  switch(anElement) {
    case xtnHtmlDTD::tHtml:
      currentElement= container;
      break;
    case xtnHtmlDTD::tHead:
      currentElement= head;
      state= inHead;
      break;
    case xtnHtmlDTD::tBody:
      currentElement= body;
      state= inBody;
      break;
    default:
      nvoElement= ((xtnHtmlDTD *)docType)->instanciateType(anElement);
  }
#endif

  nvoElement->setStartPos(linePos);

  if (currentElement != NULL) {
	if (currentElement->canInclude(anElement)) {
      currentElement->linkAsChild(nvoElement);
      currentElement= nvoElement;
	}
	else {
      xtnHtmlElement *cursor, *includer;
      cursor= (xtnHtmlElement *)currentElement->getParent();
      while (cursor != NULL) {
        if (cursor->canInclude(anElement)) break;
        cursor= (xtnHtmlElement *)cursor->getParent();
      }
      if (cursor != NULL) {
        includer= cursor;
        cursor= currentElement;
        while (cursor != includer) {
          if (!cursor->wrapUp()) {
            result= -2;
            break;
          }
          cursor= (xtnHtmlElement *)cursor->getParent();
        }
        if (result == 0) {
            includer->linkAsChild(nvoElement);
            currentElement= nvoElement;
        }
        else {
          // TODO: Notify that there was an element that could not perform the wrap-up.
          std::cerr << "@ERR [xtnHtmlDoc.startElement]: could not perform wrapup for current element.\n";
        }
      }
      else {
        // ATTN: Are we dealing with a root element or an out-of-sequence element.
        addRootElement(nvoElement);
        // result= -1;
      }
    }
  }
  else {
    addRootElement(nvoElement);
  }
  if (result < 0) {
    delete nvoElement;
  }
  else {
    if (nvoElement->getTag() == xtnHtmlDTD::tHtml) {
        if (container == NULL) container= (xtnHHtml *)nvoElement;
    }
    else if (nvoElement->getTag() == xtnHtmlDTD::tHead) {
        if (head == NULL) head= (xtnHHead *)nvoElement;
    }
    else if (nvoElement->getTag() == xtnHtmlDTD::tBody) {
        if (body == NULL) body= (xtnHBody *)nvoElement;
    }
  }
  return result;
}


int xtnHtmlDoc::endCurrentElement(unsigned int linePos)
{
  int result= 0;
  if (currentElement != NULL) {
    // TODO: Apply a check on the DTD to see if there is any mandatory element missing.
    currentElement= (xtnHtmlElement *)currentElement->getParent();
    currentElement->setEndPos(linePos);
    result= 0;
  }
  else
    result= -1;
  return result;
}


int xtnHtmlDoc::endElement(xtnHtmlDTD::HtmlTags anElement, unsigned int linePos)
{
  int result= 0;

  if (currentElement != NULL) {
    // TODO: Apply a check on the DTD to see if there is any mandatory element missing.
    xtnHtmlElement *cursor, *parent;
    bool boundaryError= false;

    cursor= currentElement;
    while (cursor != NULL) {
        if (cursor->getTag() == anElement) break;
        if (((xtnHtmlDTD *)docType)->hitBoundaryForEnding(cursor, anElement)) {
          boundaryError= true;
          break;
        }
        cursor= (xtnHtmlElement *)cursor->getParent();
    }
    if (boundaryError) {
      result= -4;
    }
    else if (cursor != NULL) {
      parent= (xtnHtmlElement *)cursor->getParent();
      cursor= currentElement;
      while (cursor != parent) {
        if (!cursor->wrapUp()) {
          cursor->setEndPos(linePos);
          result= -2;
          break;
        }
        cursor= (xtnHtmlElement *)cursor->getParent();
      }
      currentElement= parent;
      result= 0;
    }
    else {
        result= -3;
    }
  }
  else
  	result= -1;

    return result;
}


int xtnHtmlDoc::closeCurrentItem()
{
    // TODO-001130 [HD]: Apply the post-processing rules on the current element.
    return 0;
}


void xtnHtmlDoc::addRootElement(xtnHtmlElement *anElement)
{
    xtnHtEleContainer *nvoContainer= new xtnHtEleContainer(anElement, tailRootElements);
    if (rootElements == NULL) {
	rootElements= tailRootElements= nvoContainer;
    }
    tailRootElements= nvoContainer;
    currentElement= anElement;
}

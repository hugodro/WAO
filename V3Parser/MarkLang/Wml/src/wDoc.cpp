/**************************************************
* File: wDoc.cc.
* Desc: Implementation of the WML conforment document.
* $Date: 2000/09/20 03:37:34 $
* Rev: 19 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/08/23 : REV 1 : Hugo DesRosiers : Rewrote in Extenta context.
* $Log: wDoc.cpp,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
**************************************************/

#include <globDefs.h>

#include "container.h"
#include "wElementDef.h"
#include "wElements.h"
#include "wDoc.h"


xtnWmlDoc::xtnWmlDoc(char *aName, xtnWmlDTD *aDtd)
  : xtnCoreDoc(aName)
{
    docType= aDtd;
    state= initial;
    rootElements= tailRootElements= NULL;
    currentElement= NULL;
    headWml= NULL;
}


xtnWmlDoc::~xtnWmlDoc()
{
// TODO.
}


// This should be moved to the xtnCoreDoc level.
void xtnWmlDoc::treatComment(char *data)
{
    xtnWmlElementDef *definition;
    xtnWComment *comment;

    comment= new xtnWComment(data);
    if (currentElement != NULL) {
	if ((definition= (xtnWmlElementDef *)currentElement->getDefinition()) != NULL) {
	    if (definition->canInclude(xtnWmlDTD::tComment)) {
		currentElement->linkAsChild(comment);
	    }
	    else {
		xtnWmlElement *cursor, *tmpMark;
		tmpMark= currentElement;
		cursor= (xtnWmlElement *)currentElement->getParent();
		while (cursor != NULL) {
		    if ((definition= (xtnWmlElementDef *)cursor->getDefinition()) != NULL) {
			if (definition->canInclude(xtnWmlDTD::tComment)) {
			    cursor->linkAsChild(comment);
			    currentElement= cursor;
			    break;
			}
		    }
		    else {
		        // TODO-000124 [HD]: Deal with an element that has no definition.
		    }
		    cursor= (xtnWmlElement *)cursor->getParent();
		}
		if (cursor == NULL) {
		    // TODO-000124 [HD]: No container for the comment was found, signal the error.
		}
		else {
		    // Signal that all elements that have been jump during backtrace in parse tree have to
		    // be merged correctly into the new current element.
		    cursor= tmpMark;
		    while (cursor != currentElement) {
			cursor->endElement();
			cursor= (xtnWmlElement *)cursor->getParent();
		    }
		}
	    }
	}
	else {
	    // TODO-000124 [HD]: Deal with an element that has no definition.
	}
    }
    else {
	addRootElement(comment);
    }
	
}


int xtnWmlDoc::pushElement(xtnWmlDTD::WmlTags anElement)
{
    // Decripitated.
    return 0;
}


int xtnWmlDoc::addAttribute(char *attrName, bool assignFlag)
{
    xtnWmlElementDef *definition;
    xtnWmlAttrDef *attrDef;
    xtnWmlAttribute *newAttrib;
    int result= -1;

    // Error codes:
    // -1 => no current element.
    // -2 => no definition available for current element (internal error).
    // -3 => attribute unknown in the element definition.

    if (currentElement != NULL) {
	if ((definition= (xtnWmlElementDef *)currentElement->getDefinition()) != NULL) {
	    if ((attrDef= (xtnWmlAttrDef *)definition->getAttribute(attrName)) != NULL) {
		newAttrib= new xtnWmlAttribute(attrDef);
		currentElement->addAttribute(newAttrib);
		if (assignFlag) {
		    if (attrDef->isAssignable()) {
			currentElement->markExpectAssignment();
		    }
		}
		result= 0;    // All is fine.
	    }
	    else {
		// TODO: Signal that the attribute is unknown in the element definition.
		result= -3;
	    }
	}
	else {
	    // TODO: Signal that an element without definition is on the stack.
	    result= -2;
	}
    }

    return result;
}


int xtnWmlDoc::addValue(ValueType aType, char *aValue)
{
    int result= -1;
    char *tmpChar;

    // Error codes
    // -1 -> no current element.
    // -2: no assigment awaiting.

    // TODO-000124 [HD]: Implement value type and range checking.

    tmpChar= aValue;
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


int xtnWmlDoc::addData(char *someData)
{
    xtnWmlElementDef *definition;
    int result= 0;

    // Error codes:
    // -1 => no definition available for the current element (internal error).
    // -2 => element is refused from current sequence.

    if (currentElement != NULL) {
	if (currentElement->canInclude(xtnWmlDTD::tPcdata)) {
	    xtnWmlElement *newElement;

	    newElement= ((xtnWmlDTD *)docType)->instanciateType(xtnWmlDTD::tPcdata);
	    ((xtnWPcData *)newElement)->setData(someData);
	    currentElement->linkAsChild(newElement);
	    currentElement= newElement;
	}
	else {
	    // ATTN: Could a pcData cause a sequence fusion and backtrack into the tree ?
	    // TODO: Signal that pcData is refused from current element.
	    result= -2;
	}
    }
    else {
	currentElement= ((xtnWmlDTD *)docType)->instanciateType(xtnWmlDTD::tPcdata);
	addRootElement(currentElement);
    }
    return result;
}


int xtnWmlDoc::popElement(xtnWmlDTD::WmlTags anElement)
{
    // Depricated.
    return -1;
}


xtnWmlDoc::State xtnWmlDoc::getState()
{
    return state;
}


void xtnWmlDoc::setState(State aState)
{
    state= aState;
}


xtnWmlElement *xtnWmlDoc::getHead()
{
    return headWml;
}


int xtnWmlDoc::startElement(xtnWmlDTD::WmlTags anElement)
{
    xtnWmlElement *nvoElement;
    int result= 0;

    nvoElement= ((xtnWmlDTD *)docType)->instanciateType(anElement);
    if (currentElement != NULL) {
	if (currentElement->canInclude(anElement)) {
	    currentElement->linkAsChild(nvoElement);
	    currentElement= nvoElement;
	}
	else {
	    xtnWmlElement *cursor, *includer;
	    cursor= (xtnWmlElement *)currentElement->getParent();
	    while (cursor != NULL) {
		if (cursor->canInclude(anElement)) break;
		cursor= (xtnWmlElement *)cursor->getParent();
	    }
	    if (cursor != NULL) {
		includer= cursor;
		cursor= currentElement;
		while (cursor != includer) {
		    if (!cursor->wrapUp()) {
			result= -2;
			break;
		    }
		    cursor= (xtnWmlElement *)cursor->getParent();
		}
		if (result == 0) {
		    includer->linkAsChild(nvoElement);
		    currentElement= nvoElement;
		}
		else {
		    // TODO: Notify that there was an element that could not perform the wrap-up.
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
	if (nvoElement->getTag() == xtnWmlDTD::tWml) {
	    if (headWml == NULL) headWml= (xtnWWml *)nvoElement;
	}
    }
    return result;
}


int xtnWmlDoc::endCurrentElement()
{
    int result;
// TODO-000824 [HD]: Manage correctly the <element-name [...] /> closing sequence.
    if (currentElement != NULL) {
	// TODO: Apply a check on the DTD to see if there is any mandatory element missing.
	currentElement= (xtnWmlElement *)currentElement->getParent();
	result= 0;
    }
    else
	result= -1;

    return result;
}


/***************************************************
* Method: popElement.
* Args: 1- anElement => [xtnWmlDTD::WmlTags] the tag that is causing the pop.
* Return: 0 on success, or error:
*    -1 : no element to pop,
*    -2 : trying to mid-pop an element with mandatory end tag.
*    -3 : can't find the matching opened tab.
****************************************************/

int xtnWmlDoc::endElement(xtnWmlDTD::WmlTags anElement)
{
    int result;

    if (currentElement != NULL) {
	// TODO: Apply a check on the DTD to see if there is any mandatory element missing.

	xtnWmlElement *cursor, *parent;
	cursor= currentElement;
	while (cursor != NULL) {
	    if (cursor->getTag() == anElement) break;
	    cursor= (xtnWmlElement *)cursor->getParent();
	}
	if (cursor != NULL) {
	    parent= (xtnWmlElement *)cursor->getParent();
	    cursor= currentElement;
	    while (cursor != parent) {
		if (!cursor->wrapUp()) {
		    result= -2;
		    break;
		}
		cursor= (xtnWmlElement *)cursor->getParent();
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


int xtnWmlDoc::startCData(char *rawData)
{
    // TODO: check to make sure that the CData starts with a CDATA tag.
    return 0;
}


int xtnWmlDoc::endCData(char *rawData)
{
    // TODO: include all data into a container, and wrap up the sequence.
    return 0;
}


int xtnWmlDoc::closeCurrentItem()
{
    // TODO-000824 [HD]: Apply the post-processing rules on the current element.
    return 0;
}


void xtnWmlDoc::addRootElement(xtnWmlElement *anElement)
{
    xtnWEleContainer *nvoContainer= new xtnWEleContainer(anElement, tailRootElements);
    if (rootElements == NULL) {
	rootElements= tailRootElements= nvoContainer;
    }
    tailRootElements= nvoContainer;
    currentElement= anElement;
}

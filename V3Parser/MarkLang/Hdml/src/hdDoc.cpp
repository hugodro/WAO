/**************************************************
* File: hdDoc.cc.
* Desc: Implementation of the HDML conforment document.
* $Date: 2000/09/20 03:37:34 $
* Rev: 2000/09/03 : REV 0 : Hugo DesRosiers : Creation.
* $Log: hdDoc.cpp,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1  2000/09/05 07:13:40  hugo
* Initial entry of real parsing/generating HDML support.
*
**************************************************/

#include <globDefs.h>

#include "container.h"
#include "hdElementDef.h"
#include "allHdElements.h"
#include "hdDoc.h"


xtnHdmlDoc::xtnHdmlDoc(char *aName, xtnHdmlDTD *aDtd)
  : xtnCoreDoc(aName)
{
    docType= aDtd;
    state= initial;
    rootElements= tailRootElements= NULL;
    currentElement= NULL;
    headHdml= NULL;
}


xtnHdmlDoc::~xtnHdmlDoc()
{
// TODO.
}


// This should be moved to the xtnCoreDoc level.
void xtnHdmlDoc::treatComment(char *data)
{
    xtnHdmlElementDef *definition;
    xtnHdComment *comment;

    comment= new xtnHdComment(data);
    if (currentElement != NULL) {
	if ((definition= (xtnHdmlElementDef *)currentElement->getDefinition()) != NULL) {
	    if (definition->canInclude(xtnHdmlDTD::tComment)) {
		currentElement->linkAsChild(comment);
	    }
	    else {
		xtnHdmlElement *cursor, *tmpMark;
		tmpMark= currentElement;
		cursor= (xtnHdmlElement *)currentElement->getParent();
		while (cursor != NULL) {
		    if ((definition= (xtnHdmlElementDef *)cursor->getDefinition()) != NULL) {
			if (definition->canInclude(xtnHdmlDTD::tComment)) {
			    cursor->linkAsChild(comment);
			    currentElement= cursor;
			    break;
			}
		    }
		    else {
		        // TODO-000124 [HD]: Deal with an element that has no definition.
		    }
		    cursor= (xtnHdmlElement *)cursor->getParent();
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
			cursor= (xtnHdmlElement *)cursor->getParent();
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


int xtnHdmlDoc::pushElement(xtnHdmlDTD::HdmlTags anElement)
{
    // Decrepetated.
    return 0;
}


int xtnHdmlDoc::addAttribute(char *attrName, bool assignFlag)
{
    xtnHdmlElementDef *definition;
    xtnHdmlAttrDef *attrDef;
    xtnHdmlAttribute *newAttrib;
    int result= -1;

    // Error codes:
    // -1 => no current element.
    // -2 => no definition available for current element (internal error).
    // -3 => attribute unknown in the element definition.

    if (currentElement != NULL) {
	if ((definition= (xtnHdmlElementDef *)currentElement->getDefinition()) != NULL) {
	    if ((attrDef= (xtnHdmlAttrDef *)definition->getAttribute(attrName)) != NULL) {
		newAttrib= new xtnHdmlAttribute(attrDef);
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


int xtnHdmlDoc::addValue(ValueType aType, char *aValue)
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


int xtnHdmlDoc::addData(char *someData)
{
    xtnHdmlElementDef *definition;
    int result= 0;

    // Error codes:
    // -1 => no definition available for the current element (internal error).
    // -2 => element is refused from current sequence.

    if (currentElement != NULL) {
	if (currentElement->canInclude(xtnHdmlDTD::tPcdata)) {
	    xtnHdmlElement *newElement;

	    newElement= ((xtnHdmlDTD *)docType)->instanciateType(xtnHdmlDTD::tPcdata);
	    ((xtnHdPcData *)newElement)->setData(someData);
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
	currentElement= ((xtnHdmlDTD *)docType)->instanciateType(xtnHdmlDTD::tPcdata);
	addRootElement(currentElement);
    }
    return result;
}


int xtnHdmlDoc::popElement(xtnHdmlDTD::HdmlTags anElement)
{
    // Depricated.
    return -1;
}


xtnHdmlDoc::State xtnHdmlDoc::getState()
{
    return state;
}


void xtnHdmlDoc::setState(State aState)
{
    state= aState;
}


xtnHdmlElement *xtnHdmlDoc::getHead()
{
    return headHdml;
}


int xtnHdmlDoc::startElement(xtnHdmlDTD::HdmlTags anElement)
{
    xtnHdmlElement *nvoElement;
    int result= 0;

    nvoElement= ((xtnHdmlDTD *)docType)->instanciateType(anElement);
    if (currentElement != NULL) {
	if (currentElement->canInclude(anElement)) {
	    currentElement->linkAsChild(nvoElement);
	    currentElement= nvoElement;
	}
	else {
	    xtnHdmlElement *cursor, *includer;
	    cursor= (xtnHdmlElement *)currentElement->getParent();
	    while (cursor != NULL) {
		if (cursor->canInclude(anElement)) break;
		cursor= (xtnHdmlElement *)cursor->getParent();
	    }
	    if (cursor != NULL) {
		includer= cursor;
		cursor= currentElement;
		while (cursor != includer) {
		    if (!cursor->wrapUp()) {
			result= -2;
			break;
		    }
		    cursor= (xtnHdmlElement *)cursor->getParent();
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
	if (nvoElement->getTag() == xtnHdmlDTD::tDeck) {
	    if (headHdml == NULL) headHdml= (xtnHdDeck *)nvoElement;
	}
    }
    return result;
}


int xtnHdmlDoc::endCurrentElement()
{
    int result;

    if (currentElement != NULL) {
	// TODO: Apply a check on the DTD to see if there is any mandatory element missing.
	currentElement= (xtnHdmlElement *)currentElement->getParent();
	result= 0;
    }
    else
	result= -1;

    return result;
}


/***************************************************
* Method: popElement.
* Args: 1- anElement => [xtnHdmlDTD::HdmlTags] the tag that is causing the pop.
* Return: 0 on success, or error:
*    -1 : no element to pop,
*    -2 : trying to mid-pop an element with mandatory end tag.
*    -3 : can't find the matching opened tab.
****************************************************/

int xtnHdmlDoc::endElement(xtnHdmlDTD::HdmlTags anElement)
{
    int result;

    if (currentElement != NULL) {
	// TODO: Apply a check on the DTD to see if there is any mandatory element missing.

	xtnHdmlElement *cursor, *parent;
	cursor= currentElement;
	while (cursor != NULL) {
	    if (cursor->getTag() == anElement) break;
	    cursor= (xtnHdmlElement *)cursor->getParent();
	}
	if (cursor != NULL) {
	    parent= (xtnHdmlElement *)cursor->getParent();
	    cursor= currentElement;
	    while (cursor != parent) {
		if (!cursor->wrapUp()) {
		    result= -2;
		    break;
		}
		cursor= (xtnHdmlElement *)cursor->getParent();
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


int xtnHdmlDoc::startCData(char *rawData)
{
    // TODO: check to make sure that the CData starts with a CDATA tag.
    return 0;
}


int xtnHdmlDoc::endCData(char *rawData)
{
    // TODO: include all data into a container, and wrap up the sequence.
    return 0;
}


int xtnHdmlDoc::closeCurrentItem()
{
    // TODO-000824 [HD]: Apply the post-processing rules on the current element.
    return 0;
}


void xtnHdmlDoc::addRootElement(xtnHdmlElement *anElement)
{
    xtnHdEleContainer *nvoContainer= new xtnHdEleContainer(anElement, tailRootElements);
    if (rootElements == NULL) {
	rootElements= tailRootElements= nvoContainer;
    }
    tailRootElements= nvoContainer;
    currentElement= anElement;
}

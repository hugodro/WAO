/**************************************************
* File: wmlDoc.cc.
* Desc: Implementation of the WML conforment document.
* Module: WAO : SgmlParser.
* Rev: 19 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "container.h"
#include "wElementDef.h"
#include "wElements.h"
#include "wmlDoc.h"


WmlDoc::WmlDoc(char *aName, WmlDTD *aDtd)
    : SgmlDoc(aName)
{
    docType= aDtd;
    state= initial;
    rootElements= tailRootElements= NULL;
    currentElement= NULL;
}


// This should be moved to the SgmlDoc level.
void WmlDoc::treatComment(char *data)
{
    WmlElementDef *definition;
    WComment *comment;

    comment= new WComment(data);
    if (currentElement != NULL) {
	if ((definition= (WmlElementDef *)currentElement->getDefinition()) != NULL) {
	    if (definition->canInclude(WmlDTD::tComment)) {
		currentElement->linkAsChild(comment);
	    }
	    else {
		WmlElement *cursor, *tmpMark;
		tmpMark= currentElement;
		cursor= (WmlElement *)currentElement->getParent();
		while (cursor != NULL) {
		    if ((definition= (WmlElementDef *)cursor->getDefinition()) != NULL) {
			if (definition->canInclude(WmlDTD::tComment)) {
			    cursor->linkAsChild(comment);
			    currentElement= cursor;
			    break;
			}
		    }
		    else {
		        // TODO-000124 [HD]: Deal with an element that has no definition.
		    }
		    cursor= (WmlElement *)cursor->getParent();
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
			cursor= (WmlElement *)cursor->getParent();
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


int WmlDoc::pushElement(WmlDTD::WmlTags anElement)
{
    // TODO.
    return 0;
}


int WmlDoc::addAttribute(char *attrName, boolean assignFlag)
{
    WmlElementDef *definition;
    WmlAttrDef *attrDef;
    WmlAttribute *newAttrib;
    int result= -1;

    // Error codes:
    // -1 => no current element.
    // -2 => no definition available for current element (internal error).
    // -3 => attribute unknown in the element definition.

    if (currentElement != NULL) {
	if ((definition= (WmlElementDef *)currentElement->getDefinition()) != NULL) {
	    if ((attrDef= (WmlAttrDef *)definition->getAttribute(attrName)) != NULL) {
		newAttrib= new WmlAttribute(attrDef);
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


int WmlDoc::addValue(ValueType aType, char *aValue)
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


int WmlDoc::addData(char *someData)
{
    WmlElementDef *definition;
    int result= 0;

    // Error codes:
    // -1 => no definition available for the current element (internal error).
    // -2 => element is refused from current sequence.

    if (currentElement != NULL) {
	if ((definition= (WmlElementDef *)currentElement->getDefinition()) != NULL) {
	    if (definition->canInclude(WmlDTD::tPcdata)) {
		WmlElement *newElement;

		newElement= ((WmlDTD *)docType)->instanciateType(WmlDTD::tPcdata);
		((WPcData *)newElement)->setData(someData);
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
	    // TODO: Signal that the current element does not have a definition.
	    result= -1;
	}
    }
    else {
	currentElement= ((WmlDTD *)docType)->instanciateType(WmlDTD::tPcdata);
    }
    return result;
}


int WmlDoc::popElement(WmlDTD::WmlTags anElement)
{
    // TODO.
    return 0;
}


WmlDoc::State WmlDoc::getState(void)
{
    return state;
}


void WmlDoc::setState(State aState)
{
    state= aState;
}


void WmlDoc::gotHeadStart(void)
{
}


void WmlDoc::gotHeadEnd(void)
{

}


void WmlDoc::gotBodyStart(void)
{

}


void WmlDoc::gotBodyEnd(void)
{

}


WmlElement *WmlDoc::getContainer(void)
{
    return container;
}


int WmlDoc::startElement(WmlDTD::WmlTags anElement)
{
    WmlElement *nvoElement;
    int result= 0;

    nvoElement= ((WmlDTD *)docType)->instanciateType(anElement);
    if (currentElement != NULL) {
	if (currentElement->canInclude(anElement)) {
	    currentElement->linkAsChild(nvoElement);
	    currentElement= nvoElement;
	}
	else {
	    WmlElement *cursor, *includer;
	    cursor= (WmlElement *)currentElement->getParent();
	    while (cursor != NULL) {
		if (cursor->canInclude(anElement)) break;
		cursor= (WmlElement *)cursor->getParent();
	    }
	    if (cursor != NULL) {
		includer= cursor;
		cursor= currentElement;
		while (cursor != includer) {
		    if (!cursor->wrapUp()) {
			result= -2;
			break;
		    }
		    cursor= (WmlElement *)cursor->getParent();
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
		result= -1;
	    }
	    
	}
    }
    else {
	
	addRootElement(nvoElement);
    }
    if (result < 0) {
	delete nvoElement;
    }
    return result;
}


int WmlDoc::endCurrentElement(void)
{
    // TODO: end the existance of the current element.
    return 0;
}


int WmlDoc::endElement(WmlDTD::WmlTags anElement)
{
    // TODO: wrap up the sequence up to the element of type anElement.
    return 0;
}


int WmlDoc::startCData(char *rawData)
{
    // TODO: check to make sure that the CData starts with a CDATA tag.
    return 0;
}


int WmlDoc::endCData(char *rawData)
{
    // TODO: include all data into a container, and wrap up the sequence.
    return 0;
}


int WmlDoc::closeCurrentItem(void)
{
    // TODO: do any post-processing on the current element, since the parser just found the
    // closing token for it.
    return 0;
}


void WmlDoc::addRootElement(WmlElement *anElement)
{
    WEleContainer *nvoContainer= new WEleContainer(anElement, tailRootElements);
    if (rootElements == NULL) {
	rootElements= tailRootElements= nvoContainer;
    }
    tailRootElements= nvoContainer;
    currentElement= anElement;
}

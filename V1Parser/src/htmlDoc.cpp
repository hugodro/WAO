/**************************************************
* File: htmlDoc.cc.
* Desc: Implementation of the HTML conforment document.
* Module: WAO : SgmlParser.
* Rev: 20 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "htElementDef.h"
#include "htElements.h"
#include "nonStdElements.h"
#include "htmlDoc.h"

HtmlDoc::HtmlDoc(char *aName, HtmlDTD *aDtd)
    : SgmlDoc(aName)
{
    docType= aDtd;
    container= new HHtml();
    head= new HHead();
    body= new HBody();
    state= initial;
    currentElement= container;
}


void HtmlDoc::treatComment(char *data)
{
    HtmlElementDef *eleDef;
    CommentElement *docElement= new CommentElement(data);

    if (currentElement != NULL) {
	eleDef= (HtmlElementDef *)currentElement->getDefinition();
	if (eleDef->canInclude(HtmlDTD::tComment)) {
	    currentElement->linkAsChild(docElement);
	}
	else {
	    HtmlElement *tmpEle= (HtmlElement *)currentElement->getParent();
	    while (tmpEle != NULL) {
		eleDef= (HtmlElementDef *)tmpEle->getDefinition();
		if (eleDef->canInclude(HtmlDTD::tComment)) {
		    tmpEle->linkAsChild(docElement);
		    currentElement= tmpEle;
		    break;
		}
		tmpEle= (HtmlElement *)tmpEle->getParent();
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


int HtmlDoc::pushElement(HtmlDTD::HtmlTags anElement)
{
    HtmlElementDef *eleDef;
    HtmlElement *newEle;
    int result= 0;
    	// Errors: -1 -> out of sync element.

    if (currentElement != NULL) {
	eleDef= (HtmlElementDef *)currentElement->getDefinition();
	if (eleDef->canInclude(anElement)) {
	    newEle= ((HtmlDTD *)docType)->instanciateType(anElement);
	    currentElement->linkAsChild(newEle);
	    currentElement= newEle;
	}
	else if (eleDef->endType() != SgmlElementDef::mandatory) {
	    HtmlElement *tmpEle= (HtmlElement *)currentElement->getParent();
	    while (tmpEle != container) {
		eleDef= (HtmlElementDef *)tmpEle->getDefinition();
		if (eleDef->canInclude(anElement)) {
		    newEle= ((HtmlDTD *)docType)->instanciateType(anElement);
		    tmpEle->linkAsChild(newEle);
		    currentElement= newEle;
		    break;
		}
		else if (eleDef->endType() == SgmlElementDef::mandatory) {
		    result= -1;
		    break;
		}
		tmpEle= (HtmlElement *)tmpEle->getParent();
	    }
	}
	else {
	    result= -1;
	}
    }
    else {
	currentElement= ((HtmlDTD *)docType)->instanciateType(anElement);
    }
    return result;
}


int HtmlDoc::addAttribute(char *attrName, boolean assignFlag)
{
    HtmlElementDef *eleDef;
    HtmlAttrDef *attrDef;
    HtmlAttribute *newAttrib;
    int result= -1;	// Errors: -1 -> no current element.
				// 	-2: no such attribute.

    if (currentElement != NULL) {
	eleDef= (HtmlElementDef *)currentElement->getDefinition();
	if ((attrDef= (HtmlAttrDef *)eleDef->getAttribute(attrName)) != NULL) {
	    newAttrib= new HtmlAttribute(attrDef);
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


int HtmlDoc::addValue(ValueType aType, char *aValue)
{
//    HtmlElementDef *eleDef;
//    HtmlAttrDef *attrDef;
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


int HtmlDoc::addData(char *someData)
{
    HtmlElementDef *eleDef;
    HtmlElement *newEle;
    int result= 0;	// Errors: -1 -> out of sync element.

    if (currentElement != NULL) {
	eleDef= (HtmlElementDef *)currentElement->getDefinition();
	if (eleDef->canInclude(HtmlDTD::tPcdata)) {
	    newEle= ((HtmlDTD *)docType)->instanciateType(HtmlDTD::tPcdata);
	    ((HPcData *)newEle)->setData(someData);
	    currentElement->linkAsChild(newEle);
	    currentElement= newEle;
	}
	else if (eleDef->endType() != SgmlElementDef::mandatory) {
	    HtmlElement *tmpEle= (HtmlElement *)currentElement->getParent();
	    while (tmpEle != container) {
		eleDef= (HtmlElementDef *)tmpEle->getDefinition();
		if (eleDef->canInclude(HtmlDTD::tPcdata)) {
		    newEle= ((HtmlDTD *)docType)->instanciateType(HtmlDTD::tPcdata);
		    ((HPcData *)newEle)->setData(someData);
		    tmpEle->linkAsChild(newEle);
		    currentElement= newEle;
		    break;
		}
		else if (eleDef->endType() == SgmlElementDef::mandatory) {
		    result= -1;
		    break;
		}
		tmpEle= (HtmlElement *)tmpEle->getParent();
	    }
	}
	else {
	    result= -1;
	}
    }
    else {
	currentElement= ((HtmlDTD *)docType)->instanciateType(HtmlDTD::tPcdata);
    }

    return result;
}


int HtmlDoc::popElement(HtmlDTD::HtmlTags anElement)
{
    HtmlElementDef *eleDef;

    int result= -1;	// Errrors: -1 -> no element to pop.
				//	-2 -> element can not have an end tag.
				//	-3 -> trying to mid-pop an ele. with manda. end tag.
// ATTN: Must check if the close tag is ok with the stack.
    if (currentElement != NULL) {
	if (currentElement->getTag() == anElement) {
	    eleDef= (HtmlElementDef *)currentElement->getDefinition();
	    if (eleDef->endType() == SgmlElementDef::illegal) {
		result= -2;
	    }
	    else {
		currentElement= (HtmlElement *)currentElement->getParent();
	    }
	}
	else {
	    HtmlElement *tmpEle= currentElement;
	    while (tmpEle != container) {
		eleDef= (HtmlElementDef *)tmpEle->getDefinition();
		if (tmpEle != currentElement) {
		    if (tmpEle->getTag() == anElement) {
			if (eleDef->endType() == SgmlElementDef::illegal) {
			    result= -2;
			}
			else {
			    currentElement= (HtmlElement *)tmpEle->getParent();
			}
			break;
		    }
		}
		if (eleDef->endType() == SgmlElementDef::mandatory) {
		    result= -3;
		    break;
		}
		tmpEle= (HtmlElement *)tmpEle->getParent();
	    }
	}
    }
    return result;
}


HtmlDoc::State HtmlDoc::getState(void)
{
    return state;
}


void HtmlDoc::setState(State aState)
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


void HtmlDoc::gotHeadStart(void)
{
    head->startTagged();
}


void HtmlDoc::gotHeadEnd(void)
{
    head->endTagged();
}


void HtmlDoc::gotBodyStart(void)
{
    body->startTagged();
}


void HtmlDoc::gotBodyEnd(void)
{
    body->endTagged();
}


HtmlElement *HtmlDoc::getContainer(void)
{
    return container;
}


char *HtmlDoc::getTitle(void)
{
    return head->getTitle();
}


HBody *HtmlDoc::getBody(void)
{
    return body;
}


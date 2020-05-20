/**************************************************
* File: jstRender.cc.
* Desc: Definition of the Html-to-Jst instance archives engine.
* Module: WAO : SgmlParser.
* Rev: 10 septembre 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <ctype.h>
#if defined(_WIN32)
#include <string.h>
#endif
#include <stdio.h>

#include <fstream>

#include <jst/fileArchiver.h>
#include <vm/jmachine.h>
#include <vm/poolManager.h>
#include <vm/jvcup.h>
#include <vm/jvInstance.h>
#include <vm/stacks.h>
#include <vm/machineSupport.h>
#include "htmlElement.h"
#include "htmlDoc.h"
#include "elementList.h"
#include "nonStdElements.h"
#include "topElements.h"
#include "sgElementDef.h"
#include "jstRender.h"

/**************************************************
* Implementation: InstanceContainer.
**************************************************/

InstanceContainer::InstanceContainer(JVInstance *anInstance, InstanceContainer *parent)
{
    previous= parent;
    instance= anInstance;
    currentIndex= 0;
}


/**************************************************
* Implementation: JstRenderer.
**************************************************/

char *JstRenderer::htmlClassNames[HtmlDTD::numOfElements+4]= {
	"HAnchor", "HAddress", "HApplet", "HArea",
	"HBase", "HBaseFont", "HBlockQuote", "HBody", "HBreak", "HBold", "HBig",
	"HCaption", "HCenter", "HCite", "HCode",
	"HDfn", "HDir", "HDiv", "HDefList", "HDefDef", "HDefTerm",
	"HEm",
	"HFont", "HForm",
	"HHeading", "HHeading", "HHeading", "HHeading", "HHeading", "HHeading", "HHead", "HHr", "HHtml",
	"HItalic", "HImg", "HInput", "HIsIndex",
	"HKbd",
	"HLink", "HLiElement", "HListing",
	"HMap", "HMenu", "HMeta",
	"HOption", "HOList",
	"HPara", "HParam", "HPlainText", "HPre",
	"HStrike", "HSamp", "HScript", "HSelect", "HSmall", "HSpan", "HStrike", "HStrong", "HStyle", "HSub", "HSup",
	"HTable", "HTableData", "HTextArea", "HTableHeader", "HTitle", "HTableRow", "HTableType",
	"HUnderscore", "HUList",
	"HVar",
	"HXmp",
	"HPcData", "HCdata"
	, "error"
	, "error", "error", "HComment"
};
ClassFile *JstRenderer::htmlClasses[HtmlDTD::numOfElements+4]= { NULL };
ClassFile *JstRenderer::attributeClass;
ClassFile *JstRenderer::stringClass;
ClassFile *JstRenderer::baseElementClass;
JVVariable *JstRenderer:: subElementsField;
JVVariable *JstRenderer:: attributesField;
JVVariable *JstRenderer:: attrNameField;
JVVariable *JstRenderer:: attrValueField;
JVVariable *JstRenderer:: pcDataValueField;
JVVariable *JstRenderer:: commentValueField;


void JstRenderer::initHtmlClasses(JVCup *anEngine)
{
    char className[80];
    JVMachine *machine;

    strcpy(className, "wao/html/");

	// Load all HTML 3.2 official elements.
    for (unsigned int i= 0; i < HtmlDTD::numOfElements; i++) {
	strcpy(className + 9, htmlClassNames[i]);
	htmlClasses[i]= anEngine->loadClass(className);
    }
    htmlClasses[HtmlDTD::numOfElements]= NULL;
    htmlClasses[HtmlDTD::numOfElements+1]= NULL;
    htmlClasses[HtmlDTD::numOfElements+2]= NULL;
    strcpy(className + 9, htmlClassNames[HtmlDTD::tComment]);
    htmlClasses[HtmlDTD::tComment]= anEngine->loadClass(className);

	// Load additional useful classes.
    attributeClass= anEngine->loadClass("wao/html/HtmlAttribute");
    stringClass= anEngine->loadClass("java/lang/String");
    baseElementClass= anEngine->loadClass("wao/html/HtmlElement");

	// Get fast access to the fields used in the classes.
    machine= anEngine->getDefaultMachine();
    subElementsField= machine->getFieldOfClass(baseElementClass, "subElements");
    attributesField= machine->getFieldOfClass(baseElementClass, "attributes");
    attrNameField= machine->getFieldOfClass(attributeClass, "name");
    attrValueField= machine->getFieldOfClass(attributeClass, "value");
    pcDataValueField= machine->getFieldOfClass(htmlClasses[HtmlDTD::tPcdata], "value");
    commentValueField= machine->getFieldOfClass(htmlClasses[HtmlDTD::tComment], "value");
}


JstRenderer::JstRenderer(char *aName)
{
    rootInstance= NULL;
    outputName= aName;
    stack= NULL;
}


JstRenderer::~JstRenderer(void)
{
    if (stack != NULL) delete stack;
}


bool JstRenderer::initialize(JVCup *anEngine)
{
    machine= anEngine->getDefaultMachine();

    if (htmlClasses[0] == NULL) {
	initHtmlClasses(anEngine);
	if (htmlClasses[0] == NULL) return false;
    }

    archiver= new JstFileArchiver(outputName, machine);
    return archiver->startSession();
}


void JstRenderer::renderDoc(SgmlDoc *aDoc)
{
    HtmlDoc *theDoc= (HtmlDoc *)aDoc;		// Get rid of casting.
    HtmlElement *rootElement;
    unsigned int i, j;

    rootElement= theDoc->getContainer();
    render(rootElement);

	// Serialize the object tree.
    archiver->archive(rootInstance);
    archiver->endSession();
}


void JstRenderer::renderStartOf(SgmlElement *anElement)
{
    SgmlElementList *subElements;
    SgmlAttributeList *attributes;
    JVInstance *mainInstance, *anInstance, *jString;
    JVInstanceArray *array;
    ClassFile *theClass;
    unsigned int nameLength;


    if ((theClass= htmlClasses[((HtmlElement *)anElement)->getTag()]) == NULL) {
	std::cout << "ERRMSG: Can't find class for element type id " << ((HtmlElement *)anElement)->getTag() << ".\n";
	return;
    }

    mainInstance= machine->createObject(theClass);
    if (rootInstance == NULL) rootInstance= mainInstance;

    if ((((HtmlElement *)anElement)->getTag()) == HtmlDTD::tPcdata) {
	jString= machine->createStringFromNarrowArray(((HPcData *)anElement)->getData());
	JVRunValue tmpValue(TYPE_INSTANCE, jString);
	mainInstance->putField(tmpValue, pcDataValueField);
    }
    else if ((((HtmlElement *)anElement)->getTag()) == HtmlDTD::tComment) {
	jString= machine->createStringFromNarrowArray(((CommentElement *)anElement)->getData());
	JVRunValue tmpValue(TYPE_INSTANCE, jString);
	mainInstance->putField(tmpValue, commentValueField);
    }


    if ((attributes= anElement->getAttributes()) != NULL) {
	HtmlAttribute *attrib;
	unsigned int i, attrCount= attributes->count();

	array= machine->getPoolManager()->getInstanceArray(attributeClass, attrCount);
	JVRunValue tmpValue(TYPE_ARRAY, array);
	mainInstance->putField(tmpValue, subElementsField);

	for (i= 0; i < attrCount; i++) {
	    attrib= (HtmlAttribute *)attributes->objectAt(i);
	    jString= machine->createStringFromNarrowArray(attrib->getName());
	    anInstance= machine->createObject(attributeClass);

	    JVRunValue tmpValue(TYPE_INSTANCE, jString);
	    anInstance->putField(tmpValue, attrNameField);

	    if (attrib->getDefinition()->isAssignable()) {
		jString= machine->createStringFromNarrowArray(attrib->getValue());
		tmpValue.setValue(jString);
		anInstance->putField(tmpValue, attrValueField);
	    }
	    array->setElement(i, anInstance);
	}
    }

    if ((subElements= anElement->getSubElements()) != NULL) {
	array= machine->getPoolManager()->getInstanceArray(baseElementClass, subElements->count());
	JVRunValue tmpValue(TYPE_ARRAY, array);
	mainInstance->putField(tmpValue, subElementsField);
    }

    if (anElement->getParent() != NULL) {
	JVInstanceArray *parentArray;
	parentArray= (JVInstanceArray *)stack->instance->getField(subElementsField);
	parentArray->setElement(stack->currentIndex++, mainInstance);
    }

    stack= new InstanceContainer(mainInstance, stack);
}


void JstRenderer::renderEndOf(SgmlElement *anElement)
{
    InstanceContainer *tmpInstance= stack;
    stack= stack->previous;
    delete tmpInstance;
}



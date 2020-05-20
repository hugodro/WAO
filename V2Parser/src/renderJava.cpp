/**************************************************
* File: renderJava.cc.
* Desc: Implementation of the Html-to-Java spit engine.
* Module: WAO : SgmlParser.
* Rev: 24 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <ctype.h>
#if defined(_WIN32)
#include <string.h>
#endif

#include <fstream>

#include <stdio.h>
#include "htmlElement.h"
#include "htmlDoc.h"
#include "elementList.h"
#include "nonStdElements.h"
#include "topElements.h"
#include "sgElementDef.h"
#include "renderJava.h"

/**************************************************
* Implementation: NameContainer.
**************************************************/

NameContainer::NameContainer(char *aName, NameContainer *parent)
{
    name= new char[strlen(aName)+1];
    strcpy(name, aName);
    previous= parent;
    index= 0;
}

NameContainer::~NameContainer(void)
{
    delete[] name;
}


/**************************************************
* Implementation: JavaRenderer.
**************************************************/

char *JavaRenderer::elementClassName[HtmlDTD::numOfElements+4]= {
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


JavaRenderer::JavaRenderer(char *aName, std::ostream *output)
{
    outStream= output;
    outputName= aName;
    nameStack= NULL;
    for (unsigned int i= 0; i < HtmlDTD::numOfElements+4; i++) usage[i]= 0;
    scratchPad= new char[512];
}


JavaRenderer::~JavaRenderer(void)
{
    delete outStream;
    delete[] scratchPad;
}


void JavaRenderer::renderDoc(SgmlDoc *aDoc)
{
    HtmlDoc *theDoc= (HtmlDoc *)aDoc;		// Get rid of casting.
    HtmlElement *rootElement;
    unsigned int i, j;

    *outStream << "/**************************************************\n";
    *outStream << " File: " <<  outputName << ".\n";
    *outStream << " Desc: Automatic translation of HTML file " << theDoc->getSourceName() << ".\n";
    *outStream << " Date Translated: " << theDoc->getDateParsed() << ".\n";
    *outStream << "**************************************************/\n\n\n";

    strcpy(scratchPad, theDoc->getSourceName());
    j= strlen(scratchPad);
    for (i= 0; i < j; i++) {
	if (scratchPad[i] == '/') scratchPad[i]= '_';
	if (scratchPad[i] == '.') {
	    if (strcmp(&scratchPad[i+1], "html") == 0) {
		scratchPad[i]= '\0';
		break;
	    }
	    else {
		scratchPad[i]= '_';
	    }
	}
    }

    *outStream << "import wao.server.OutputStream;\nimport wao.html.*;\n\n\n";

    *outStream << "public class makeDoc_" << scratchPad << " extends HtmlDocCreation {\n";

    *outStream << "\n    static public void main() {\n";
    *outStream << "\tHtmlDocCreation aTest= new makeDoc_" << scratchPad << "();\n";
    *outStream << "\tOutputStream aStream= new OutputStream();\n";
    *outStream << "\taTest.spitDoc(aStream);\n    }\n\n";

    *outStream << "    public boolean createIt()\n    {\n";
    *outStream << "\ttheDoc= new HtmlDoc(\"" << theDoc->getDocType()->getName() << "\");\n";

    rootElement= theDoc->getContainer();
    render(rootElement);
    
    *outStream << "\trootElement= html_0;\n";
    *outStream << "//\ttheDoc.serialize(args[args.length-1]);\n";
    *outStream << "return true;\n    }\n}\n";
}


void JavaRenderer::renderStartOf(SgmlElement *anElement)
{
    SgmlElementList *subElements;
    SgmlAttributeList *attributes;
    unsigned int nameLength;

    strcpy(scratchPad, elementClassName[((HtmlElement *)anElement)->getTag()]+1);
    nameLength= strlen(scratchPad);
    scratchPad[0]= tolower(scratchPad[0]);
    scratchPad[nameLength]= '_';
    sprintf(&scratchPad[nameLength+1], "%d", usage[(unsigned int)(((HtmlElement *)anElement)->getTag())]++);

    *outStream << "\t" << elementClassName[(unsigned int)(((HtmlElement *)anElement)->getTag())] << " "
    		<< scratchPad << "= new " << elementClassName[(unsigned int)(((HtmlElement *)anElement)->getTag())]
		<< "();\n";

    if ((((HtmlElement *)anElement)->getTag()) == HtmlDTD::tPcdata) {
	char *tmpScanner= ((HPcData *)anElement)->getData();

	*outStream << "\t" << scratchPad << ".setValue(\"";
	while (*tmpScanner != '\0') {
	    switch(*tmpScanner) {
		case '\r': *outStream << "\\r"; break;
		case '\n': *outStream << "\\n"; break;
		case '"': *outStream << "\\" << '"'; break;
		default: *outStream << *tmpScanner; break;
	    }
	    tmpScanner++;
	}
	*outStream << "\");\n";
    }
    else if ((((HtmlElement *)anElement)->getTag()) == HtmlDTD::tComment) {
	char *tmpScanner= ((CommentElement *)anElement)->getData();
	*outStream << "\t" << scratchPad << ".setValue(\"";
	while (*tmpScanner != '\0') {
	    switch(*tmpScanner) {
		case '\r': *outStream << "\\r"; break;
		case '\n': *outStream << "\\n"; break;
		case '"': *outStream << "\\" << '"'; break;
		default: *outStream << *tmpScanner; break;
	    }
	    tmpScanner++;
	}
	 *outStream << "\");\n";
    }


    if ((attributes= anElement->getAttributes()) != NULL) {
	HtmlAttribute *attrib;
	unsigned int i, attrCount= attributes->count();

	*outStream << "\t" << scratchPad << ".attributes= new HtmlAttribute[" << attrCount
		<< "];\n";

	for (i= 0; i < attrCount; i++) {
	    attrib= (HtmlAttribute *)attributes->objectAt(i);
	    *outStream << "\t" << scratchPad << ".attributes[" << i << "]= new HtmlAttribute(\""
			<< attrib->getName() << "\", ";
	    if (attrib->getDefinition()->isAssignable()) {
		char *tmpScanner= attrib->getValue();
		*outStream << '"';
		while (*tmpScanner != '\0') {
		    switch(*tmpScanner) {
			case '\r': *outStream << "\\r"; break;
			case '\n': *outStream << "\\n"; break;
			case '"': *outStream << "\\" << '"'; break;
			default: *outStream << *tmpScanner; break;
		    }
		    tmpScanner++;
		}
		*outStream << "\");\n";
	    }
	    else {
		*outStream << "null);\n";
	    }
	}
    }

    if ((subElements= anElement->getSubElements()) != NULL) {
	*outStream << "\t" << scratchPad << ".subElements= new HtmlElement[" << subElements->count()
		<< "];\n";
    }

    if (anElement->getParent() != NULL) {
	*outStream << "\t" << nameStack->name << ".subElements[" << nameStack->index++ << "]= "
	    << scratchPad << ";\n";
    }

    nameStack= new NameContainer(scratchPad, nameStack);;
}


void JavaRenderer::renderEndOf(SgmlElement *anElement)
{
    NameContainer *tmpName= nameStack;
    nameStack= nameStack->previous;
    delete tmpName;
}



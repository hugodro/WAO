/**************************************************
* File: htmlAnalyzer.cc.
* Desc: «desc».
* Module: «module».
* Rev: «rev».
**************************************************/

#include <stdio.h>
#include <ctype.h>
#if !defined(_WIN32)
#include <iostream.h>
#endif
#include "htmlDTD.h"
#include "htmlDoc.h"
#include "htmlElement.h"
#include "htmlAnalyzer.h"


HtmlAnalyzer::HtmlAnalyzer(void)
{
    state= initial;
    dtd= new HtmlDTD();
}


int HtmlAnalyzer::handle(SgmlToken aToken, char *rawData)
{
    HtmlDoc *doc= (HtmlDoc *)currentDoc;	// Just to do away with casting.
    int errorCode;
    HtmlDoc::State docState;
    HtmlDTD::HtmlTags tag;
    char *tmpChar;
    boolean assignation;

    if ((state != parseDoc) && ((aToken != markupStart) && (aToken != comment))) {
	state= parseDoc;		// Skip the DocType definition.
	((HtmlDTD *)dtd)->useVersion("-//W3C//DTD HTML 3.2//EN");
    }

    docState= doc->getState();
    switch(aToken) {
	case startTag:
	    tag= preProcessTag(rawData);
	    if ((tag != HtmlDTD::emptyTag) && (tag != HtmlDTD::unknownTag)) {
		if (docState == HtmlDoc::inBody) {	// Most frequent situation.
		    if (((HtmlDTD*)dtd)->checkCategory(tag, HtmlDTD::eBody)) {
			if ((errorCode= doc->pushElement(tag)) != 0) {
			    if ((flags & silent) != 1) {
#if !defined(_WIN32)
				cout << "ERRMSG: Tag ["<< rawData << "] is refused from sequence [" << ((HtmlDTD*)dtd)->nameTag(doc->getCurrentElement()->getTag()) << "].\n";
#endif
			    }
			}
		    }
		}
		else if (docState == HtmlDoc::inHead) {
		    if (((HtmlDTD*)dtd)->checkCategory(tag, HtmlDTD::eHead)) {
			if ((errorCode= doc->pushElement(tag)) != 0) {
			    if ((flags & silent) != 1) {
#if !defined(_WIN32)
				cout << "ERRMSG: Tag is refused from sequence ["<< rawData << "].\n";
#endif
			    }
			}
		    }
		    else if (tag == HtmlDTD::tBody) {
			if (doc->popElement(HtmlDTD::tHead)) {
			    doc->setState(HtmlDoc::inBody);
			    doc->gotBodyStart();
			}
			else {
			    if ((flags & silent) != 1) {
#if !defined(_WIN32)
				cout << "ERRMSG: Body tag out of sync.\n";
#endif
			    }
			}
		    }
		    else if (((HtmlDTD*)dtd)->checkCategory(tag, HtmlDTD::eBody)) {
			if (doc->popElement(HtmlDTD::tHead)) {
			    doc->setState(HtmlDoc::inBody);
			    if ((errorCode= doc->pushElement(tag)) != 0) {
				if ((flags & silent) != 1) {
#if !defined(_WIN32)
				    cout << "ERRMSG: Tag is refused from Head ["<< rawData << "].\n";
#endif
				}
			    }
			}
			else {
			    if ((flags & silent) != 1) {
#if !defined(_WIN32)
				cout << "ERRMSG: Body tag out of sync.\n";
#endif
			    }
			}
		    }
		}
		else {	// Entry/exit situations.
		    if (tag == HtmlDTD::tHtml) {
			if (docState != HtmlDoc::initial) {
			    // Erreur !
#if !defined(_WIN32)
			    cout << "ERRMSG: out of context tag 'HTML' (ignored).\n";
#endif
			}
			else {
			    doc->setState(HtmlDoc::postHtml);
			}
		    }
		    else if (tag == HtmlDTD::tHead) {
			if (docState != HtmlDoc::postHtml) {
			    // Erreur !
			    if ((flags & silent) != 1) {
#if !defined(_WIN32)
				cout << "ERRMSG: out of context tag 'HEAD' (ignored).\n";
#endif
			    }
			}
			else {
			    doc->gotHeadStart();
			    doc->setState(HtmlDoc::inHead);
			}
		    }
		    else if (tag == HtmlDTD::tBody) {
			if (docState != HtmlDoc::postHead) {
			    // Erreur !
			    if ((flags & silent) != 1) {
#if !defined(_WIN32)
				cout << "ERRMSG: out of context tag 'BODY' (ignored).\n";
#endif
			    }
			}
			else {
			    doc->gotBodyStart();
			    doc->setState(HtmlDoc::inBody);
			}
		    }
		    else {	// Some other tag than <html>, <head> or <body>.
			if (((HtmlDTD*)dtd)->checkCategory(tag, HtmlDTD::eHead)) {
			    doc->setState(HtmlDoc::inHead);
			    if ((errorCode= doc->pushElement(tag)) != 0) {
				if ((flags & silent) != 1) {
#if !defined(_WIN32)
				    cout << "ERRMSG: Tag is refused from Head ["<< rawData << "].\n";
#endif
				}
			    }
			}
			else if (((HtmlDTD*)dtd)->checkCategory(tag, HtmlDTD::eBody)) {
			    if (docState != HtmlDoc::postHead) {
				if ((flags & silent) != 1) {
#if !defined(_WIN32)
				    cout << "ERRMSG: Body tag out of sequence ["<< rawData << "].\n";
#endif
				}
			    }
			    else {
				doc->setState(HtmlDoc::inBody);
				if ((errorCode= doc->pushElement(tag)) != 0) {
				    if ((flags & silent) != 1) {
#if !defined(_WIN32)
					cout << "ERRMSG: Tag is refused from Body ["<< rawData << "].\n";
#endif
				    }
				}
			    }
			}
			else {
			    if ((flags & silent) != 1) {
#if !defined(_WIN32)
				cout << "ERRMSG: Out of sync tag: ["<< rawData << "].\n";
#endif
			    }
			}
		    }
		}
	    }
	    else {
		if ((flags & silent) != 1) {
#if !defined(_WIN32)
		    cout << "ERRMSG: Unknown HTML tag [" << rawData << "].\n";
#endif
		}
	    }
	    break;

	case endTag:
	    tag= preProcessTag(rawData);
	    if ((tag != HtmlDTD::emptyTag) && (tag != HtmlDTD::unknownTag)) {
		if (doc->popElement(tag)) {
		    if (tag == HtmlDTD::tHead) {
			if (docState == HtmlDoc::inHead) {
			    doc->setState(HtmlDoc::postHead);
			}
			else {
			    if ((flags & silent) != 1) {
#if !defined(_WIN32)
				cout << "ERRMSG: Improper head end tag.\n";
#endif
			    }
			}
		    }
		    else if (tag == HtmlDTD::tBody) {
			if ((docState == HtmlDoc::inHead) || (docState == HtmlDoc::postHead) ||
				(docState == HtmlDoc::inBody)) {
			    doc->setState(HtmlDoc::postBody);
			}
			else {
			    if ((flags & silent) != 1) {
#if !defined(_WIN32)
				cout << "ERRMSG: Improper body end tag.\n";
#endif
			    }
			}
		    }
		    else if (tag == HtmlDTD::tHtml) {
			if ((docState != HtmlDoc::initial) || (docState != HtmlDoc::postHtml)) {
			    doc->setState(HtmlDoc::postDoc);
			}
			else {
			    if ((flags & silent) != 1) {
#if !defined(_WIN32)
				cout << "ERRMSG: Improper html end tag.\n";
#endif
			    }
			}
		    }
		}
		else {
		    if ((flags & silent) != 1) {
#if !defined(_WIN32)
			cout << "ERRMSG: Tag refused [" << rawData << "].\n";
#endif
		    }
		}
	    }
	    else {
		if ((flags & silent) != 1) {
#if !defined(_WIN32)
		    cout << "ERRMSG: Unknown HTML closing tag [" << rawData << "].\n";
#endif
		}
	    }
	    break;

	case attribute:
	    tmpChar= rawData;
	    assignation= false;
	    while (*tmpChar != '\0') {
		if (toupper(*tmpChar)) *tmpChar= tolower(*tmpChar);
		tmpChar++;
	    }
	    if (tmpChar > rawData) {
		tmpChar--;
		if (*tmpChar == '=') {
		    assignation= true;
		    *tmpChar= '\0';
		}
	    }

	    if ((errorCode= doc->addAttribute(rawData, assignation)) != 0) {
		if ((flags & silent) != 1) {
#if !defined(_WIN32)
		    cout << "ERRMSG: Unknown attribute [" << rawData << "].\n";
#endif
		}
	    }
	    break;

	case literal:
	    doc->addValue(SgmlDoc::literal, rawData);
	    break;
	case unqLiteralHack:
	    doc->addValue(SgmlDoc::unqLiterhack, rawData);
	    break;
	case name:
	    doc->addValue(SgmlDoc::name, rawData);
	    break;
	case nameToken:
	    doc->addValue(SgmlDoc::nameToken, rawData);
	    break;
	case dataChar:
	case pcDataChar:
	    doc->addData(rawData);
	    break;
	case comment:
	    doc->treatComment(rawData);
	    break;
	case markupStart:
	    // Should be <!doctype ...>.
	    state= parseDoc;
	    break;
    }
    return 0;
}


HtmlDTD::HtmlTags HtmlAnalyzer::preProcessTag(char *rawData)
{
    char *postScanner;

    if (*rawData == '\0') return HtmlDTD::emptyTag;

    postScanner= rawData;
    while ((*postScanner != '\0') && (*postScanner != '\n') && (*postScanner != '\r') && (*postScanner != ' ') && (*postScanner != '\t')) {
	if (islower(*postScanner)) *postScanner= toupper(*postScanner);
	postScanner++;
    }
    *postScanner= '\0';		// Insure there is no trailing spaces.
    if (*rawData != '\0') {
	return HtmlDTD::identifyTag(rawData);	// Warning: quick exit.
    }
    return HtmlDTD::emptyTag;
}


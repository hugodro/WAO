/**************************************************
* File: main.cc.
* Desc: Main file of the HtmlParser utility.
* Module: Wao : HtmlParser.
* Rev: 19 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <stdlib.h>
#include <iostream.h>
#include <fstream.h>
#include <RunTime/jvcup.h>
#include "htmlAnalyzer.h"
#include "htmlDoc.h"
#include "renderJava.h"
#include "renderHtml.h"
#include "jstRender.h"

#define NO_WORK	0
#define GET_TITLE	1
#define SPIT_JAVA	2
#define SPIT_HTML	3
#define SPIT_JST		4


/*** Functions defined in this module. ***/
void ScanOptions(int, char **);
void ShowUtil(void);
char *MakeOutputName(char *, char *);


/*** Global variables defined in this module. ***/
int runFlags= 0;
unsigned int workToDo= NO_WORK;
unsigned int nbrFilesIn= 0;
char **filesInNames;

main(int argc, char **argv)
{
    HtmlAnalyzer *htAnalyzer;
    HtmlDoc *theDoc;
    JVCup *pzCup= NULL;
    istream *inputStream;
    ostream *outputStream;
    char *outName;
    bool pzRunning= false;

    if (argc > 1) {
	ScanOptions(argc, argv);
    }

    htAnalyzer= new HtmlAnalyzer();
    htAnalyzer->setFlags(runFlags);

    if (nbrFilesIn == 0) {
	inputStream= &cin;
	outputStream= &cout;
    }
    else {
	HtmlRenderer *htmlSpitter;
	JavaRenderer *javaSpitter;
	JstRenderer *jstSpitter;
	unsigned int i;
	char *title;

	for (i= 0; i < nbrFilesIn; i++) {
#if defined(_WIN32)
	    inputStream= new ifstream(filesInNames[i], ios::in | ios::binary);
#else
	    inputStream= new ifstream(filesInNames[i], ios::in);
#endif
	    htAnalyzer->parseConformentDoc(inputStream, filesInNames[i]);
	    theDoc= (HtmlDoc *)htAnalyzer->getCurrentDoc();
	    switch(workToDo) {
		case GET_TITLE:
		    if ((title= theDoc->getTitle()) != NULL) {
//			cout << filesInNames[i] << ": " << title << ".\n";
			    cout << "<p><a href=\"" 
					 << filesInNames[i] << "\">"
					 << title << "</a></p>\n";
		    }
		    else {
			cout << "No title found in document: " << filesInNames[i] << ".\n";
		    }
		    break;
		case SPIT_JAVA:
		    outName= MakeOutputName(theDoc->getSourceName(), "java");
#if defined(_WIN32)
		    if ((outputStream= new ofstream(outName, ios::binary)) != (ofstream *)-1) {
#else
		    if ((outputStream= new ofstream(outName)) != (ofstream *)-1) {
#endif
			javaSpitter= new JavaRenderer(outName, outputStream);
			javaSpitter->renderDoc(theDoc);
			delete javaSpitter;
		    }
		    delete outName;
		    break;
		case SPIT_HTML:
#if defined(_WIN32)
		    if ((outputStream= new ofstream("/tmp/copie.html", ios::binary)) != (ofstream *)-1) {
#else
		    if ((outputStream= new ofstream("/tmp/copie.html")) != (ofstream *)-1) {
#endif
			htmlSpitter= new HtmlRenderer(outputStream);
			htmlSpitter->renderDoc(theDoc);
			delete htmlSpitter;
		    }
		    break;
		case SPIT_JST:
		    outName= MakeOutputName(theDoc->getSourceName(), "jst");
		    if (pzCup == NULL) {
		        pzCup= new JVCup();
		        if (pzCup->boot() == 0) pzRunning= true;
		    }
		    if (pzRunning) {
			jstSpitter= new JstRenderer(outName);
			if (jstSpitter->initialize(pzCup)) {
			    jstSpitter->renderDoc(theDoc);
			    delete jstSpitter;
			}
		    }
		    delete outName;
		    break;
	    }
	    delete theDoc;
	}
    }
}


void ScanOptions(int nbrArgs, char **args)
{
#if !defined(_WIN32)
    extern int optind;
    extern char *optarg;
#else
    int optind;
#endif
    int c;
    boolean errCondition= false;

#if defined(_WIN32)
    int i, j;
    for (optind= 0, j= 1, i= 1; i < nbrArgs;) {
	if (args[i][0] == '-') {
	    switch(args[i][j]) {
		case 'a':
		    j++;
		    workToDo= SPIT_JST;
		    break;
	       case 'h':    /* Give program documentation. */
		    i= nbrArgs-1; j++;
		    ShowUtil();
		    exit(0);
		    break;
		case 'd':
		    j++;
		    runFlags|= SgmlAnalyzer::debug;
		    break;
		case 't':
		    j++;
		    workToDo= GET_TITLE;
		    break;
		case 'j':
		    j++;
		    workToDo= SPIT_JAVA;
		    break;
		case 'r':
		    j++;
		    workToDo= SPIT_HTML;
		    break;
		case 's':
		    j++;
		    runFlags|= SgmlAnalyzer::silent;
		    break;
	       default:
		  /* Unknown option ! */
		    cout << "Unknown option [" << args[i] << "].\n";
		    j++;
		    errCondition= true;
		    break;
	    }
	    if (i < nbrArgs) {
		if (!args[i][j]) {
		    i++;
		    j= 1;
		    optind++;
		}
	    }
	}	// End of the scan of a '-' something.
	else {	// We got something else than an option spec.
	    optind++;
	    break;
	}
    }
#else
    while ((c = getopt(nbrArgs, args, "adhtjrs")) != EOF) {
	switch((char)c) {
	    case 'a':
		workToDo= SPIT_JST;
		break;
	    case 'h':
		ShowUtil();
		exit(0);
		break;
	    case 'd':
		runFlags|= SgmlAnalyzer::debug;
		break;
	    case 't':
		workToDo= GET_TITLE;
		break;
	    case 'j':
		workToDo= SPIT_JAVA;
		break;
	    case 'r':
		workToDo= SPIT_HTML;
		break;
	    case 's':
		runFlags|= SgmlAnalyzer::silent;
		break;
	    case '?':
	    default:
		// Handle error condition.
		errCondition= true;
		break;
	}
    }
#endif

    if (errCondition) {
	ShowUtil();
	exit(-1);
    }

    if (optind == nbrArgs) {
	nbrFilesIn= 0;
    }
    else {
	nbrFilesIn= nbrArgs - optind;
	filesInNames= new char *[nbrFilesIn];

	for (unsigned int i= 0; optind < nbrArgs; optind++, i++) {
	    filesInNames[i]= args[optind];
	}
    }

    if (workToDo == NO_WORK) workToDo= SPIT_JAVA;
}


void ShowUtil(void)
{
    cout << "Util: phtml [<options>] <fichier-in>.\n";
    cout << "Options:\n";
    cout << "-a: produce JST archive.\n";
    cout << "-d: debug mode.\n";
    cout << "-j: produce java version.\n";
    cout << "-r: reproduce HTML version.\n";
    cout << "-t: extract title.\n";
    cout << "-s: run silently, without error reporting.\n";
    cout << "-h: show help.\n";
}


char *MakeOutputName(char *sourceName, char *extension)
{
    unsigned int i= 0;
    unsigned int pathDelimPos[256], nbrPathDelims= 0, extLength= 0;
    char *result;

    if (extension != NULL) extLength= strlen(extension);

    while (sourceName[i] != '\0') {
	if ((sourceName[i] == '/') ||  (sourceName[i] == '\\')) {
	    pathDelimPos[nbrPathDelims++]= i;	// ATTN: Will crash if nbrPathDelims > limit (256).
	}
	else {
	    if (sourceName[i] == '.') {
		if (strcmp(&sourceName[i+1], "html") == 0) {
		    break;
		}
		else {
		    sourceName[i]= '_';
		}
	    }
	}
	i++;
    }

    result= new char[i + extLength + 2];
    memcpy(result, sourceName, i * sizeof(char));
    if (extLength > 0) {
	result[i]= '.';
	memcpy(result+i+1, extension, extLength * sizeof(char));
    }
    result[i+1+extLength]= '\0';
    return result;
}


#if defined(IRIX) || defined(NeXT)
#include <pwd.h>
#endif
#include <RunTime/stringSupport.h>

void fakeSymbols(void)
{
    getpwuid(getuid());
    gettimeofday(NULL, NULL);
    StringSupport::mapStringToNarrowArray(NULL, NULL);
}

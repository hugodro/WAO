/**************************************************
* File: testWml.cpp.
* Desc: Test Main file of the WmlParser utility.
* Module: Wao : SgmlParser.
* Rev: 19 janvier 2000 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <iostream.h>
#include <fstream.h>
#include "wmlAnalyzer.h"
#include "wmlDoc.h"
#include "xmlLexer.h"


/*** Functions defined in this module. ***/
void ScanOptions(int, char **);


/*** Global variables defined in this module. ***/
int runFlags;
unsigned int nbrFilesIn= 0;
char **filesInNames;


int main(int argc, char **argv)
{
    WmlAnalyzer *wAnalyzer;
    WmlDoc *theDoc;
    istream *inputStream;
    ostream *outputStream;
    char *outName;


    if (argc > 1) {
	ScanOptions(argc, argv);
    }

    wAnalyzer= new WmlAnalyzer();
    wAnalyzer->setFlags(runFlags);

    if (nbrFilesIn == 0) {
	inputStream= &cin;
	outputStream= &cout;
    }
    else {
	unsigned int i;
	for (i= 0; i < nbrFilesIn; i++) {
#if defined(_WIN32)
	    inputStream= new ifstream(filesInNames[i], ios::in | ios::binary);
#else
	    inputStream= new ifstream(filesInNames[i], ios::in);
#endif
	    wAnalyzer->parseConformentDoc(inputStream, filesInNames[i]);
	    theDoc= (WmlDoc *)wAnalyzer->getCurrentDoc();
	    // TODO: Treat the document produced.

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
		    break;
	        case 'h':    /* Give program documentation. */
		    i= nbrArgs-1; j++;
		    exit(0);
		    break;
	        case 'd':
		    j++;
		    runFlags|= SgmlAnalyzer::debug;
		    break;
		case 't':
		    j++;
		    break;
		case 'j':
		    j++;
		    break;
		case 'r':
		    j++;
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
		break;
	    case 'h':
		exit(0);
		break;
	    case 'd':
		runFlags|= SgmlAnalyzer::debug;
		break;
	    case 't':
		break;
	    case 'j':
		break;
	    case 'r':
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

}

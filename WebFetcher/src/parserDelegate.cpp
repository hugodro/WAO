/**************************************************
* File: parserDelegate.cc.
* Desc: Implementation of the ParserDelegate class.
* Module: AkraLog : WebFetcher.
* Rev: 25 mars 2000 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <stdlib.h>
#include <fstream>

#include "parserDelegate.h"


ParserDelegate::ParserDelegate(void)
{
    analyzer= new HtmlAnalyzer(void);
}


ParserDelegate::~ParserDelegate(void)
{
    if (analyzer != NULL) delete analyzer;
}


bool ParserDelegate::beginReception(HttpSession *aSession)
{
    // TODO.
    return true;
}


bool ParserDelegate::noticeHeader(HttpSession *aSession, HttpResponse *aResponse)
{
    // TODO: Extraire tous les headers important pour le document.
    return true;
}


bool ParserDelegate::noticeContent(HttpSession *aSession, HttpResponse *aResponse, char *data, unsigned int dataLength)
{
    char tmpFileName[80];
    int fileDesc;
    bool result= false;

    strcpy(tmpFileName, "/tmp/.fetcher.XXXXXX");

    if ((fileDesc= mkstemp(tmpFileName)) != -1) {
	ifstream *inputStream;
	HtmlDoc *theDoc;

	// TODO: Passer au travers de la reponse,
	// regarder si l'arbre a ete cree,
	write(data, dataLength);
	close(fileDesc);

	inputStream= ifstream(tmpFileName, ios::in);

	analyzer->parseConformentDoc(inputStream, tmpFileName);
	if ((theDoc= (HtmlDoc)analyzer->getCurrentDoc()) != NULL) {
	    // descendre dans l'arbre selon le site -> appliquer un des PageReader.
	    // construire de nouvelles requetes, ou sauver l'information trouvee (la reponse originale).
	}

	unlink(tmpFileName);
	result= true;
    }

    return result;
}


bool ParserDelegate::endReception(HttpSession *aSession)
{
    // TODO.
    return true;
}

/**************************************************
* File: fetchFolio.cc.
* Desc: Module principal pour aller chercher les articles de loi du site de l'AQUIJ.
* Module: AkraLog : WebFetcher.
* Rev: 6 septembre 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "httpSession.h"
#include "request.h"
#include "fileDelegate.h"

main(int argc, char **argv)
{
    HttpSession *session;
    FileDelegate *delegate;
    unsigned int i, pageID, nbrIterations, offset, endRecord;
    char pageName[256];
    char fileName[80];
    bool firstTime= true;

/*
2: t16037: A
3: t49606: B
4: t54827: C
5: t136394: D
6: t144545: E
7: t164741: F
8: t175578: G
9: t175911: H
10: t177201: I
11: t232430: J
12: t232974: L
13: t235250: M
14: t250967: N
15: t253773: O
16: t258759: P
17: t280554: Q
18: t283623: R
19: t313919: S
20: t347017: T
*/

    offset= 16037;
    endRecord= 384657;

    if (argc > 1) {
	if (argc > 2) {
	    sscanf(argv[argc-1], "%d", &endRecord);
	    sscanf(argv[argc-2], "%d", &offset);
	}
	else {
	    sscanf(argv[argc-1], "%d", &offset);
	}
    }

    delegate= new FileDelegate();
    session= new HttpSession(delegate);
    pageID= offset;
    nbrIterations= 0;
    do {
	sprintf(pageName, "/cgi-bin/foliocgi.exe/gratnet.nfo/query=*/doc/{t%d}/pageitems={body}?", pageID);
	sprintf(fileName, "/tmp/Lois/t%d", pageID);
	printf("Fait page t%d.\n", pageID);
	if (firstTime) {
	    if (!session->open("folio.point-net.com", 80)) {
		break;
	    }
	    firstTime= false;
	}
	else {
	    if (!session->reopen()) {
		break;
	    }
	}
	if (delegate->fileOn(fileName)) {
	    HttpRequest *request= new HttpGetRequest(pageName);
	    session->execute(request);
	    delete request;
	    delegate->close();
	}
	else {
	    break;
	}
	pageID+= 30;
	nbrIterations++;
    } while (pageID <= endRecord);
    delete session;

}

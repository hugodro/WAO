/**************************************************
* File: fTest.cc.
* Desc: Test wrapper for the webFetcher library.
* Module: AkraLog : WebFetcher.
* Rev: 4 septembre 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "httpSession.h"
#include "request.h"
#include "fileDelegate.h"

main(int argc, char **argv)
{
    HttpSession *session;
    HttpRequest *request[2];
    FileDelegate *delegate;
    char hostName[80];

    if (argc < 2) {
	printf("Util: testFetcher [ <options> ] <nom-de-serveur>.\n");
	exit(0);
    }

    strcpy(hostName, argv[argc-1]);
    delegate= new FileDelegate();
    session= new HttpSession(delegate);

//    request[0]= new HttpGetRequest("/cgi-bin/query?pg=q&sc=on&hl=on&q=wireless&kl=XX&stype=stext");
    request[0]= new HttpGetRequest("/hdml/newmsg.bmp");

    if (session->open(hostName, 8080)) {
	delegate->fileOn("/tmp/t1");
	session->execute(request[0]);
    }
/*
    if (session->reopen()) {
	delegate->fileOn("/tmp/t2");
	session->execute(request[1]);
    }
*/

    delete request[0];
    delete session;
    delete delegate;
}

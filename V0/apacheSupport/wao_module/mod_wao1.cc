/**************************************************
* File: mod_wao1.
* Desc: First test of inclusion of WAO in Apache.
* Module: WAO : Apache-Module.
* Rev: 25 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <time.h>
#include <stdio.h>

extern "C" {
#include "httpd.h"
#include "http_config.h"
#include "http_core.h"
#include "http_log.h"
#include "http_main.h"
#include "http_protocol.h"
#include "util_script.h"
}
#include <RunTime/jvcup.h>
#include <RunTime/jmachine.h>
#include "waoLink.h"


extern "C" {
/*** Declaration of handlers. ***/
    static void wao_init(server_rec *, pool *);
    static int wao_handler(request_rec *);
}



/*** Definition of this module. ***/
module MODULE_VAR_EXPORT wao_module;


/* Subsidiary dispatch table for response-phase handlers, by MIME type */

handler_rec wao_handlers[] = {
    { "test-wao", wao_handler },
    { NULL }
};



module MODULE_VAR_EXPORT wao_module = {
   STANDARD_MODULE_STUFF,
   wao_init,                     /* initializer */
   NULL,                     /* dir config creator */
   NULL,                     /* dir merger --- default is to override */
   NULL,   /* server config */
   NULL,  /* merge server config */
   NULL,                 /* command table */
   wao_handlers,             /* handlers */
   NULL,    		/* filename translation */
   NULL,                     /* check_user_id */
   NULL,                     /* check auth */
   NULL,                     /* check access */
   NULL,         		/* type_checker */
   NULL,                     /* fixups */
   NULL,                     /* logger */
   NULL                      /* header parser */
};


static JVCup *myCup= NULL;
static WaoLink *myLink= NULL;
static char **knownDocuments= NULL;
static JVInstance **loadedDocuments;
static unsigned int nbrKnownDocuments= 0;

static void wao_init(server_rec *s, pool *p)
{
    if (myCup == NULL) {
	myCup= new JVCup();

	if (myCup->boot() < 0) {
		// Could not boot the Plzen processor.
	    delete myCup;
	    myCup= NULL;
	}
    }
    if ((myCup != NULL) && (myLink == NULL)) {
	JVInstance *apacheStream;
	if ((apacheStream= myCup->createInstance("wao/apache/TestStream")) != NULL) {
	    myLink= new WaoLink(apacheStream, myCup->getDefaultMachine());
	    myLink->set_dual(myLink);		// The WaoLink is its own dual !
	    knownDocuments= new char *[10];
	    loadedDocuments= new JVInstance *[10];
	    nbrKnownDocuments= 0;
	}
    }
}


static int wao_handler(request_rec *r)
{
    struct tm *timeptr;
    time_t timer;
    int gotError;
    char ourTime[80];

    if (myCup != NULL) {
	JVInstance *tmpInstance;
	if ((tmpInstance= loadedDocuments[0]) == NULL) {
	    loadedDocuments[0]= myCup->createInstance("testWao");
	    tmpInstance= loadedDocuments[0];
	}
	if (tmpInstance != NULL) {
	    void *argBlock[1];
	    argBlock[0]= myLink->get_this();
	    myLink->setRequestContext(r);
	    myCup->runMethod("spitDoc", "(Lwao/server/OutputStream;)V", tmpInstance, 1, argBlock);
	    gotError= 0;
	}
	else gotError= 1;
    }
    else gotError= 2;

    if (gotError != 0) {
	time(&timer);
	timeptr = localtime(&timer);
	strftime(ourTime, 80, "[%Y/%m/%d %H:%M:%S]", timeptr);

	r->content_type = "text/html";
	soft_timeout("send example call trace", r);
	send_http_header(r);
	kill_timeout(r);
	rputs("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 3.2//EN\">\n", r);
	rputs("<HTML>\n", r);
	rputs("<HEAD>\n", r);
	rputs("<TITLE>WAO: Premier test.</TITLE>\n", r);
	rputs("</HEAD>\n", r);
	rputs("<BODY>\n", r);
	rputs("<H1>Un premier test de WAO-Module.</H1>\n", r);
	rputs("<P>Date de generation: ", r);
	rputs(ourTime, r);
	switch (gotError) {
	    case 1:
		rputs("<P><B>Ne trouve pas testWao.</B>\n", r);
		break;
	    case 2:
		rputs("<P><B>N'a pas de machine.</B>\n", r);
		break;
	}
	rputs("</BODY>\n", r);
	rputs("</HTML>\n", r);
    }
    return OK;
}


#include <sys/time.h>
#include <RunTime/stringSupport.h>
#include <libc.h>


void fakeCode(void)
{
    gettimeofday(NULL, NULL);
    StringSupport::mapStringToNarrowArray(NULL, NULL);
    dup(NULL);
}

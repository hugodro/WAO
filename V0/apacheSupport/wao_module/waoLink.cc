/**************************************************
* File: waoLink.cc.
* Desc: Implementation of the WaoLink class.
* Module: Wao : ApacheSupport.
* Rev: 26 mars 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <RunTime/jmachine.h>
#include <RunTime/jvInstance.h>
#include <RunTime/stacks.h>
#include "waoLink.h"
extern "C" {
#include "httpd.h"
#include "http_main.h"
#include "http_protocol.h"
}

JVVariable *WaoLink::dualField;
boolean WaoLink::mustFetchDict= true;

boolean WaoLink::fetchDictionary(JVMachine *aMachine, ClassFile *aClass)
{
    if (mustFetchDict) {
	dualField= aMachine->getFieldOfClass(aClass, "dual");
	mustFetchDict= false;
    }

    return (dualField != NULL);
}



WaoLink::WaoLink(JVInstance *anInstance, JVMachine *aMachine)
{
    javaEquiv= anInstance;
    if (mustFetchDict) {
	if (!fetchDictionary(aMachine, javaEquiv->category())) {
	    // ATTN: Must throw an error.
	}
    }
}


void WaoLink::setRequestContext(request_rec *r)
{
    requestContext= r;
}


void WaoLink::defineHeader(char *aString)
{
    requestContext->content_type = aString;
    soft_timeout("waoLink defineHeader", requestContext);
    send_http_header(requestContext);
    kill_timeout(requestContext);
}


void WaoLink::puts(char *aString)
{
    if (requestContext != NULL) {
	rputs(aString, requestContext);
    }
}

JVInstance *WaoLink::get_this(void)
{
    return javaEquiv;
}


void WaoLink::set_dual(void *thisValue)
{
    if (!mustFetchDict) {
	JVRunValue thisValue(TYPE_BASIC, thisValue);
	javaEquiv->putField(thisValue, dualField);
    }
    else {
	// ATTN: Must throw an error.
    }
}


WaoLink *WaoLink::get_dual(void)
{
    return (WaoLink *)javaEquiv->getField(dualField);
}

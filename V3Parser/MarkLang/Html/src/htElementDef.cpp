/**************************************************
* File: htElementDef.cpp.
* Desc: Implementation of the HTML Element definition.
* $Date$
* Rev: 2000/09/03 : REV 1 : Hugo DesRosiers : Creation.
* Rev: 2000/11/30 : REV 1 : Hugo DesRosiers : Created out of Hdml/hdElementDef.cpp.
* $Log$
**************************************************/

#include <ctype.h>
#if defined(_WIN32)
#include <string>
#endif

#include <globDefs.h>

#include "htElementDef.h"


xtnHtmlElementDef::xtnHtmlElementDef(char *aName, unsigned int startFlag, unsigned int endFlag)
  : xtnSgmlElementDef(aName, startFlag, endFlag)
{
    attributes= 0;
    // ATTN-980323 [HD]: The following should generate an error on 'unknownTag'.
    tag= xtnHtmlDTD::identifyTag(aName);
}


bool xtnHtmlElementDef::canInclude(xtnHtmlDTD::HtmlTags aTag)
{
  if (aTag == xtnHtmlDTD::tComment) return true;
  switch(tag) {
	case xtnHtmlDTD::tHtml:		// Accept the out of bounds data.
	    return ((aTag == xtnHtmlDTD::tPcdata) || (aTag == xtnHtmlDTD::tHead) || (aTag == xtnHtmlDTD::tBody));
	    break;
	case xtnHtmlDTD::tHead:
	    return (xtnHtmlDTD::isFromEntity(aTag, xtnHtmlDTD::headContent) || xtnHtmlDTD::isFromEntity(aTag, xtnHtmlDTD::headMisc));
	    break;
	case xtnHtmlDTD::tTitle:
	    return (aTag == xtnHtmlDTD::tPcdata);
	    break;
	case xtnHtmlDTD::tStyle:
	    return (aTag == xtnHtmlDTD::tPcdata);
	    break;
	case xtnHtmlDTD::tBody:
        // MOD-050203 [HD]: Added style and script for 4.0 conf.
	    return (xtnHtmlDTD::isFromEntity(aTag, xtnHtmlDTD::bodyContent) || (aTag == xtnHtmlDTD::tStyle) || (aTag == xtnHtmlDTD::tScript));
	    break;
	case xtnHtmlDTD::tH1: case xtnHtmlDTD::tH2: case xtnHtmlDTD::tH3:
	case xtnHtmlDTD::tH4: case xtnHtmlDTD::tH5: case xtnHtmlDTD::tH6:
	    return (xtnHtmlDTD::isFromEntity(aTag, xtnHtmlDTD::text));
	    break;
	case xtnHtmlDTD::tAddress:
	    return (xtnHtmlDTD::isFromEntity(aTag, xtnHtmlDTD::addressContent));
	    break;
	case xtnHtmlDTD::tP:
	    return (xtnHtmlDTD::isFromEntity(aTag, xtnHtmlDTD::text));
	    break;
	case xtnHtmlDTD::tUl:
	case xtnHtmlDTD::tOl:
	    return (aTag == xtnHtmlDTD::tLi);
	    break;
	case xtnHtmlDTD::tLi:
	    return (xtnHtmlDTD::isFromEntity(aTag, xtnHtmlDTD::flow));
	    break;
	case xtnHtmlDTD::tDl:
	    return ((aTag == xtnHtmlDTD::tDt) || (aTag == xtnHtmlDTD::tDd));
	    break;
	case xtnHtmlDTD::tDt:
	    return (xtnHtmlDTD::isFromEntity(aTag, xtnHtmlDTD::text));
	    break;
	case xtnHtmlDTD::tDd:
	    return (xtnHtmlDTD::isFromEntity(aTag, xtnHtmlDTD::flow));
	    break;
	case xtnHtmlDTD::tDir:
	case xtnHtmlDTD::tMenu:
	    return (aTag == xtnHtmlDTD::tLi);
	    break;
	case xtnHtmlDTD::tPre:
	    if (xtnHtmlDTD::isFromEntity(aTag, xtnHtmlDTD::preExclusion)) return false;
	    return (xtnHtmlDTD::isFromEntity(aTag, xtnHtmlDTD::text));
	    break;
	case xtnHtmlDTD::tDiv:
	case xtnHtmlDTD::tCenter:
	case xtnHtmlDTD::tBlockquote:
	    return (xtnHtmlDTD::isFromEntity(aTag, xtnHtmlDTD::bodyContent));
	    break;
	case xtnHtmlDTD::tForm:
	    if (aTag == xtnHtmlDTD::tForm) return false;
	    return (xtnHtmlDTD::isFromEntity(aTag, xtnHtmlDTD::bodyContent));
	    break;
	case xtnHtmlDTD::tTable:
	    return ((aTag == xtnHtmlDTD::tCaption) || (aTag == xtnHtmlDTD::tTr) || (aTag == xtnHtmlDTD::tPcdata) || (aTag == xtnHtmlDTD::tForm));
	    break;
	case xtnHtmlDTD::tCaption:
	    return (xtnHtmlDTD::isFromEntity(aTag, xtnHtmlDTD::text));
	    break;
	case xtnHtmlDTD::tTr:
          // MOD-051030 [HD]: Hack mod for Google support.
	    return ((aTag == xtnHtmlDTD:: tTh) || (aTag == xtnHtmlDTD:: tTd) || (aTag == xtnHtmlDTD::tPcdata) || (aTag == xtnHtmlDTD::tForm));
	    break;
	case xtnHtmlDTD::tTh:
	case xtnHtmlDTD::tTd:
        // MOD-050203 [HD]: Hack mod for 4.0 conformance.
	    return (xtnHtmlDTD::isFromEntity(aTag, xtnHtmlDTD::bodyContent) || (aTag == xtnHtmlDTD::tStyle));
	    break;
	case xtnHtmlDTD::tTt:		case xtnHtmlDTD::tI:
	case xtnHtmlDTD::tB:		case xtnHtmlDTD::tU:
	case xtnHtmlDTD::tStrike:	case xtnHtmlDTD::tBig:
	case xtnHtmlDTD::tSmall:	case xtnHtmlDTD::tSub:
	case xtnHtmlDTD::tSup:	case xtnHtmlDTD::tEm:
	case xtnHtmlDTD::tStrong:	case xtnHtmlDTD::tDfn:
	case xtnHtmlDTD::tCode:	case xtnHtmlDTD::tSamp:	case xtnHtmlDTD::tKbd:	case xtnHtmlDTD::tVar:
	case xtnHtmlDTD::tCite:
	    return (xtnHtmlDTD::isFromEntity(aTag, xtnHtmlDTD::text));
	    break;
	case xtnHtmlDTD::tA:
	    if (aTag == xtnHtmlDTD::tA) return false;	// Stop recursion.
	    if (aTag == xtnHtmlDTD::tCenter) return true;	// ATTN: Non Html 3.2 conforment.
	    if (aTag == xtnHtmlDTD::tSpan) return true;	// ATTN: Non Html 3.2 conforment.
	    return (xtnHtmlDTD::isFromEntity(aTag, xtnHtmlDTD::text));
	    break;
	case xtnHtmlDTD::tApplet:
	    if (aTag == xtnHtmlDTD::tParam) return true;
	    return (xtnHtmlDTD::isFromEntity(aTag, xtnHtmlDTD::text));
	    break;
	case xtnHtmlDTD::tFont:
	    return (xtnHtmlDTD::isFromEntity(aTag, xtnHtmlDTD::text));
	    break;
	case xtnHtmlDTD::tMap:
	    return (aTag == xtnHtmlDTD::tArea);
	    break;
	case xtnHtmlDTD::tSelect:
	    return (aTag == xtnHtmlDTD::tOption);
	    break;
	case xtnHtmlDTD::tOption:
	    return (aTag == xtnHtmlDTD::tPcdata);
	    break;
	case xtnHtmlDTD::tTextarea:
	    return (aTag == xtnHtmlDTD::tPcdata);
	    break;
	case xtnHtmlDTD::tSpan:
	    return (xtnHtmlDTD::isFromEntity(aTag, xtnHtmlDTD::text));
	    break;
	case xtnHtmlDTD::tScript:
	    return (xtnHtmlDTD::isFromEntity(aTag, xtnHtmlDTD::text)) || (aTag == xtnHtmlDTD::tPcdata) || (aTag == xtnHtmlDTD::tCdata) || (aTag == xtnHtmlDTD::tComment);
	    break;
	case xtnHtmlDTD::tNoScript:
	    return (xtnHtmlDTD::isFromEntity(aTag, xtnHtmlDTD::bodyContent));
	    break;
	case xtnHtmlDTD::tObject:
	    return (aTag == xtnHtmlDTD::tEmbed) || (aTag == xtnHtmlDTD::tParam);
	    break;
  case xtnHtmlDTD::tPcdata:
      return false;
      if (aTag != xtnHtmlDTD::tPcdata)
        return true;
      else
        return false;
      break;
    case xtnHtmlDTD::tCdata:
      return false;
      break;
    }

    return false;
}





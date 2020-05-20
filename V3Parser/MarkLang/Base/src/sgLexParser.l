/**************************************************
* File: sgLexParser.l.
* Desc: Implementation of the token parser for the SGML family of documents.
* Module: AkraLog : Wao.
* Rev: 19 mars 1998 : REV 0 : Hugo DesRosiers : Creation (according to SgmlLex).
* Rev: 2000/08/22 : REV 1: Hugo DesRosiers : Rewrote within Extenta context.
* $Log: sgLexParser.l,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1.1.2  2000/09/20 03:26:47  hugo
* Initial entry
*
**************************************************/

%option noyywrap
%option debug
%option yyclass="xtnSgmlFlexLexer"
%option prefix="sg"
%option yylineno

%{

#include <ctype.h>
#include <stdio.h>

#include <iostream>

#define LEX_INCLUDE	1
#define DEBUG_LEX

#include "analyzer.h"
#include "sgLexer.h"

%}

/* Figure 1 -- Character Classes: Abstract Syntax */

Digit		[0-9]
LCLetter	[a-z]
Special		['()_,\-\./:=?]
UCLetter	[A-Z]

/* Figure 2 -- Character Classes: Concrete Syntax */

LCNMCHAR	[\.-]
/* LCNMSTRT	[] */
UCNMCHAR	[\.-]
/* UCNMSTRT	[] */
 /* @# hmmm. sgml spec says \015 */
RE		\n
 /* @# hmmm. sgml spec says \012 */
RS		\r
SEPCHAR		\011
SPACE		\040

/* Figure 3 -- Reference Delimiter Set: General */

COM	"--"
CRO	"&#"
DSC	"]"
DSO	"["
ERO	"&"
ETAGO	"</"
LIT	\"
LITA	"'"
MDC	">"
MDO	"<!"
MSC	"]]"
NET     "/"
PERO    "%"
PIC	">"
PIO	"<?"
REFC	";"
STAGO	"<"
TAGC	">"

/* 9.2.1 SGML Character */

/*name_start_character	{LCLetter}|{UCLetter}|{LCNMSTRT}|{UCNMSTRT}*/
name_start_character	{LCLetter}|{UCLetter}
name_character		{name_start_character}|{Digit}|{LCNMCHAR}|{UCNMCHAR}

/* 9.3 Name */

name		{name_start_character}{name_character}*
number		{Digit}+
number_token	{Digit}{name_character}*
name_token	{name_character}+

/* 6.2.1 Space */
s		{SPACE}|{RE}|{RS}|{SEPCHAR}
ps		({SPACE}|{RE}|{RS}|{SEPCHAR})+

/* trailing white space */
ws		({SPACE}|{RE}|{RS}|{SEPCHAR})*

/* 9.4.5 Reference End */
reference_end	{REFC}|{RE}

/*
 * 10.1.2 Parameter Literal
 * 7.9.3  Attribute Value Literal
 * (we leave recognition of character references and entity references,
 *  and whitespace compression to further processing)
 *
 * @# should split this into minimum literal, parameter literal,
 * @# and attribute value literal.
 */
literal		({LIT}[^\"]*{LIT})|({LITA}[^\']*{LITA})



/* 9.6.1 Recognition modes */

/*
 * Recognition modes are represented here by start conditions.
 * The default start condition, INITIAL, represents the
 * CON recognition mode. This condition is used to detect markup
 * while parsing normal data charcters (mixed content).
 *
 * The CDATA start condition represents the CON recognition
 * mode with the restriction that only end-tags are recognized,
 * as in elements with CDATA declared content.
 * (@# no way to activate it yet: need hook to parser.)
 *
 * The TAG recognition mode is split into two start conditions:
 * ATTR, for recognizing attribute value list sub-tokens in
 * start-tags, and TAG for recognizing the TAGC (">") delimiter
 * in end-tags.
 *
 * The MD start condition is used in markup declarations. The COM
 * start condition is used for comment declarations.
 *
 * The DS condition is an approximation of the declaration subset
 * recognition mode in SGML. As we only use this condition after signalling
 * an error, it is merely a recovery device.
 *
 * The CXT, LIT, PI, and REF recognition modes are not separated out
 * as start conditions, but handled within the rules of other start
 * conditions. The GRP mode is not represented here.
 */


/* %x CON == INITIAL */
%x CDATA

%x TAG
%x ATTR
%x ATTRVAL

%x MD
%x COM
%x DS


%%


 /*
  * 9.6 Delimiter Recognition and
  * Figure 3 -- Reference Delimiter Set: General
  *
  * This is organized by recognition mode: first CON, then TAG,
  * MD, and DS. Within a mode, the rules are ordered alphabetically
  * by delimiter name.
  */


  /* &#60; -- numeric character reference */
{CRO}{number}{reference_end}?	 {
#if defined(DEBUG_LEX)
    if (analyzer->doLexDebug()) {
      cerr << "@DBG [xtnSgmlFlexer]: numeric character reference [" << yytext << "].\n";
    }
#endif
      // cerr << "@ERR [xtnSgmlFlexer]: Unsupported; numeric character reference [" << yytext << "].\n";
	analyzer->handle(xtnCoreAnalyzer::dataChar, yytext);
    }

  /* &#60xyz. -- syntax error */
{CRO}{number_token}{reference_end}?	{
         cerr << "@ERR [xtnSgmlFlexer]: syntax error " << yytext << ".\n";
    }


  /* &#SPACE; -- named character reference. Not supported. */
{CRO}{name}{reference_end}?		{
#if defined(DEBUG_LEX)
    if (analyzer->doLexDebug()) {
      cerr << "@DBG [xtnSgmlFlexer]: named character reference [" << yytext << "].\n";
    }
#endif
     //  cerr << "@ERR [xtnSgmlFlexer]: Unsupported; named character reference [" << yytext << "].\n";
	analyzer->handle(xtnCoreAnalyzer::dataChar, yytext);
    }


  /* &amp; -- general entity reference */
{ERO}{name}{reference_end}?	{
#if defined(DEBUG_LEX)
    if (analyzer->doLexDebug()) {
      cerr << "@DBG [xtnSgmlFlexer]: general entity reference [" << yytext << "].\n";
    }
#endif
    // cerr << "@ERR [xtnSgmlFlexer]: Unhandled; general entity reference [" << yytext << "].\n";
	analyzer->handle(xtnCoreAnalyzer::dataChar, yytext);
    }

  /* </title> -- end tag */
 <INITIAL,CDATA>{ETAGO}{name}{ws} {
#if defined(DEBUG_LEX)
    if (analyzer->doLexDebug()) {
      cerr << "@DBG [xtnSgmlFlexer]: eng tag [" << yytext << "].\n";
    }
#endif
	analyzer->handle(xtnCoreAnalyzer::endTag, yytext+2);
	BEGIN(TAG);
    }

  /* @# HACK for XMP, LISTING?
  Date: Fri, 19 Jan 1996 23:13:43 -0800
  Message-Id: <v01530502ad25cc1a251b@[206.86.76.80]>
  To: www-html@w3.org
  From: chris@walkaboutsoft.com (Chris Lovett)
  Subject: Re: Daniel Connolly's SGML Lex Specification
  */

  /* </> -- empty end tag */
{ETAGO}{TAGC}	{
	cerr << "@ERR [xtnSgmlFlexer]: empty tag !\n";
    }

  /* <!DOCTYPE -- markup declaration */
{MDO}{name}{ws}	{
#if defined(DEBUG_LEX)
    if (analyzer->doLexDebug()) {
      cerr << "@DBG [xtnSgmlFlexer]: markup declaration [" << yytext << "].\n";
    }
#endif
	analyzer->handle(xtnCoreAnalyzer::markupStart, yytext+2);
	BEGIN(MD);
    }

  /* <!> -- empty comment */
{MDO}{MDC} { }

  /* <!--  -- comment declaration */
{MDO}/{COM}		{
	BEGIN(COM);
    }

  /* <![ -- marked section */
{MDO}{DSO}{ws}	{
	BEGIN(DS);
    }

  /* ]]> -- marked section end */
{MSC}{MDC}			{ }

  /* <? ...> -- processing instruction */
{PIO}[^>]*{PIC}			{ }

  /* <name -- start tag */
{STAGO}{name}{ws}	{
#if defined(DEBUG_LEX)
    if (analyzer->doLexDebug()) {
      cerr << "@DBG [xtnSgmlFlexer]: start tag [" << yytext << "].\n";
    }
#endif
	analyzer->handle(xtnCoreAnalyzer::startTag, yytext+1);
	BEGIN(ATTR);
    }


  /* <> -- empty start tag */
{STAGO}{TAGC}			{ }

  /* abcd -- data characters */
([^<&]|(<[^<&a-zA-Z!->?])|(&[^<&#a-zA-Z]))+|. {
#if defined(DEBUG_LEX)
    if (analyzer->doLexDebug()) {
      cerr << "@DBG [xtnSgmlFlexer]: pcData [" << yytext << "].\n";
    }
#endif
	analyzer->handle(xtnCoreAnalyzer::pcDataChar, yytext);
    }

  /* abcd -- data characters */
<CDATA>[^<]+|.	{
#if defined(DEBUG_LEX)
    if (analyzer->doLexDebug()) {
      cerr << "@DBG [xtnSgmlFlexer]: cData [" << yytext << "].\n";
    }
#endif
	analyzer->handle(xtnCoreAnalyzer::dataChar, yytext);
}

 /* 7.4 Start Tag */
 /* Actually, the generic identifier specification is consumed
  * along with the STAGO delimiter ("<"). So we're only looking
  * for tokens that appear in an attribute specification list,
  * plus TAGC (">"). NET ("/") and STAGO ("<") signal limitations.
  */

 /* 7.5 End Tag */
 /* Just looking for TAGC. NET, STAGO as above */

  /* <a ^href = "xxx"> -- attribute name */
<ATTR>{name}{s}*={ws}	{
#if defined(DEBUG_LEX)
    if (analyzer->doLexDebug()) {
      cerr << "@DBG [xtnSgmlFlexer]: attribute name [" << yytext << "].\n";
    }
#endif
	analyzer->handle(xtnCoreAnalyzer::attribute, yytext);
	BEGIN(ATTRVAL);
    }

  /* <img src="xxx" ^ismap> -- name */
<ATTR>{name}{ws} {
#if defined(DEBUG_LEX)
    if (analyzer->doLexDebug()) {
      cerr << "@DBG [xtnSgmlFlexer]: name [" << yytext << "].\n";
    }
#endif
	analyzer->handle(xtnCoreAnalyzer::name, yytext);
    }

  /* <a name = ^xyz> -- name token */
<ATTRVAL>{name_token}{ws}	{
#if defined(DEBUG_LEX)
    if (analyzer->doLexDebug()) {
      cerr << "@DBG [xtnSgmlFlexer]: name token [" << yytext << "].\n";
    }
#endif
	analyzer->handle(xtnCoreAnalyzer::nameToken, yytext);
	BEGIN(ATTR);
    }

  /* <a href = ^"a b c"> -- literal */
<ATTRVAL>{literal}{ws}		{
#if defined(DEBUG_LEX)
    if (analyzer->doLexDebug()) {
      cerr << "@DBG [xtnSgmlFlexer]: literal [" << yytext << "].\n";
    }
#endif
	analyzer->handle(xtnCoreAnalyzer::literal, yytext);
	BEGIN(ATTR);
    }

  /* <a href = ^http://foo/> -- unquoted literal HACK */
<ATTRVAL>[^ "\t\n>]+{ws}	{
#if defined(DEBUG_LEX)
    if (analyzer->doLexDebug()) {
      cerr << "@DBG [xtnSgmlFlexer]: unq literhack [" << yytext << "].\n";
    }
#endif
	analyzer->handle(xtnCoreAnalyzer::unqLiteralHack, yytext);
	BEGIN(ATTR);
    }

  /* <a name= ^> -- illegal tag close */
<ATTRVAL>{TAGC}	{
	fprintf(stderr, "@ERR [xtnSgmlFlexer]: illegal tag close !\n");
	BEGIN(INITIAL);
    }

  /* <a name=foo ^>,</foo^> -- tag close */
<ATTR,TAG>{TAGC}	{
	BEGIN(INITIAL);
    }

  /* <em^/ -- NET tag */
<ATTR,ATTRVAL>{NET}	{
	BEGIN(INITIAL);
    }

  /* <foo^<bar> -- unclosed start tag */
<ATTR,ATTRVAL,TAG>{STAGO}	{
	fprintf(stderr, "@ERR [xtnSgmlFlexer]: unclosed start tag !\n");
	BEGIN(INITIAL);
}

<ATTR,ATTRVAL,TAG>.	{ }

 /* 10 Markup Declarations: General */

 /* <!^--...-->   -- comment v1:
<MD,COM>{COM}([^-]|-[^-])*{COM}{TAGC}	{
#if defined(DEBUG_LEX)
    if (analyzer->doLexDebug()) {
      cerr << "@DBG [xtnSgmlFlexer]: comment [" << yytext << "].\n";
    }
#endif
	analyzer->handle(xtnCoreAnalyzer::comment, yytext+2);
	BEGIN(INITIAL);
}
*/

<MD,COM>{COM}	{
  int c;
  int mylineno= 0;
  uint bufLength= 1024, curBufUsed= 0;
  char *buffer, *cpyBuffer;

  buffer= new char[bufLength];

  while ((c = yyinput()) != 0) {
    if (curBufUsed == bufLength) {
      cpyBuffer= new char[bufLength + 4096];
      memcpy(cpyBuffer, buffer, bufLength);
      bufLength+= 4096;
      delete[] buffer;
      buffer= cpyBuffer;
    }
    buffer[curBufUsed++]= (char)c;
    if (c == '\n')
       ++mylineno;
    else if (c == '-') {
      if ((c = yyinput()) == '-')
        if ((c = yyinput()) == '>')
          break;
        else
          unput(c);
      else
        unput(c);
    }
  }
  buffer[curBufUsed]= '\0';
  analyzer->handle(xtnCoreAnalyzer::comment, buffer);
  BEGIN(INITIAL);
}


 /* <!doctype ^%foo;> -- parameter entity reference */
<MD>{PERO}{name}{reference_end}?{ws}		{
#if defined(DEBUG_LEX)
    if (analyzer->doLexDebug()) {
      cerr << "@DBG [xtnSgmlFlexer]: parameter entity reference [" << yytext << "].\n";
    }
#endif
}

 /* The limited set of markup declarations we're interested in
  * use only numbers, names, and literals.
  */
<MD>{number}{ws}	{
#if defined(DEBUG_LEX)
    cerr << "@DBG [xtnSgmlFlexer]: short number [" << yytext << "].\n";
#endif
    }

<MD>{name}{ws}		{
#if defined(DEBUG_LEX)
    if (analyzer->doLexDebug()) {
      cerr << "@DBG [xtnSgmlFlexer]: short name [" << yytext << "].\n";
    }
#endif

    }

<MD>{literal}{ws}	        {
#if defined(DEBUG_LEX)
    if (analyzer->doLexDebug()) {
      cerr << "@DBG [xtnSgmlFlexer]: short literal [" << yytext << "].\n";
    }
#endif

    }

<MD,COM>{MDC}		{
	BEGIN(INITIAL);
    }

 /* other constructs are errors. */
   /* <!doctype foo ^[  -- declaration subset */
<MD>{DSO}	{
	BEGIN(DS);
    }

<MD,COM>.				{ }


 /* 10.4 Marked Section Declaration */
 /* 11.1 Document Type Declaration Subset */

 /* Our parsing of declaration subsets is just an error recovery technique:
  * we attempt to skip them, but we may be fooled by "]"s
  * inside comments, etc.
  */

  /* ]]> -- marked section end */
<DS>{MSC}{MDC}		{
	BEGIN(INITIAL);
    }

  /* ] -- declaration subset close */
<DS>{DSC}	{
	BEGIN(COM);
    }

<DS>[^\]]+			{ }

%%

/**************************************************
* File: xLexParser.l.
* Desc: Implementation of the token parser for the XML.
* $Date: 2000/09/20 03:37:34 $
* Rev: 15 fevrier 2000 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 2000/08/22 : REV 1: Hugo DesRosiers : Rewrote within Extenta context.
* $Log: xLexParser.l,v $
* Revision 1.1.1.1  2000/09/20 03:37:34  hugo
* Initial Entry
*
* Revision 1.1.1.2  2000/09/20 03:26:47  hugo
* Initial entry
*
**************************************************/

%option noyywrap
%option debug
%option yyclass="xtnXmlFlexLexer"
%option prefix="xx"


%{

#include <ctype.h>
#include <stdio.h>

#include <iostream>
#if defined(_WIN32)
//using std::cerr;
#endif

#define LEX_INCLUDE	1

#include "xAnalyzer.h"
#include "xLexer.h"

%}

/* 2.2: Characters. */

/* 2.3: Common Syntactic Construct. */

Space		(\040|\011|\015|\012)+
EmptySpace          (\040|\011|\015|\012)*

LCLetterAnsi	[a-z]
DigitAnsi		[0-9]
HexaDigitAnsi	[0-9A-Fa-f]
UCLetterAnsi	[A-Z]

LetterAnsi	({LCLetterAnsi}|{UCLetterAnsi})

/* For UC, missing CombiningChar, Extender. */
NameChar	({LetterAnsi}|{DigitAnsi}|\.|\-|_|:)
NameAnsi	({LetterAnsi}|_|:)({NameChar})*
NmToken		({NameChar})+
NmTokens	{NmToken}({Space}{NmToken})+

SimpleNumber        ({DigitAnsi})+
DblQuote      	"\""
NotDblQuote	[^\"]
SngQuote	"'"
NotSngQuote	[^']
Ampercent	"&"
Percent                 "%"
SemiColon	";"
QuestionMark        "?"
EndReference       ({SemiColon}|\015)

CRO	    "&#"
CROHexa    "&#x"
STAGO	    "<"
MDO	"<!"
PIO	"<?"
ETAGO   "</"
DSO	"["
COM	"--"
MSC	"]]"
DSC       "]"
TAGC	">"
CDataName	"CDATA"

PIC1		[\040\015\012]
PIC2		({LetterAnsi}|{DigitAnsi})
PIC3		[\-()+,\./:=?;!*#@$_%]
PIC4		({PIC1}|{PIC2}|{PIC3})
PubIdChar	({PIC4}|{SngQuote})	

EntityValue  ({DblQuote}([^%&"]|{PEReference}|{Reference})* {DblQuote})|({SngQuote}([^%&']|{PEReference}|{Reference})* {SqnQuote})

AttValue	 ({DblQuote}([^<&"]|{Reference})*{DblQuote})|({SngQuote}([^<&']|{Reference})*{SngQuote})

SystemLiteral ({DblQuote}{NotDblQuote}*{DblQuote})|({SngQuote}{NotSngQuote}*{SngQuote})

PubIdLiteral	({DblQuote}{PubIdChar}*{DblQuote})|({SngQuote}{PIC4}*{SngQuote})


 /* R66: */
CharRef			({CRO}{DigitAnsi}+{SemiColon})|({CROHexa}{HexaDigitAnsi}+{SemiColon})
 /* R67: */
Reference		{EntityRef}|{CharRef}
 /* R68: */
EntityRef		{Ampercent}{NameAnsi}{SemiColon}
 /* R69: */
PEReference		 {Percent}{NameAnsi}{SemiColon}


/* Tokenizing States. */

%x CDATA

%x Comment
%x ProcInstr
%x MarkDef
%x Attribute
%x AttribValue
%x Tag
%x DeclSubset

%%

 /* 2.4: Character Data and Markup.  */
 /* TODO: R14. */

 /* 2.5: Comments. */

{MDO}/{COM} {
     BEGIN(Comment);
 }

<MarkDef,Comment>{COM}([^-]|-[^-])*{COM}{EmptySpace} {

#if defined(DEBUG_STEPS)
    if (YYSTATE == MarkDef) {
	cerr << "@DBG [xtnXmlFlexer]: Found markup declaration.\n";
    }
    else {
	cerr << "@DBG [xtnXmlFlexer]: Found comment.\n";
    }
     cerr << "@DBG [xtnXmlFlexer]: [" << yytext << "]\n";
#endif
     analyzer->handle((YYSTATE == MarkDef) ? xtnCoreAnalyzer::markup : xtnCoreAnalyzer::comment, yytext + 2);
 }

<MarkDef,Comment>{TAGC} {
    analyzer->handle(xtnCoreAnalyzer::itemEnd, NULL);
    BEGIN(INITIAL);
 }

{MDO}{TAGC} {

#if defined(DEBUG_STEPS)
     cerr << "@DBG [xtnXmlFlexer]: Empty comment.\n";
#endif
     // Nothing done at analyzer level, just reset the parser data.
 }


 /* 2.6: Processing Instructions. */
{PIO}{NameAnsi} {

#if defined(DEBUG_STEPS)
     cerr << "@DBG [xtnXmlFlexer]: Found a Proc Instr. name.\n";
     cerr << "@DBG [xtnXmlFlexer]: [" << yytext << "]\n";
#endif
     analyzer->handle(xtnCoreAnalyzer::procInstrName, yytext + 2);
     BEGIN(ProcInstr);
 }

<ProcInstr>[^>]*{QuestionMark}{TAGC} {
     /* TODO: Handle Processing Instruction. */
#if defined(DEBUG_STEPS)
     cerr << "@DBG [xtnXmlFlexer]: end of proc instr.\n";
     cerr << "@DBG [xtnXmlFlexer]: [" << yytext << "]\n";
#endif
     analyzer->handle(xtnCoreAnalyzer::procInstr, yytext);
     BEGIN(INITIAL);
 }


 /* 2.7: CDATA. */
{MDO}{DSO}{CDataName}\[ {

#if defined(DEBUG_STEPS)
     cerr << "@DBG [xtnXmlFlexer]: Beginning of CDATA.\n";
     cerr << "@DBG [xtnXmlFlexer]: [" << yytext << "]\n";
#endif
     analyzer->handle(xtnXmlAnalyzer::cDataStart, yytext);

     BEGIN(CDATA);
 }

<CDATA>{MSC}{TAGC} {

#if defined(DEBUG_STEPS)
     cerr << "@DBG [xtnXmlFlexer]: End of CDATA.\n";
#endif
    analyzer->handle(xtnCoreAnalyzer::itemEnd, NULL);
     BEGIN(INITIAL);
 }

 /* 2.8: Prolog and document type. */
{MDO}{NameAnsi}{EmptySpace} {

#if defined(DEBUG_STEPS)
     cerr << "@DBG [xtnXmlFlexer]: Starting a markup declaration\n";
     cerr << "@DBG [xtnXmlFlexer]: [" << yytext << "]\n";
#endif
     /* The type of markup declaration can be: doctype, element or attlist. */
     analyzer->handle(xtnCoreAnalyzer::markupStart, yytext + 2);
     BEGIN(MarkDef);
 }

<MarkDef>{PEReference}{EmptySpace} {
#if defined(DEBUG_STEPS)
     cerr << "@DBG [xtnXmlFlexer]: Parameter Entity Reference.\n";
     cerr << "@DBG [xtnXmlFlexer]: [" << yytext << "]\n";
#endif
     analyzer->handle(xtnCoreAnalyzer::per, yytext);
 }

<MarkDef>{SimpleNumber}{EmptySpace} {
    // TODO: Handle a number in a markup def.
#if defined(DEBUG_STEPS)
     cerr << "@DBG [xtnXmlFlexer]: Number in markup.\n";
     cerr << "@DBG [xtnXmlFlexer]: [" << yytext << "]\n";
#endif
 }

<MarkDef>{NameAnsi}{EmptySpace} {
    // TODO: Handle a name in a markup def.
#if defined(DEBUG_STEPS)
     cerr << "@DBG [xtnXmlFlexer]: Name in markup.\n";
     cerr << "@DBG [xtnXmlFlexer]: [" << yytext << "]\n";
#endif
 }

<MarkDef>{AttValue}{EmptySpace} {
    // TODO: Handle an attribute value in a markup def.
#if defined(DEBUG_STEPS)
     cerr << "@DBG [xtnXmlFlexer]: Literal value in markup.\n";
     cerr << "@DBG [xtnXmlFlexer]: [" << yytext << "]\n";
#endif
 }

<MarkDef>{DSO} {
    // TODO: Handle a markup subset start.
    BEGIN(DeclSubset);
 }


<DeclSubset>{MSC}{TAGC} {
    // TODO: Handle a markup and subset end.
    analyzer->handle(xtnCoreAnalyzer::itemEnd, NULL);
    BEGIN(INITIAL);
 }

<DeclSubset>{DSC} {
    // TODO: Handle a markup subset end.
    analyzer->handle(xtnCoreAnalyzer::itemEnd, NULL);
    BEGIN(MarkDef);
 }

<DeclSubset>[^\]]+ {
    /* TODO: Handle a declaration subset data . */
 }

 /* 3.Logical structures.. */

 /* 3.1 Start tag. */
{STAGO}{NameAnsi}{EmptySpace} {
#if defined(DEBUG_STEPS)
     cerr << "@DBG [xtnXmlFlexer]: Start tag.\n";
     cerr << "@DBG [xtnXmlFlexer]: [" << yytext << "]\n";
#endif
     analyzer->handle(xtnCoreAnalyzer::startTag, yytext+1);
     BEGIN(Attribute);
 }

<Attribute>{NameAnsi}{Space}*={EmptySpace} {
#if defined(DEBUG_STEPS)
     cerr << "@DBG [xtnXmlFlexer]: Attribute name assignment.\n";
     cerr << "@DBG [xtnXmlFlexer]: [" << yytext << "]\n";
#endif
     analyzer->handle(xtnCoreAnalyzer::attribute, yytext);
     BEGIN(AttribValue);
 }

<Attribute>{NameAnsi}{EmptySpace} {
#if defined(DEBUG_STEPS)
     cerr << "@DBG [xtnXmlFlexer]: Attribute name.\n";
     cerr << "@DBG [xtnXmlFlexer]: [" << yytext << "]\n";
#endif
     analyzer->handle(xtnCoreAnalyzer::name, yytext);
 }

<AttribValue>{AttValue}{EmptySpace} {
#if defined(DEBUG_STEPS)
     cerr << "@DBG [xtnXmlFlexer]: Literal value.\n";
     cerr << "@DBG [xtnXmlFlexer]: [" << yytext << "]\n";
#endif
     analyzer->handle(xtnCoreAnalyzer::literal, yytext);
     BEGIN(Attribute);
 }

<AttribValue>{NameAnsi}{EmptySpace} {
#if defined(DEBUG_STEPS)
     cerr << "@DBG [xtnXmlFlexer]: Error: encountered non-quoted value in attrib assignment.\n";
     cerr << "@DBG [xtnXmlFlexer]: [" << yytext << "]\n";
#endif
     analyzer->handle(xtnCoreAnalyzer::nameToken, yytext);
     BEGIN(Attribute);
 }

<Attribute,Tag>{TAGC} {
    analyzer->handle(xtnCoreAnalyzer::itemEnd, NULL);
    BEGIN(INITIAL);
 }

<Attribute,Tag>[/]{TAGC} {
    analyzer->handle(xtnXmlAnalyzer::fastEndTag, NULL);
    BEGIN(INITIAL);
}


<INITIAL,CDATA>{ETAGO}{NameAnsi}{EmptySpace} {
#if defined(DEBUG_STEPS)
    cerr << "@DBG [xtnXmlFlexer]: Found end tag.\n";
     cerr << "@DBG [xtnXmlFlexer]: [" << yytext << "]\n";
#endif

     analyzer->handle((YYSTATE == CDATA) ? xtnXmlAnalyzer::cDataEnd : xtnCoreAnalyzer::endTag, yytext + 1);
     BEGIN(Tag);
 }

<Attribute,AttribValue,Tag>{STAGO} {
    /* TODO: Transport this error onto the driver analyser. */
    cerr << "@DBG [xtnXmlFlexer]: Error: start tag within a tag.\n";
    BEGIN(INITIAL);
 }

<Attribute,AttribValue,Tag>. {
#if defined(DEBUG_STEPS)
    cerr << "@DBG [xtnXmlFlexer]: Misc data in attr, attrValue, tag.\n";
    cerr << "@DBG [xtnXmlFlexer]: [" << yytext << "]\n";
#endif
    // TODO: Find out who should be handling this case (and when it occurs).
 }


 /* Helping rules. */

<MarkDef,Comment>. {
#if defined(DEBUG_STEPS)
    if (YYSTATE == MarkDef) {
	cerr << "@DBG [xtnXmlFlexer]: Misc data in markup decl\n";
    }
    else {
    cerr << "@DBG [xtnXmlFlexer]: Misc data in comment.\n";
    }
    cerr << "@DBG [xtnXmlFlexer]: [" << yytext << "]\n";
#endif
    // TODO: Handle the interns of a markup decl.
 }


 /* Miscellanous. */

 /* abcd -- data characters */
([^<&]|(<[^<&a-zA-Z!->?])|(&[^<&#a-zA-Z]))+|. {
#if defined(DEBUG_STEPS)
    cerr << "@DBG [xtnXmlFlexer]: pcData [" << yytext << "].\n";
#endif
    analyzer->handle(xtnCoreAnalyzer::pcDataChar, yytext);
 }


 /* &#60; -- numeric character reference */
{CRO}{SimpleNumber}{EndReference}? {
#if defined(DEBUG_STEPS)
    cerr << "@DBG [xtnXmlFlexer]: numeric character reference [" << yytext << "].\n";
#endif
    // TODO: Handle this kind of data.
 }

 /* &#60xyz. -- syntax error */
{CRO}{NmToken}{EndReference}? {
    cerr << "@DBG [xtnXmlFlexer]: Error: bad char ref [" << yytext <<"].\n";
    // TODO: Handle this kind of data.
 }


  /* &#SPACE; -- named character reference. Not supported. */
{CRO}{NameAnsi}{EndReference}? {
#if defined(DEBUG_STEPS)
    cerr << "@DBG [xtnXmlFlexer]: named character reference [" << yytext << "].\n";
#endif
    // TODO: Handle this kind of data.
 }


  /* &amp; -- general entity reference */
{Ampercent}{NameAnsi}{EndReference}? {
#if defined(DEBUG_STEPS)
    cerr << "@DBG [xtnXmlFlexer]: general entity reference [" << yytext << "].\n";
#endif
    // TODO: Handle this kind of data.
 }


%%

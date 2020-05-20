/**************************************************
* File: fetchWFB.cc.
* Desc: Main module to fetch the world fact book from the CIA site.
* Module: AkraLog : WebFetcher.
* Rev: 6 septembre 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "httpSession.h"
#include "fileDelegate.h"


char *pagesCIA[266]= {
    "aa", "ac", "af", "ag", "aj", "al", "am", "an",
    "ao", "aq", "ar", "as", "at", "au", "av", "ay",
    "ba", "bb", "bc", "bd", "be", "bf", "bg", "bh",
    "bk", "bl", "bm", "bn", "bo", "bp", "bq", "br",
    "bs", "bt", "bu", "bv", "bx", "by", "ca", "cb",
    "cd", "ce", "cf", "cg", "ch", "ci", "cj", "ck",
    "cm", "cn", "co", "cq", "cr", "cs", "ct", "cu",
    "cv", "cw", "cy", "da", "dj", "do", "dq", "dr",
    "ec", "eg", "ei", "ek", "en", "er", "es", "et",
    "eu", "ez", "fa", "fg", "fi", "fj", "fm", "fo",
    "fp", "fq", "fr", "fs", "ga", "gb", "gg", "gh",
    "gi", "gj", "gk", "gl", "gm", "go", "gp", "gq",
    "gr", "gt", "gv", "gy", "gz", "ha", "hk", "hm",
    "ho", "hq", "hr", "hu", "ic", "id", "im", "in",
    "io", "ip", "ir", "is", "it", "iv", "iz", "ja", "je",
    "jm", "jn", "jo", "jq", "ju", "ke", "kg", "kn",
    "kq", "kr", "ks", "kt", "ku", "kz", "la", "le",
    "lg", "lh", "li", "lo", "lq", "ls", "lt", "lu", "ly",
    "ma", "mb", "mc", "md", "mf", "mg", "mh", "mi",
    "mk", "ml", "mn", "mo", "mp", "mq", "mr", "mt",
    "mu", "mv", "mx", "my", "mz", "nc", "ne", "nf",
    "ng", "nh", "ni", "nl", "no", "np", "nr", "ns",
    "nt", "nu", "nz", "pa", "pc", "pe", "pf", "pg",
    "pk", "pl", "pm", "po", "pp", "ps", "pu", "qa",
    "re", "rm", "ro", "rp", "rq", "rs", "rw", "sa",
    "sb", "sc", "se", "sf", "sg", "sh", "si", "sl",
    "sm", "sn", "so", "sp", "sr", "st", "su", "sv",
    "sw", "sx", "sy", "sz", "tc", "td", "te", "th",
    "ti", "tk", "tl", "tn", "to", "tp", "ts", "tu", "tv",
    "tw", "tx", "tz", "ug", "uk", "up", "us", "uv",
    "uy", "uz", "vc", "ve", "vi", "vm", "vq", "vt",
    "wa", "we", "wf", "wi", "wq", "ws", "wz", "xo",
    "xq", "xx", "ym", "za", "zh", "zi", "zn"
};


main(int argc, char **argv)
{
    HttpSession *session;
    FileDelegate *delegate;
    unsigned int i;
    char pageName[40];
    char fileName[80];

    strcpy(pageName, "/cia/publications/factbook/00.html");
    strcpy(fileName, "/Users/hugo/WWW/CIA/WorldBook/00");

    delegate= new FileDelegate();
    session= new HttpSession(delegate);
    for (i= 0; i < 266; i++) {
	pageName[27]= pagesCIA[i][0];
	pageName[28]= pagesCIA[i][1];
	fileName[30]= pagesCIA[i][0];
	fileName[31]= pagesCIA[i][1];
	if (i == 0) {
	    if (!session->open("www.odci.gov", 80)) {
		break;
	    }
	}
	else {
	    if (!session->reopen()) {
		break;
	    }
	}
	if (delegate->fileOn(fileName)) {
	    session->setPage(pageName);
	    session->execute(HttpSession::get);
	    delegate->close();
	}
	else {
	    break;
	}
	printf("Fait %s\n", pagesCIA[i]);
    }
    delete session;

}
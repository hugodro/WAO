/**************************************************
* File: fileDelegate.cc.
* Desc: Implementation of the FileDelegate class.
* Module: AkraLog : WebFetcher.
* Rev: 6 septembre 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <fstream.h>
#include "fileDelegate.h"


FileDelegate::FileDelegate(void)
{
    output= NULL;
    fileName= NULL;
}


FileDelegate:: ~FileDelegate(void)
{
    if (output != NULL) delete output;
    if (fileName != NULL) delete fileName;
}


void FileDelegate::fileOn(char *aName)
{
    unsigned int nameLength;

    nameLength= strlen(aName)+6;
    fileName= new char[nameLength];
    memcpy(fileName, aName, (aName, nameLength - 6) * sizeof(char));
    strcpy(fileName + nameLength - 6, ".html");
}


bool FileDelegate::beginReception(HttpSession *aSession)
{
#if defined(_WIN32)
    output= new ofstream(fileName, ios::binary);
#else
    output= new ofstream(fileName);
#endif
    return output->good();
}


bool FileDelegate::noticeHeader(HttpSession *aSession, HttpResponse *aResponse)
{
// TODO: Prendre soin de l'information qui est donnee dans le 'response'.
    return true;
}


bool FileDelegate::noticeContent(HttpSession *aSession, HttpResponse *aResponse, char *data, unsigned int dataLength)
{
// TODO: Operer selon le type de reponse.
    if (dataLength > 0) {
	output->write(data, dataLength);
    }

    return true;
}


bool FileDelegate::endReception(HttpSession *aSession, HttpResponse *aResponse, int aStatus)
{
    // TODO: Take care of the parameters content.
    output->close();
}


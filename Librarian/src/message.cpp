/**************************************************
* File: message.cc.
* Desc: Implementation of the AkMessage class.
* Module: WAO : Librarian.
* Rev: 29 juin 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "reorder.h"
#include "message.h"


AkMessage::AkMessage(void)
{
    msgID= 0;
    length= 0;
    format= 0;
    body= NULL;
}

AkMessage::~AkMessage(void)
{
    if (body != NULL) delete[] body;
}


/********************************************************************
* Returns:
*	- [uint] < 0x010000: read everything, [uint]  is left-over quantity.
*	- 0x0FFFFFFFF: read everything, still need more data.
*	- 0x0FFFFFFFE: error, message body too long.
*	- 0x0FFFFFFFD: error, got out of the loop in a bad way.
********************************************************************/
unsigned int AkMessage::extract(unsigned char *dataPtr, unsigned int dataLength, unsigned int readSoFar)
{
    unsigned int i;
    ExtractStage stage;
    bool noError= true;

    if (readSoFar != 0) {
	if (readSoFar < 4) stage= fillID;
	else if (readSoFar < 8) stage= fillLength;
	else if (readSoFar < 10) stage= fillFormat;
	else stage= fillData;
    }
    else {
	stage= rID;
    }

    do {
	switch(stage) {
	    case rID:
		if (dataLength > 3) {
		    msgID= MakeUInt32(dataPtr);
		    dataLength-= 4; dataPtr+= 4;
		    stage= rLength;
		}
		else {
		    for (i= 0; i < dataLength; i++, dataPtr++) {
			msgID|= MakeUInt32Byte(*dataPtr, i);
		    }
		    return 0x0FFFFFFFF;		// Warning: quick exit.
		}
		break;
	    case rLength:
		if (dataLength > 3) {
		    length= MakeUInt32(dataPtr);
		    dataLength-= 4; dataPtr+= 4;
		    stage= rFormat;
		}
		else {
		    for (i= 0; i < dataLength; i++, dataPtr++) {
			length|= MakeUInt32Byte(*dataPtr, i);
		    }
		    return 0x0FFFFFFFF;		// Warning: quick exit.
		}
		break;
	    case rFormat:
		if (dataLength > 1) {
		    format= MakeUInt16(dataPtr);
		    dataLength-= 2; dataPtr+= 2;
		    stage= rData;
		}
		else {
		    format= MakeUInt32Byte(*dataPtr, 0);
		    return 0x0FFFFFFFF;		// Warning: quick exit.
		}
		break;
	    case rData:
		    // TMPTMP: Accept messages with body smaller than 64k while not using buckets.
		if (length < (2 << 16)) {
		    body= new unsigned char[length];	// TMPTMP: Replace by heap-managed buckets.
		    if (length > dataLength) {
			memcpy(body, dataPtr, dataLength);
			return 0x0FFFFFFFF;
		    }
		    else {
			memcpy(body, dataPtr, length);
			return (dataLength - length);
		    }
		}
		else return 0x0FFFFFFFE;		// Warning: quick exit.
		break;
	    case fillID:
		if (dataLength > (4-readSoFar)) {
		    for (i= readSoFar; i < 4; i++, dataPtr++) {
			msgID|= MakeUInt32Byte(*dataPtr, i);
		    }
		    stage= rLength;
		}
		else {
		    for (i= 0; i < dataLength; i++, dataPtr++) {
			msgID|= MakeUInt32Byte(*dataPtr, i+readSoFar);
		    }
		    return 0x0FFFFFFFF;		// Warning: quick exit.
		}
		break;
	    case fillLength:
		readSoFar-= 4;
		if (dataLength > (4-readSoFar)) {
		    for (i= readSoFar; i < 4; i++, dataPtr++) {
			length|= MakeUInt32Byte(*dataPtr, i);
		    }
		    stage= rFormat;
		}
		else {
		    for (i= 0; i < dataLength; i++, dataPtr++) {
			length|= MakeUInt32Byte(*dataPtr, i+readSoFar);
		    }
		    return 0x0FFFFFFFF;		// Warning: quick exit.
		}
		break;
	    case fillFormat:
		readSoFar-= 8;
		if (dataLength > (2-readSoFar)) {
		    for (i= readSoFar; i < 2; i++, dataPtr++) {
			length|= MakeUInt32Byte(*dataPtr, i);
		    }
		    stage= rData;
		}
		else {
		    for (i= 0; i < dataLength; i++, dataPtr++) {
			length|= MakeUInt32Byte(*dataPtr, i+readSoFar);
		    }
		    return 0x0FFFFFFFF;		// Warning: quick exit.
		}
		break;
	    case fillData:
		readSoFar-= 10;
		if (length > (dataLength + readSoFar)) {
		    memcpy(body + readSoFar, dataPtr, dataLength);
		    return 0x0FFFFFFFF;		// Warning: quick exit.
		}
		else {
		    memcpy(body + readSoFar, dataPtr, length - readSoFar);
		    return (dataLength - (length - readSoFar));
		}
		break;
	    default:
		noError= false;
		break;
	}
    } while (noError);

    return 0x0FFFFFFFD;		// If we get here, something went wrong in the extraction loop.
}
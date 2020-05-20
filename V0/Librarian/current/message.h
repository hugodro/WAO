#ifndef _AKMESSAGE_H_
#define _AKMESSAGE_H_
/**************************************************
* File: message.h.
* Desc: Definition of the AkMessage class.
* Module: WAO : Librarian.
* Rev: 29 juin 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include <akra/portableDefs.h>


class AkMessage : public AkObject {
  public:
    enum ExtractStage {
	rID, rLength, rFormat, rData
	, fillID, fillLength, fillFormat, fillData
    };

    friend class AkSocketChannel;
  protected:		// Instance variables.
    AkMessage *next;
	// ATTN: 'unsigned int' is taken to be 32 bits long, and 'short' to be 16 bits.
    unsigned int msgID;
    unsigned int length;
    unsigned short format;
    unsigned char *body;		// TMPTMP: Replace by heap-managed buckets.

  public:			// Instance methods.
    AkMessage(void);
    virtual ~AkMessage(void);
    virtual unsigned int extract(unsigned char *dataPtr, unsigned int dataLength, unsigned int readSoFar);

};


#endif		/* _AKMESSAGE_H_ */

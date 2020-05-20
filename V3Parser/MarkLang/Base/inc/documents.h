#ifndef _XTN_HB_DOCUMENTS_H_
#define _XTN_HB_DOCUMENTS_H_
/*******************************************
 * File: documents.h.
 * Desc: Definition of the xtnHBDoc and xtnMLDoc class.
 * History: 2000/05/13 : REV 0 : [HD] : Creation.
******************************************/

#include <exportDefs.h>

/*****************************************
* Class: xtnHBDoc.
* Super-Class: nil.
* Desc: Container for replies from HomeBases.
*****************************************/

class ClExp xtnHBDoc {
  public:
    enum Constants {
	maxDocSize= 16384
    };

  protected:
    xtnHBDoc *next;	// Next document part.
    char *contentData;
    unsigned int contentLength;
    unsigned int useCount;
    bool cacheable;

  public:
    xtnHBDoc(void);
    xtnHBDoc(char *someData, unsigned int length);
    virtual ~xtnHBDoc(void);

    virtual unsigned int getClass(void);
    virtual bool loadFromFile(char *fileName);
    virtual unsigned int spitInto(char *aBuffer, unsigned int maxLength);

    inline char *getData(void) { return contentData; }
    inline unsigned int getLength(void) { return contentLength; }
    inline xtnHBDoc *getNext(void) { return next; }
    inline void acquire(void) { useCount++; }
    inline void release(void) { if (useCount > 0) useCount--; }
    inline bool isUsed(void) { return (useCount > 0); }
};


/*****************************************
* Class: xtnMLDoc.
* Super-Class: nil.
* Desc: Generic class for marked-up documents returned by HB.
*****************************************/

class ClExp xtnMLDoc : public xtnHBDoc {
  public:
    xtnMLDoc(void);
    xtnMLDoc(char *someData, unsigned int length);
    virtual unsigned int getClass(void);
};

#endif    /* _XTN_HB_DOCUMENTS_H_ */

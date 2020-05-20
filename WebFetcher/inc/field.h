#ifndef _HTTP_FIELD_VARIABLE_H_
#define _HTTP_FIELD_VARIABLE_H_
/**************************************************
* File: fieldVar.h.
* Desc: Definition of the FieldVariable class.
* Module: Utils : WebFetcher .
* Rev: 25 mars 2000 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include <akra/portableDefs.h>


class FieldVar : public AkObject {
    enum ValueType {
        vtChar, vtInteger, vtFloat, vtArray
    };

  protected:
    char *name;
    void *content;
    ValueType dataType;

  public:
    FieldVar(char *aName);
    ~FieldVar(void);
    bool setValue(void *data, ValueType aType);

    inline ValueType getType(void) { return dataType; }
    inline char *getName(void) { return name; }
    inline void *getValue(void) { return content; }
};


#endif	/* _HTTP_FIELD_VARIABLE_H_ */

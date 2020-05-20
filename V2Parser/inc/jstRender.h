#ifndef _JST_RENDER_H_
#define _JST_RENDER_H_
/**************************************************
* File: jstRender.h.
* Desc: Definition of the Html-to-Jst instance archives engine.
* Module: WAO : SgmlParser.
* Rev: 10 septembre 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include "htmlDTD.h"
#include "sgmlRenderer.h"


class JVInstance;
class ClassFile;
class JVCup;
class JstFileArchiver;
class JVVariable;
class JVMachine;


class InstanceContainer : public AkObject {
    friend class JstRenderer;
  protected:
    InstanceContainer *previous;
    JVInstance *instance;
    unsigned int currentIndex;

  public:
    InstanceContainer(JVInstance *anInstance, InstanceContainer *parent);
};


class JstRenderer : public SgmlRenderer {
  protected:
    static char *htmlClassNames[HtmlDTD::numOfElements+4];
    static ClassFile *htmlClasses[HtmlDTD::numOfElements+4];
    static ClassFile *attributeClass;
    static ClassFile *stringClass;
    static ClassFile *baseElementClass;
    static JVVariable *subElementsField, *attributesField;
    static JVVariable *attrNameField, *attrValueField;
    static JVVariable *pcDataValueField, *commentValueField;

  protected:
    static void initHtmlClasses(JVCup *anEngine);

  protected:
    JVMachine *machine;
    JstFileArchiver *archiver;
    InstanceContainer *stack;
    char *outputName;
    JVInstance *rootInstance;

  public:
    JstRenderer(char *aName);
    virtual ~JstRenderer(void);
    virtual bool initialize(JVCup *anEngine);
    virtual void renderDoc(SgmlDoc *aDoc);
    virtual void renderStartOf(SgmlElement *anElement);
    virtual void renderEndOf(SgmlElement *anElement);
};


#endif	/*  _JST_RENDER_H_ */

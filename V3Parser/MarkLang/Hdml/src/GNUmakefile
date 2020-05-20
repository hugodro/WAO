#------------------------------------------------------------------------------
# Copyright (c) 2000 Extenta, Inc.
#
#------------------------------------------------------------------------------

PACKAGE = Hdml

include $(XTNTAPROJ)/Soft/Generic/$(MAKE_TRGT)/defs.mk

ADD_CFLAGS+= /DDLL
CXXOBJS= $(OBJDIR)/allHdmlElements.$(OBJ_SUFFIX) \
	$(OBJDIR)/container.$(OBJ_SUFFIX) \
	$(OBJDIR)/hdAnalyzer.$(OBJ_SUFFIX) \
	$(OBJDIR)/hdDTD.$(OBJ_SUFFIX) \
	$(OBJDIR)/hdDoc.$(OBJ_SUFFIX) \
	$(OBJDIR)/hdElement.$(OBJ_SUFFIX) \
	$(OBJDIR)/hdElementDef.$(OBJ_SUFFIX) \
	$(OBJDIR)/hdRender.$(OBJ_SUFFIX) \
	$(OBJDIR)/hdmlPage.$(OBJ_SUFFIX)

DLL_LIBS= /libpath:$(LIBDIR) libMarkLng.lib libHttpSup.lib

LIBTARGET = $(LIBDIR)/lib$(PACKAGE)$(LIB_DYN_SUFFIX)

.PHONY : all
all : $(LIBTARGET)

.PHONY : clean
clean :
	-@rm -rf $(OBJDIR)/*.$(OBJ_SUFFIX)
	-@rm -rf $(LIBTARGET)

include $(XTNTAPROJ)/Soft/Generic/$(MAKE_TRGT)/rules.mk



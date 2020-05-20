#------------------------------------------------------------------------------
# Copyright (c) 2000 Extenta, Inc.
#
#------------------------------------------------------------------------------

PACKAGE = Wml

include $(XTNTAPROJ)/Soft/Generic/$(MAKE_TRGT)/defs.mk

ADD_CFLAGS+= /DDLL
CXXOBJS= $(OBJDIR)/container.$(OBJ_SUFFIX) \
	$(OBJDIR)/wAnalyzer.$(OBJ_SUFFIX) \
	$(OBJDIR)/wDTD.$(OBJ_SUFFIX) \
	$(OBJDIR)/wDoc.$(OBJ_SUFFIX) \
	$(OBJDIR)/wElement.$(OBJ_SUFFIX) \
	$(OBJDIR)/wElementDef.$(OBJ_SUFFIX) \
	$(OBJDIR)/wRender.$(OBJ_SUFFIX) \
	$(OBJDIR)/wTopElements.$(OBJ_SUFFIX) \
	$(OBJDIR)/wmlPage.$(OBJ_SUFFIX)

DLL_LIBS= /libpath:$(LIBDIR) libMarkLng.lib libHttpSup.lib

LIBTARGET = $(LIBDIR)/lib$(PACKAGE)$(LIB_DYN_SUFFIX)

.PHONY : all
all : $(LIBTARGET)

.PHONY : clean
clean :
	-@rm -rf $(OBJDIR)/*.o
	-@rm -rf $(LIBTARGET)

include $(XTNTAPROJ)/Soft/Generic/$(MAKE_TRGT)/rules.mk



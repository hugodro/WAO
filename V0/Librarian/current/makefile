#/************************************************
#* File: makefile.
#* Desc: Building definitions for the Librarian.

AKRAHOME= /Users/hugo/AkraLog/Projets
PLZENHOME= $(AKRAHOME)/Plzen
PROJECT= Librarian
ARCHITECTURE= next_i386

SRCS= main.cc librarian.cc wlibNotificator.cc \
	commCenter.cc socketChannel.cc notification.cc \
	message.cc
OBJS= main.o librarian.o wlibNotificator.o \
	commCenter.o socketChannel.o notification.o \
	message.o


ARCHPATH= $(PLZENHOME)/bins/$(ARCHITECTURE)/$(PROJECT)
VPATH= ../objs

INC= -I$(AKRAHOME) -I$(AKRAHOME)/Plzen
LIBS= -lg++
# Optional defines: YYDEBUG=1
CFLAGS= -g

CC= cc

.SUFFIXES: .c .cc

all: antoine

antoine: $(OBJS)
	$(CC)  $(CFLAGS) -o  ../objs/$@ $(OBJS) $(LIBS)

.c.o:
	$(CC) $(INC) $(CFLAGS) -o $(ARCHPATH)/$@ -c  $<

.cc.o:
	$(CC) $(INC) $(CFLAGS) -o $(ARCHPATH)/$@ -c  $<

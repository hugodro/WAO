# Makefile options inherited from Configure
###############
EXTRA_CFLAGS=
EXTRA_LDFLAGS=
EXTRA_LIBS=
EXTRA_INCLUDES= -I/Users/hugo/AkraLog/Projets/Plzen/include -I/Users/hugo/AkraLog/Projets
RANLIB='/bin/ranlib'
##Rule:STATUS=yes
##Rule:SOCKS4=no
##Rule:IRIXNIS=no
##Rule:IRIXN32=no
##Rule:PARANOID=no
##Rule:WANTHSREGEX=default
###############
###############
# Platform: NeXT
# Final Rules:
#  Rule WANTHSREGEX=yes
###############
CC=cc
OPTIM=
CFLAGS1= -DNEXT -g
INCLUDES1=
INCLUDES_DEPTH0=-Iregex -Ios/unix -Imain 
INCLUDES_DEPTH1=-I/Users/hugo/Developpement/apache_1.3b3/src/regex -I/Users/hugo/Developpement/apache_1.3b3/src/os/unix -I/Users/hugo/Developpement/apache_1.3b3/src/main 
INCLUDES_DEPTH2=-I../../regex -I../../os/unix -I../../main 
LIBS1=
LDFLAGS1=
BROKEN_BPRINTF_FLAGS=
REGLIB=regex/libregex.a
RANLIB=sleep 5; /bin/ranlib
SHELL=/bin/sh
OSDIR=os/unix
SUBDIRS=$(OSDIR) main ap modules regex
TARGET=httpd

#### End of Configure created section ####
CFLAGS=$(OPTIM) $(CFLAGS1) $(EXTRA_CFLAGS)
LIBS=$(EXTRA_LIBS) $(LIBS1)
INCLUDES=$(INCLUDES1) $(INCLUDES_DEPTH1) $(EXTRA_INCLUDES)
LDFLAGS=$(LDFLAGS1) $(EXTRA_LDFLAGS)
INCDIR=/Users/hugo/Developpement/apache_1.3b3/src/main
OBJS=mod_wao1.o waoLink.o
LIB=libwao.a

.SUFFIXES: .o .c .cc

all:	$(LIB)

$(LIB): $(OBJS)
	rm -f $@
	ar cr $@ $(OBJS)
	$(RANLIB) $@

.c.o:
	$(CC) -c $(INCLUDES) $(CFLAGS) $(SPACER) $<

.cc.o:
	$(CC) -c $(INCLUDES) $(CFLAGS) $(SPACER) $<

clean:
	rm -f *.o $(LIB)

$(OBJS): Makefile
# this is enough to get us a default Makefile

##############################
# Makefile for WM_sort root6 #
# J.G. Cubiss 10/06/2019     #
##############################

# Where to install
BINDIR=.

# compilation and link flags
CXX= $(shell root-config --cxx)
CFLAGS= $(shell root-config --cflags) -g2 -O3 -c -fPIC
LDFLAGS= $(shell root-config --glibs)

# Test for mac for libraries
UNAME = $(shell uname)
ifeq ($(UNAME), Darwin)
LDARGS = -shared -Wl,-install_name
else
LDARGS = -shared -Wl,-soname
endif

# Dependencies
DEPS=Makefile AnaDefs.hh Ana.hh AnaRoot.hh Linkdef.h

# List of objects needed
OBJS=AnaDict.o AnaMain.o Ana.o
LOBJS=AnaDict.o Ana.o

# Name of executable
EXE=anaSort

# Name of shared library
SHLIB=AnaRootLib.so

# Name of dictionary file
DICT=AnaDict.cc AnaDict_rdict.pcm

all: $(EXE) $(SHLIB)

compile:	clean	all	cleanobj

compileall:	cleandict	compile

#######################################################
AnaDict.cc:
	rootcint -f AnaDict.cc -c AnaRoot.hh Linkdef.h

AnaDict.o:	AnaDict.cc $(DEPS)
	$(CXX) $(CFLAGS) AnaDict.cc

AnaMain.o:	AnaMain.cc $(DEPS)
	$(CXX) $(CFLAGS) AnaMain.cc

Ana.o:	Ana.cc $(DEPS)
	$(CXX) $(CFLAGS) Ana.cc

#######################################################

$(EXE):		 $(OBJS) $(DEPS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(EXE)

$(SHLIB):	 $(OBJS)
	$(CXX) $(LDARGS),$(SHLIB) -o $(SHLIB) $(LOBJS) $(LDFLAGS)

clean:
	-rm -f *.o $(EXE) $(SHLIB) $(DICT)

cleanobj:
	-rm -f *.o

cleandict:
	-rm -f AnaDict.cc AnaDict.h

unpack: 
	tar zxvf pristine_sources.tgz
	for file in patches/*.patch ; do patch < $$file ; done

install: $(EXE)
	install -s -m 755 -o 0 -g 0 $(EXE) $(BINDIR)/$(EXE)

### Macros ###
NAME		= eda031_project
SRCDIR		= ../src
BINDIR		= ../bin
LIBDIR		= ../lib
INCDIR		= ../include
SRCS		= $(wildcard $(SRCDIR)/*.cc)
OBJS		= $(wildcard *.o)
DFILES		= $(patsubst $(SRCDIR)/%.cc,%.d,$(SRCS))
#VPATH		= src include					# Search path for all prerequisites.
VPATH		= $(SRCDIR) $(LIBDIR)
#DESTDIR	= bin
THISDIR		= $(shell basename `pwd`)
TAGFILE		= ../tags
PROGS		= prog0

# Compiler and compiler options:
CXX		=  g++
CC		=  $(CXX)		# For implicit linking rule.
OPTLVL		= 2			# Default is 2.
# Change with make -e DEBUG=false
DEBUG		= true
DEBUGOPT	= -ggdb
ERRFLAGS	= -Wall -W -Wmissing-braces -Wparentheses -Wold-style-cast
CXXFLAGS	=  -pipe $(OPTI) $(ERRFLAGS) -ansi -pedantic-errors -fstack-protector-all -z noexecstack
CXXFLAGS	+= $(ERRFLAGS)
#LDFLAGS	=
#LDLIBE		=

ifeq ($(DEBUG), true)
		CXXFLAGS += $(DEBUGOPT)
		LDFLAGS  += $(DEBUGOPT)
else
		CXXFLAGS += -O$(OPTLVL)
endif


## Targets ##
.PHONY: all clean help list tar doc install uninstall

# target: all - Make all executable programs.
all: $(PROGS)

# target: help - Display all targets.
help :
		egrep "#\starget:" [Mm]akefile	| cut -d " " -f3-

# target: clean - Remove all objects.
clean:
		$(RM) $(OBJS)
		$(RM) $(TAGFILE)
		$(RM) $(DFILES)

# target: clean - Remove all executables.
cleaner: clean
		$(RM) $(PROGS)

# target: install - Installs executables and libraries.
install: $(PROGS)
		 install $(PROGS) $(BINDIR)
		 install $(OBJS) $(LIBDIR)

# target: uninstall - Deletes all files installed by install-target.
uninstall:
		for prog in $(PROGS); do \
				$(RM) $(BINDIR)/$$prog; \
		done
		for obj in $(OBJS); do \
				$(RM) $(LIBDIR)/$$obj; \
		done
		#$(RM) lib/list.o

# target: list - List all source files.
list :
		ls -l $(SRCDIR)/*.{cc,h}

# target: tar - Pack all the files to a gzip'd tarball.
tar :
		tar pvczf ../../$(NAME).tar.gz -C .. .

# target: tar-src - Pack the source files only.
tar-src :
		tar pvczf ../../$(NAME).src.tar.gz $(SRCDIR) $(INCDIR)
# target: tags - Generate tags with ctags for all files.
tags :
		ctags -R -f $(TAGFILE) ../

# target: doc - Generate documentation.
doc :
		#doxygen ../src

# Generate Makefiles describing "name.cc"s dependencies.
%.d: %.cc
		@set -e; rm -f $@; \
		$(CXX) -MM $(CXXFLAGS) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$
include $(DFILES)

# Linking of $(PROGS)
prog0: prog0.o lib0.o

### Macros ###
NAME		= eda031_project
SRCDIR		= ../src
BINDIR		= ../bin
LIBDIR		= ../lib
INCDIR		= ../include
SRCS		= $(wildcard $(SRCDIR)/**/*.cc)
OBJS		= $(shell find -iname '*.o')
DFILES		= $(patsubst $(SRCDIR)/%.cc,%.d,$(SRCS))
VPATH		= $(SRCDIR) $(LIBDIR) 
THISDIR		= $(shell basename `pwd`)
TAGSFILE	= ../tags
PROGS		= client/client_main server/server_main

DBOBJS		= $(patsubst $(SRCDIR)/db/%.cc,db/%.o,$(wildcard $(SRCDIR)/db/*.cc))

# Compiler and compiler options:
CXX		=  $(shell hash clang++ 2>/dev/null && echo clang++ || echo g++)
CXX		=  g++ # LTH systems clang cant find system headers.
CC		=  $(CXX)		# For implicit linking rule.
OPTLVL		= 2			# Default is 2.
# Change with $make -e DEBUG=false
DEBUG		= true
DEBUGOPT	= -ggdb
ERRFLAGS	= -Wall -Wextra -Wmissing-braces -Wparentheses -Wold-style-cast
CXXFLAGS	= -pipe -ansi -pedantic-errors -fstack-protector-all
ifeq ($(CXX), g++) 
	CXXFLAGS +=  -z noexecstack
endif
CXXFLAGS	+= $(ERRFLAGS) -I$(SRCDIR)
#LDFLAGS	=
#LDLIBE		=

ifeq ($(DEBUG), true)
		CXXFLAGS += $(DEBUGOPT) -O0
		LDFLAGS  += $(DEBUGOPT)
else
		CXXFLAGS += -O$(OPTLVL)
endif


## Targets ##
.PHONY: all test run-test clean help list tar doc install uninstall

# target: all - Make all executable programs.
all: $(PROGS)

# target: help - Display all targets.
help :
		@egrep "#\starget:" [Mm]akefile	| cut -d " " -f3-

# target: test - Compile all tests
test: test/test_db

run-test: test
	./test/test_db
# target: clean - Remove all objects.
clean:
		$(RM) $(OBJS)
		$(RM) $(TAGSFILE)
		#$(RM) $(DFILES)
		find . -iregex '.*\.d\(\.[0-9]+\)?$$' -exec rm \{\} \;

# target: clean - Remove all executables.
cleaner: clean
		$(RM) $(PROGS)
		#$(RM) -r $(fileter $(shell find . -type d),.) # Useless with include($(DFILES)).

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
		@find ../src/ -iregex '.*\.\(cc\|h\)'

# target: tar - Pack all the files to a gzip'd tarball.
tar :
		tar pvczf ../../$(NAME).tar.gz -C .. .

# target: tar-src - Pack the source files only.
tar-src :
		#tar pvczf ../../$(NAME).src.tar.gz $(SRCDIR) $(INCDIR)
		tar pvczf ../../$(NAME).src.tar.gz $(SRCDIR)
# target: tags - Generate tags with ctags for all files.
tags :
		ctags -R --tag-relative=yes -f $(TAGSFILE) ../

# target: doc - Generate documentation.
doc :
		#doxygen ../src

# Generate Makefiles describing "name.cc"s dependencies.
# The double escaped `echo` is needed because the normal .o : .c implicit rule will not be invoked when target is not in the same directory as prerequisite.
%.d: %.cc
	@set -e; rm -f $@; \
	mkdir -p $(shell echo $< | sed -e "s/\.\.\/src\/\(.*\)\/[-_[:alnum:]]*\.cc/\1/g"); \
	$(CXX) -MM $(CXXFLAGS) $< > $@.$$$$; \
	sed 's,\(.*\)\.o[ :]*,$(shell echo $< | sed -e "s/\.\.\/src\/\(.*\)\/[-_[:alnum:]]*\.cc/\1/g")\/\1.o $@ : ,g' < $@.$$$$ > $@; \
	echo "	\$$(CXX) \$$(CXXFLAGS) -c -o \$$(patsubst %.d,%.o,\$$@) \$$<" >> $@; \
	rm -f $@.$$$$
include $(DFILES)

# Linking of $(PROGS)
client/client_main: client/client_main.o
server/server_main: server/server_main.o server/server.o server/server_message_interpreter.o net/connection.o net/messagehandler.o $(DBOBJS)

# Linking of tests
test/test_db: test/test_db.o net/connection.o $(DBOBJS)

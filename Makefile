#!/usr/bin/make

# Help: --
# Type 'make help' for tips using this Makefile.

# Fairly simple Makefile. Source files either become programs, or they go into
# the convenience library, against which the programs are linked.

# Help: Try setting CXX, CXXFLAGS etc. https://www.gnu.org/software/make/manual/html_node/Implicit-Variables.html
# If no flags are set (?=), use at least these.
CXXFLAGS ?= -Wall -std=c++23 -pthread -lncurses

# Help: Try: 'make PCH=off' to disable precompiled headers. Or comment out in Makefile.
# Help: always do: 'make clean' when switching from PCH to no PCH or the other way around.
PCH ?= true

# To build non-C++ programs, append here. And perhaps add rules.
PROGRAMS = $(CXX_PROGRAMS)

# We build a static convenience library. The linker needs flags to find it.
# Notice that it's ok to use LIBNAME before setting it.
LDFLAGS += -L. -l$(LIBNAME)

SET_VERSION := $(lastword $(shell grep ^Set ../metadata.txt))
SET_VERSION := $(if $(SET_VERSION),$(SET_VERSION),-unknown)

# Make treats spaces as separators. But we really need a space.
SPACE := $(subst ,, )
# From e.g. '.cc .cpp', builds: 'name \*.cc -o -name \*.cpp'.
BUILD_FIND_EXPR = $(subst .,-name \*.,$(subst $(SPACE), -o ,$(strip $(1))))

# Multiple extensions will be compiled by $(CXX) ( = 'g++' by default).
# But it's dumb to have e.g. both foo.cc and foo.cpp.
CXX_SRC_EXTENSIONS := .cc .cpp .cxx .C
CXX_HEADER_EXTENSIONS := .h .hh .hpp .H
TXT_EXTENSIONS := .txt
# We recursively scan the entire directory for source files.
CXX_SOURCES := $(patsubst ./%,%,$(shell find . -type f $(call BUILD_FIND_EXPR,$(CXX_SRC_EXTENSIONS))))
# Header extensions only for order.txt.
CXX_HEADERS := $(patsubst ./%,%,$(shell find . -type f $(call BUILD_FIND_EXPR,$(CXX_HEADER_EXTENSIONS))))
TXT_FILES := $(patsubst ./%,%,$(shell find . -type f $(call BUILD_FIND_EXPR,$(TXT_EXTENSIONS))))
# Turns foo.* into foo.o
OBJ_OF_SRC = $(addsuffix .o,$(basename $(1)))
# Consequently, obj of foo.cc is foo.o
CXX_OBJECTS = $(call OBJ_OF_SRC,$(CXX_SOURCES))
# Turns foo.cc into $(DEPDIR)/foo.cc.dep
DEP_OF_CXX_SRC = $(patsubst %,$(DEPDIR)/%.dep,$(1))
# Dependency generation is side effect of compilation.
CXX_OBJ_DEPS = $(call DEP_OF_CXX_SRC,$(CXX_SOURCES))
# Files to put in order.txt
ORDERABLE_FILES = $(TXT_FILES) $(CXX_HEADERS) $(CXX_INTERNAL_HEADERS) $(CXX_LIBSOURCES) $(CXX_PROGSOURCES)

# If it has a 'main' function, it's a program.
MAIN_REGEX = '^[[:space:]]*int[[:space:]]+main[[:space:]]*[(]'
# /dev/null is sentinel in case no source files found.
CXX_PROG_SOURCES = $(shell grep -lE $(MAIN_REGEX) $(CXX_SOURCES) /dev/null)
CXX_PROGRAMS = $(basename $(CXX_PROG_SOURCES))

# Whatever is not a program source goes into the convenience library.
CXX_LIBSOURCES = $(filter-out $(CXX_PROG_SOURCES),$(CXX_SOURCES))
CXX_LIBOBJECTS = $(addsuffix .o,$(basename $(CXX_LIBSOURCES)))

# Stick to one filename extension for internal headers. We detect it here.
CXX_IH_EXT := $(suffix $(word 1,$(shell find . -type f \( -name \*.ih -o -name \*.ihh -o -name \*.iH \)) sentinel.ihh))
CXX_INTERNAL_HEADERS = $(patsubst ./%,%,$(shell find . -type f -name \*$(CXX_IH_EXT)))

# Precompiled headers are on by default.
CXX_PCH_EXT = .gch
CXX_PRECOMPILED_HEADERS = $(patsubst %,%$(CXX_PCH_EXT),$(CXX_INTERNAL_HEADERS))
CXX_PCH_DEPS = $(patsubst %,$(DEPDIR)/%.dep,$(CXX_INTERNAL_HEADERS))

# FixMe: This is GNU-g++-specific. Disable PCH if clang++ is used.
# FixMe: to save time in small compiles, disable pch if goals are specified on the command line.

# Name of our convenience library and the file containing it.
LIBNAME = proj
LIBRARY = lib$(LIBNAME).a

# When compiling, generate dependency listings, too.
DEPFLAGS = -MQ $@ -MMD -MP -MF $(DEPDIR)/$<.dep
DEPDIR = generated_deps

# When used, ensures dependency directories exist.
ENSURE_DEPDIR = $(shell test -d $(dir $(DEPDIR)/$@) || mkdir -p $(dir $(DEPDIR)/$@))

# This is for 'make show'.
EDGES = $(DEPDIR)/build.edges
ADD_EDGES = $(foreach PREREQ,$^,$(file >> $(EDGES),"$(PREREQ)" -> "$@" [label = "$(ACTION)"]))

# There are many words for true and false. But all other words cause an error.
boolalpha = $(or \
   $(if $(filter $(1),t true  True  TRUE  yes Yes YES YESS! on  On  ON  one  One  ONE  1),true,),\
   $(if $(filter $(1),f false False FALSE no  No  NO  NOO!  off Off OFF zero Zero ZERO 0),false,),\
   $(if $(strip $(1)),,false),\
   $(error cannot interpret $(1) as boolean)\
)

# Help: Try: 'VERBOSE=1 make'
QUIET := $(if $(filter true,$(call boolalpha,$(VERBOSE))),,@)

# If there are no programs, at least build the library.
ALL = $(if $(PROGRAMS),$(PROGRAMS),$(LIBRARY))
# The default target (by convention called 'all').
all: $(ALL)

# Phony targets. Build 'all' even if a file 'all' accidentally exists.
.PHONY: all

# Build programs by linking their object files against the convenience library.
# This is a static pattern rule:
# https://www.gnu.org/software/make/manual/html_node/Static-Usage.html#Static-Usage
# Call the linker through the compiler, not directly.
$(CXX_PROGRAMS): %: %.o $(LIBRARY)
	@printf "\t[Linking $@]\n"
	$(ENSURE_DEPDIR)
	$(QUIET) $(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)
	@$(ADD_EDGES)
$(CXX_PROGRAMS): ACTION = link

# The library contains all object files that don't become programs.
$(LIBRARY): $(CXX_LIBOBJECTS)
	@printf "\t[Composing $@]\n"
	$(ENSURE_DEPDIR)
	$(QUIET) ar rcs $@ $^
	@$(ADD_EDGES)
$(LIBRARY): ACTION = gather

$(CXX_OBJECTS): ACTION = compile

# Build precompiled headers from internal headers.
$(CXX_PRECOMPILED_HEADERS): %$(CXX_IH_EXT)$(CXX_PCH_EXT): %$(CXX_IH_EXT)
	@printf "\t[Precompiling $@]\n"
	$(ENSURE_DEPDIR)
	$(QUIET) $(CXX) $(CXXFLAGS) $(DEPFLAGS) -x c++-header -o $@ $<
	@$(ADD_EDGES)

# The use of $(DEPFLAGS) causes a dependency file to also be written.
# (But, importantly, Make is not aware of that that!)
define CXX_RECIPE
	@printf "\t[Compiling $@]\n"
	$(ENSURE_DEPDIR)
	$(QUIET) $(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEPFLAGS) -c -o $@ $<
	$(CXX_PCH_POSTDEP)
	@$(ADD_EDGES)
endef

# Pattern rules for various C++ extensions. Use the same recipe each time.
%.o: %.cc
	$(CXX_RECIPE)
%.o: %.cpp
	$(CXX_RECIPE)
%.o: %.cxx
	$(CXX_RECIPE)
%.o: %.C
	$(CXX_RECIPE)

order.txt: $(filter-out order.txt,$(ORDERABLE_FILES))
	$(QUIET) test -e $@|| touch $@
	$(QUIET) sed -i -e :a -e '/^\n*$$/{$$d;N;};/\n$$/ba' $@
	$(QUIET) tail -1 $@|grep -qx ^$||echo >> $@
	$(QUIET) for F in $^ ; do grep -qx $${F} $@ || echo $${F} >> $@ ; done
	$(QUIET) echo "Order.txt was updated. Please edit it by hand."

../../set$(SET_VERSION).zip: ../metadata.txt $(patsubst %,%/order.txt,$(shell find .. -mindepth 1 -maxdepth 1 -type d))
	cd .. \
 && (echo metadata.txt \
 && find -mindepth 2 -maxdepth 2 -type f -name order.txt \
 && find -mindepth 1 -maxdepth 1 -type d \
   | xargs -I%d find %d -type f -name order.txt -exec sed -E '/^[[:space:]]*$$/ d; s/^[[:space:]]*//; s#^#%d/#' {} \; ) \
   | zip $(ZIPFLAGS) --must-match --names-stdin $(patsubst ../%,%,$@)

buildgraph.dot: all
	echo "digraph " > $@
	echo "{" >> $@
	echo "rankdir = LR;" >> $@
	echo "concentrate = true" >> $@
	echo "{rank = same; $(foreach SRC,$(CXX_SOURCES), \"$(SRC)\";) }" >> $@
	cat $(EDGES) >> $@
	find generated_deps/ -type f -name \*.dep -exec cat {} \;\
          |grep -v ':$$'\
          |tr -d ':'\
          |tr -s ' '\
          |awk '{for(i=NF;i>=1;i--) printf "\"%s\" ", $$i;print ""}'\
          |sed -e :a -e '/\\$/N; s/\\\n//; ta'\
          |sed 's/[[:space:]]*$$//g ; s/ / -> /g ; s/$$//' \
           >> $@
	echo "}" >> $@
	cat $@

# Help: Try: 'make show' to get a dependency graph - sort of.
show: buildgraph.dot
	xdot $<

HELP_EXPR = ^\#[[:space:]]*Help:[[:space:]]*
help:
	@sed -E -n '/$(HELP_EXPR)/ { s/$(HELP_EXPR)/  / ; p }' $(word 1,$(MAKEFILE_LIST))

.PHONY: show help

# 'make clean' removes all generated files.
clean: depclean pchclean
	rm -f $(PROGRAMS) $(CXX_OBJECTS) $(LIBRARY) buildgraph.dot $(LIBRARY) $(CXX_PRECOMPILED_HEADERS)

depclean:
	rm -rf $(DEPDIR)

pchclean:
	rm -f $(CXX_PRECOMPILED_HEADERS)

# Thorough cleaning. Also removes straggling objects and executables, among others... Modify on a Mac to find MACH executables.
distclean: clean
	rm -f $(patsubst ./%,%,$(shell find . -type f \( -name \*$(CXX_PCH_EXT) -o -name \*.o -o -name \*~ -o -name lib\*.a -o -exec sh -c 'file {}|grep -q ELF' \; -print \)))

# Even if a file 'clean' should exist, run the recipe anyway.
.PHONY: clean depclean pchclean distclean order.txt cppzip

ifeq (true,$(call boolalpha,$(PCH)))
    # When using PCHs ...
    CXXFLAGS += -Winvalid-pch
    DEPFLAGS += -fpch-deps

    # If no goals were specified on the command line,
    # or if they were, but weren't all 'clean' goals, include PCHDEPs.
    NOPCH_GOALS = clean depclean distclean pchclean help zip order.txt ../../set$(SET_VERSION).zip
    ifneq (,$(or $(if $(MAKECMDGOALS),,empty),$(filter-out $(NOPCH_GOALS),$(MAKECMDGOALS))))
        # Include all PCH deps. They are side effects of compiling a PCH from an IH.
        -include $(CXX_PCH_DEPS)
        # So trigger compilation of PCH deps by making PCHDEPS require PCHs. (Empty recipe so no rebuild.)
        $(CXX_PCH_DEPS): $(CXX_PRECOMPILED_HEADERS);
    endif
    # With precompiled headers, foo/*.o depends on foo/internal.ih.ghc, not on foo/internal.ih directly.
    # Make the generated deps (see below) reflect this:
    CXX_PCH_POSTDEP = $(QUIET) sed -E -i 's/\$(CXX_IH_EXT)\b([^:])/$(CXX_IH_EXT)$(CXX_PCH_EXT)\1/g' $(call DEP_OF_CXX_SRC,$<)
    # ^ Any .ih, if not before a ':', gets replace by .ih.gch
else
    # When not using PCHs, PostDep is a no-op.
    CXX_PCH_POSTDEP := $(QUIET) true
endif

# Source files need to be recompiled when header files that they include are
# newer than the object. Including the generated dependency files ensures this.
# If make has run previously, $(DEPDIR) will exist.
ifneq (,$(wildcard $(DEPDIR)))

    # They list the dependencies of source files on the headers they include,
    # which ensures that sources that include foo.hh have their objects rebuilt
    # when foo.hh is newer. Thus we need run 'make clean' less often.
    -include $(CXX_OBJ_DEPS)

    # Don't let Make try to rebuild the .deps. (We don't even tell it how to,
    # but it would try to find a rule for them anyway.)
    $(CXX_OBJ_DEPS):;
endif

# Also block any attempts to remake the Makefile itself.
Makefile:;

# Help: --
# Help: more help: https://www.gnu.org/software/make/manual/html_node/index.html
# Help: more help: https://www.gnu.org/software/make/manual/html_node/Reading-Makefiles.html

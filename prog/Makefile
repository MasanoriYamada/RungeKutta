### User modification part START ###############################
#####  OPTIONS  ################################################

use_mpi = no
use_debug = no

inc_dirs= ../include ../lib
src_dirs = ./
build_dirs=./
target = RungeKutta.out

### User modification part END #################################
#####  GNU C/C++  ##############################################


ifeq ($(use_mpi),yes)
CXX = openmpic++
#CXX = mpic++
else
CXX = g++
endif

ifeq ($(use_debug),yes)
CXXFLAGS = -g -O0 -Wall -Wno-unused
CPP_DEFS += -DDEBUG
else
CXXFLAGS = -O3
CPP_DEFS += -DRELEASE
endif

LD = $(CXX)
#LDFLAGS =
LDLIBS = -lm $(EXTRA_LIBS)

CXXDEP = $(CXX)

CONFIGFLAGS = CC=gcc
CONFIGFLAGS += CFLAGS=-O3


###################################################################

#
sources = $(wildcard $(addsuffix /*.cpp, $(src_dirs)))
includes = $(wildcard $(addsuffix /*.h, $(inc_dirs)))
program = $(target)
CPPFLAGS = $(addprefix -I, $(inc_dirs))
CPPFLAGS += $(EXTRA_INCLUDES)
CPPFLAGS += $(CPP_DEFS)

# make all.
.PHONY: all msg
all: msg $(program)

# main target.
$(program): $(sources) 
	$(CXX) $(LDFLAGS) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

msg:
	@echo "----------------------------------------------------------------"
	@echo "Compilation Environment Summary"
	@echo
	@echo "Options:"
	@echo "  use_mpi          =" $(use_mpi)
	@echo "  use_debug        =" $(use_debug)
	@echo "  target           =" $(target)
	@echo
	@echo "Compiler and options:"
	@echo "  CXX         =" $(CXX)
	@echo "  CXXFLAGS    =" $(CXXFLAGS)
	@echo "  LD          =" $(LD)
	@echo "  LDFLAGS     =" $(LDFLAGS)
	@echo "  LDLIBS      =" $(LDLIBS)
	@echo "  CXXDEP      =" $(CXXDEP)
	@echo "  CXXDEPFLAGS =" $(CXXDEPFLAGS)
	@echo "  CONFIGFLAGS =" $(CONFIGFLAGS)
	@echo "Reading file:"
	@echo "  Source file =" $(sources)
	@echo "  Include file =" $(includes)
	@echo "----------------------------------------------------------------"

#for flymake
PHONY: check-syntax
check-syntax:
	$(CXX) $(LDFLAGS) -Wall -Wextra -pedantic -fsyntax-only $(CHK_SOURCES)

clean:
	@rm -rf $(target) *.out *.o *~ *.bak *.deps *.dSYM

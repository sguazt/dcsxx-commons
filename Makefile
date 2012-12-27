## This is the makefile for the dcsxx-commons project.
##
##
## When used the first time, check the sections "CUSTOM SETTINGS" and "ALMOST
## FIXED SETTING" below to see if default settings fit your configuration.
##
## Copyright (C) 2009-2012  Distributed Computing System (DCS) Group,
##                          Computer Science Institute,
##                          Department of Science and Technological Innovation,
##                          University of Piemonte Orientale,
##                          Alessandria (Italy).
##
## This program is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published
## by the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.
##
##
## Author: Marco Guazzone (marco.guazzone@gmail.com)
##
##
## FIXME:
## * Auto-dependencies still does not work
## * Pre-compiled headers still does not work
##

## Create configuration stuff
ifneq ($(MAKECMDGOALS),clean)

$(info === Running configuration scripts ===)
user_config_check=$(shell scripts/return_value_of.sh test -f user-config.sh)
ifneq (0,$(user_config_check))
$(error Unable to create configurations. Missing 'user-config.sh' file.)
endif
config_ret=$(shell scripts/return_value_of.sh $(PWD)/scripts/config.sh $(CURDIR))
ifneq (0,$(config_ret))
$(error Unable to create configurations. Please check the log file.)
endif

endif


### CUSTOM SETTINGS
##
## Adjust the following if necessary:
## - builddir: path where storing build and bin files.
## - docdir: path where storing the documentation.
## - srcdir: path where are located source files.
## - testdir: path where are located test files.
## - xmpdir: path where are located examples files.
## - incdirs: list of include paths.
## - libdirs: list of library paths.
## - libs: list of libraries to link in.
## - srcdirs: list of source paths.
## - target: target executable's filename.
export target := none
export docdir := ./docs
export srcdir := ./src
export builddir := ./build
export testdir := ./test
export test_srcdir := $(testdir)/src
export test_builddir := ./build
export xmpdir := ./examples
export xmp_srcdir := $(xmpdir)/src
export xmp_builddir := ./build
export srcdirs := . #dcs dcs/config dcs/control dcs/math dcs/meta
#export test_srcdirs := . dcs/des dcs/iterator dcs/math/la dcs/math/random dcs/math/stats dcs/util
#export test_srcdirs := . dcs/algorithm dcs/iterator dcs/math/la dcs/math/random dcs/math/stats
export test_srcdirs := . dcs/test dcs/test/algorithm dcs/test/iterator dcs/test/math dcs/test/math/random dcs/test/math/stats dcs/test/math/type dcs/test/system
export xmp_srcdirs := . dcs/des dcs/des/simple_simulator dcs/des dcs/des/bank
export libdirs :=
export test_libdirs :=
export xmp_libdirs :=
export incdirs := ./inc
export test_incdirs := $(test_srcdir)/inc
export xmp_incdirs := $(xmpdir)/inc
export libs := m lapack
#export test_libs := boost_unit_test_framework
export test_libs :=
export xmp_libs := 


### ALMOST FIXED SETTINGS
##
## Now alter any implicit rules' variables if you like.
##
build := release
#build := debug
#bit := 32
#bit := 64
srcdirs := $(addprefix $(srcdir)/,$(srcdirs))
test_srcdirs := $(addprefix $(test_srcdir)/,$(test_srcdirs))
xmp_srcdirs := $(addprefix $(xmp_srcdir)/,$(xmp_srcdirs))
buildtmpdir := $(builddir)/.build
bindir_release := $(builddir)/release
bindir_debug := $(builddir)/debug
libsdir := ./libs
test_buildtmpdir := $(test_builddir)/.test_build
test_bindir := $(test_builddir)/test
xmp_buildtmpdir := $(xmp_builddir)/.examples_build
xmp_bindir := $(xmp_builddir)/examples
bin_ext :=
obj_ext := o
pch_ext := hpp.gch
use_pch := true
#use_pch := false
CLEANER := rm -rf
DOXYGEN := doxygen
CXXFLAGS_common = -Wall -Wextra -ansi -pedantic -DBOOST_UBLAS_TYPE_CHECK=0 $(addprefix -I, $(incdirs)) -I$(libsdir)/include
LDFLAGS_common = $(addprefix -L, $(libdirs)) -L$(libsdir)/lib $(addprefix -l,$(libs))
CPPFLAGS += -MD


### FIXED SETTINGS
##
## You shouldn't need to change anything below this point.
##
SOURCES := $(wildcard $(addsuffix /*.cpp,$(srcdirs)))
HEADERS := $(wildcard $(addsuffix /*.hpp,$(srcdirs)))
OBJS := $(patsubst $(srcdir)/%,$(buildtmpdir)/%,$(patsubst %.cpp,%.$(obj_ext),$(SOURCES)))
#DEPS := $(addprefix $(buildtmpdir)/,$(patsubst %.$(obj_ext),%.d,$(OBJS)))
DEPS := $(patsubst %.$(obj_ext),%.d,$(OBJS))
MISSING_DEPS := $(filter-out $(wildcard $(DEPS)),$(DEPS))
MISSING_DEPS_SOURCES := $(patsubst $(buildir),$(srcdir),$(patsubst %.d,%.cpp,$(MISSING_DEPS)))

## Load configuration stuff
ifneq ($(MAKECMDGOALS),clean)

include ./config.mk
include $(testdir)/include.mk
include $(xmpdir)/include.mk

endif

CXXFLAGS_debug += -g -O0 $(CXXFLAGS_common)
CXXFLAGS_release += -g0 -O3 -DNDEBUG $(CXXFLAGS_common)
CXXFLAGS_test += -g -O0 $(CXXFLAGS_common)
CXXFLAGS_xmp += -g -O0 $(CXXFLAGS_common)
LDFLAGS_debug += -g -O0 $(LDFLAGS_common)
LDFLAGS_release += -g0 -O3 $(LDFLAGS_common)
LDFLAGS_test += -g -O0 $(LDFLAGS_common) $(addprefix -L, $(test_libdirs)) $(addprefix -l,$(test_libs))
LDFLAGS_xmp += -g -O0 $(LDFLAGS_common) $(addprefix -L, $(xmp_libdirs)) $(addprefix -l,$(xmp_libs))

.DEFAULT_GOAL := all

# Uncomment for debugging this makefile
#$(info TARGET ==> $(target))
#$(info HEADERS ==> $(HEADERS))
#$(info SOURCES ==> $(SOURCES))
#$(info OBJS ==> $(OBJS))
#$(info DEPS ==> $(DEPS))
#$(info MISSING_DEPS ==> $(MISSING_DEPS))
#$(info MISSING_DEPS_SOURCES ==> $(MISSING_DEPS_SOURCES))
#$(info TEST SRCDIRS ==> $(test_srcdirs))
#$(info TEST BUILDTMPDIR ==> $(test_buildtmpdir))
#$(info TEST SOURCES ==> $(test_SOURCES))
#$(info TEST OBJS ==> $(test_OBJS))
#$(info TEST TARGETS ==> $(test_TARGETS))


.PHONY: all all-build all-debug all-release clean deps docs docs-clean objs realclean rebuild test test-clean test-dirs test-msg xmp xmp-clean xmp-dirs xmp-msg

all: all-debug

all-release: override build := release
all-release: CXXFLAGS := $(CXXFLAGS_release)
all-release: LDFLAGS := $(LDFLAGS_release)
all-release: $(bindir_release) $(bindir_release)/$(target)


all-debug: override build := debug
all-debug: CXXFLAGS := $(CXXFLAGS_debug)
all-debug: LDFLAGS := $(LDFLAGS_debug)
all-debug: $(bindir_debug) $(bindir_debug)/$(target)


#build-conf: config.sh
#	@$(SHELL) config.sh


deps : $(DEPS)


objs : $(OBJS)


docs:
	@echo "=== Building API documentation ==="
	@mkdir -p $(docdir)/apidoc
	$(DOXYGEN) Doxyfile


clean: test-clean xmp-clean
	@echo "=== Cleaning build files ==="
	@$(CLEANER) $(buildtmpdir)
	@$(CLEANER) $(bindir_debug)
	@$(CLEANER) $(bindir_release)


docs-clean:
	@echo "=== Cleaning doc files ==="
	@$(CLEANER) $(docdir)/apidoc


realclean: clean docs-clean
	@echo "=== Cleaning ==="
	@$(CLEANER) config.mk
	@$(CLEANER) config.sh.log
	@$(CLEANER) inc/dcs/detail/boost.hpp
	@$(CLEANER) inc/dcs/detail/config.hpp
	@$(CLEANER) inc/dcs/detail/version.hpp


rebuild: realclean all


## Targets rules

$(bindir_release)/$(target) : $(buildtmpdir) $(OBJS) $(HEADERS)
	@echo "=== Building Target: $@ ==="
#	$(CXX) $(LDFLAGS) -o $(bindir_release)/$(target) $(OBJS)


$(bindir_debug)/$(target) : $(buildtmpdir) $(OBJS) $(HEADERS)
	@echo "=== Building Target: $@ ==="
#	$(CXX) $(LDFLAGS) -o $(bindir_debug)/$(target) $(OBJS)


$(buildtmpdir) $(bindir_release) $(bindir_debug):
	@echo "Creating dir $@"
	@mkdir -p $@


## Test-related targets

test: override build := debug
test: CXXFLAGS := $(CXXFLAGS_test)
test: LDFLAGS := $(LDFLAGS_test)
test: test-msg test-dirs test-build
#test: test-msg all-build test-dirs $(test_TARGETS)

test-msg:
	@echo "=== Building Tests ==="


test-dirs:
	@mkdir -p $(test_buildtmpdir)
	@mkdir -p $(test_bindir)


#$(test_TARGETS): override CC=$(CXX)
#$(test_TARGETS): $(test_OBJS)
#	@mkdir -p $(dir $@)
#	$(CXX) $(LDFLAGS) -o $@ $@.o


test-clean:
	@echo "=== Cleaning test files ==="
	@$(CLEANER) $(test_buildtmpdir)
	@$(CLEANER) $(test_bindir)


## Examples-related targets

xmp: override build := debug
xmp: CXXFLAGS := $(CXXFLAGS_xmp)
xmp: LDFLAGS := $(LDFLAGS_xmp)
xmp: xmp-msg xmp-dirs xmp-build
#xmp: xmp-msg all-build xmp-dirs $(xmp_TARGETS)

xmp-msg:
	@echo "=== Building Examples ==="


xmp-dirs:
	@mkdir -p $(xmp_buildtmpdir)
	@mkdir -p $(xmp_bindir)


#$(xmp_TARGETS): override CC=$(CXX)
#$(xmp_TARGETS): $(xmp_OBJS)
#	@mkdir -p $(dir $@)
#	$(CXX) $(LDFLAGS) -o $@ $@.o


xmp-clean:
	@echo "=== Cleaning examples files ==="
	@$(CLEANER) $(xmp_buildtmpdir)
	@$(CLEANER) $(xmp_bindir)


## Source to Object rules

$(buildtmpdir)/%.$(obj_ext): $(srcdir)/%.cpp
	@echo "=== Compiling: $@ ==="
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ -c $<


## Header to Precompiled header rules

ifeq ($(use_pch),true)
$(buildtmpdir)/%.$(pch_ext): $(srcdir)/%.hpp
	@echo "=== Pre-compiling header: $@ ==="
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@
else
$(buildtmpdir)/%.$(pch_ext): ;
endif


## Source to Dependency rules

$(buildtmpdir)/%.d: $(srcdir)/%.cpp
	@echo "=== Creating dependencies file: $@ ==="
	@set -e; rm -f $@; \
		$(CXX) $(CPPFLAGS) $< > $@.$$$$; \
		sed ’s,\($*\)\.$(obj_ext)[ :]*,\1.$(obj_ext) $@ : ,g’ < $@.$$$$ > $@; \
		rm -f $@.$$$$


## Include files for auto-dependencies

ifneq ($(MISSING_DEPS),)
$(MISSING_DEPS) :
	@$(CLEANER) $(patsubst %.d,%.$(obj_ext),$@)
endif

-include $(DEPS)

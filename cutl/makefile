# file      : cutl/makefile
# author    : Boris Kolpackov <boris@codesynthesis.com>
# copyright : Copyright (c) 2009 Code Synthesis Tools CC
# license   : MIT; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../build/bootstrap.make

cxx_tun   := shared-ptr/base.cxx

cxx_tun   +=              \
compiler/context.cxx      \
compiler/type-info.cxx    \
compiler/cxx-indenter.cxx

cxx_obj   := $(addprefix $(out_base)/,$(cxx_tun:.cxx=.o))
cxx_od    := $(cxx_obj:.o=.o.d)

cutl.l             := $(out_base)/cutl.l
cutl.l.cpp-options := $(out_base)/cutl.l.cpp-options

clean     := $(out_base)/.clean


# Build.
#
$(cutl.l): $(cxx_obj)

$(cxx_obj) $(cxx_od): $(cutl.l.cpp-options)
$(cutl.l.cpp-options): value := -I$(src_root)

$(call include-dep,$(cxx_od))


# Convenience alias for default target.
#
$(out_base)/: $(cutl.l)


# Clean.
#
$(clean): $(cutl.l).o.clean          \
  $(cutl.l.cpp-options).clean        \
  $(addsuffix .cxx.clean,$(cxx_obj)) \
  $(addsuffix .cxx.clean,$(cxx_od))


# How to.
#
$(call include,$(bld_root)/cxx/o-l.make)
$(call include,$(bld_root)/cxx/cxx-o.make)
$(call include,$(bld_root)/cxx/cxx-d.make)

# file      : cutl/makefile
# author    : Boris Kolpackov <boris@codesynthesis.com>
# copyright : Copyright (c) 2009-2012 Code Synthesis Tools CC
# license   : MIT; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../build/bootstrap.make

sources   := exception.cxx shared-ptr/base.cxx

sources   += fs/exception.cxx fs/path.cxx fs/auto-remove.cxx

sources   += re/re.cxx

sources   +=              \
compiler/context.cxx      \
compiler/type-info.cxx    \
compiler/cxx-indenter.cxx

boost_sources   :=                                \
details/boost/regex/src/regex.cxx                 \
details/boost/regex/src/usinstances.cxx           \
details/boost/regex/src/regex_raw_buffer.cxx      \
details/boost/regex/src/fileiter.cxx              \
details/boost/regex/src/cpp_regex_traits.cxx      \
details/boost/regex/src/instances.cxx             \
details/boost/regex/src/wide_posix_api.cxx        \
details/boost/regex/src/regex_debug.cxx           \
details/boost/regex/src/c_regex_traits.cxx        \
details/boost/regex/src/posix_api.cxx             \
details/boost/regex/src/wc_regex_traits.cxx       \
details/boost/regex/src/cregex.cxx                \
details/boost/regex/src/w32_regex_traits.cxx      \
details/boost/regex/src/regex_traits_defaults.cxx \
details/boost/regex/src/static_mutex.cxx          \
details/boost/regex/src/icu.cxx                   \
details/boost/regex/src/winstances.cxx

cxx_tun   := $(sources) $(boost_sources)
cxx_obj   := $(addprefix $(out_base)/,$(cxx_tun:.cxx=.o))
cxx_od    := $(cxx_obj:.o=.o.d)

cutl.l             := $(out_base)/cutl.l
cutl.l.cpp-options := $(out_base)/cutl.l.cpp-options

default   := $(out_base)/
dist      := $(out_base)/.dist
install   := $(out_base)/.install
clean     := $(out_base)/.clean


# Build.
#
$(cutl.l): $(cxx_obj)

$(cxx_obj) $(cxx_od): $(cutl.l.cpp-options)
$(cutl.l.cpp-options): value := -I$(out_root) -I$(src_root)
$(cxx_obj) $(cxx_od): $(odb_tracer.l.cpp-options) $(out_base)/details/config.h

$(out_base)/details/config.h:
	@echo '// file      : cutl/details/config.h'               >$@
	@echo '// author    : automatically generated'            >>$@
	@echo ''                                                  >>$@
	@echo '#ifndef CUTL_DETAILS_CONFIG_H'                     >>$@
	@echo '#define CUTL_DETAILS_CONFIG_H'                     >>$@
	@echo ''                                                  >>$@
	@echo ''                                                  >>$@
	@echo '#endif // CUTL_DETAILS_CONFIG_H'                   >>$@

$(call include-dep,$(cxx_od),$(cxx_obj),$(out_base)/details/config.h)

# Convenience alias for default target.
#
$(out_base)/: $(cutl.l)

# Dist.
#
$(dist): export sources := $(sources)
$(dist): export boost_sources := $(boost_sources)
$(dist): export headers := $(subst $(src_base)/,,$(shell find $(src_base) \
-name '*.hxx' -o -name '*.ixx' -o -name '*.txx'))
$(dist): data_dist := details/config-vc.h $(subst $(src_base)/,,$(shell find \
$(src_base)/details/boost -type f -name '*.hpp')) details/boost/LICENSE \
details/boost/README
$(dist): export extra_dist := $(data_dist) libcutl-vc9.vcproj \
libcutl-vc10.vcxproj libcutl-vc10.vcxproj.filters
$(dist): export interface_version = $(shell sed -e \
's/^\([0-9]*\.[0-9]*\).*/\1/' $(src_root)/version)

$(dist):
	$(call dist-data,$(sources) $(boost_sources) $(headers) $(data_dist) details/config.h.in)
	$(call meta-vc9proj,libcutl-vc9.vcproj)
	$(call meta-vc10proj,libcutl-vc10.vcxproj)
	$(call meta-automake)

# Install.
#
$(install): $(cutl.l)
	$(call install-lib,$<,$(install_lib_dir)/$(ld_lib_prefix)cutl$(ld_lib_suffix))
	$(call install-dir,$(src_base),$(install_inc_dir)/cutl,\
'(' -name '*.hxx' -o -name '*.ixx' -o -name '*.txx' ')')
	$(call install-data,$(out_base)/details/config.h,\
$(install_inc_dir)/cutl/details/config.h)

# Clean.
#
$(clean): $(cutl.l).o.clean          \
  $(cutl.l.cpp-options).clean        \
  $(addsuffix .cxx.clean,$(cxx_obj)) \
  $(addsuffix .cxx.clean,$(cxx_od))
	$(call message,rm $$1,rm -f $$1,$(out_base)/details/config.h)

# Generated .gitignore.
#
ifeq ($(out_base),$(src_base))
$(cutl.l): | $(out_base)/.gitignore

$(out_base)/.gitignore: files := details/config.h
$(clean): $(out_base)/.gitignore.clean

$(call include,$(bld_root)/git/gitignore.make)
endif

# How to.
#
$(call include,$(bld_root)/dist.make)
$(call include,$(bld_root)/install.make)
$(call include,$(bld_root)/meta/vc9proj.make)
$(call include,$(bld_root)/meta/vc10proj.make)
$(call include,$(bld_root)/meta/automake.make)

$(call include,$(bld_root)/cxx/o-l.make)
$(call include,$(bld_root)/cxx/cxx-o.make)
$(call include,$(bld_root)/cxx/cxx-d.make)

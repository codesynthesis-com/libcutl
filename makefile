# file      : makefile
# author    : Boris Kolpackov <boris@codesynthesis.com>
# copyright : Copyright (c) 2009 Code Synthesis Tools CC
# license   : MIT; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))build/bootstrap.make

default  := $(out_base)/
test     := $(out_base)/.test
install  := $(out_base)/.install
clean    := $(out_base)/.clean

# Build.
#
$(default): $(out_base)/cutl/ $(out_base)/tests/

# Test.
#
$(test): $(out_base)/tests/.test

# Install.
#
$(install): $(out_base)/cutl/.install           \
            $(out_base)/doc/.install
	$(call install-data,$(src_base)/LICENSE,$(install_doc_dir)/libcutl/LICENSE)
	$(call install-data,$(src_base)/NEWS,$(install_doc_dir)/libcutl/NEWS)
	$(call install-data,$(src_base)/README,$(install_doc_dir)/libcutl/README)

# Clean.
#
$(clean): $(out_base)/cutl/.clean $(out_base)/tests/.clean

$(call include,$(bld_root)/install.make)

$(call import,$(src_base)/cutl/makefile)
$(call import,$(src_base)/tests/makefile)

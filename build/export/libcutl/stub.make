# file      : build/export/libcutl/stub.make
# license   : MIT; see accompanying LICENSE file

$(call include-once,$(src_root)/cutl/makefile,$(out_root))

$(call export,\
  l: $(out_root)/cutl/cutl.l,\
  cpp-options: $(out_root)/cutl/cutl.l.cpp-options)

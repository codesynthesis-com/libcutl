# file      : build/export/libcutl/stub.make
# author    : Boris Kolpackov <boris@codesynthesis.com>
# copyright : Copyright (c) 2009-2012 Code Synthesis Tools CC
# license   : MIT; see accompanying LICENSE file

$(call include-once,$(src_root)/cutl/makefile,$(out_root))

$(call export,\
  l: $(out_root)/cutl/cutl.l,\
  cpp-options: $(out_root)/cutl/cutl.l.cpp-options)

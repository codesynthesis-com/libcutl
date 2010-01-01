# file      : build/import/libcutl/configuration-rules.make
# author    : Boris Kolpackov <boris@codesynthesis.com>
# copyright : Copyright (c) 2009-2010 Code Synthesis Tools CC
# license   : MIT; see accompanying LICENSE file

$(dcf_root)/import/libcutl/configuration-dynamic.make: | $(dcf_root)/import/libcutl/.
	$(call message,,$(scf_root)/import/libcutl/configure $@)

ifndef %foreign%

disfigure::
	$(call message,rm $(dcf_root)/import/libcutl/configuration-dynamic.make,\
rm -f $(dcf_root)/import/libcutl/configuration-dynamic.make)

endif

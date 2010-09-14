# file      : cutl/Makefile.am
# author    : Boris Kolpackov <boris@codesynthesis.com>
# copyright : Copyright (c) 2009-2010 Code Synthesis Tools CC
# license   : MIT; see accompanying LICENSE file

EXTRA_DIST = __file__(extra_dist)

lib_LTLIBRARIES = libcutl.la
libcutl_la_SOURCES = __path__(sources)

cutlincludedir = $(includedir)/cutl
nobase_cutlinclude_HEADERS = __path__(headers)

AM_CPPFLAGS = -I$(top_builddir) -I$(top_srcdir)
libcutl_la_LDFLAGS = -release __value__(interface_version)

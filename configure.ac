# file      : configure.ac
# author    : Boris Kolpackov <boris@codesynthesis.com>
# copyright : Copyright (c) 2009-2012 Code Synthesis Tools CC
# license   : MIT; see accompanying LICENSE file

AC_PREREQ(2.60)
AC_INIT([libcutl], [__value__(version)], [libcutl-users@codesynthesis.com])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([cutl/exception.hxx])

AM_INIT_AUTOMAKE([-Wall -Werror foreign nostdinc subdir-objects dist-bzip2 dist-zip tar-ustar])

LT_INIT([win32-dll])

AC_CANONICAL_HOST

# Check for C++ compiler and use it to compile the tests.
#
AC_PROG_CXX
AC_LANG(C++)

# Create the libtool executable so that we can use it in further tests.
#
LT_OUTPUT

# Check if we need to use external Boost.
#
AC_MSG_CHECKING([if we should use external boost])

AC_ARG_WITH(
  [external-boost],
  [AC_HELP_STRING([--with-external-boost],[use external boost instead of the internal subset])],
  [external_boost=${withval}],
  [external_boost=no])

if test x"$external_boost" != xno; then
  AC_MSG_RESULT([yes])

  # Check if we have Boost.
  #
  boost_found=yes
  LIBBOOST([],[boost_found=no])
  LIBBOOST_REGEX([],[boost_found=no])
  LIBBOOST_SYSTEM

  if test x"$boost_found" == xno; then
    AC_MSG_ERROR([boost regex is not found; consider using CPPFLAGS/LDFLAGS or --with-boost=DIR to specify its location])
  fi

  AC_DEFINE([LIBCUTL_EXTERNAL_BOOST], [1], [Use external boost.])
else
  AC_MSG_RESULT([no])
fi

AM_CONDITIONAL([LIBCUTL_EXTERNAL_BOOST], [test x"$external_boost" != xno])


# Define LIBODB_STATIC_LIB if we are build static library on certain platforms.
#
STATIC_LIB([LIBCUTL_STATIC_LIB], [Static library interface.])

# Allow the user to specify the pkgconfig directory.
#
PKGCONFIG

# Check if we should disable rpath.
#
DISABLE_RPATH

# Output.
#
AC_CONFIG_HEADERS([cutl/config.h cutl/details/config.h])
AC_CONFIG_FILES([
  __path__(config_files)
])
AC_OUTPUT

// file      : cutl/details/export.hxx
// copyright : Copyright (c) 2009-2013 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#ifndef CUTL_DETAILS_EXPORT_HXX
#define CUTL_DETAILS_EXPORT_HXX

#include <cutl/details/config.hxx>

#ifdef LIBCUTL_STATIC_LIB
#  define LIBCUTL_EXPORT
#else
#  ifdef _WIN32
#    ifdef _MSC_VER
#      ifdef LIBCUTL_DYNAMIC_LIB
#        define LIBCUTL_EXPORT __declspec(dllexport)
#      else
#        define LIBCUTL_EXPORT __declspec(dllimport)
#      endif
#    else
#      ifdef LIBCUTL_DYNAMIC_LIB
#        ifdef DLL_EXPORT
#          define LIBCUTL_EXPORT __declspec(dllexport)
#        else
#          define LIBCUTL_EXPORT
#        endif
#      else
#        define LIBCUTL_EXPORT __declspec(dllimport)
#      endif
#    endif
#  else
#    define LIBCUTL_EXPORT
#  endif
#endif

#endif // CUTL_DETAILS_EXPORT_HXX

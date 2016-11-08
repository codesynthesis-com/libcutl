// file      : cutl/details/config.hxx
// copyright : Copyright (c) 2009-2013 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#ifndef CUTL_DETAILS_CONFIG_HXX
#define CUTL_DETAILS_CONFIG_HXX

#ifdef LIBCUTL_BUILD2
#  ifdef _MSC_VER
#    include <cutl/details/build2/config-vc.h>
#  else
#    include <cutl/details/build2/config.h>
#  endif
#else
#  ifdef _MSC_VER
#    include <cutl/details/config-vc.h>
#  else
#    include <cutl/details/config.h>
#  endif
#endif

#endif // CUTL_DETAILS_CONFIG_HXX

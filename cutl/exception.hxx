// file      : cutl/exception.hxx
// copyright : Copyright (c) 2009-2013 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#ifndef CUTL_EXCEPTION_HXX
#define CUTL_EXCEPTION_HXX

#include <exception>

#include <cutl/details/export.hxx>

namespace cutl
{
  struct LIBCUTL_EXPORT exception: std::exception
  {
    // By default return the exception type name ( typeid (*this).name () ).
    //
    virtual char const*
    what () const throw ();
  };
}

#endif // CUTL_EXCEPTION_HXX

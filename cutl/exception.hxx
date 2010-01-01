// file      : cutl/exception.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2010 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#ifndef CUTL_EXCEPTION_HXX
#define CUTL_EXCEPTION_HXX

#include <exception>

namespace cutl
{
  struct exception: std::exception
  {
    // By default return the exception type name ( typeid (*this).name () ).
    //
    virtual char const*
    what () const throw ();
  };
}

#endif // CUTL_EXCEPTION_HXX

// file      : cutl/exception.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2010 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#include <typeinfo>

#include <cutl/exception.hxx>

namespace cutl
{
  char const* exception::
  what () const throw ()
  {
    return typeid (*this).name ();
  }
}

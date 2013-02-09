// file      : cutl/exception.cxx
// copyright : Copyright (c) 2009-2013 Code Synthesis Tools CC
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

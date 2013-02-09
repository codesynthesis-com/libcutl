// file      : cutl/fs/exception.cxx
// copyright : Copyright (c) 2009-2013 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#include <cutl/fs/exception.hxx>

namespace cutl
{
  namespace fs
  {
    char const* error::
    what () const throw ()
    {
      return "filesystem error";
    }
  }
}

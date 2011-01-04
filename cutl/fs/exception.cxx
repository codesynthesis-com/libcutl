// file      : cutl/fs/exception.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
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

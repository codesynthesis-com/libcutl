// file      : cutl/fs/path.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#include <cutl/fs/path.hxx>

namespace cutl
{
  namespace fs
  {
    char const* invalid_path_base::
    what () const throw ()
    {
      return "invalid filesystem path";
    }
  }
}

// file      : cutl/compiler/context.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#include <cutl/compiler/context.hxx>

namespace cutl
{
  namespace compiler
  {
    void context::
    remove (char const* key)
    {
      map::iterator i (map_.find (key));

      if (i == map_.end ())
        throw no_entry ();

      map_.erase (i);
    }
  }
}

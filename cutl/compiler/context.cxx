// file      : cutl/compiler/context.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#include <cutl/compiler/context.hxx>

namespace cutl
{
  namespace compiler
  {
    void context::
    remove (std::string const& key)
    {
      map::iterator i (map_.find (key));

      if (i == map_.end ())
        throw no_entry ();

      map_.erase (i);
    }

    std::type_info const& context::
    type_info (std::string const& key) const
    {
      map::const_iterator i (map_.find (key));

      if (i == map_.end ())
        throw no_entry ();

      return i->second.type_info ();
    }
  }
}

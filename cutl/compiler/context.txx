// file      : cutl/compiler/context.txx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

namespace cutl
{
  namespace compiler
  {
    template <typename X>
    X& context::
    get (char const* key)
    {
      map::iterator i (map_.find (key));

      if (i == map_.end ())
        throw no_entry ();

      try
      {
        return i->second. template value<X> ();
      }
      catch (container::any::typing const&)
      {
        throw typing ();
      }
    }

    template <typename X>
    X const& context::
    get (char const* key) const
    {
      map::const_iterator i (map_.find (key));

      if (i == map_.end ())
        throw no_entry ();

      try
      {
        return i->second. template value<X> ();
      }
      catch (container::any::typing const&)
      {
        throw typing ();
      }
    }

    template <typename X>
    X const& context::
    get (char const* key, X const& default_value) const
    {
      map::const_iterator i (map_.find (key));

      if (i == map_.end ())
        return default_value;

      try
      {
        return i->second. template value<X> ();
      }
      catch (container::any::typing const&)
      {
        throw typing ();
      }
    }

    template <typename X>
    void context::
    set (char const* key, X const& value)
    {
      try
      {
        std::pair<map::iterator, bool> r (
          map_.insert (map::value_type (key, value)));

        if (!r.second)
          r.first->second. template value<X> () = value;
      }
      catch (container::any::typing const&)
      {
        throw typing ();
      }
    }
  }
}

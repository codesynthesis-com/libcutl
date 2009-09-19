// file      : cutl/compiler/context.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#ifndef CUTL_COMPILER_CONTEXT_HXX
#define CUTL_COMPILER_CONTEXT_HXX

#include <map>
#include <string>
#include <cstddef> // std::size_t

#include <cutl/exception.hxx>
#include <cutl/container/any.hxx>

namespace cutl
{
  namespace compiler
  {
    class context
    {
    public:
      struct no_entry: exception {};
      struct typing: exception {};

    public:
      context () {}

    private:
      context (context const&);

      context&
      operator= (context const&);

    public:
      std::size_t
      count (char const* key) const
      {
        return map_.count (key);
      }

      template <typename X>
      X&
      get (char const* key);

      template <typename X>
      X const&
      get (char const* key) const;

      template <typename X>
      X const&
      get (char const* key, X const& default_value) const;

      template <typename X>
      void
      set (char const* key, X const& value);

      void
      remove (char const* key);

    private:
      typedef std::map<std::string, container::any> map;

      map map_;
    };
  }
}

#include <cutl/compiler/context.txx>

#endif // CUTL_COMPILER_CONTEXT_HXX

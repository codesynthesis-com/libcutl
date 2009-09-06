// file      : cutl/compiler/type-id.txx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

namespace cutl
{
  namespace compiler
  {
    template <typename X>
    inline
    type_id::
    type_id (X const volatile& x)
        : ti_ (&typeid (x))
    {
    }
  }
}

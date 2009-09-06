// file      : cutl/meta/class-p.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#ifndef CUTL_META_CLASS_HXX
#define CUTL_META_CLASS_HXX

#include <cutl/meta/answer.hxx>

namespace cutl
{
  namespace meta
  {
    template <typename X>
    struct class_p
    {
      template <typename Y> static no test (...);
      template <typename Y> static yes test (void* Y::*);

      static bool const r = sizeof (
        class_p<X>::template test<X> (0)) == sizeof (yes);
    };
  }
}

#endif // CUTL_META_CLASS_HXX

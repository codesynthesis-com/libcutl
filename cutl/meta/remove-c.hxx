// file      : cutl/meta/remove-c.hxx
// copyright : Copyright (c) 2009-2019 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#ifndef CUTL_META_REMOVE_C_HXX
#define CUTL_META_REMOVE_C_HXX

namespace cutl
{
  namespace meta
  {
    template <typename X>
    struct remove_c
    {
      typedef X r;
    };

    template <typename X>
    struct remove_c<X const>
    {
      typedef X r;
    };
  }
}

#endif // CUTL_META_REMOVE_C_HXX

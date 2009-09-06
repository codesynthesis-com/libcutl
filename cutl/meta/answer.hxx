// file      : cutl/meta/answer.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#ifndef CUTL_META_ANSWER_HXX
#define CUTL_META_ANSWER_HXX

namespace cutl
{
  namespace meta
  {
    struct yes
    {
      char filling;
    };

    struct no
    {
      char filling[2];
    };
  }
}

#endif // CUTL_META_ANSWER_HXX

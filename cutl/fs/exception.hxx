// file      : cutl/fs/exception.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#ifndef CUTL_FS_EXCEPTION_HXX
#define CUTL_FS_EXCEPTION_HXX

#include <cutl/exception.hxx>

namespace cutl
{
  namespace fs
  {
    struct error: exception
    {
      error (int code): code_ (code) {}

      // Error code (errno).
      //
      int
      code () const
      {
        return code_;
      }

      virtual char const*
      what () const throw ();

    private:
      int code_;
    };
  }
}

#endif // CUTL_FS_EXCEPTION_HXX

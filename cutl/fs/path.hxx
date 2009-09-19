// file      : cutl/fs/path.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#ifndef CUTL_FS_PATH_HXX
#define CUTL_FS_PATH_HXX

#include <string>
#include <iosfwd>

#include <cutl/exception.hxx>

namespace cutl
{
  namespace fs
  {
    struct invalid_path: exception
    {
      virtual char const*
      what () const throw ();
    };

    template <typename C>
    class basic_path;

    typedef basic_path<char> path;
    typedef basic_path<wchar_t> wpath;

    template <typename C>
    class basic_path
    {
    public:
      typedef std::basic_string<C> string_type;
      typedef typename string_type::size_type size_type;

      explicit
      basic_path (C const* s)
          : path_ (s)
      {
        init (false);
      }

      explicit
      basic_path (string_type const& s)
          : path_ (s)
      {
        init (false);
      }

    public:
      basic_path
      leaf () const;

      basic_path
      directory () const;

      basic_path
      base () const;

    public:
      basic_path
      operator/ (basic_path const&);

    public:
      string_type
      string () const
      {
        return path_.empty () ? string_type (1, '/') : path_;
      }

    private:
      void
      init (bool internal);

      // Assume internal format.
      //
      basic_path (C const* s, size_type n)
          : path_ (s, n)
      {
        init (true);
      }

    private:
      string_type path_;
    };

    template <typename C>
    inline std::basic_ostream<C>&
    operator<< (std::basic_ostream<C>& os, basic_path<C> const& p)
    {
      return os << p.string ();
    }
  }
}

#include <cutl/fs/path.txx>

#endif // CUTL_FS_PATH_HXX

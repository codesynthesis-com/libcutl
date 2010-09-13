// file      : cutl/fs/path.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2010 Code Synthesis Tools CC
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
    template <typename C>
    class basic_path;

    template <typename C>
    struct path_traits
    {
      typedef std::basic_string<C> string_type;
      typedef typename string_type::size_type size_type;

      // Canonical directory and path seperators.
      //
#ifdef _WIN32
      static char const directory_separator = '\\';
      static char const path_separator = ';';
#else
      static char const directory_separator = '/';
      static char const path_separator = ':';
#endif

      // Directory separator tests. On some platforms there
      // could be multiple seperators. For example, on Windows
      // we check for both '/' and '\'.
      //

      static bool
      is_separator (C c)
      {
#ifdef _WIN32
        return c == '\\' || c == '/';
#else
        return c == '/';
#endif
      }

      static size_type
      find_separator (string_type const& s)
      {
        for (size_type i (0), n (s.size ()); i < n; ++i)
        {
          if (is_separator (s[i]))
            return i;
        }

        return string_type::npos;
      }

      static size_type
      rfind_separator (string_type const& s)
      {
        for (size_type i (s.size ()) ; i > 0; --i)
        {
          if (is_separator (s[i - 1]))
            return i - 1;
        }

        return string_type::npos;
      }
    };


    template <typename C>
    class invalid_basic_path;

    typedef basic_path<char> path;
    typedef invalid_basic_path<char> invalid_path;

    typedef basic_path<wchar_t> wpath;
    typedef invalid_basic_path<wchar_t> invalid_wpath;

    //
    //
    class invalid_path_base: exception
    {
    public:
      virtual char const*
      what () const throw ();
    };

    template <typename C>
    class invalid_basic_path: public invalid_path_base
    {
    public:
      typedef std::basic_string<C> string_type;

      invalid_basic_path (C const* p): path_ (p) {}
      invalid_basic_path (string_type const& p): path_ (p) {}
      ~invalid_basic_path () throw () {}

      string_type const&
      path () const
      {
        return path_;
      }

    private:
      string_type path_;
    };

    template <typename C>
    class basic_path
    {
    public:
      typedef std::basic_string<C> string_type;
      typedef typename string_type::size_type size_type;

      typedef path_traits<C> traits;

      // Construct special empty path.
      //
      basic_path ()
      {
      }

      explicit
      basic_path (C const* s)
          : path_ (s)
      {
        init ();
      }

      basic_path (C const* s, size_type n)
          : path_ (s, n)
      {
        init ();
      }

      explicit
      basic_path (string_type const& s)
          : path_ (s)
      {
        init ();
      }

    public:
      // Return the path without the directory part.
      //
      basic_path
      leaf () const;

      // Return the directory part of the path or empty path if
      // there is no directory.
      //
      basic_path
      directory () const;

      // Return the path without the extension, if any.
      //
      basic_path
      base () const;

    public:
      basic_path
      operator/ (basic_path const& x)
      {
        basic_path r (*this);
        r /= x;
        return r;
      }

      basic_path&
      operator/= (basic_path const&);

      basic_path
      operator+ (string_type const& s)
      {
        return basic_path (path_ + s);
      }

      basic_path&
      operator+= (string_type const& s)
      {
        path_ += s;
        return *this;
      }

      bool
      operator== (basic_path const& x) const
      {
        return path_ == x.path_;
      }

      bool
      operator!= (basic_path const& x) const
      {
        return !(*this == x);
      }

    public:
      bool
      empty () const
      {
        return path_.empty ();
      }

      string_type
      string () const
      {
        return path_;
      }

    private:
      void
      init ();

      bool
      root () const
      {
        return path_.size () == 1 && traits::is_separator (path_[0]);
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

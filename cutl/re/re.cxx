// file      : cutl/re/re.cxx
// copyright : Copyright (c) 2009-2013 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#include <cutl/re.hxx>

#include <cutl/details/config.hxx> // LIBCUTL_*

// For build2 build it is either C++11 regex or external Boost.
//
#ifdef LIBCUTL_BUILD2
#  ifdef LIBCUTL_CXX11
#    include <regex>
#  else
#    include <boost/tr1/regex.hpp>
#  endif
#else
#  ifndef LIBCUTL_EXTERNAL_BOOST
#    include <cutl/details/boost/tr1/regex.hpp>
#  else
#    include <boost/tr1/regex.hpp>
#  endif
#endif

using namespace std;

namespace cutl
{
  namespace re
  {
#if defined(LIBCUTL_BUILD2) && defined(LIBCUTL_CXX11)
    namespace ire = std;
#else
    namespace ire = std::tr1;
#endif

    //
    // format_base
    //

    char const* format_base::
    what () const LIBCUTL_NOTHROW_NOEXCEPT
    {
      return description_.c_str ();
    }

    //
    // basic_regex
    //
    template <typename C>
    struct basic_regex<C>::impl
    {
      typedef basic_string<C> string_type;
      typedef ire::basic_regex<C> regex_type;
      typedef typename regex_type::flag_type flag_type;

      impl () {}
      impl (regex_type const& r): r (r) {}
      impl (string_type const& s, bool icase)
      {
        flag_type f (ire::regex_constants::ECMAScript);

        if (icase)
          f |= ire::regex_constants::icase;

        r.assign (s, f);
      }

      regex_type r;
    };

    template <>
    basic_regex<char>::
    ~basic_regex ()
    {
      delete impl_;
    }

    template <>
    basic_regex<wchar_t>::
    ~basic_regex ()
    {
      delete impl_;
    }

    template <>
    basic_regex<char>::
    basic_regex (basic_regex const& r)
        : str_ (r.str_), impl_ (new impl (r.impl_->r))
    {
    }

    template <>
    basic_regex<wchar_t>::
    basic_regex (basic_regex const& r)
        : str_ (r.str_), impl_ (new impl (r.impl_->r))
    {
    }

    template <>
    basic_regex<char>& basic_regex<char>::
    operator= (basic_regex const& r)
    {
      string_type tmp (r.str_);
      impl_->r = r.impl_->r;
      str_.swap (tmp);
      return *this;
    }

    template <>
    basic_regex<wchar_t>& basic_regex<wchar_t>::
    operator= (basic_regex const& r)
    {
      string_type tmp (r.str_);
      impl_->r = r.impl_->r;
      str_.swap (tmp);
      return *this;
    }

    template <>
    void basic_regex<char>::
    init (string_type const* s, bool icase)
    {
      string_type tmp (s == 0 ? string_type () : *s);

      try
      {
        if (impl_ == 0)
          impl_ = s == 0 ? new impl : new impl (*s, icase);
        else
        {
          impl::flag_type f (ire::regex_constants::ECMAScript);

          if (icase)
            f |= ire::regex_constants::icase;

          impl_->r.assign (*s, f);
        }
      }
      catch (ire::regex_error const& e)
      {
        throw basic_format<char> (s == 0 ? "" : *s, e.what ());
      }

      str_.swap (tmp);
    }

    template <>
    void basic_regex<wchar_t>::
    init (string_type const* s, bool icase)
    {
      string_type tmp (s == 0 ? string_type () : *s);

      try
      {
        if (impl_ == 0)
          impl_ = s == 0 ? new impl : new impl (*s, icase);
        else
        {
          impl::flag_type f (ire::regex_constants::ECMAScript);

          if (icase)
            f |= ire::regex_constants::icase;

          impl_->r.assign (*s, f);
        }
      }
      catch (ire::regex_error const& e)
      {
        throw basic_format<wchar_t> (s == 0 ? L"" : *s, e.what ());
      }

      str_.swap (tmp);
    }

    template <>
    bool basic_regex<char>::
    match (string_type const& s) const
    {
      return ire::regex_match (s, impl_->r);
    }

    template <>
    bool basic_regex<wchar_t>::
    match (string_type const& s) const
    {
      return ire::regex_match (s, impl_->r);
    }

    template <>
    bool basic_regex<char>::
    search (string_type const& s) const
    {
      return ire::regex_search (s, impl_->r);
    }

    template <>
    bool basic_regex<wchar_t>::
    search (string_type const& s) const
    {
      return ire::regex_search (s, impl_->r);
    }

    template <>
    string basic_regex<char>::
    replace (string_type const& s,
             string_type const& sub,
             bool first_only) const
    {
      ire::regex_constants::match_flag_type f (
        ire::regex_constants::format_default);

      if (first_only)
        f |= ire::regex_constants::format_first_only;

      return ire::regex_replace (s, impl_->r, sub, f);
    }

    template <>
    wstring basic_regex<wchar_t>::
    replace (string_type const& s,
             string_type const& sub,
             bool first_only) const
    {
      ire::regex_constants::match_flag_type f (
        ire::regex_constants::format_default);

      if (first_only)
        f |= ire::regex_constants::format_first_only;

      return ire::regex_replace (s, impl_->r, sub, f);
    }
  }
}

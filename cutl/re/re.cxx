// file      : cutl/re/re.cxx
// copyright : Copyright (c) 2009-2012 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#include <cutl/re.hxx>

#ifndef LIBCUTL_EXTERNAL_BOOST
#  include <cutl/details/boost/tr1/regex.hpp>
#else
#  include <boost/tr1/regex.hpp>
#endif

using namespace std;

namespace cutl
{
  namespace re
  {
    //
    // format_base
    //

    format_base::
    ~format_base () throw ()
    {
    }

    char const* format_base::
    what () const throw ()
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
      typedef tr1::basic_regex<C> regex_type;

      impl () {}
      impl (string_type const& s): r (s, tr1::regex_constants::ECMAScript) {}
      impl (regex_type const& r): r (r) {}

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
        : impl_ (new impl (r.impl_->r))
    {
    }

    template <>
    basic_regex<wchar_t>::
    basic_regex (basic_regex const& r)
        : impl_ (new impl (r.impl_->r))
    {
    }

    template <>
    basic_regex<char>& basic_regex<char>::
    operator= (basic_regex const& r)
    {
      impl_->r = r.impl_->r;
      return *this;
    }

    template <>
    basic_regex<wchar_t>& basic_regex<wchar_t>::
    operator= (basic_regex const& r)
    {
      impl_->r = r.impl_->r;
      return *this;
    }

    template <>
    void basic_regex<char>::
    init (string_type const* s)
    {
      try
      {
        if (impl_ == 0)
          impl_ = s == 0 ? new impl : new impl (*s);
        else
          impl_->r = *s;
      }
      catch (tr1::regex_error const& e)
      {
        throw basic_format<char> (s == 0 ? "" : *s, e.what ());
      }
    }

    template <>
    void basic_regex<wchar_t>::
    init (string_type const* s)
    {
      try
      {
        if (impl_ == 0)
          impl_ = s == 0 ? new impl : new impl (*s);
        else
          impl_->r = *s;
      }
      catch (tr1::regex_error const& e)
      {
        throw basic_format<wchar_t> (s == 0 ? L"" : *s, e.what ());
      }
    }

    template <>
    bool basic_regex<char>::
    match (string_type const& s) const
    {
      return tr1::regex_match (s, impl_->r);
    }

    template <>
    bool basic_regex<wchar_t>::
    match (string_type const& s) const
    {
      return tr1::regex_match (s, impl_->r);
    }

    template <>
    bool basic_regex<char>::
    search (string_type const& s) const
    {
      return tr1::regex_search (s, impl_->r);
    }

    template <>
    bool basic_regex<wchar_t>::
    search (string_type const& s) const
    {
      return tr1::regex_search (s, impl_->r);
    }

    template <>
    string basic_regex<char>::
    replace (string_type const& s,
             string_type const& sub,
             bool first_only) const
    {
      tr1::regex_constants::match_flag_type f (
        tr1::regex_constants::format_default);

      if (first_only)
        f |= tr1::regex_constants::format_first_only;

      return tr1::regex_replace (s, impl_->r, sub, f);
    }

    template <>
    wstring basic_regex<wchar_t>::
    replace (string_type const& s,
             string_type const& sub,
             bool first_only) const
    {
      tr1::regex_constants::match_flag_type f (
        tr1::regex_constants::format_default);

      if (first_only)
        f |= tr1::regex_constants::format_first_only;

      return tr1::regex_replace (s, impl_->r, sub, f);
    }

    template <>
    string basic_regex<char>::
    str () const
    {
      return impl_->r.str ();
    }

    template <>
    wstring basic_regex<wchar_t>::
    str () const
    {
      return impl_->r.str ();
    }

    template <>
    bool basic_regex<char>::
    empty () const
    {
      return impl_->r.empty ();
    }

    template <>
    bool basic_regex<wchar_t>::
    empty () const
    {
      return impl_->r.empty ();
    }
  }
}

// file      : cutl/re/re.cxx
// copyright : Copyright (c) 2009-2012 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#include <ostream>

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
    // format
    //

    format::
    ~format () throw ()
    {
    }

    char const* format::
    what () const throw ()
    {
      return description_.c_str ();
    }

    //
    // regex
    //
    struct regex::impl
    {
      impl () {}
      impl (string const& s): r (s, tr1::regex_constants::ECMAScript) {}
      impl (tr1::regex const& r): r (r) {}

      tr1::regex r;
    };

    regex::
    ~regex ()
    {
      delete impl_;
    }

    regex::
    regex (regex const& r)
        : impl_ (new impl (r.impl_->r))
    {
    }

    regex& regex::
    operator= (regex const& r)
    {
      impl_->r = r.impl_->r;
      return *this;
    }

    void regex::
    init (string const* s)
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
        throw format (s == 0 ? "" : *s, e.what ());
      }
    }

    bool regex::
    match (string const& s) const
    {
      return tr1::regex_match (s, impl_->r);
    }

    bool regex::
    search (string const& s) const
    {
      return tr1::regex_search (s, impl_->r);
    }

    string regex::
    replace (string const& s, string const& sub, bool first_only) const
    {
      tr1::regex_constants::match_flag_type f (
        tr1::regex_constants::format_default);

      if (first_only)
        f |= tr1::regex_constants::format_first_only;

      return regex_replace (s, impl_->r, sub, f);
    }

    string regex::
    str () const
    {
      return impl_->r.str ();
    }

    bool regex::
    empty () const
    {
      return impl_->r.empty ();
    }

    ostream&
    operator<< (ostream& os, regex const& r)
    {
      return os << r.str ().c_str ();
    }

    //
    // regexsub
    //
    void regexsub::
    init (string const& s)
    {
      string r;
      string::size_type p (parse (s, 0, r));
      regex_ = r;
      p = parse (s, p, sub_);
      if (p + 1 < s.size ())
        throw format (s, "junk after third delimiter");
    }

    //
    // parse()
    //
    string::size_type
    parse (string const& s, string::size_type p, string& r)
    {
      r.clear ();
      string::size_type n (s.size ());

      if (p >= n)
        throw format (s, "empty expression");

      char d (s[p++]);

      for (; p < n; ++p)
      {
        if (s[p] == d)
          break;

        if (s[p] == '\\')
        {
          if (++p < n)
          {
            if (s[p] != d && s[p] != '\\')
              r += '\\';
            r += s[p];
          }
          // else {we ran out of stuff before finding the delimiter}
        }
        else
          r += s[p];
      }

      if (p == n)
        throw format (s, "missing closing delimiter");

      return p;
    }
  }
}

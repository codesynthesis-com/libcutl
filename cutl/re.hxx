// file      : cutl/re.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2012 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#ifndef CUTL_RE_HXX
#define CUTL_RE_HXX

#include <string>
#include <iosfwd> // std::ostream

#include <cutl/exception.hxx>
#include <cutl/details/export.hxx>

namespace cutl
{
  namespace re
  {
    struct LIBCUTL_EXPORT format: exception
    {
      virtual
      ~format () throw ();

      format (std::string const& e, std::string const& d)
          : regex_ (e), description_ (d)
      {
      }

      std::string const&
      regex () const
      {
        return regex_;
      }

      std::string const&
      description () const
      {
        return description_;
      }

      virtual char const*
      what () const throw ();

    private:
      std::string regex_;
      std::string description_;
    };

    // Regular expression pattern.
    //
    struct LIBCUTL_EXPORT regex
    {
      ~regex ();

      regex ()
          : impl_ (0)
      {
        init (0);
      }

      explicit
      regex (std::string const& s)
          : impl_ (0)
      {
        init (&s);
      }

      regex&
      operator= (std::string const& s)
      {
        init (&s);
        return *this;
      }

      regex (regex const&);

      regex&
      operator= (regex const&);

    public:
      bool
      match (std::string const&) const;

      bool
      search (std::string const&) const;

      std::string
      replace (std::string const& s,
               std::string const& sub,
               bool first_only = false) const;

    public:
      std::string
      str () const;

      bool
      empty () const;

    private:
      void
      init (std::string const*);

    private:
      struct impl;
      impl* impl_;
    };

    LIBCUTL_EXPORT std::ostream&
    operator<< (std::ostream&, regex const&);

    // Regular expression pattern and substituation.
    //
    struct LIBCUTL_EXPORT regexsub
    {
      typedef re::regex regex_type;

      regexsub ()
      {
      }

      // Expression is of the form /regex/substitution/ where '/' can
      // be replaced with any delimiter. Delimiters must be escaped in
      // regex and substitution using back slashes (e.g., "\/"). Back
      // slashes themselves can be escaped using the double back slash
      // sequence (e.g., "\\").
      //
      explicit
      regexsub (std::string const& e)
      {
        init (e);
      }

      regexsub (std::string const& regex, std::string const& sub)
          : regex_ (regex), sub_ (sub)
      {
      }

      regexsub (regex_type const& regex, std::string const& sub)
          : regex_ (regex), sub_ (sub)
      {
      }

      regexsub&
      operator= (std::string const& e)
      {
        init (e);
        return *this;
      }

    public:
      bool
      match (std::string const& s) const
      {
        return regex_.match (s);
      }

      bool
      search (std::string const& s) const
      {
        return regex_.search (s);
      }

      std::string
      replace (std::string const& s, bool first_only = false) const
      {
        return regex_.replace (s, sub_, first_only);
      }

    public:
      const regex_type&
      regex () const
      {
        return regex_;
      }

      const std::string&
      substitution () const
      {
        return sub_;
      }

      bool
      empty () const
      {
        return sub_.empty () && regex_.empty ();
      }

    private:
      void
      init (std::string const&);

    private:
      regex_type regex_;
      std::string sub_;
    };

    // Once-off regex execution.
    //
    inline bool
    match (std::string const& s, std::string const& regex)
    {
      re::regex r (regex);
      return r.match (s);
    }

    inline bool
    search (std::string const& s, std::string const& regex)
    {
      re::regex r (regex);
      return r.search (s);
    }

    inline std::string
    replace (std::string const& s,
             std::string const& regex,
             std::string const& sub,
             bool first_only = false)
    {
      re::regex r (regex);
      return r.replace (s, sub, first_only);
    }

    inline std::string
    replace (std::string const& s,
             std::string const& regexsub, // /regex/subst/
             bool first_only = false)
    {
      re::regexsub r (regexsub);
      return r.replace (s, first_only);
    }

    // Utility function for parsing expressions in the form /regex/subst/
    // where '/' can be replaced with any delimiter. This function handles
    // escaping. It return the position of the next delimiter and stores
    // the unescaped chunk in result or throws the format exception if
    // the expression is invalid.
    //
    LIBCUTL_EXPORT std::string::size_type
    parse (std::string const& s,
           std::string::size_type start,
           std::string& result);
  }
}

#endif // CUTL_RE_HXX

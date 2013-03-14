// file      : cutl/xml/parser.ixx
// copyright : Copyright (c) 2009-2013 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

namespace cutl
{
  namespace xml
  {
    inline void parser::
    next_expect (event_type e, const qname_type& qn)
    {
      return next_expect (e, qn.namespace_ (), qn.name ());
    }

    inline void parser::
    next_expect (event_type e, const std::string& n)
    {
      return next_expect (e, std::string (), n);
    }
  }
}

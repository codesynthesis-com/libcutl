// file      : cutl/xml/qname.cxx
// copyright : Copyright (c) 2009-2013 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#include <ostream>

#include <cutl/xml/qname.hxx>

using namespace std;

namespace cutl
{
  namespace xml
  {
    ostream&
    operator<< (ostream& os, const qname& qn)
    {
      const string& ns (qn.namespace_ ());
      return os << ns << (ns.empty () ? "" : "#") << qn.name ();
    }
  }
}

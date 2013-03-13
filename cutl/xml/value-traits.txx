// file      : cutl/xml/value-traits.txx
// copyright : Copyright (c) 2009-2013 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#include <sstream>

#include <cutl/xml/parser.hxx>
#include <cutl/xml/serializer.hxx>

namespace cutl
{
  namespace xml
  {
    template <typename T>
    std::string default_value_traits<T>::
    serialize (const T& v, const serializer& s)
    {
      std::ostringstream os;
      if (!(os << v))
        throw serialization (s.output_name (), "invalid value");
      return os.str ();
    }
  }
}

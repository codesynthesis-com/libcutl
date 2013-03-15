// file      : cutl/xml/parser.txx
// copyright : Copyright (c) 2009-2013 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#include <cutl/xml/value-traits.hxx>

namespace cutl
{
  namespace xml
  {
    template <typename T>
    T parser::
    attribute (const qname_type& qn, const T& dv) const
    {
      attribute_map::const_iterator i (attr_map_.find (qn));

      if (i != attr_map_.end ())
      {
        if (!i->second.handled)
        {
          i->second.handled = true;
          attr_unhandled_--;
        }
        return value_traits<T>::parse (i->second.value, *this);
      }
      else
        return dv;
    }
  }
}

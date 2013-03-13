// file      : cutl/xml/value-traits.hxx
// copyright : Copyright (c) 2009-2013 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#ifndef CUTL_XML_VALUE_TRAITS_HXX
#define CUTL_XML_VALUE_TRAITS_HXX

#include <string>

#include <cutl/details/export.hxx>

namespace cutl
{
  namespace xml
  {
    class parser;
    class serializer;

    template <typename T>
    struct default_value_traits
    {
      static std::string
      serialize (const T&, const serializer&);
    };

    template <>
    struct LIBCUTL_EXPORT default_value_traits<bool>
    {
      static std::string
      serialize (bool v, const serializer&)
      {
        return v ? "true" : "false";
      }
    };

    template <typename T>
    struct value_traits: default_value_traits<T> {};
  }
}

#include <cutl/xml/value-traits.txx>

#endif // CUTL_XML_VALUE_TRAITS_HXX

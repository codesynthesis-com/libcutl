// file      : cutl/xml/value-traits.hxx
// copyright : Copyright (c) 2009-2013 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#ifndef CUTL_XML_VALUE_TRAITS_HXX
#define CUTL_XML_VALUE_TRAITS_HXX

#include <string>
#include <cstddef> // std::size_t

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
      static T
      parse (std::string, const parser&);

      static std::string
      serialize (const T&, const serializer&);
    };

    template <>
    struct LIBCUTL_EXPORT default_value_traits<bool>
    {
      static bool
      parse (std::string, const parser&);

      static std::string
      serialize (bool v, const serializer&)
      {
        return v ? "true" : "false";
      }
    };

    template <typename T>
    struct value_traits: default_value_traits<T> {};

    template <typename T, std::size_t N>
    struct value_traits<T[N]>: default_value_traits<const T*> {};
  }
}

#include <cutl/xml/value-traits.txx>

#endif // CUTL_XML_VALUE_TRAITS_HXX

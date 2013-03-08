// file      : cutl/xml/serializer.ixx
// copyright : Copyright (c) 2009-2013 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

namespace cutl
{
  namespace xml
  {
    inline void serializer::
    start_element (const qname_type& qname)
    {
      start_element (qname.namespace_ (), qname.name ());
    }

    inline void serializer::
    start_element (const std::string& name)
    {
      start_element (std::string (), name);
    }

    inline void serializer::
    start_attribute (const qname_type& qname)
    {
      start_attribute (qname.namespace_ (), qname.name ());
    }

    inline void serializer::
    start_attribute (const std::string& name)
    {
      start_attribute (std::string (), name);
    }

    inline void serializer::
    attribute (const qname_type& qname, const std::string& value)
    {
      attribute (qname.namespace_ (), qname.name (), value);
    }

    inline void serializer::
    attribute (const std::string& name, const std::string& value)
    {
      attribute (std::string (), name, value);
    }
  }
}

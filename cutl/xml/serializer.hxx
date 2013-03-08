// file      : cutl/xml/serializer.hxx
// copyright : Copyright (c) 2009-2013 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#ifndef CUTL_XML_SERIALIZER_HXX
#define CUTL_XML_SERIALIZER_HXX

#include <string>
#include <ostream>
#include <cstddef> // std::size_t

#include <cutl/details/genx/genx.h>

#include <cutl/xml/qname.hxx>
#include <cutl/xml/exception.hxx>

#include <cutl/details/export.hxx>

namespace cutl
{
  namespace xml
  {
    struct LIBCUTL_EXPORT serialization: exception
    {
      virtual
      ~serialization () throw ();

      serialization (const std::string& name,
                     const std::string& description);

      const std::string&
      name () const {return name_;}

      const std::string&
      description () const {return description_;}

      virtual const char*
      what () const throw ();

    private:
      std::string name_;
      std::string description_;
      std::string what_;
    };

    class LIBCUTL_EXPORT serializer
    {
    public:
      ~serializer ();

      typedef xml::qname qname_type;

      // Serialize to std::ostream. Name is used in diagnostics to identify
      // the document being serialized. std::ios_base::failure exception is
      // used to report io errors (badbit and failbit). The indentation
      // argument specifies the number of indentation spaces that should
      // be used for pretty-printing. If 0 is passed, no pretty-printing
      // is performed.
      //
      serializer (std::ostream&,
                  const std::string& name,
                  unsigned short indentation = 2);

      // Serialization functions.
      //
    public:

      // Elements.
      //
      void
      start_element (const qname_type& qname);

      void
      start_element (const std::string& name);

      void
      start_element (const std::string& ns, const std::string& name);

      void
      end_element ();

      // Attributes.
      //
      void
      start_attribute (const qname_type& qname);

      void
      start_attribute (const std::string& name);

      void
      start_attribute (const std::string& ns, const std::string& name);

      void
      end_attribute ();

      void
      attribute (const qname_type& qname, const std::string& value);

      void
      attribute (const std::string& name, const std::string& value);

      void
      attribute (const std::string& ns,
                 const std::string& name,
                 const std::string& value);

      // Characters.
      //
      void
      characters (const std::string& value);

      // Namespaces declaration. If prefix is empty, then the default
      // namespace is declared. If both prefix and namespace are empty,
      // then the default namespace declaration is cleared (xmlns="").
      //
      void
      namespace_decl (const std::string& ns, const std::string& prefix);

      // XML Declaration. If encoding or standalone are not specified,
      // then these attributes are omitted from the output.
      //
      void
      xml_decl (const std::string& version = "1.0",
                const std::string& encoding = "UTF-8",
                const std::string& standalone = "");

      // Other functions.
      //
    public:
      // Return true if there is a mapping. In this case, prefix contains
      // the mapped prefix.
      //
      bool
      lookup_namespace_prefix (const std::string& ns, std::string& prefix);

    private:
      void
      handle_error (genxStatus);

    private:
      std::ostream& os_;
      std::ostream::iostate os_state_; // Original exception state.
      const std::string name_;

      genxWriter s_;
      genxSender sender_;
      std::size_t depth_;
    };
  }
}

#include <cutl/xml/serializer.ixx>

#endif // CUTL_XML_SERIALIZER_HXX

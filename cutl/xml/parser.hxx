// file      : cutl/xml/parser.hxx
// copyright : Copyright (c) 2009-2013 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#ifndef CUTL_XML_PARSER_HXX
#define CUTL_XML_PARSER_HXX

#include <string>
#include <vector>
#include <iosfwd>
#include <cstddef> // std::size_t

#include <cutl/details/config.hxx> // LIBCUTL_EXTERNAL_EXPAT

#ifndef LIBCUTL_EXTERNAL_EXPAT
#  include <cutl/details/expat/expat.h>
#else
#  include <expat.h>
#endif

// We only support UTF-8 expat.
//
#ifdef XML_UNICODE
#  error UTF-16 expat (XML_UNICODE defined) is not supported
#endif

#include <cutl/xml/qname.hxx>
#include <cutl/xml/exception.hxx>

#include <cutl/details/export.hxx>

namespace cutl
{
  namespace xml
  {
    struct LIBCUTL_EXPORT parsing: exception
    {
      virtual
      ~parsing () throw ();

      parsing (const std::string& name,
               unsigned long long line,
               unsigned long long column,
               const std::string& description);

      const std::string&
      name () const {return name_;}

      unsigned long long
      line () const {return line_;}

      unsigned long long
      column () const {return column_;}

      const std::string&
      description () const {return description_;}

      virtual const char*
      what () const throw ();

    private:
      std::string name_;
      unsigned long long line_;
      unsigned long long column_;
      std::string description_;
      std::string what_;
    };

    class LIBCUTL_EXPORT parser
    {
    public:
      ~parser ();

      typedef xml::qname qname_type;
      typedef unsigned short feature_type;

      static const feature_type receive_elements = 0x0001;
      static const feature_type receive_characters = 0x0002;
      static const feature_type receive_attributes = 0x0004;
      static const feature_type receive_namespace_decls = 0x0008;

      static const feature_type receive_default = receive_elements |
                                                  receive_characters |
                                                  receive_attributes;

      // Parse std::istream. Name is used in diagnostics to identify the
      // document being parsed. std::ios_base::failure exception is used
      // to report io errors (badbit and failbit).
      //
      parser (std::istream&,
              const std::string& name,
              feature_type = receive_default);

      enum event_type
      {
        // If adding new events, also update the stream insertion operator.
        //
        start_element,
        end_element,
        start_attribute,
        end_attribute,
        characters,
        start_namespace_decl,
        end_namespace_decl,
        eof
      };

      event_type
      next ();

      const qname_type& qname () const {return *pqname_;}

      const std::string& namespace_ () const {return pqname_->namespace_ ();}
      const std::string& name () const {return pqname_->name ();}
      const std::string& prefix () const {return pqname_->prefix ();}

      const std::string& value () const {return *pvalue_;}

      unsigned long long line () const {return line_;}
      unsigned long long column () const {return column_;}

      // Optional content processing.
      //
    public:
      enum content_type
      {
                 //  element   characters  whitespaces
        empty,   //    no          no        ignored
        simple,  //    no          yes       preserved
        complex, //    yes         no        ignored
        mixed    //    yes         yes       preserved
      };

      void
      content (content_type c)
      {
        if (!content_.empty () && content_.back ().depth == depth_)
          content_.back ().content = c;
        else
          content_.push_back (content_entry (depth_, c));
      }

      content_type
      content () const
      {
        return !content_.empty () && content_.back ().depth == depth_
          ? content_.back ().content : mixed;
      }

    private:
      static void XMLCALL
      start_element_ (void*, const XML_Char*, const XML_Char**);

      static void XMLCALL
      end_element_ (void*, const XML_Char*);

      static void XMLCALL
      characters_ (void*, const XML_Char*, int);

      static void XMLCALL
      start_namespace_decl_ (void*, const XML_Char*, const XML_Char*);

      static void XMLCALL
      end_namespace_decl_ (void*, const XML_Char*);

    private:
      event_type
      next_ ();

      void
      handle_error ();

    private:
      std::istream& is_;
      const std::string name_;
      feature_type feature_;

      XML_Parser p_;
      std::size_t depth_;
      event_type event_;
      event_type queue_;

      qname_type qname_;
      std::string value_;

      // These are used to avoid copying when we are handling attributes
      // and namespace decls.
      //
      const qname_type* pqname_;
      const std::string* pvalue_;

      unsigned long long line_;
      unsigned long long column_;

      // Attributes.
      //
      struct attribute
      {
        qname_type qname;
        std::string value;
      };

      typedef std::vector<attribute> attributes;

      attributes attr_;
      attributes::size_type attr_i_; // Index of the current attribute.

      // Namespace declarations.
      //
      typedef std::vector<qname_type> namespace_decls;

      namespace_decls start_ns_;
      namespace_decls::size_type start_ns_i_; // Index of the current decl.

      namespace_decls end_ns_;
      namespace_decls::size_type end_ns_i_; // Index of the current decl.

      // Content.
      //
      struct content_entry
      {
        content_entry (std::size_t d, content_type c)
            : depth (d), content (c) {}

        std::size_t depth;
        content_type content;
      };

      std::vector<content_entry> content_;
    };

    LIBCUTL_EXPORT
    std::ostream&
    operator<< (std::ostream&, parser::event_type);
  }
}

#endif // CUTL_XML_PARSER_HXX

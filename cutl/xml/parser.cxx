// file      : cutl/xml/parser.cxx
// copyright : Copyright (c) 2009-2013 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#include <new>     // std::bad_alloc
#include <cassert>
#include <cstring> // std::strchr
#include <istream>
#include <ostream>
#include <sstream>

#include <cutl/xml/parser.hxx>

using namespace std;

namespace cutl
{
  namespace xml
  {
    // parsing
    //
    parsing::
    ~parsing () throw () {}

    parsing::
    parsing (const string& n,
             unsigned long long l,
             unsigned long long c,
             const string& d)
        : name_ (n), line_ (l), column_ (c), description_ (d)
    {
      ostringstream os;
      if (!n.empty ())
        os << n << ':';
      os << l << ':' << c << ": error: " << d;
      what_ = os.str ();
    }

    char const* parsing::
    what () const throw ()
    {
      return what_.c_str ();
    }

    // parser
    //
    parser::
    ~parser ()
    {
      if (p_ != 0)
        XML_ParserFree (p_);
    }

    parser::
    parser (istream& is, const string& name, feature_type f)
        : is_ (is), name_ (name), feature_ (f),
          depth_ (0), event_ (eof), queue_ (eof),
          pqname_ (&qname_), pvalue_ (&value_),
          attr_i_ (0), start_ns_i_ (0), end_ns_i_ (0)
    {
      // Allocate the parser. Make sure nothing else can throw after
      // this call since otherwise we will leak it.
      //
      p_ = XML_ParserCreateNS (0, XML_Char (' '));

      if (p_ == 0)
        throw bad_alloc ();

      // Get prefixes in addition to namespaces and local names.
      //
      XML_SetReturnNSTriplet (p_, true);

      // Set handlers.
      //
      XML_SetUserData(p_, this);

      if ((f & receive_elements) != 0)
      {
        XML_SetStartElementHandler (p_, &start_element_);
        XML_SetEndElementHandler (p_, &end_element_);
      }

      if ((f & receive_characters) != 0)
        XML_SetCharacterDataHandler (p_, &characters_);

      if ((f & receive_namespace_decls) != 0)
        XML_SetNamespaceDeclHandler (p_,
                                     &start_namespace_decl_,
                                     &end_namespace_decl_);
    }

    void parser::
    handle_error ()
    {
      XML_Error e (XML_GetErrorCode (p_));

      if (e == XML_ERROR_ABORTED)
      {
        // For now we only abort the parser in the characters_() handler.
        //
        switch (content ())
        {
        case empty:
          throw parsing (name_, line_, column_, "character in empty content");
        case complex:
          throw parsing (name_, line_, column_, "character in complex content");
        default:
          assert (false);
        }
      }
      else
        throw parsing (name_,
                       XML_GetCurrentLineNumber (p_),
                       XML_GetCurrentColumnNumber (p_),
                       XML_ErrorString (e));
    }

    struct stream_exception_controller
    {
      ~stream_exception_controller ()
      {
        istream::iostate s = is_.rdstate ();
        s &= ~istream::failbit;

        // If our error state (sans failbit) intersects with the
        // exception state then that means we have an active
        // exception and changing error/exception state will
        // cause another to be thrown.
        //
        if (!(old_state_ & s))
        {
          // Clear failbit if it was caused by eof.
          //
          if (is_.fail () && is_.eof ())
            is_.clear (s);

          is_.exceptions (old_state_);
        }
      }

      stream_exception_controller (istream& is)
          : is_ (is), old_state_ (is_.exceptions ())
      {
        is_.exceptions (old_state_ & ~istream::failbit);
      }

    private:
      stream_exception_controller (const stream_exception_controller&);

      stream_exception_controller&
      operator= (const stream_exception_controller&);

    private:
      istream& is_;
      istream::iostate old_state_;
    };

    parser::event_type parser::
    next ()
    {
      event_type e (next_ ());

      // Content-specific processing. Note that we handle characters in the
      // characters_() Expat handler for two reasons. Firstly, it is faster
      // to ignore the whitespaces at the source. Secondly, this allows us
      // to distinguish between element and attribute characters. We can
      // move this processing to the handler because the characters event
      // is never queued.
      //
      switch (e)
      {
      case start_element:
        {
          switch (content ())
          {
          case empty:
            throw parsing (name_, line_, column_, "element in empty content");
          case simple:
            throw parsing (name_, line_, column_, "element in simple content");
          default:
            break;
          }

          depth_++;
          break;
        }
      case end_element:
        {
          if (!content_.empty () && content_.back ().depth == depth_)
            content_.pop_back ();

          depth_--;
          break;
        }
      default:
        break;
      }

      return e;
    }

    parser::event_type parser::
    next_ ()
    {
      // See if we have any start namespace declarations we need to return.
      //
      if (start_ns_i_ < start_ns_.size ())
      {
        // Based on the previous event determine what's the next one must be.
        //
        switch (event_)
        {
        case start_namespace_decl:
          {
            if (++start_ns_i_ == start_ns_.size ())
            {
              start_ns_i_ = 0;
              start_ns_.clear ();
              pqname_ = &qname_;
              break; // No more declarations.
            }
            // Fall through.
          }
        case start_element:
          {
            event_ = start_namespace_decl;
            pqname_ = &start_ns_[start_ns_i_];
            return event_;
          }
        default:
          {
            assert (false);
            return eof;
          }
        }
      }

      // See if we have any attributes we need to return.
      //
      if (attr_i_ < attr_.size ())
      {
        // Based on the previous event determine what's the next one must be.
        //
        switch (event_)
        {
        case start_attribute:
          {
            event_ = characters;
            pvalue_ = &attr_[attr_i_].value;
            return event_;
          }
        case characters:
          {
            event_ = end_attribute; // Name is already set.
            return event_;
          }
        case end_attribute:
          {
            if (++attr_i_ == attr_.size ())
            {
              attr_i_ = 0;
              attr_.clear ();
              pqname_ = &qname_;
              pvalue_ = &value_;
              break; // No more attributes.
            }
            // Fall through.
          }
        case start_element:
        case start_namespace_decl:
          {
            event_ = start_attribute;
            pqname_ = &attr_[attr_i_].qname;
            return event_;
          }
        default:
          {
            assert (false);
            return eof;
          }
        }
      }

      // See if we have any end namespace declarations we need to return.
      //
      if (end_ns_i_ < end_ns_.size ())
      {
        // Based on the previous event determine what's the next one must be.
        //
        switch (event_)
        {
        case end_namespace_decl:
          {
            if (++end_ns_i_ == end_ns_.size ())
            {
              end_ns_i_ = 0;
              end_ns_.clear ();
              pqname_ = &qname_;
              break; // No more declarations.
            }
            // Fall through.
          }
          // The end namespace declaration comes before the end element
          // which means it can follow pretty much any other event.
          //
        default:
          {
            event_ = end_namespace_decl;
            pqname_ = &end_ns_[end_ns_i_];
            return event_;
          }
        }
      }

      // Check the queue.
      //
      if (queue_ != eof)
      {
        event_type r (queue_);
        queue_ = eof;
        return r;
      }

      XML_ParsingStatus ps;
      XML_GetParsingStatus (p_, &ps);

      switch (ps.parsing)
      {
      case XML_INITIALIZED:
        {
          // As if we finished the previous chunk.
          break;
        }
      case XML_PARSING:
        {
          assert (false);
          return eof;
        }
      case XML_FINISHED:
        {
          return eof;
        }
      case XML_SUSPENDED:
        {
          switch (XML_ResumeParser (p_))
          {
          case XML_STATUS_SUSPENDED:
            {
              // If the parser is again in the suspended state, then
              // that means we have the next event.
              //
              return event_;
            }
          case XML_STATUS_OK:
            {
              // Otherwise, we need to get and parse the next chunk of data
              // unless this was the last chunk, in which case this is eof.
              //
              if (ps.finalBuffer)
                return eof;

              break;
            }
          case XML_STATUS_ERROR:
            handle_error ();
          }

          break;
        }
      }

      // Get and parse the next chunk of data until we get the next event
      // or reach eof.
      //
      event_ = eof;
      XML_Status s;
      do
      {
        const size_t cap (4096);

        char* b (static_cast<char*> (XML_GetBuffer (p_, cap)));
        if (b == 0)
          throw bad_alloc ();

        // Temporarily unset the exception failbit. Also clear the fail bit
        // when we reset the old state if it was caused by eof.
        //
        {
          stream_exception_controller sec (is_);
          is_.read (b, static_cast<streamsize> (cap));
        }

        s = XML_ParseBuffer (p_, static_cast<int> (is_.gcount ()), is_.eof ());

        if (s == XML_STATUS_ERROR)
          handle_error ();

      } while (s != XML_STATUS_SUSPENDED && !is_.eof ());

      return event_;
    }

    static void
    split_name (const XML_Char* s, qname& qn)
    {
      string& ns (qn.namespace_ ());
      string& name (qn.name ());
      string& prefix (qn.prefix ());

      const char* p (strchr (s, ' '));

      if (p == 0)
      {
        ns.clear ();
        name = s;
        prefix.clear ();
      }
      else
      {
        ns.assign (s, 0, p - s);

        s = p + 1;
        p = strchr (s, ' ');

        if (p == 0)
        {
          name = s;
          prefix.clear ();
        }
        else
        {
          name.assign (s, 0, p - s);
          prefix = p + 1;
        }
      }
    }

    void XMLCALL parser::
    start_element_ (void* v, const XML_Char* name, const XML_Char** atts)
    {
      parser& p (*static_cast<parser*> (v));

      XML_ParsingStatus ps;
      XML_GetParsingStatus (p.p_, &ps);

      // Expat has a (mis)-feature of a possibily calling handlers even
      // after the non-resumable XML_StopParser call.
      //
      if (ps.parsing == XML_FINISHED)
        return;

      // Cannot be a followup event.
      //
      assert (ps.parsing == XML_PARSING);

      p.event_ = start_element;
      split_name (name, p.qname_);

      p.line_ = XML_GetCurrentLineNumber (p.p_);
      p.column_ = XML_GetCurrentColumnNumber (p.p_);

      // Handle attributes.
      //
      if ((p.feature_ & receive_attributes) != 0)
      {
        for (; *atts != 0; atts += 2)
        {
          p.attr_.push_back (attribute ());
          split_name (*atts, p.attr_.back ().qname);
          p.attr_.back ().value = *(atts + 1);
        }
      }

      XML_StopParser (p.p_, true);
    }

    void XMLCALL parser::
    end_element_ (void* v, const XML_Char* name)
    {
      parser& p (*static_cast<parser*> (v));

      XML_ParsingStatus ps;
      XML_GetParsingStatus (p.p_, &ps);

      // Expat has a (mis)-feature of a possibily calling handlers even
      // after the non-resumable XML_StopParser call.
      //
      if (ps.parsing == XML_FINISHED)
        return;

      // This can be a followup event for empty elements (<foo/>). In this
      // case the element name is already set.
      //
      if (ps.parsing != XML_PARSING)
        p.queue_ = end_element;
      else
      {
        // We may also have the end namespace declaration events which
        // should come before the end element. If that's the case, then
        // queue the end element and return the end namespace as the next
        // event.
        //
        if (p.end_ns_i_ < p.end_ns_.size ())
        {
          p.event_ = end_namespace_decl;
          p.queue_ = end_element;
        }
        else
          p.event_ = end_element;

        split_name (name, p.qname_);

        p.line_ = XML_GetCurrentLineNumber (p.p_);
        p.column_ = XML_GetCurrentColumnNumber (p.p_);

        XML_StopParser (p.p_, true);
      }
    }

    void XMLCALL parser::
    characters_ (void* v, const XML_Char* s, int n)
    {
      parser& p (*static_cast<parser*> (v));

      XML_ParsingStatus ps;
      XML_GetParsingStatus (p.p_, &ps);

      // Expat has a (mis)-feature of a possibily calling handlers even
      // after the non-resumable XML_StopParser call.
      //
      if (ps.parsing == XML_FINISHED)
        return;

      // If this is empty of complex content, see if these are whitespaces.
      //
      switch (p.content ())
      {
      case empty:
      case complex:
        {
          for (int i (0); i != n; ++i)
          {
            char c (s[i]);
            if (c == 0x20 || c == 0x0A || c == 0x0D || c == 0x09)
              continue;

            // It would have been easier to throw the exception directly,
            // however, the Expat code is most likely not exception safe.
            //
            p.line_ = XML_GetCurrentLineNumber (p.p_);
            p.column_ = XML_GetCurrentColumnNumber (p.p_);
            XML_StopParser (p.p_, false);
            break;
          }
          return;
        }
      default:
        break;
      }

      // This can be a followup event for another character event. In
      // this case simply append the data.
      //
      if (ps.parsing != XML_PARSING)
      {
        assert (p.event_ == characters);
        p.value_.append (s, n);
      }
      else
      {
        p.event_ = characters;
        p.value_.assign (s, n);

        p.line_ = XML_GetCurrentLineNumber (p.p_);
        p.column_ = XML_GetCurrentColumnNumber (p.p_);

        XML_StopParser (p.p_, true);
      }
    }

    void XMLCALL parser::
    start_namespace_decl_ (void* v, const XML_Char* prefix, const XML_Char* ns)
    {
      parser& p (*static_cast<parser*> (v));

      XML_ParsingStatus ps;
      XML_GetParsingStatus (p.p_, &ps);

      // Expat has a (mis)-feature of a possibily calling handlers even
      // after the non-resumable XML_StopParser call.
      //
      if (ps.parsing == XML_FINISHED)
        return;

      p.start_ns_.push_back (qname_type ());
      p.start_ns_.back ().prefix () = (prefix != 0 ? prefix : "");
      p.start_ns_.back ().namespace_ () = (ns != 0 ? ns : "");
    }

    void XMLCALL parser::
    end_namespace_decl_ (void* v, const XML_Char* prefix)
    {
      parser& p (*static_cast<parser*> (v));

      XML_ParsingStatus ps;
      XML_GetParsingStatus (p.p_, &ps);

      // Expat has a (mis)-feature of a possibily calling handlers even
      // after the non-resumable XML_StopParser call.
      //
      if (ps.parsing == XML_FINISHED)
        return;

      p.end_ns_.push_back (qname_type ());
      p.end_ns_.back ().prefix () = (prefix != 0 ? prefix : "");
    }

    static const char* parser_event_str[] =
    {
      "start element",
      "end element",
      "start attribute",
      "end attribute",
      "characters",
      "start namespace declaration",
      "end namespace declaration",
      "end of file"
    };

    ostream&
    operator<< (ostream& os, parser::event_type e)
    {
      return os << parser_event_str[e];
    }
  }
}

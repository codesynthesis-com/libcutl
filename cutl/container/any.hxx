// file      : cutl/container/any.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#ifndef CUTL_CONTAINER_ANY_HXX
#define CUTL_CONTAINER_ANY_HXX

#include <memory>   // std::auto_ptr
#include <typeinfo> // std::type_info

namespace cutl
{
  namespace container
  {
    class any
    {
    public:
      struct typing {};

    public:
      template <typename X>
      any (X const& x)
          : holder_ (new holder_impl<X> (x))
      {
      }

      any (any const& x)
          : holder_ (x.holder_->clone ())
      {
      }

      template <typename X>
      any&
      operator= (X const& x)
      {
        holder_.reset (new holder_impl<X> (x));
        return *this;
      }

      any&
      operator= (any const& x)
      {
        holder_.reset (x.holder_->clone ());
        return *this;
      }

    public:
      template <typename X>
      X&
      value ()
      {
        if (holder_impl<X>* p = dynamic_cast<holder_impl<X>*> (holder_.get ()))
          return p->value ();
        else
          throw typing ();
      }

      template <typename X>
      X const&
      value () const
      {
        if (holder_impl<X>* p = dynamic_cast<holder_impl<X>*> (holder_.get ()))
          return p->value ();
        else
          throw typing ();
      }

    public:
      std::type_info const&
      type_info () const
      {
        return holder_->type_info ();
      }

    private:
      class holder
      {
      public:
        virtual
        ~holder () {}

        virtual holder*
        clone () const = 0;

        virtual std::type_info&
        type_info () const = 0;
      };

      template <typename X>
      class holder_impl: public holder
      {
      public:
        holder_impl (X const& x)
            : x_ (x)
        {
        }

        virtual holder_impl*
        clone () const
        {
          return new holder_impl (x_);
        }

        virtual std::type_info&
        type_info () const
        {
          return typeid (x_);
        }

        X const&
        value () const
        {
          return x_;
        }

        X&
        value ()
        {
          return x_;
        }

      private:
        X x_;
      };

    private:
      std::auto_ptr<holder> holder_;
    };
  }
}

#endif // CUTL_CONTAINER_ANY_HXX

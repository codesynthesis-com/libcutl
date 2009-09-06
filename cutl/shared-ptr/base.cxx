// file      : cutl/shared-ptr/base.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#include <cutl/shared-ptr/base.hxx>

using std::size_t;

//
//
cutl::share shared = cutl::share (1);
cutl::share exclusive = cutl::share (2);

//
//
namespace cutl
{
  char const* not_shared::
  what () const throw ()
  {
    return "object is not shared";
  }
}

//
//
void*
operator new (size_t n, cutl::share s) throw (std::bad_alloc)
{
  if (s == shared)
  {
    // Here we need to make sure we don't break the alignment of the
    // returned block. For that we need to know the maximum alignment
    // of this platform. Twice the pointer size is a good guess for
    // most platforms.
    //
    size_t* p = static_cast<size_t*> (operator new (n + 2 * sizeof (size_t)));
    *p++ = 1;          // Initial count.
    *p++ = 0xDEADBEEF; // Signature.
    return p;
  }
  else
    return operator new (n);

}

void
operator delete (void* p, cutl::share s) throw ()
{
  // This version of operator delete is only called when the c-tor
  // fails. In this case there is no object and we can just free the
  // memory.
  //
  if (s == shared)
  {
    size_t* sp = static_cast<size_t*> (p);
    sp -= 2;
    operator delete (sp);
  }
  else
    operator delete (p);
}

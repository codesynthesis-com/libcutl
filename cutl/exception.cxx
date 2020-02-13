// file      : cutl/exception.cxx
// license   : MIT; see accompanying LICENSE file

#include <typeinfo>

#include <cutl/exception.hxx>

namespace cutl
{
  char const* exception::
  what () const LIBCUTL_NOTHROW_NOEXCEPT
  {
    return typeid (*this).name ();
  }
}

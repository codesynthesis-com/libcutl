// file      : cutl/fs/exception.cxx
// license   : MIT; see accompanying LICENSE file

#include <cutl/fs/exception.hxx>

namespace cutl
{
  namespace fs
  {
    char const* error::
    what () const LIBCUTL_NOTHROW_NOEXCEPT
    {
      return "filesystem error";
    }
  }
}

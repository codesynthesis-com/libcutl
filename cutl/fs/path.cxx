// file      : cutl/fs/path.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2010 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#ifdef _WIN32
#  include <direct.h> // _getcwd, _wgetcwd, _MAX_PATH
#else
#  include <stdlib.h> // mbstowcs
#  include <limits.h> // PATH_MAX
#  include <unistd.h> // getcwd
#endif

#include <cutl/fs/path.hxx>

namespace cutl
{
  namespace fs
  {
    char const* invalid_path_base::
    what () const throw ()
    {
      return "invalid filesystem path";
    }

    template <>
    basic_path<char> basic_path<char>::
    current ()
    {
#ifdef _WIN32
      char cwd[_MAX_PATH];
      if(_getcwd(cwd, _MAX_PATH) == 0)
        throw invalid_basic_path<char> (".");
#else
      char cwd[PATH_MAX];
      if (getcwd (cwd, PATH_MAX) == 0)
        throw invalid_basic_path<char> (".");
#endif

      return basic_path<char> (cwd);
    }

    template <>
    basic_path<wchar_t> basic_path<wchar_t>::
    current ()
    {
#ifdef _WIN32
      wchar_t wcwd[_MAX_PATH];
      if(_wgetcwd(wcwd, _MAX_PATH) == 0)
        throw invalid_basic_path<wchar_t> (".");
#else
      char cwd[PATH_MAX];
      if (getcwd (cwd, PATH_MAX) == 0)
        throw invalid_basic_path<wchar_t> (L".");

      wchar_t wcwd[PATH_MAX];
      if (mbstowcs (wcwd, cwd, PATH_MAX) == size_type (-1))
        throw invalid_basic_path<wchar_t> (L".");
#endif

      return basic_path<wchar_t> (wcwd);
    }
  }
}

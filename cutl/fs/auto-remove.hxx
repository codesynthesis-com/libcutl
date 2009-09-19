// file      : cutl/fs/auto-remove.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#ifndef CUTL_FS_AUTO_REMOVE_HXX
#define CUTL_FS_AUTO_REMOVE_HXX

#include <vector>

#include <cutl/exception.hxx>
#include <cutl/fs/path.hxx>

namespace cutl
{
  namespace fs
  {
    // Remove a file or an empty directory on destruction unless canceled.
    //
    struct auto_remove
    {
      explicit
      auto_remove (path const& p)
          : path_ (p), canceled_ (false)
      {
      }

      ~auto_remove ();

      void
      cancel ()
      {
        canceled_ = true;
      }

    private:
      auto_remove (auto_remove const&);

      auto_remove&
      operator= (auto_remove const&);

    private:
      path path_;
      bool canceled_;
    };

    // Remove a list of file or aempty directories on destruction unless
    // canceled.
    //
    struct auto_removes
    {
      ~auto_removes ();

      void
      add (path const& p)
      {
        paths_.push_back (p);
      }

      void
      cancel ()
      {
        canceled_ = true;
      }

    private:
      auto_removes (auto_removes const&);

      auto_removes&
      operator= (auto_removes const&);

    private:
      typedef std::vector<path> paths;

      paths paths_;
      bool canceled_;
    };
  }
}

#endif // CUTL_FS_AUTO_REMOVE_HXX

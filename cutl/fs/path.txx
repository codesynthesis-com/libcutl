// file      : cutl/fs/path.txx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2010 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

namespace cutl
{
  namespace fs
  {
    template <typename C>
    basic_path<C> basic_path<C>::
    leaf () const
    {
      size_type p (traits::rfind_separator (path_));

      return p != string_type::npos
        ? basic_path (path_.c_str () + p + 1, path_.size () - p - 1)
        : *this;
    }

    template <typename C>
    basic_path<C> basic_path<C>::
    directory () const
    {
      if (root ())
        return basic_path ();

      size_type p (traits::rfind_separator (path_));

      // Include the trailing slash so that we get correct behavior
      // if directory is root.
      //
      return p != string_type::npos
        ? basic_path (path_.c_str (), p + 1)
        : basic_path ();
    }

    template <typename C>
    basic_path<C> basic_path<C>::
    base () const
    {
      size_type i (path_.size ());

      for (; i > 0; --i)
      {
        if (path_[i - 1] == '.')
          break;

        if (traits::is_separator (path_[i - 1]))
        {
          i = 0;
          break;
        }
      }

      // Weed out paths like ".txt" and "/.txt"
      //
      if (i > 1 && !traits::is_separator (path_[i - 2]))
      {
        return basic_path (path_.c_str (), i - 1);
      }
      else
        return *this;
    }

    template <typename C>
    basic_path<C>& basic_path<C>::
    operator/= (basic_path<C> const& r)
    {
      if (r.root ())
        throw invalid_basic_path<C> (r.path_);

      if (path_.empty () || r.path_.empty ())
      {
        path_ += r.path_;
        return *this;
      }

      if (!root ())
        path_ += traits::directory_separator;

      path_ += r.path_;

      return *this;
    }

    template <typename C>
    void basic_path<C>::
    init ()
    {
      // Strip trailing slashes except for the case where the single
      // slash represents the root directory.
      //
      size_type n (path_.size ());
      for (; n > 1 && traits::is_separator (path_[n - 1]); --n) ;
      path_.resize (n);
    }
  }
}

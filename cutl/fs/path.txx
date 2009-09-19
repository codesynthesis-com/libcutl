// file      : cutl/fs/path.txx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

namespace cutl
{
  namespace fs
  {
    template <typename C>
    basic_path<C> basic_path<C>::
    leaf () const
    {
      size_type n (path_.size ()), i (n);

      for (; i > 0; --i)
      {
        if (path_[i - 1] == '/' || path_[i - 1] == '\\')
          break;
      }

      return i != 0 ? basic_path (path_.c_str () + i, n - i) : *this;
    }

    template <typename C>
    basic_path<C> basic_path<C>::
    directory () const
    {
      size_type i (path_.size ());

      for (; i > 0; --i)
      {
        if (path_[i - 1] == '/' || path_[i - 1] == '\\')
          break;
      }

      return i != 0 ? basic_path (path_.c_str (), i - 1) : *this;
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

        if (path_[i - 1] == '/' || path_[i - 1] == '\\')
        {
          i = 0;
          break;
        }
      }

      // Weed out paths like ".txt" and "/.txt"
      //
      if (i > 1 && path_[i - 2] != '/' && path_[i - 2] != '\\')
      {
        return basic_path (path_.c_str (), i - 1);
      }
      else
        return *this;
    }

    template <typename C>
    basic_path<C> basic_path<C>::
    operator/ (basic_path<C> const& r)
    {
      if (r.path_.empty ())
        throw invalid_basic_path<C> (r.path_);

      basic_path<C> x (*this);
      x.path_ += '/';
      x.path_ += r.path_;
      return x;
    }

    template <typename C>
    void basic_path<C>::
    init (bool internal)
    {
      if (!internal && path_.empty ())
        throw invalid_basic_path<C> (path_);

      // Strip trailing slashes. This way empty string represents
      // root directory.
      //
      size_type n (path_.size ());
      for (; n > 0 && (path_[n - 1] == '/' || path_[n - 1] == '\\'); --n) ;
      path_.resize (n);
    }
  }
}

// file      : tests/fs/path/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2010 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#include <cassert>

#include <cutl/fs/path.hxx>

using namespace cutl::fs;

int
main ()
{
  assert (path ("/").string () == "/");
  assert (path ("//").string () == "/");
  assert (path ("/tmp/foo/").string () == "/tmp/foo");
#ifdef _WIN32
  assert (path ("\\\\").string () == "\\");
  assert (path ("/\\").string () == "/");
  assert (path ("C:").string () == "C:");
  assert (path ("C:\\").string () == "C:");
  assert (path ("C:\\tmp\\foo\\").string () == "C:\\tmp\\foo");
#endif

  // leaf
  //
  assert (path ("/").leaf ().string () == "");
  assert (path ("/tmp").leaf ().string () == "tmp");
  assert (path ("//tmp").leaf ().string () == "tmp");
#ifdef _WIN32
  assert (path ("C:").leaf ().string () == "C:");
  assert (path ("C:\\tmp").leaf ().string () == "tmp");
  assert (path ("C:\\\\tmp").leaf ().string () == "tmp");
#endif

  // directory
  //
  assert (path ("/").directory ().string () == "");
  assert (path ("/tmp").directory ().string () == "/");
  assert (path ("//tmp").directory ().string () == "/");
#ifdef _WIN32
  assert (path ("C:").directory ().string () == "");
  assert (path ("C:\\tmp").directory ().string () == "C:");
  assert (path ("C:\\\\tmp").directory ().string () == "C:");
#endif

  // base
  //
  assert (path ("/").base ().string () == "/");
  assert (path ("/foo.txt").base ().string () == "/foo");
  assert (path (".txt").base ().string () == ".txt");
  assert (path ("/.txt").base ().string () == "/.txt");
  assert (path ("foo.txt.orig").base ().string () == "foo.txt");
#ifdef _WIN32
  assert (path ("C:").base ().string () == "C:");
  assert (path ("C:\\foo.txt").base ().string () == "C:\\foo");
#endif

  // operator/
  //
#ifndef _WIN32
  assert ((path ("/") / path ("tmp")).string () == "/tmp");
  assert ((path ("foo") / path ("bar")).string () == "foo/bar");
#else
  assert ((path ("\\") / path ("tmp")).string () == "\\tmp");
  assert ((path ("C:\\") / path ("tmp")).string () == "C:\\tmp");
  assert ((path ("foo") / path ("bar")).string () == "foo\\bar");
#endif

}

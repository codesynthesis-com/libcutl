// file      : tests/fs/path/driver.cxx
// copyright : Copyright (c) 2009-2012 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#include <cassert>
#include <iostream>

#include <cutl/fs/path.hxx>

using std::cerr;
using std::endl;

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

  // abslote/relative/root
  //
#ifndef _WIN32
  assert (path ("/").root ());
  assert (path ("//").root ());
  assert (path ("/").absolute ());
  assert (path ("/foo/bar").absolute ());
  assert (path ("bar/baz").relative ());
#else
  assert (path ("C:").root ());
  assert (path ("C:\\").root ());
  assert (path ("C:\\").absolute ());
  assert (path ("C:\\foo\\bar").absolute ());
  assert (path ("bar\\baz").relative ());
#endif


  // leaf
  //
#ifndef _WIN32
  assert (path ("/").leaf ().string () == "");
  assert (path ("/tmp").leaf ().string () == "tmp");
  assert (path ("//tmp").leaf ().string () == "tmp");
#else
  assert (path ("C:").leaf ().string () == "C:");
  assert (path ("C:\\tmp").leaf ().string () == "tmp");
  assert (path ("C:\\\\tmp").leaf ().string () == "tmp");
#endif

  // directory
  //
#ifndef _WIN32
  assert (path ("/").directory ().string () == "");
  assert (path ("/tmp").directory ().string () == "/");
  assert (path ("//tmp").directory ().string () == "/");
#else
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

  // normalize
  //
#ifndef _WIN32
  assert (path ("../foo").normalize ().string () == "../foo");
  assert (path ("..///foo").normalize ().string () == "../foo");
  assert (path ("../../foo").normalize ().string () == "../../foo");
  assert (path (".././foo").normalize ().string () == "../foo");
  assert (path (".").normalize ().string () == "");
  assert (path ("./..").normalize ().string () == "..");
  assert (path ("../.").normalize ().string () == "..");
  assert (path ("foo/./..").normalize ().string () == "");
  assert (path ("/foo/./..").normalize ().string () == "/");
  assert (path ("./foo").normalize ().string () == "foo");
#else
  assert (path ("../foo").normalize ().string () == "..\\foo");
  assert (path ("..///foo").normalize ().string () == "..\\foo");
  assert (path ("..\\../foo").normalize ().string () == "..\\..\\foo");
  assert (path (".././foo").normalize ().string () == "..\\foo");
  assert (path (".").normalize ().string () == "");
  assert (path ("./..").normalize ().string () == "..");
  assert (path ("../.").normalize ().string () == "..");
  assert (path ("foo/./..").normalize ().string () == "");
  assert (path ("C:/foo/./..").normalize ().string () == "c:");
  assert (path ("./foo").normalize ().string () == "foo");

  assert (path ("C:").normalize ().string () == "c:");
  assert (path ("C:\\Foo12//Bar").normalize ().string () == "c:\\foo12\\bar");
#endif

  /*
  path p ("../foo");
  p.complete ();

  cerr << path::current () << endl;
  cerr << p << endl;
  p.normalize ();
  cerr << p << endl;
  */
}

// file      : tests/compiler/sloc-counter/driver.cxx
// copyright : Copyright (c) 2009-2013 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#include <fstream>
#include <iostream>

#include <cutl/compiler/code-stream.hxx>
#include <cutl/compiler/sloc-counter.hxx>

using namespace std;
using namespace cutl::compiler;

int
main (int argc, char* argv[])
{
  if (argc != 2)
  {
    cerr << "usage: " << argv[0] << " <file>" << endl;
    return 1;
  }

  ostream_filter<sloc_counter, char> filt (cout);

  ifstream ifs(argv[1]);

  for (istream::int_type c (ifs.get ());
       c != istream::traits_type::eof ();
       c = ifs.get ())
  {
    cout.put (istream::traits_type::to_char_type (c));
  }

  cout << endl
       << filt.stream ().count () << endl;
}

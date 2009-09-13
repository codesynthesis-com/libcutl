// file      : tests/compiler/cxx-indenter/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#include <fstream>
#include <iostream>

#include <cutl/compiler/code-stream.hxx>
#include <cutl/compiler/cxx-indenter.hxx>

using namespace std;
using namespace cutl::compiler;

int
main ()
{
  //std::wostream& os (wcout);
  //ostream_filter<cxx_indenter, wchar_t> filt (os);

  std::ostream& os (cout);
  ostream_filter<cxx_indenter, char> filt (os);

  os << "if (true)"
     << "{"
     << "// Hello there" << endl
     << "//" << endl
     << "a ();"
     << "}"
     << "else"
     << "{"
     << "b ();"
     << "}";

  os << "if (false)"
     << "{"
     << "if (true)"
     << "{"
     << "// test" << endl
     << "}"
     << "else"
     << "{"
     << "// test" << endl
     << "b ();"
     << "}"
     << "}";

  os << "namespace a"
     << "{"
     << "void f ();"
     << "}"
     << "#if defined(__HP_aCC) && __HP_aCC <= 39999" << endl
     << "#include <foo.h>" << endl
     << "#endif" << endl
     << endl
     << "namespace b"
     << "{"
     << "void f ();"
     << "}";

  // Test do-while handling.
  //
  os << "do" << endl
     << "f ();"
     << "while (false);"
     << endl;

  os << "do"
     << "{"
     << "f ();"
     << "}"
     << "while (false);"
     << endl;

  os << "do"
     << "{"
     << "if (f ())"
     << "{"
     << "g ();"
     << "}"
     << "}"
     << "while (false);"
     << endl;

  os << "do"
     << "{"
     << "do" << endl
     << "f ();"
     << "while (false);"
     << "}"
     << "while (false);"
     << endl;

  os << "do"
     << "{"
     << "do"
     << "{"
     << "f ();"
     << "}"
     << "while (false);"
     << "}"
     << "while (false);"
     << endl;
}

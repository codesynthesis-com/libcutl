// file      : tests/re/driver.cxx
// copyright : Copyright (c) 2009-2013 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#include <string>
#include <cassert>
#include <iostream>

#include <cutl/re.hxx>

using namespace cutl::re;

int
main ()
{
  // empty() and str().
  //
  {
    regex r;
    assert (r.empty ());
    r = "['`]foo([^ ]*)bar['`]";
    assert (!r.empty ());
    assert (r.str () == "['`]foo([^ ]*)bar['`]");
  }

  // Error handling.
  //
  try
  {
    regex r ("['`]foo([^ ]*bar['`]");
    assert (false);
  }
  catch (format const& e)
  {
    assert (e.regex () == "['`]foo([^ ]*bar['`]");
    assert (!e.description ().empty ());
    //std::cerr << e.description () << std::endl;
  }

  // match(), search(), and replace().
  //
  {
    regex r ("['`]foo([^ ]*)bar['`]");

    assert (r.match ("'foofoxbar'"));
    assert (!r.match ("'foof xbar'"));

    assert (r.search ("prefix 'foofoxbar' suffix"));
    assert (!r.search ("prefix 'foof xbar' suffix"));

    assert (r.replace ("'foofoxbar'", "\\u$1") == "Fox");
  }

  // regexsub
  //
  {
    regexsub r ("/['`]foo([^ ]*)bar['`]/\\u$1/");

    assert (r.replace ("'foofoxbar'") == "Fox");
  }

  // regexsub escaping
  //
  {
    regexsub r ("#a\\#\\\\#a?\\\\#");

    assert (r.replace ("a#\\") == "a?\\");
  }

  // regexsub error handling.
  //
  try
  {
    regexsub r ("/['`]foo([^ ]*)bar['`]#\\u$1/");
    assert (false);
  }
  catch (format const& e)
  {
    assert (e.regex () == "/['`]foo([^ ]*)bar['`]#\\u$1/");
    assert (!e.description ().empty ());
    //std::cerr << e.description () << std::endl;
  }
}

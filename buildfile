# file      : buildfile
# copyright : Copyright (c) 2009-2013 Code Synthesis Tools CC
# license   : MIT; see accompanying LICENSE file

d = cutl/ tests/
./: $d doc{INSTALL LICENSE NEWS README version} file{manifest}
include $d

# Don't install tests or the INSTALL file.
#
dir{tests/}: install = false
doc{INSTALL}@./: install = false

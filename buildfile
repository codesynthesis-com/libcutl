# file      : buildfile
# copyright : Copyright (c) 2009-2017 Code Synthesis Tools CC
# license   : MIT; see accompanying LICENSE file

./: {*/ -build/ -doc/ -m4/} doc{INSTALL LICENSE NEWS README version} \
    file{manifest}

# Don't install tests or the INSTALL file.
#
dir{tests/}:     install = false
doc{INSTALL}@./: install = false

# file      : buildfile
# license   : MIT; see accompanying LICENSE file

./: {*/ -build/ -doc/} doc{INSTALL NEWS README} legal{LICENSE} manifest

# Don't install tests or the INSTALL file.
#
tests/:          install = false
doc{INSTALL}@./: install = false

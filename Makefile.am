## Process this file with automake to produce Makefile.in

AUTOMAKE_OPTIONS = foreign 1.7

ACLOCAL_AMFLAGS = -I m4

# Libtools versioning is as follows: current:revision:age (c:r:a)
#
#  * If anything have changed in the source code, increase revision.
#    Next version will be (c:r+1:a)
#
#  * If interface have changed (added, removed or changed functions)
#    Next version will be (c+1:0:a)
#
#  * If any interfaces have been added, increate age.
#    Next version will be (c:r:a+1)
#
#  * If any interfaces have been removed or changed, reset age to 0.
#    Next version will be (c:r:0)
#
VERSION_INFO = 1:0:0

# Release versioning is (major:minor)
# The Name of the final version (major:minor:interface)
# where interface is described by the VERSION_INFO above.
RELEASE = 0.1

GENERIC_LDFLAGS = -release $(RELEASE) -version-info $(VERSION_INFO)

lib_LTLIBRARIES = libde.la

libde_la_SOURCES = src/Emitter.cpp
libde_la_LDFLAGS = $(GENERIC_LDFLAGS)

include_HEADERS    = src/de.h
pkginclude_HEADERS = src/Emitter.h

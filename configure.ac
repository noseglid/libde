#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)

# Additional m4 scripts
AC_CONFIG_MACRO_DIR([m4])

AC_INIT(libde, 0.1, noseglid@gmail.com)
AC_LANG(C++)
AX_CXX_COMPILE_STDCXX_11

AM_INIT_AUTOMAKE([1.7 foreign])

# Required headers
AC_CONFIG_SRCDIR([src/Emitter.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LIBTOOL

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_TYPE_SIZE_T

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

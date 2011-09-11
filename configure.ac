dnl Process this file with autoconf to produce a configure script.

AC_INIT(IndigoPlayer, 1.0)
AC_PREREQ(2.59)

AM_INIT_AUTOMAKE([1.10 -Wall no-define])

AC_CONFIG_HEADER([config.h])

AC_PROG_CXX

PKG_CHECK_MODULES([DEPS], [gtkmm-2.4 >= 1.0.0 log4cpp >= 1.0])

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
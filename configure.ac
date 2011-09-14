dnl Process this file with autoconf to produce a configure script.

AC_INIT(indigoplayer, 1.0)
AC_PREREQ(2.59)

AM_INIT_AUTOMAKE([1.10 -Wall no-define])

AC_CONFIG_HEADER([config.h])

AC_PROG_CXX

PKG_CHECK_MODULES([DEPS], [gtkmm-2.4 >= 1.0.0 log4cpp >= 1.0])

# I18n
GETTEXT_PACKAGE=indigoplayer
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED([GETTEXT_PACKAGE], ["$GETTEXT_PACKAGE"],
		   [The domain name to use with gettext.])

# List all available languages here
ALL_LINGUAS="sk"
AM_GLIB_GNU_GETTEXT

AC_CONFIG_FILES([Makefile po/Makefile.in bin/Makefile])
AC_OUTPUT

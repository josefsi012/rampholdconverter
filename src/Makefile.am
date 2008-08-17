## Process this file with automake to produce Makefile.in

# Copyright (C) 2008 Jose Negron <Jose.Negron@FlightSafety.com>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

bin_PROGRAMS = rampholdconverter
rampholdconverter_SOURCES = main.c usage.c usage.h nav_iplib.h nav_iplib.c reposn.c reposn.h utils.c utils.h
AM_CPPFLAGS = -I$(top_builddir)/lib -I$(top_srcdir)/lib
LDADD = $(top_srcdir)/lib/libgnu.a


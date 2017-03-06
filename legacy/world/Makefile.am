#
# @file legacy/world/Makefile.am
# @brief automake recipe for Legacy world submodule
#
# Copyright 2016 Stephen M. Webb  <stephen.webb@bregmasoft.ca>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

noinst_LTLIBRARIES = liblegacyworld.la libnoise.la

libnoise_la_SOURCES = \
  ${top_srcdir}/legacy/3rd_party/FastNoise/FastNoise.h ${top_srcdir}/legacy/3rd_party/FastNoise/FastNoise.cpp

libnoise_la_CPPFLAGS = \
  -I${top_srcdir} \
  -I${top_srcdir}/legacy/3rd_party

libnoise_la_CXXFLAGS = \
  $(AM_CXXFLAGS) \
  -Wno-strict-aliasing -Wno-maybe-uninitialized -Wno-unused-function

liblegacyworld_la_SOURCES = \
  cell.h \
  cellcache.h \
  map.h              map.cpp \
  maplayer.h         maplayer.cpp \
  mapbuildersimple.h mapbuildersimple.cpp \
  mapbuilderstatic.h mapbuilderstatic.cpp \
  mapbuilderstream.h mapbuilderstream.cpp

liblegacyworld_la_CPPFLAGS = \
  -I${top_srcdir} \
  -I${top_srcdir}/legacy/3rd_party

liblegacyworld_la_LIBADD = \
  libnoise.la


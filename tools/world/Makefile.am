#
# @file tools/world/Makefile.am
# @brief automake recipe for Legacy world tools
#
# Copyright 2011-2016 Stephen M. Webb  <stephen.webb@bregmasoft.ca>
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

bin_PROGRAMS = \
  dump_map

dump_map_SOURCES = \
  dump_map.cpp

dump_map_CPPFLAGS = \
  -I${top_srcdir}

dump_map_LDADD = \
  ${top_builddir}/legacy/world/liblegacyworld.la

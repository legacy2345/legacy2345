#
# @file tools/character/Makefile.am
# @brief automake recipe for Legacy world tools
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

bin_PROGRAMS = \
  test_character_namegen

test_character_namegen_SOURCES = \
  test_character_namegen.cpp

test_character_namegen_CPPFLAGS = \
  -I${top_srcdir}

test_character_namegen_LDADD = \
  ${top_builddir}/legacy/character/liblegacycharacter.la \
  ${top_builddir}/legacy/core/liblegacycore.la

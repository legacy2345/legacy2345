#
# @file legacy/tests/character/Makefile.am
# @brief automake recipe for Legacy character submodule tests
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

check_PROGRAMS = test_character

test_character_SOURCES = \
  test_character.cpp \
  test_name_generator.cpp \
  test_sexuality.cpp

test_character_CPPFLAGS = \
  -I$(top_srcdir) \
  -I$(top_srcdir)/legacy/tests/3rd_party

test_character_LDADD = \
  ${top_builddir}/legacy/character/liblegacycharacter.la \
  ${top_builddir}/legacy/core/liblegacycore.la

TESTS = $(check_PROGRAMS)

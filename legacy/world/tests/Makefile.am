#
# @file legacy/world/tests/Makefile.am
# @brief automake recipe for Legacy world submodule tests
#
# Copyright 20162-17 Stephen M. Webb  <stephen.webb@bregmasoft.ca>
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

check_PROGRAMS = test_world

test_world_SOURCES = \
  fake_mapbuilder.h \
  test_cell.cpp \
  test_cellcache.cpp \
  test_map.cpp \
  test_map_save_and_load.cpp \
  test_maplayer.cpp \
  test_world.cpp 

test_world_CPPFLAGS = \
  -I$(top_srcdir) \
  -I$(top_srcdir)/legacy/3rd_party \
  -I$(top_srcdir)/legacy/3rd_party/catch

test_world_LDADD = \
  ${top_builddir}/legacy/world/liblegacyworld.la

LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) $(top_srcdir)/config.aux/tap-driver.sh

TESTS = $(check_PROGRAMS)

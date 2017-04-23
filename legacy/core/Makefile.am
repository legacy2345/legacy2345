#
# @file legacy/core/Makefile.am
# @brief automake recipe for Legacy core submodule
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

SUBDIRS = . tests

noinst_LTLIBRARIES = liblegacycore.la

liblegacycore_la_SOURCES = \
  argparse.h          argparse.cpp \
  config.h            config.cpp \
  config_file.h       config_file.cpp \
  config_paths.h      config_paths.cpp \
  filesystem.h        filesystem.cpp \
  logger.h            logger.cpp \
  posix_filesystem.h  posix_filesystem.cpp \
  random.h            random.cpp

liblegacycore_la_CPPFLAGS = \
  -I${top_srcdir} \
  -I${top_srcdir}/legacy/3rd_party

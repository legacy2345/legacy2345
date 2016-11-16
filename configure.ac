#
# @file configure.ac
# @brief autoconf recipe for the Legacy project
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

AC_PREREQ(2.67)
AC_COPYRIGHT([Copyright 201102016 Stephen M. Webb  <stephen.webb@bregmasoft.ca>])
AC_INIT([Legacy 2345],
        [0.3.0],
        [stephen.webb@bregmasoft.ca],
        [legacy2345],
        [http://legacy2345.github.io/development/]])
AC_CONFIG_AUX_DIR([config.aux])
AC_CONFIG_MACRO_DIRS([m4])
AM_INIT_AUTOMAKE([1.11 foreign -Wall color-tests])
AM_SILENT_RULES([yes])
AC_CONFIG_HEADER([legacy_config.h])

# Checks for required tools
AC_PROG_CXX
AC_LANG([C++])
AM_PROG_AR
LT_PREREQ([2.4.2])
LT_INIT

# Check compiler support
legacy_save_cxxflags="$CXXFLAGS"
CXXFLAGS="$CXXFLAGS -fvisibility=hidden"
AC_CACHE_CHECK([if ]$CXX[ supports -fvisibility-hidden],
               [legacy_cv_cxx_flag_visibility_hidden],
               AC_COMPILE_IFELSE([AC_LANG_SOURCE([int i;])],
                                 [legacy_cv_cxx_flag_visibility_hidden=yes],
                                 [legacy_cv_cxx_flag_visibility_hidden=no]))
if test x$legacy_cv_cxx_flag_visibility_hidden = xyes; then
  AM_CXXFLAGS="-fvisibility=hidden $AM_CXXFLAGS"
fi
CXXFLAGS="$legacy_save_cxxflags"
AC_CACHE_CHECK([if ]$CXX[ supports -std=c++11],
               [legacy_cv_cxx_std_cxx11],
               AC_COMPILE_IFELSE([AC_LANG_SOURCE([int i;])],
                                 [legacy_cv_cxx_std_cxx11=yes],
                                 [AC_MSG_FAILURE([C++11 support is required])]))
if test x$legacy_cv_cxx_std_cxx11 = xyes; then
  AM_CXXFLAGS="-std=c++11 $AM_CXXFLAGS"
fi
CXXFLAGS="$legacy_save_cxxflags"

# Checks for required external packages
#PKG_CHECK_MODULES([SDL],       [sdl SDL_image])
#PKG_CHECK_MODULES([GL],        [gl glew])
#PKG_CHECK_MODULES([FREETYPE],  [freetype2])

AC_DEFINE([LEGACY_UNUSED],[__attribute__((unused))],[symbol is unused])
AC_SUBST(AM_CXXFLAGS, "-Wall -Wextra -pedantic $AM_CXXFLAGS")

AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([legacy/Makefile])
AC_CONFIG_FILES([legacy/core/Makefile])
AC_CONFIG_FILES([legacy/character/Makefile])
AC_CONFIG_FILES([legacy/world/Makefile])
AC_CONFIG_FILES([legacy/tests/Makefile])
AC_CONFIG_FILES([legacy/tests/core/Makefile])
AC_CONFIG_FILES([legacy/tests/character/Makefile])
AC_CONFIG_FILES([legacy/tests/world/Makefile])
AC_CONFIG_FILES([tools/Makefile])
AC_CONFIG_FILES([tools/world/Makefile])
AC_OUTPUT

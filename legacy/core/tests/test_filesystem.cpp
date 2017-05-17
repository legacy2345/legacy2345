/**
 * @file legacy/core/tests/test_filesystem.cpp
 * @brief Tests for the Legacy core filesystem module.
 */

/*
 * Copyright 2017 Stephen M. Webb <stephen.webb@bregmasoft.ca>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "catch/catch.hpp"
#include "legacy/core/filesystem.h"

using namespace Legacy::Core;


SCENARIO("basic path operations")
{
  GIVEN("a Path created from a string with a single directory and filename")
  {
    std::string simple_path_string = "/dir/file";
    Path path(simple_path_string);

    WHEN("a copy is made")
    {
      Path path_copy = path;

      THEN("it evaluates as equal to the original")
      {
        REQUIRE(path_copy == path);
      }
    }

    WHEN("its string() is observed")
    {
      THEN("it matches the original string.")
      {
        REQUIRE(path.string() == simple_path_string);
      }
    }

    WHEN("its basename is taken")
    {
      THEN("it matches the last part of the string after the rightmost separator")
      {
        REQUIRE(path.basename() == "file");
      }
    }

    WHEN("its dirname is taken")
    {
      THEN("it matches the part of the string up to the rightmost separator")
      {
        REQUIRE(path.dirname() == "/dir");
      }
    }
  }
}

SCENARIO("path basename edge cases")
{
  GIVEN("a Path with a directory, ending in a path separator")
  {
    Path path("/some/dir/");
    WHEN("the basename is examined")
    {
      THEN("is should be just the directory name, no slash")
      {
        REQUIRE(path.basename() == "dir");
      }
    }
  }
  GIVEN("a path consisting of a filename starting with path separator")
  {
    Path path("/filename");
    WHEN("the basename is examined")
    {
      THEN("is should be just the filename")
      {
        REQUIRE(path.basename() == "filename");
      }
    }
  }
  GIVEN("a path consisting of just the filename")
  {
    Path path("filename");
    WHEN("the basename is examined")
    {
      THEN("is should be just the filename")
      {
        REQUIRE(path.basename() == "filename");
      }
    }
  }
  GIVEN("a path consisting of just the root")
  {
    Path path("/");
    WHEN("the basename is examined")
    {
      THEN("it should be unchanged")
      {
        REQUIRE(path.basename() == "/");
      }
    }
  }
  GIVEN("an empty path")
  {
    Path path("");
    WHEN("the basename is examined")
    {
      THEN("it should be empty")
      {
        REQUIRE(path.basename() == "");
      }
    }
  }
}

SCENARIO("path dirname edge cases")
{
  GIVEN("a path consisting of just the root")
  {
    Path path("/");
    WHEN("the dirname is examined")
    {
      THEN("it should be unchanged")
      {
        REQUIRE(path.dirname() == "/");
      }
    }
  }
  GIVEN("an empty path")
  {
    Path path("");
    WHEN("the dirname is examined")
    {
      THEN("it should be dot")
      {
        REQUIRE(path.dirname() == ".");
      }
    }
  }
}

SCENARIO("appending paths")
{
  GIVEN("a path")
  {
    Path path("/dir/");
    WHEN("a filename is appended")
    {
      Path path2 = path / "filename";
      THEN("the resulting path is as expected")
      {
        REQUIRE(path2.string() == "/dir/filename");
      }
    }
  }
}

SCENARIO("parsing a colon-separated pathlist_string into a PathList")
{
  std::string path_1 = "/home/gflingus";
  std::string path_2 = "/usr/share/data";
  GIVEN("an empty pathlist_string")
  {
    std::string pathlist_string = "";
    WHEN("a PathList is created from it")
    {
      PathList path_list = create_pathlist_from_string(pathlist_string);
      THEN("the resulting PathList should be empty.")
      {
        REQUIRE(path_list.size() == 0);
      }
    }
  }
  GIVEN("a pathlist_string with one entry, no colons")
  {
    std::string pathlist_string = path_1;
    WHEN("a PathList is created from it")
    {
      PathList path_list = create_pathlist_from_string(pathlist_string);
      THEN("the resulting PathList should have one entry equal to the original string.")
      {
        REQUIRE(path_list.size() == 1);
        REQUIRE(path_list[0] == pathlist_string);
      }
    }
  }
  GIVEN("a pathlist_string with one entry, one colon at the beginning")
  {
    std::string pathlist_string = ":" + path_1;
    WHEN("a PathList is created from it")
    {
      PathList path_list = create_pathlist_from_string(pathlist_string);
      THEN("the resulting PathList should have one entry.")
      {
        REQUIRE(path_list.size() == 1);
        REQUIRE(path_list[0] == path_1);
      }
    }
  }
  GIVEN("a pathlist_string with one entry, one colon at the end")
  {
    std::string pathlist_string = path_1 + ":";
    WHEN("a PathList is created from it")
    {
      PathList path_list = create_pathlist_from_string(pathlist_string);
      THEN("the resulting PathList should have one entry.")
      {
        REQUIRE(path_list.size() == 1);
        REQUIRE(path_list[0] == path_1);
      }
    }
  }
  GIVEN("a pathlist_string with two entries")
  {
    std::string pathlist_string = path_1 + ":" + path_2;
    WHEN("a PathList is created from it")
    {
      PathList path_list = create_pathlist_from_string(pathlist_string);
      THEN("the resulting PathList should have two entries.")
      {
        REQUIRE(path_list.size() == 2);
        REQUIRE(path_list[0] == path_1);
        REQUIRE(path_list[1] == path_2);
      }
    }
  }
  GIVEN("a pathlist_string with two entries and two colons")
  {
    std::string pathlist_string = path_1 + "::" + path_2;
    WHEN("a PathList is created from it")
    {
      PathList path_list = create_pathlist_from_string(pathlist_string);
      THEN("the resulting PathList should have two entries.")
      {
        REQUIRE(path_list.size() == 2);
        REQUIRE(path_list[0] == path_1);
        REQUIRE(path_list[1] == path_2);
      }
    }
  }
}

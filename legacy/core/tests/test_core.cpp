#define CATCH_CONFIG_RUNNER
#include "catch/catch.hpp"
#include "catch/catch_reporter_tap.hpp"

int
main(int argc, char* argv[])
{
  Catch::Session session;

  int return_code = session.applyCommandLine(argc, argv);
  if (return_code != 0)
    return return_code;

  session.configData().reporterNames.push_back("tap");

  int num_failed = session.run();
  return num_failed < 0xff ? num_failed : 0xff;
}


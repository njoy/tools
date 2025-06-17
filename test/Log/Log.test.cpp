// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/Log.hpp"

// other includes
#include <fstream>
#include <sstream>
#include <filesystem>

// convenience typedefs
using namespace njoy::tools;

std::string getContent( std::string filename ) {

  std::stringstream ss;
  std::ifstream fs( filename, std::ifstream::in );
  ss << fs.rdbuf();
  return ss.str();
}

SCENARIO( "Log" ) {

  GIVEN( "a file name" ) {

    std::string filename = "output.txt";
    std::filesystem::remove( filename ); // ensure the file is not there

    WHEN( "the Log redirects to a file" ) {

      Log::add_sink( filename );

      THEN( "the file contains the log after flushing" ) {

        Log::error( "Some error occurred" );
        Log::warning( "Some warning was issued" );
        Log::info( "Some info was printed" );
        Log::debug( "Some debug info was given" );
        Log::flush();

        std::string content = getContent( filename );

#ifdef NDEBUG
        CHECK( "[error] Some error occurred\n"
               "[warning] Some warning was issued\n"
               "[info] Some info was printed\n" == content );
#else
        CHECK( "[error] Some error occurred\n"
               "[warning] Some warning was issued\n"
               "[info] Some info was printed\n"
               "[debug] Some debug info was given\n"   == content );
#endif
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

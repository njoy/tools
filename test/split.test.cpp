// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/split.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools;

SCENARIO( "split" ) {

  GIVEN( "a string and a string separator" ) {

    std::string empty = "";
    std::string none = "abcdef";
    std::string middle = "ab->cd->ef";
    std::string start = "->ab->cd->ef";
    std::string end = "ab->cd->ef->";

    THEN( "the strings can be split" ) {

      auto result = split( empty, "->" );
      CHECK( 1 == result.size() );
      CHECK( "" == result[0] );

      result = split( none, "->" );
      CHECK( 1 == result.size() );
      CHECK( "abcdef" == result[0] );

      result = split( middle, "->" );
      CHECK( 3 == result.size() );
      CHECK( "ab" == result[0] );
      CHECK( "cd" == result[1] );
      CHECK( "ef" == result[2] );

      result = split( start, "->" );
      CHECK( 4 == result.size() );
      CHECK( "" == result[0] );
      CHECK( "ab" == result[1] );
      CHECK( "cd" == result[2] );
      CHECK( "ef" == result[3] );

      result = split( end, "->" );
      CHECK( 4 == result.size() );
      CHECK( "ab" == result[0] );
      CHECK( "cd" == result[1] );
      CHECK( "ef" == result[2] );
      CHECK( "" == result[3] );
    } // THEN
  } // GIVEN

  GIVEN( "a string and a char separator" ) {

    std::string empty = "";
    std::string none = "abcdef";
    std::string middle = "ab,cd,ef";
    std::string start = ",ab,cd,ef";
    std::string end = "ab,cd,ef,";

    THEN( "the strings can be split" ) {

      auto result = split( empty, ',' );
      CHECK( 1 == result.size() );
      CHECK( "" == result[0] );

      result = split( none, ',' );
      CHECK( 1 == result.size() );
      CHECK( "abcdef" == result[0] );

      result = split( middle, ',' );
      CHECK( 3 == result.size() );
      CHECK( "ab" == result[0] );
      CHECK( "cd" == result[1] );
      CHECK( "ef" == result[2] );

      result = split( start, ',' );
      CHECK( 4 == result.size() );
      CHECK( "" == result[0] );
      CHECK( "ab" == result[1] );
      CHECK( "cd" == result[2] );
      CHECK( "ef" == result[3] );

      result = split( end, ',' );
      CHECK( 4 == result.size() );
      CHECK( "ab" == result[0] );
      CHECK( "cd" == result[1] );
      CHECK( "ef" == result[2] );
      CHECK( "" == result[3] );
    } // THEN
  } // GIVEN
} // SCENARIO

// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/disco/FreeFormatCharacter.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools::disco;

SCENARIO( "Character" ) {

  THEN( "strings can be read" ) {

    std::string string;
    auto iter = string.begin();
    auto begin = string.begin();
    auto end = string.end();

    string = "abcd";
    iter = string.begin();
    end = string.end();
    CHECK( "abcd" == FreeFormatCharacter::read< std::string >( iter, end ) );
    CHECK( iter == end );

    string = "ab\n";
    iter = string.begin();
    end = string.end();
    CHECK( "ab" == FreeFormatCharacter::read< std::string >( iter, end ) );
    CHECK( iter == end - 1 );

    string = "  abcd";
    iter = string.begin();
    end = string.end();
    CHECK( "abcd" == FreeFormatCharacter::read< std::string >( iter, end ) );
    CHECK( iter == end );

    string = "  \n  abcd";
    iter = string.begin();
    end = string.end();
    CHECK( "abcd" == FreeFormatCharacter::read< std::string >( iter, end ) );
    CHECK( iter == end );

    string = " \r\n  abcd";
    iter = string.begin();
    end = string.end();
    CHECK( "abcd" == FreeFormatCharacter::read< std::string >( iter, end ) );
    CHECK( iter == end );
  } // THEN
} // SCENARIO

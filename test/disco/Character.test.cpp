// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/disco/Character.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools::disco;

SCENARIO( "Character" ) {

  THEN( "strings can be read" ) {

    std::string string;
    auto begin = string.begin();
    auto end = string.end();

    string = "abcd";
    begin = string.begin();
    end = string.end();
    CHECK( "abcd" == Character< 4 >::read< std::string >( begin, end ) );
    CHECK( begin == end );

    string = "abcde";
    begin = string.begin();
    end = string.end();
    CHECK( "abcd" == Character< 4 >::read< std::string >( begin, end ) );
    CHECK( begin == end - 1 );

    string = "ab\n";
    begin = string.begin();
    end = string.end();
    CHECK( "ab  " == Character< 4 >::read< std::string >( begin, end ) );
    CHECK( begin == end - 1 );
  } // THEN

  THEN( "strings can be written" ) {

    std::string string;
    std::string buffer;
    auto iter = std::back_inserter( buffer );

    string = "abcd";
    buffer = "";
    iter = std::back_inserter( buffer );
    Character< 4 >::write( string, iter );
    CHECK( "abcd" == buffer );

    string = "abcde";
    buffer = "";
    iter = std::back_inserter( buffer );
    Character< 4 >::write( string, iter );
    CHECK( "abcd" == buffer );

    string = "ab";
    buffer = "";
    iter = std::back_inserter( buffer );
    Character< 4 >::write( string, iter );
    CHECK( "  ab" == buffer );

    string = "";
    buffer = "";
    iter = std::back_inserter( buffer );
    Character< 4 >::write( string, iter );
    CHECK( "    " == buffer );
  } // THEN
} // SCENARIO

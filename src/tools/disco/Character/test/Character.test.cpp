// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/disco/Character.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools::disco;

SCENARIO( "Character" ) {

  std::string string;
  auto begin = string.begin();
  auto end = string.end();

  string = "abcd";
  begin = string.begin();
  end = string.end();
  CHECK( "abcd" == Character< 4 >::read< std::string >( begin, end ) );
  CHECK( begin == end );

  string = "ab\n";
  begin = string.begin();
  end = string.end();
  CHECK( "ab  " == Character< 4 >::read< std::string >( begin, end ) );
  CHECK( begin == end - 1 );

} // SCENARIO

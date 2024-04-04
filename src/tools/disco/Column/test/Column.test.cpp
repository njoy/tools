// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/disco/Column.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools::disco;

SCENARIO( "Column" ) {

  std::string string;
  auto begin = string.begin();
  auto end = string.end();

  string = "    ";
  begin = string.begin();
  end = string.end();
  Column< 1 >::read( begin, end );
  CHECK( begin == end - 3 );
  Column< 3 >::read( begin, end );
  CHECK( begin == end );

  string = "abcd";
  begin = string.begin();
  end = string.end();
  Column< 1 >::read( begin, end );
  CHECK( begin == end - 3 );
  Column< 3 >::read( begin, end );
  CHECK( begin == end );

  string = "  \n";
  begin = string.begin();
  end = string.end();
  Column< 1 >::read( begin, end );
  CHECK( begin == end - 2 );
  Column< 3 >::read( begin, end );
  CHECK( begin == end - 1 );

} // SCENARIO

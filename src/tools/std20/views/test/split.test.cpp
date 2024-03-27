// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/views.hpp"

// other includes
#include <vector>
#include <string>
#include "tools/std20/algorithm.hpp"

// convenience typedefs
//using namespace njoy::tools;
namespace std20 = nano;

SCENARIO( "split" ) {

  std::vector< int > values = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  std::vector< int > splitter = { 4, 5, 6 };
  std::string string = "Hello^_^World!^_^Nice^_^Weather^_^Today";
  std::string delim = "^_^";

  std::vector< std::vector< int > > split_values = { { 1, 2, 3 }, { 7, 8, 9 } };
  std::vector< std::string > split_string = { "Hello", "World!", "Nice", "Weather", "Today" };

  auto result = std20::views::split( string, delim );
  auto iter = result.begin();
  CHECK( std20::equal( *iter, split_string[0] ) );
  ++iter;
  CHECK( std20::equal( *iter, split_string[1] ) );
  ++iter;
  CHECK( std20::equal( *iter, split_string[2] ) );
  ++iter;
  CHECK( std20::equal( *iter, split_string[3] ) );
  ++iter;
  CHECK( std20::equal( *iter, split_string[4] ) );

  auto vresult = std20::views::split( values, splitter );
  auto viter = vresult.begin();
  CHECK( std20::equal( *viter, split_values[0] ) );
  ++viter;
  CHECK( std20::equal( *viter, split_values[1] ) );
} // SCENARIO

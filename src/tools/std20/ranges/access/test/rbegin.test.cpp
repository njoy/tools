// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/ranges.hpp"

// other includes
#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <set>
#include <string>
#include <string_view>
#include <vector>

// convenience typedefs
using namespace njoy::tools;

// test code
struct Foo {};

SCENARIO( "rbegin" ) {

  std::array< int, 3 > array = { 1, 2, 3 };
  CHECK( std20::ranges::rbegin( array ) == array.rbegin() );

  std::deque< int > deque = { 1, 2, 3 };
  CHECK( std20::ranges::rbegin( deque ) == deque.rbegin() );

  // no forward_list: not a bidirectional range

  std::list< int > list = { 1, 2, 3 };
  CHECK( std20::ranges::rbegin( list ) == list.rbegin() );

  std::set< int > set = { 1, 2, 3 };
  CHECK( std20::ranges::rbegin( set ) == set.rbegin() );

  std::string string = "Hello World!";
  CHECK( std20::ranges::rbegin( string ) == string.rbegin() );

  std::vector< int > vector = { 1, 2, 3 };
  CHECK( std20::ranges::rbegin( vector ) == vector.rbegin() );
} // SCENARIO

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

SCENARIO( "crend" ) {

  std::array< int, 3 > array = { 1, 2, 3 };
  CHECK( std20::ranges::crend( array ) == array.crend() );

  std::deque< int > deque = { 1, 2, 3 };
  CHECK( std20::ranges::crend( deque ) == deque.crend() );

  // no forward_list: not a bidirectional range

  std::list< int > list = { 1, 2, 3 };
  CHECK( std20::ranges::crend( list ) == list.crend() );

  std::set< int > set = { 1, 2, 3 };
  CHECK( std20::ranges::crend( set ) == set.crend() );

  std::string string = "Hello World!";
  CHECK( std20::ranges::crend( string ) == string.crend() );

  std::vector< int > vector = { 1, 2, 3 };
  CHECK( std20::ranges::crend( vector ) == vector.crend() );
} // SCENARIO

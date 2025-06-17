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

SCENARIO( "ssize" ) {

  int a[2] = {};
  CHECK( std20::ranges::ssize( a ) == 2 );

  constexpr long b[2] = {};
  CHECK( std20::ranges::ssize( b ) == 2 );

  std::array< int, 3 > array = { 1, 2, 3 };
  CHECK( std20::ranges::ssize( array ) == 3 );

  std::deque< int > deque = { 1, 2, 3 };
  CHECK( std20::ranges::ssize( deque ) == 3 );

  // no forward_list since it does not have ssize()

  std::list< int > list = { 1, 2, 3 };
  CHECK( std20::ranges::ssize( list ) == 3 );

  std::set< int > set = { 1, 2, 3 };
  CHECK( std20::ranges::ssize( set ) == 3 );

  std::string string = "Hello World!";
  CHECK( std20::ranges::ssize( string ) == 12 );

  std::vector< int > vector = { 1, 2, 3 };
  CHECK( std20::ranges::ssize( vector ) == 3 );
} // SCENARIO

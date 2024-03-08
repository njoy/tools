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
//using namespace njoy::tools;
namespace std20 = nano;

// test code
struct Foo {};

SCENARIO( "distance" ) {

  int a[2] = {};
  CHECK( std20::ranges::distance( a ) == 2 );

  constexpr long b[2] = {};
  CHECK( std20::ranges::distance( b ) == 2 );

  std::array< int, 3 > array = { 1, 2, 3 };
  CHECK( std20::ranges::distance( array ) == 3 );

  std::deque< int > deque = { 1, 2, 3 };
  CHECK( std20::ranges::distance( deque ) == 3 );

  std::forward_list< int > forward_list = { 1, 2, 3 };
  CHECK( std20::ranges::distance( forward_list ) == 3 );

  std::list< int > list = { 1, 2, 3 };
  CHECK( std20::ranges::distance( list ) == 3 );

  std::set< int > set = { 1, 2, 3 };
  CHECK( std20::ranges::distance( set ) == 3 );

  std::string string = "Hello World!";
  CHECK( std20::ranges::distance( string ) == 12 );

  std::vector< int > vector = { 1, 2, 3 };
  CHECK( std20::ranges::distance( vector ) == 3 );
} // SCENARIO

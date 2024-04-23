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

SCENARIO( "begin" ) {

  int a[2] = {};
  CHECK( std20::same_as< decltype( std20::ranges::begin( a )), int* > );
  CHECK( std20::same_as< decltype( std20::ranges::begin( a )), decltype( a + 0 ) > );
  CHECK( std20::ranges::begin( a ) == ( a + 0 ) );

  constexpr long b[2] = {};
  CHECK( std20::ranges::begin( b ) == ( b + 0 ) );

  using Bar = Foo[];
  extern Bar& f();
  CHECK( std20::same_as< decltype( std20::ranges::begin( f() ) ), Foo* > );

  std::array< int, 3 > array = { 1, 2, 3 };
  CHECK( std20::ranges::begin( array ) == array.begin() );

  std::deque< int > deque = { 1, 2, 3 };
  CHECK( std20::ranges::begin( deque ) == deque.begin() );

  std::forward_list< int > forward_list = { 1, 2, 3 };
  CHECK( std20::ranges::begin( forward_list ) == forward_list.begin() );

  std::list< int > list = { 1, 2, 3 };
  CHECK( std20::ranges::begin( list ) == list.begin() );

  std::set< int > set = { 1, 2, 3 };
  CHECK( std20::ranges::begin( set ) == set.begin() );

  std::string string = "Hello World!";
  CHECK( std20::ranges::begin( string ) == string.begin() );

  std::vector< int > vector = { 1, 2, 3 };
  CHECK( std20::ranges::begin( vector ) == vector.begin() );
} // SCENARIO

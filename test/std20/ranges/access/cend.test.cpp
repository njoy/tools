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

SCENARIO( "cend" ) {

  int a[2] = {};
  CHECK( std20::same_as< decltype( std20::ranges::cend( a )), const int* > );
  CHECK( std20::ranges::cend( a ) == ( a + 2 ) );

  constexpr long b[2] = {};
  CHECK( std20::ranges::cend( b ) == ( b + 2 ) );

  using Bar = Foo[];
  extern Bar& f();
  CHECK( std20::same_as< decltype( std20::ranges::cend( f() ) ), const Foo* > );

  std::array< int, 3 > array = { 1, 2, 3 };
  CHECK( std20::ranges::cend( array ) == array.cend() );

  std::deque< int > deque = { 1, 2, 3 };
  CHECK( std20::ranges::cend( deque ) == deque.cend() );

  std::forward_list< int > forward_list = { 1, 2, 3 };
  CHECK( std20::ranges::cend( forward_list ) == forward_list.cend() );

  std::list< int > list = { 1, 2, 3 };
  CHECK( std20::ranges::cend( list ) == list.cend() );

  std::set< int > set = { 1, 2, 3 };
  CHECK( std20::ranges::cend( set ) == set.cend() );

  std::string string = "Hello World!";
  CHECK( std20::ranges::cend( string ) == string.cend() );

  std::vector< int > vector = { 1, 2, 3 };
  CHECK( std20::ranges::cend( vector ) == vector.cend() );
} // SCENARIO

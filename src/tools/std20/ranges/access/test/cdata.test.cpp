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

SCENARIO( "cdata" ) {

  int a[2] = {};
  CHECK( std20::same_as< decltype( std20::ranges::cdata( a )), const int* > );
  CHECK( std20::ranges::cdata( a ) == ( a + 0 ) );

  constexpr long b[2] = {};
  CHECK( std20::ranges::cdata( b ) == ( b + 0 ) );

  using Bar = Foo[];
  extern Bar& f();
  CHECK( std20::same_as< decltype( std20::ranges::cdata( f() ) ), const Foo* > );

  std::array< int, 3 > array = { 1, 2, 3 };
  CHECK( std20::ranges::cdata( array ) == &array[0] );

  // no dequeue since it is not contiguous

  // no forward_list since it is not contiguous

  // no list since it is not contiguous

  // no set since it is not contiguous

  std::string string = "Hello World!";
  CHECK( std20::ranges::cdata( string ) == &string[0] );

  std::vector< int > vector = { 1, 2, 3 };
  CHECK( std20::ranges::cdata( vector ) == &vector[0] );
} // SCENARIO

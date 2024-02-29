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

SCENARIO( "end" ) {

  int a[2] = {};
  CHECK( std20::same_as< decltype( std20::ranges::end( a )), int* > );
  CHECK( std20::same_as< decltype( std20::ranges::end( a )), decltype( a + 0 ) > );
  CHECK( std20::ranges::end( a ) == ( a + 2 ) );

  constexpr long b[2] = {};
  CHECK( std20::ranges::end( b ) == ( b + 2 ) );

  using Bar = Foo[];
  extern Bar& f();
  CHECK( std20::same_as< decltype( std20::ranges::end( f() ) ), Foo* > );

  std::array< int, 3 > array = { 1, 2, 3 };
  CHECK( std20::ranges::end( array ) == array.end() );

  std::deque< int > deque = { 1, 2, 3 };
  CHECK( std20::ranges::end( deque ) == deque.end() );

  std::forward_list< int > forward_list = { 1, 2, 3 };
  CHECK( std20::ranges::end( forward_list ) == forward_list.end() );

  std::list< int > list = { 1, 2, 3 };
  CHECK( std20::ranges::end( list ) == list.end() );

  std::set< int > set = { 1, 2, 3 };
  CHECK( std20::ranges::end( set ) == set.end() );

  std::string string = "Hello World!";
  CHECK( std20::ranges::end( string ) == string.end() );

  std::vector< int > vector = { 1, 2, 3 };
  CHECK( std20::ranges::end( vector ) == vector.end() );
} // SCENARIO

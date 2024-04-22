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

SCENARIO( "ccbegin" ) {

  int a[2] = {};
  CHECK( std20::same_as< decltype( std20::ranges::cbegin( a )), const int* > );
  CHECK( std20::ranges::cbegin( a ) == ( a + 0 ) );

  constexpr long b[2] = {};
  CHECK( std20::ranges::cbegin( b ) == ( b + 0 ) );

  using Bar = Foo[];
  extern Bar& f();
  CHECK( std20::same_as< decltype( std20::ranges::cbegin( f() ) ), const Foo* > );

  std::array< int, 3 > array = { 1, 2, 3 };
  CHECK( std20::ranges::cbegin( array ) == array.cbegin() );

  std::deque< int > deque = { 1, 2, 3 };
  CHECK( std20::ranges::cbegin( deque ) == deque.cbegin() );

  std::forward_list< int > forward_list = { 1, 2, 3 };
  CHECK( std20::ranges::cbegin( forward_list ) == forward_list.cbegin() );

  std::list< int > list = { 1, 2, 3 };
  CHECK( std20::ranges::cbegin( list ) == list.cbegin() );

  std::set< int > set = { 1, 2, 3 };
  CHECK( std20::ranges::cbegin( set ) == set.cbegin() );

  std::string string = "Hello World!";
  CHECK( std20::ranges::cbegin( string ) == string.cbegin() );

  std::vector< int > vector = { 1, 2, 3 };
  CHECK( std20::ranges::cbegin( vector ) == vector.cbegin() );
} // SCENARIO

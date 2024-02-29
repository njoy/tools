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

SCENARIO( "empty" ) {

  int a[2] = {};
  CHECK( std20::ranges::empty( a ) == false );

  constexpr long b[2] = {};
  CHECK( std20::ranges::empty( b ) == false );

  std::array< int, 3 > array = { 1, 2, 3 };
  CHECK( std20::ranges::empty( array ) == false );

  std::deque< int > deque = { 1, 2, 3 };
  CHECK( std20::ranges::empty( deque ) == false );
  deque.clear();
  CHECK( std20::ranges::empty( deque ) == true );

  // no forward_list since it does not have empty()

  std::list< int > list = { 1, 2, 3 };
  CHECK( std20::ranges::empty( list ) == false );
  list.clear();
  CHECK( std20::ranges::empty( list ) == true );

  std::set< int > set = { 1, 2, 3 };
  CHECK( std20::ranges::empty( set ) == false );
  set.clear();
  CHECK( std20::ranges::empty( set ) == true );

  std::string string = "Hello World!";
  CHECK( std20::ranges::empty( string ) == false );
  string.clear();
  CHECK( std20::ranges::empty( string ) == true );

  std::vector< int > vector = { 1, 2, 3 };
  CHECK( std20::ranges::empty( vector ) == false );
  vector.clear();
  CHECK( std20::ranges::empty( vector ) == true );
} // SCENARIO

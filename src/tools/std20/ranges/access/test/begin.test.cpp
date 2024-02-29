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

SCENARIO( "bidirectional_range" ) {

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
} // SCENARIO

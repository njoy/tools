// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/algorithm.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools;

SCENARIO( "adjacent_find" ) {

  int a[] = { 1, 2, 3, 3, 4, 5 };

  std::vector< int > va = { 1, 2, 3, 3, 4, 5 };

  auto compare = [] ( auto&& value ) { return value % 2 == 0; };

  CHECK( 2 == std20::count_if( std20::ranges::begin( a ), std20::ranges::end( a ), compare ) );

  CHECK( 2 == std20::count_if( std20::ranges::begin( va ), std20::ranges::end( va ), compare ) );

  CHECK( 2 == std20::count_if( a, compare ) );

  CHECK( 2 == std20::count_if( va, compare ) );

} // SCENARIO

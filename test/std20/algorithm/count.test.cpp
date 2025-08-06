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

  CHECK( 1 == std20::count( std20::ranges::begin( a ), std20::ranges::end( a ), 1 ) );
  CHECK( 1 == std20::count( std20::ranges::begin( a ), std20::ranges::end( a ), 2 ) );
  CHECK( 2 == std20::count( std20::ranges::begin( a ), std20::ranges::end( a ), 3 ) );
  CHECK( 1 == std20::count( std20::ranges::begin( a ), std20::ranges::end( a ), 4 ) );
  CHECK( 1 == std20::count( std20::ranges::begin( a ), std20::ranges::end( a ), 5 ) );

  CHECK( 1 == std20::count( std20::ranges::begin( va ), std20::ranges::end( va ), 1 ) );
  CHECK( 1 == std20::count( std20::ranges::begin( va ), std20::ranges::end( va ), 2 ) );
  CHECK( 2 == std20::count( std20::ranges::begin( va ), std20::ranges::end( va ), 3 ) );
  CHECK( 1 == std20::count( std20::ranges::begin( va ), std20::ranges::end( va ), 4 ) );
  CHECK( 1 == std20::count( std20::ranges::begin( va ), std20::ranges::end( va ), 5 ) );

  CHECK( 1 == std20::count( a, 1 ) );
  CHECK( 1 == std20::count( a, 2 ) );
  CHECK( 2 == std20::count( a, 3 ) );
  CHECK( 1 == std20::count( a, 4 ) );
  CHECK( 1 == std20::count( a, 5 ) );

  CHECK( 1 == std20::count( va, 1 ) );
  CHECK( 1 == std20::count( va, 2 ) );
  CHECK( 2 == std20::count( va, 3 ) );
  CHECK( 1 == std20::count( va, 4 ) );
  CHECK( 1 == std20::count( va, 5 ) );

} // SCENARIO

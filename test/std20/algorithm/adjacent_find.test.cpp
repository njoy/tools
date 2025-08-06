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

  auto predicate = [] ( const auto& left, const auto& right ) { return left == right; };
  auto not_predicate = [] ( const auto& left, const auto& right ) { return left != right; };

  // without predicate
  auto iter = std20::ranges::adjacent_find( a );
  CHECK( *iter == 3 );
  CHECK( iter != std20::ranges::end( a ) );
  iter = std20::ranges::adjacent_find( std20::ranges::begin( a ), std20::ranges::end( a ) );
  CHECK( *iter == 3 );
  CHECK( iter != std20::ranges::end( a ) );

  auto viter = std20::ranges::adjacent_find( va );
  CHECK( *viter == 3 );
  CHECK( viter == std20::ranges::begin( va ) + 2 );
  CHECK( viter != std20::ranges::end( va ) );
  viter = std20::ranges::adjacent_find( std20::ranges::begin( va ), std20::ranges::end( va ) );
  CHECK( *viter == 3 );
  CHECK( viter == std20::ranges::begin( va ) + 2 );
  CHECK( viter != std20::ranges::end( va ) );

  // with predicate
  iter = std20::ranges::adjacent_find( a, predicate );
  CHECK( *iter == 3 );
  CHECK( iter != std20::ranges::end( a ) );
  iter = std20::ranges::adjacent_find( std20::ranges::begin( a ), std20::ranges::end( a ), predicate );
  CHECK( *iter == 3 );
  CHECK( iter != std20::ranges::end( a ) );
  iter = std20::ranges::adjacent_find( a, not_predicate );
  CHECK( *iter == 1 );
  CHECK( iter != std20::ranges::end( a ) );
  iter = std20::ranges::adjacent_find( std20::ranges::begin( a ), std20::ranges::end( a ), not_predicate );
  CHECK( *iter == 1 );
  CHECK( iter != std20::ranges::end( a ) );

  viter = std20::ranges::adjacent_find( va, predicate );
  CHECK( *viter == 3 );
  CHECK( viter == std20::ranges::begin( va ) + 2 );
  CHECK( viter != std20::ranges::end( va ) );
  viter = std20::ranges::adjacent_find( std20::ranges::begin( va ), std20::ranges::end( va ), predicate );
  CHECK( *viter == 3 );
  CHECK( viter == std20::ranges::begin( va ) + 2 );
  CHECK( viter != std20::ranges::end( va ) );
  viter = std20::ranges::adjacent_find( va, not_predicate );
  CHECK( *viter == 1 );
  CHECK( viter == std20::ranges::begin( va ) );
  CHECK( viter != std20::ranges::end( va ) );
  viter = std20::ranges::adjacent_find( std20::ranges::begin( va ), std20::ranges::end( va ), not_predicate );
  CHECK( *viter == 1 );
  CHECK( viter == std20::ranges::begin( va ) );
  CHECK( viter != std20::ranges::end( va ) );

} // SCENARIO

// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/algorithm.hpp"

// other includes

// convenience typedefs
//using namespace njoy::tools;
namespace std20 = nano;

SCENARIO( "equal" ) {

  int a[] = { 1, 2, 3 };

  std::vector< int > va = { 1, 2, 3 };

  auto predicate = [] ( const auto& value ) { return value%2 == 0; };
  auto not_predicate = [] ( const auto& value ) { return value%2 != 0; };

  // find
  auto iter = std20::ranges::find( a, 2 );
  CHECK( *iter == 2 );
  CHECK( iter != std20::ranges::end( a ) );
  iter = std20::ranges::find( std20::ranges::begin( a ), std20::ranges::end( a ), 2 );
  CHECK( *iter == 2 );
  CHECK( iter != std20::ranges::end( a ) );
  iter = std20::ranges::find( a, -100 );
  CHECK( iter == std20::ranges::end( a ) );
  iter = std20::ranges::find( std20::ranges::begin( a ), std20::ranges::end( a ), -100 );
  CHECK( iter == std20::ranges::end( a ) );

  auto viter = std20::ranges::find( va, 2 );
  CHECK( *viter == 2 );
  CHECK( viter != va.end() );
  viter = std20::ranges::find( va.begin(), va.end(), 2 );
  CHECK( *viter == 2 );
  CHECK( viter != va.end() );
  viter = std20::ranges::find( va, -100 );
  CHECK( viter == va.end() );
  viter = std20::ranges::find( va.begin(), va.end(), -100 );
  CHECK( viter == va.end() );

  // find_if
  iter = std20::ranges::find_if( a, predicate );
  CHECK( *iter == 2 );
  CHECK( iter != std20::ranges::end( a ) );
  iter = std20::ranges::find_if( std20::ranges::begin( a ), std20::ranges::end( a ), predicate );
  CHECK( *iter == 2 );
  CHECK( iter != std20::ranges::end( a ) );

  viter = std20::ranges::find_if( va, predicate );
  CHECK( *viter == 2 );
  CHECK( viter != va.end() );
  viter = std20::ranges::find_if( va.begin(), va.end(), predicate );
  CHECK( *viter == 2 );
  CHECK( viter != va.end() );

  // find_if_not
  iter = std20::ranges::find_if_not( a, not_predicate );
  CHECK( *iter == 2 );
  CHECK( iter != std20::ranges::end( a ) );
  iter = std20::ranges::find_if_not( std20::ranges::begin( a ), std20::ranges::end( a ), not_predicate );
  CHECK( *iter == 2 );
  CHECK( iter != std20::ranges::end( a ) );

  viter = std20::ranges::find_if_not( va, not_predicate );
  CHECK( *viter == 2 );
  CHECK( viter != va.end() );
  viter = std20::ranges::find_if_not( va.begin(), va.end(), not_predicate );
  CHECK( *viter == 2 );
  CHECK( viter != va.end() );
} // SCENARIO

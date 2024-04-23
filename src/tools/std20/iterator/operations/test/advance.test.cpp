// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/iterator.hpp"

// other includes
#include <list>
#include <vector>

// convenience typedefs
using namespace njoy::tools;

SCENARIO( "advance" ) {

  WHEN( "when using a container with bidirectional iterators" ) {

    std::list< int > values = { 1, 2, 3, 4, 5 };

    THEN( "advance can be used" ) {

      auto iter = std20::ranges::begin( values );

      std20::ranges::advance( iter, 1 );
      CHECK( *iter == 2 );
      std20::ranges::advance( iter, -1 );
      CHECK( *iter == 1 );
      std20::ranges::advance( iter, 3 );
      CHECK( *iter == 4 );
      std20::ranges::advance( iter, std20::ranges::end( values ) );
      CHECK( iter == values.end() );

      iter = std20::ranges::begin( values );

      std20::ranges::advance( iter, 2, std20::ranges::end( values ) );
      CHECK( *iter == 3 );
      std20::ranges::advance( iter, 50, std20::ranges::end( values ) );
      CHECK( iter == values.end() );

      std20::ranges::advance( iter, -2, std20::ranges::begin( values ) );
      CHECK( *iter == 4 );
      std20::ranges::advance( iter, -50, std20::ranges::begin( values ) );
      CHECK( *iter == 1 );
      CHECK( iter == values.begin() );
    } // THEN
  } // WHEN

  WHEN( "when using a container with random access iterators" ) {

    std::vector< int > values = { 1, 2, 3, 4, 5 };

    THEN( "advance can be used" ) {

      auto iter = std20::ranges::begin( values );

      std20::ranges::advance( iter, 1 );
      CHECK( iter == values.begin() + 1 );
      std20::ranges::advance( iter, -1 );
      CHECK( iter == values.begin() );
      std20::ranges::advance( iter, 3 );
      CHECK( iter == values.begin() + 3 );
      std20::ranges::advance( iter, std20::ranges::end( values ) );
      CHECK( iter == values.end() );

      iter = std20::ranges::begin( values );

      std20::ranges::advance( iter, 2, std20::ranges::end( values ) );
      CHECK( iter == values.begin() + 2 );
      std20::ranges::advance( iter, 50, std20::ranges::end( values ) );
      CHECK( iter == values.end() );

      std20::ranges::advance( iter, -2, std20::ranges::begin( values ) );
      CHECK( iter == values.begin() + 3 );
      std20::ranges::advance( iter, -50, std20::ranges::begin( values ) );
      CHECK( iter == values.begin() );
    } // THEN
  } // WHEN
} // SCENARIO

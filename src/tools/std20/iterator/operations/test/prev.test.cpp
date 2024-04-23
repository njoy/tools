// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/iterator.hpp"

// other includes
#include <list>
#include <vector>

// convenience typedefs
using namespace njoy::tools;

SCENARIO( "prev" ) {

  WHEN( "when using a container with bidirectional iterators" ) {

    std::list< int > values = { 1, 2, 3, 4, 5 };

    THEN( "prev can be used" ) {

      auto iter = std20::ranges::end( values );

      iter = std20::ranges::prev( iter );
      CHECK( *iter == 5 );
      iter  = std20::ranges::prev( iter, -1 );
      CHECK( iter == values.end() );
      iter = std20::ranges::prev( iter, 1 );
      CHECK( *iter == 5 );
      iter = std20::ranges::prev( iter, 3 );
      CHECK( *iter == 2 );

      iter = std20::ranges::end( values );

      iter = std20::ranges::prev( iter, 2, std20::ranges::begin( values ) );
      CHECK( *iter == 4 );
      iter = std20::ranges::prev( iter, 50, std20::ranges::begin( values ) );
      CHECK( iter == values.begin() );

      iter = std20::ranges::prev( iter, -2, std20::ranges::end( values ) );
      CHECK( *iter == 3 );
      iter = std20::ranges::prev( iter, -50, std20::ranges::end( values ) );
      CHECK( iter == values.end() );
    } // THEN
  } // WHEN

  WHEN( "when using a container with random access iterators" ) {

    std::vector< int > values = { 1, 2, 3, 4, 5 };

    THEN( "prev can be used" ) {

      auto iter = std20::ranges::end( values );

      iter = std20::ranges::prev( iter );
      CHECK( iter == values.end() - 1 );
      iter = std20::ranges::prev( iter, -1 );
      CHECK( iter == values.end() );
      iter = std20::ranges::prev( iter, 1 );
      CHECK( iter == values.end() - 1 );
      iter = std20::ranges::prev( iter, 3 );
      CHECK( iter == values.begin() + 1 );

      iter = std20::ranges::end( values );

      iter = std20::ranges::prev( iter, 2, std20::ranges::begin( values ) );
      CHECK( iter == values.begin() + 3 );
      iter = std20::ranges::prev( iter, 50, std20::ranges::begin( values ) );
      CHECK( iter == values.begin() );

      iter = std20::ranges::prev( iter, -2, std20::ranges::end( values ) );
      CHECK( iter == values.begin() + 2 );
      iter = std20::ranges::prev( iter, -50, std20::ranges::end( values ) );
      CHECK( iter == values.end() );
    } // THEN
  } // WHEN
} // SCENARIO

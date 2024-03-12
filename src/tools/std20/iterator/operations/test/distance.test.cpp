// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/iterator.hpp"

// other includes
#include <list>
#include <vector>

// convenience typedefs
//using namespace njoy::tools;
namespace std20 = nano;

SCENARIO( "distance" ) {

  WHEN( "when using a container with bidirectional iterators" ) {

    std::list< int > values = { 1, 2, 3, 4, 5 };

    THEN( "distance can be used" ) {

      CHECK( 5 == std20::ranges::distance( values.begin(), values.end() ) );
    } // THEN
  } // WHEN

  WHEN( "when using a container with random access iterators" ) {

    std::vector< int > values = { 1, 2, 3, 4, 5 };

    THEN( "distance can be used" ) {

      CHECK( 5 == std20::ranges::distance( values.begin(), values.end() ) );
      CHECK( 3 == std20::ranges::distance( values.begin() + 1, values.end() - 1 ) );
    } // THEN
  } // WHEN
} // SCENARIO

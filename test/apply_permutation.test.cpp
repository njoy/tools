// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/apply_permutation.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools;

SCENARIO( "apply_permutation" ) {

  GIVEN( "a range of values and a range of indices" ) {

    THEN( "the permutation can be performed using iterators" ) {

      std::vector< int > values = { 0, 1, 2, 3, 4 };
      std::vector< int > indices = { 4, 3, 2, 1, 0 };
      apply_permutation( values.begin(), values.end(), indices.begin() );

      CHECK( 4 == values[0] );
      CHECK( 3 == values[1] );
      CHECK( 2 == values[2] );
      CHECK( 1 == values[3] );
      CHECK( 0 == values[4] );

      CHECK( 0 == indices[0] );
      CHECK( 1 == indices[1] );
      CHECK( 2 == indices[2] );
      CHECK( 3 == indices[3] );
      CHECK( 4 == indices[4] );
    } // THEN

    THEN( "the permutation can be performed using vectors" ) {

      std::vector< int > values = { 0, 1, 2, 3, 4 };
      std::vector< int > indices = { 4, 3, 2, 1, 0 };
      apply_permutation( values, indices );

      CHECK( 4 == values[0] );
      CHECK( 3 == values[1] );
      CHECK( 2 == values[2] );
      CHECK( 1 == values[3] );
      CHECK( 0 == values[4] );

      CHECK( 0 == indices[0] );
      CHECK( 1 == indices[1] );
      CHECK( 2 == indices[2] );
      CHECK( 3 == indices[3] );
      CHECK( 4 == indices[4] );
    } // THEN
  } // GIVEN
} // SCENARIO

// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/ranges/make_view.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools::ranges;

SCENARIO( "make_view" ) {

  GIVEN( "a container with values" ) {

    std::vector< int > values = { -2, -1, 0, 1, 2 };

    WHEN( "when make functions are used" ) {

      auto chunk = make_view( values );

      THEN( "an IteratorView can be constructed and members can be tested" ) {

        CHECK( 5 == chunk.size() );
        CHECK( false == chunk.empty() );

        CHECK( -2 == chunk[0] );
        CHECK( -1 == chunk[1] );
        CHECK(  0 == chunk[2] );
        CHECK(  1 == chunk[3] );
        CHECK(  2 == chunk[4] );

        CHECK( -2 == chunk.at( 0 ) );
        CHECK( -1 == chunk.at( 1 ) );
        CHECK(  0 == chunk.at( 2 ) );
        CHECK(  1 == chunk.at( 3 ) );
        CHECK(  2 == chunk.at( 4 ) );

        CHECK( -2 == chunk.front() );
        CHECK(  2 == chunk.back() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

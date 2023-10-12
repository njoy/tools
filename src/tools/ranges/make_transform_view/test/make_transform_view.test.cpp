// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/ranges/make_transform_view.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools::ranges;

SCENARIO( "make_view" ) {

  GIVEN( "a container with values and a transformation" ) {

    std::vector< int > values = { -2, -1, 0, 1, 2 };
    auto transform = [] ( auto&& value ) { return 2 * value; };

    WHEN( "when using iterators and the transformation" ) {

      auto chunk = make_transform_view( values.begin(), values.end(), transform );

      THEN( "an IteratorView can be constructed and members can be tested" ) {

        CHECK( 5 == chunk.size() );
        CHECK( false == chunk.empty() );

        CHECK( -4 == chunk[0] );
        CHECK( -2 == chunk[1] );
        CHECK(  0 == chunk[2] );
        CHECK(  2 == chunk[3] );
        CHECK(  4 == chunk[4] );

        CHECK( -4 == chunk.at( 0 ) );
        CHECK( -2 == chunk.at( 1 ) );
        CHECK(  0 == chunk.at( 2 ) );
        CHECK(  2 == chunk.at( 3 ) );
        CHECK(  4 == chunk.at( 4 ) );

        CHECK( -4 == chunk.front() );
        CHECK(  4 == chunk.back() );
      } // THEN
    } // WHEN

    WHEN( "when using the container and the transformation" ) {

      auto chunk = make_transform_view( values, transform );

      THEN( "an IteratorView can be constructed and members can be tested" ) {

        CHECK( 5 == chunk.size() );
        CHECK( false == chunk.empty() );

        CHECK( -4 == chunk[0] );
        CHECK( -2 == chunk[1] );
        CHECK(  0 == chunk[2] );
        CHECK(  2 == chunk[3] );
        CHECK(  4 == chunk[4] );

        CHECK( -4 == chunk.at( 0 ) );
        CHECK( -2 == chunk.at( 1 ) );
        CHECK(  0 == chunk.at( 2 ) );
        CHECK(  2 == chunk.at( 3 ) );
        CHECK(  4 == chunk.at( 4 ) );

        CHECK( -4 == chunk.front() );
        CHECK(  4 == chunk.back() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

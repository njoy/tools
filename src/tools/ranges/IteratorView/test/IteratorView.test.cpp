// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/ranges/IteratorView.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools::ranges;

SCENARIO( "IteratorView" ) {

  GIVEN( "a container with values" ) {

    std::vector< int > values = { -2, -1, 0, 1, 2 };

    WHEN( "when iterators are used" ) {

      IteratorView< std::vector< int >::iterator > chunk( values.begin(), values.end() );

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

      THEN( "an exception is thrown when using an index that is too large or "
            "too small" ) {

        CHECK_NOTHROW( chunk.at( 0 ) );
        CHECK_NOTHROW( chunk.at( 4 ) );
        CHECK_THROWS( chunk.at( 5 ) );
        CHECK_THROWS( chunk.at( 10 ) );
      } // THEN
    } // WHEN

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

      THEN( "an exception is thrown when using an index that is too large or "
            "too small" ) {

        CHECK_NOTHROW( chunk.at( 0 ) );
        CHECK_NOTHROW( chunk.at( 4 ) );
        CHECK_THROWS( chunk.at( 5 ) );
        CHECK_THROWS( chunk.at( 10 ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "containers and views with values" ) {

    std::vector< double > container1 = { 1., 2., 3., 4. };
    std::vector< double > container2 = { 1., 2., 3. };

    std::vector< double > copy1 = container1;
    std::vector< double > copy2 = container2;

    auto view1 = make_view( copy1 );
    auto view2 = make_view( copy2 );

    WHEN( "when make comparison functions are used" ) {

      THEN( "views and containers can be compared" ) {

        CHECK( view1 == container1 );
        CHECK( view1 == copy1 );
        CHECK( container1 == view1 );
        CHECK( copy1 == view1 );

        CHECK( view1 != container2 );
        CHECK( view1 != copy2 );
        CHECK( container2 != view1 );
        CHECK( copy2 != view1 );

        CHECK( view2 == container2 );
        CHECK( view2 == copy2 );
        CHECK( container2 == view2 );
        CHECK( copy2 == view2 );

        CHECK( view2 != container1 );
        CHECK( view2 != copy1 );
        CHECK( container1 != view2 );
        CHECK( copy1 != view2 );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

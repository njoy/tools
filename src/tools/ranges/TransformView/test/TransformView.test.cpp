// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/ranges/TransformView.hpp"

// other includes
#include <forward_list>
#include <list>
#include <vector>

// convenience typedefs
using namespace njoy::tools::ranges;

SCENARIO( "TransformView" ) {

  auto transform = [] ( auto&& value ) { return value - 2; };

  GIVEN( "a container with forward iterators" ) {

    std::forward_list< int > values = { 0, 1, 2, 3, 4 };

    WHEN( "when the container and the transformation are used" ) {

      TransformView chunk( values.begin(), values.end(), transform );

      THEN( "an TransformView can be constructed and members can be tested" ) {

        CHECK( 5 == chunk.size() );
        CHECK( false == chunk.empty() );
        CHECK( false == bool( chunk ) );

        unsigned int counter = 0;
        for ( auto value : chunk ) {

          ++counter;
        }
        CHECK( 5 == counter );

        // the following should not compile: no random access iterator
        // CHECK( -2 == chunk[0] );
        // CHECK( -2 == chunk.at(0) );

        CHECK( -2 == chunk.front() );

        // the following should not compile: no bidirectional iterator
        // CHECK(  2 == chunk.back() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a container with bidirectional iterators" ) {

    std::list< int > values = { 0, 1, 2, 3, 4 };

    WHEN( "when the container and the transformation are used" ) {

      TransformView chunk( values.begin(), values.end(), transform );

      THEN( "an TransformView can be constructed and members can be tested" ) {

        CHECK( 5 == chunk.size() );
        CHECK( false == chunk.empty() );
        CHECK( false == bool( chunk ) );

        unsigned int counter = 0;
        for ( auto value : chunk ) {

          ++counter;
        }
        CHECK( 5 == counter );

        // the following should not compile: no random access iterator
        // CHECK( -2 == chunk[0] );
        // CHECK( -2 == chunk.at(0) );

        CHECK( -2 == chunk.front() );
        CHECK(  2 == chunk.back() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a container with random access iterators" ) {

    std::vector< int > values = { 0, 1, 2, 3, 4 };

    WHEN( "when the container and the transformation are used" ) {

      TransformView chunk( values.begin(), values.end(), transform );

      THEN( "an TransformView can be constructed and members can be tested" ) {

        CHECK( 5 == chunk.size() );
        CHECK( false == chunk.empty() );
        CHECK( false == bool( chunk ) );

        unsigned int counter = 0;
        for ( auto value : chunk ) {

          ++counter;
        }
        CHECK( 5 == counter );

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

    std::vector< double > base1 = { 1., 2., 3., 4. };
    std::vector< double > base2 = { 1., 2., 3. };

    std::vector< double > container1 = { -1., 0., 1., 2. };
    std::vector< double > container2 = { -1., 0., 1. };

    std::vector< double > copy1 = container1;
    std::vector< double > copy2 = container2;

    TransformView view1( base1.begin(), base1.end(), transform );
    TransformView view2( base2.begin(), base2.end(), transform );

    WHEN( "when comparison functions are used" ) {

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

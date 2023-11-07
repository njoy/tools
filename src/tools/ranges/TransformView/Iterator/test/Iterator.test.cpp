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

      TransformView chunk( values, transform );

      THEN( "the TransformView::Iterator functions as a normal forward iterator" ) {

        auto begin = chunk.begin();
        auto second = ++chunk.begin();
        auto end = chunk.end();
        auto iter = begin;

        unsigned int counter = 0;
        for ( auto iter = begin; iter != end; ++iter ) {

          ++counter;
        }
        CHECK( 5 == counter );

        CHECK( 5 == std::distance( begin, end ) );
        CHECK( begin != end );

        CHECK( -2 == *begin );
        CHECK( -1 == *second );

        // the following should not compile: no random access iterator
        // CHECK( -2 == begin[0] );
        // CHECK( -1 == begin[1] );
        // CHECK(  0 == begin[2] );
        // CHECK(  1 == begin[3] );
        // CHECK(  2 == begin[4] );

        // the following should not compile: no random access iterator
        // iter += 1;
        // CHECK( second == iter );
        // iter -= 1;
        // CHECK( begin == iter );

        CHECK( second == ++begin );
        // the following should not compile: no bidirectional iterator
        // CHECK( begin == --begin );

        begin = chunk.begin();
        iter = begin;
        CHECK( begin == iter++ );
        CHECK( second == iter );
        // the following should not compile: no bidirectional iterator
        // CHECK( second == iter-- );
        // CHECK( begin == iter );

        // the following should not compile: no random access iterator
        // iter = begin + 1;
        // CHECK( second == iter );
        // iter = second - 1;
        // CHECK( begin == iter );
        // iter = 1 + begin;
        // CHECK( second == iter );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a container with bidirectional iterators" ) {

    std::list< int > values = { 0, 1, 2, 3, 4 };

    WHEN( "when the container and the transformation are used" ) {

      TransformView chunk( values, transform );

      THEN( "the TransformView::Iterator functions as a normal bidirectional iterator" ) {

        auto begin = chunk.begin();
        auto second = ++chunk.begin();
        auto end = chunk.end();
        auto iter = begin;

        unsigned int counter = 0;
        for ( auto iter = begin; iter != end; ++iter ) {

          ++counter;
        }
        CHECK( 5 == counter );

        CHECK( 5 == std::distance( begin, end ) );
        CHECK( begin != end );

        CHECK( -2 == *begin );
        CHECK( -1 == *second );

        // the following should not compile: no random access iterator
        // CHECK( -2 == begin[0] );
        // CHECK( -1 == begin[1] );
        // CHECK(  0 == begin[2] );
        // CHECK(  1 == begin[3] );
        // CHECK(  2 == begin[4] );

        // the following should not compile: no random access iterator
        // iter += 1;
        // CHECK( second == iter );
        // iter -= 1;
        // CHECK( begin == iter );

        CHECK( second == ++begin );
        CHECK( begin == --begin );

        iter = begin;
        CHECK( begin == iter++ );
        CHECK( second == iter );
        CHECK( second == iter-- );
        CHECK( begin == iter );

        // the following should not compile: no random access iterator
        // iter = begin + 1;
        // CHECK( second == iter );
        // iter = second - 1;
        // CHECK( begin == iter );
        // iter = 1 + begin;
        // CHECK( second == iter );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a container with random access iterators" ) {

    std::vector< int > values = { 0, 1, 2, 3, 4 };

    WHEN( "when the container and the transformation are used" ) {

      TransformView chunk( values, transform );

      THEN( "the TransformView::Iterator functions as a normal random access "
            "iterator" ) {

        auto begin = chunk.begin();
        auto second = begin + 1;
        auto end = chunk.end();
        auto iter = begin;

        unsigned int counter = 0;
        for ( auto iter = begin; iter != end; ++iter ) {

          ++counter;
        }
        CHECK( 5 == counter );

        CHECK( 5 == std::distance( begin, end ) );
        CHECK( 5 == end - begin );
        CHECK( begin != end );

        CHECK( -2 == *begin );
        CHECK( -1 == *second );

        CHECK( -2 == begin[0] );
        CHECK( -1 == begin[1] );
        CHECK(  0 == begin[2] );
        CHECK(  1 == begin[3] );
        CHECK(  2 == begin[4] );

        iter += 1;
        CHECK( second == iter );
        iter -= 1;
        CHECK( begin == iter );

        CHECK( second == ++begin );
        CHECK( begin == --begin );

        iter = begin;
        CHECK( begin == iter++ );
        CHECK( second == iter );
        CHECK( second == iter-- );
        CHECK( begin == iter );

        iter = begin + 1;
        CHECK( second == iter );
        iter = second - 1;
        CHECK( begin == iter );
        iter = 1 + begin;
        CHECK( second == iter );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

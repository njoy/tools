// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/ranges/AnyIterator.hpp"

// other includes
#include <forward_list>
#include <list>
#include <vector>

// convenience typedefs
using namespace njoy::tools::ranges;

SCENARIO( "AnyIterator" ) {

  GIVEN( "a container with forward iterators" ) {

    std::forward_list< int > values = { 0, 1, 2, 3, 4 };

    WHEN( "an AnyIterator can be constructed and members can be tested" ) {

      AnyIterator< std::forward_iterator_tag, int > begin( values.begin() );
      AnyIterator< std::forward_iterator_tag, int > second( ++values.begin() );
      AnyIterator< std::forward_iterator_tag, int > end( values.end() );

      THEN( "the TransformView::Iterator functions as a normal forward iterator" ) {

        unsigned int counter = 0;
        for ( auto iter = begin; iter != end; ++iter ) {

          ++counter;
        }
        CHECK( 5 == counter );

        CHECK( 5 == std::distance( begin, end ) );
        CHECK( begin != end );

        CHECK( 0 == *begin );
        CHECK( 1 == *second );

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

        auto start = begin;
        CHECK( second == ++start );
        // the following should not compile: no bidirectional iterator
        // CHECK( begin == --begin );

        auto iter = begin;
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

        // the following should not compile: no random access iterator
        // CHECK( second >= begin );
        // CHECK( second > begin );
        // CHECK( begin <= second );
        // CHECK( begin < second );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a container with bidirectional iterators" ) {

    std::list< int > values = { 0, 1, 2, 3, 4 };

    WHEN( "when the container and the transformation are used" ) {

      AnyIterator< std::bidirectional_iterator_tag, int > begin( values.begin() );
      AnyIterator< std::bidirectional_iterator_tag, int > second( ++values.begin() );
      AnyIterator< std::bidirectional_iterator_tag, int > end( values.end() );

      THEN( "the TransformView::Iterator functions as a normal bidirectional iterator" ) {

        unsigned int counter = 0;
        for ( auto iter = begin; iter != end; ++iter ) {

          ++counter;
        }
        CHECK( 5 == counter );

        CHECK( 5 == std::distance( begin, end ) );
        CHECK( begin != end );

        CHECK( 0 == *begin );
        CHECK( 1 == *second );

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

        auto iter = begin;
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

        // the following should not compile: no random access iterator
        // CHECK( second >= begin );
        // CHECK( second > begin );
        // CHECK( begin <= second );
        // CHECK( begin < second );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a container with random access iterators" ) {

    std::vector< int > values = { 0, 1, 2, 3, 4 };

    WHEN( "when the container and the transformation are used" ) {

      AnyIterator< std::random_access_iterator_tag, int > begin( values.begin() );
      AnyIterator< std::random_access_iterator_tag, int > second( ++values.begin() );
      AnyIterator< std::random_access_iterator_tag, int > end( values.end() );

      THEN( "the TransformView::Iterator functions as a normal random access "
            "iterator" ) {

        unsigned int counter = 0;
        for ( auto iter = begin; iter != end; ++iter ) {

          ++counter;
        }
        CHECK( 5 == counter );

        CHECK( 5 == std::distance( begin, end ) );
        CHECK( begin != end );

        CHECK( 0 == *begin );
        CHECK( 1 == *second );

        CHECK( 0 == begin[0] );
        CHECK( 1 == begin[1] );
        CHECK( 2 == begin[2] );
        CHECK( 3 == begin[3] );
        CHECK( 4 == begin[4] );

        auto iter = begin;
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

        CHECK( second >= begin );
        CHECK( second > begin );
        CHECK( begin <= second );
        CHECK( begin < second );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

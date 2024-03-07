// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/views/AnyIterator.hpp"

// other includes
#include <forward_list>
#include <list>
#include <vector>

// convenience typedefs
using namespace njoy::tools;

template < typename ValueType >
using AnyForwardIterator = ranges::AnyForwardIterator< ValueType, ValueType&, ValueType* >;
template < typename ValueType >
using AnyBidirectionalIterator = ranges::AnyBidirectionalIterator< ValueType, ValueType&, ValueType* >;
template < typename ValueType >
using AnyRandomAccessIterator = ranges::AnyRandomAccessIterator< ValueType, ValueType&, ValueType* >;

SCENARIO( "AnyIterator" ) {

  GIVEN( "a container with forward iterators" ) {

    std::forward_list< int > values = { 0, 1, 2, 3, 4 };

    WHEN( "an AnyIterator can be constructed and members can be tested" ) {

      AnyForwardIterator< int > begin( values.begin() );
      AnyForwardIterator< int > second( ++values.begin() );
      AnyForwardIterator< int > end( values.end() );

      THEN( "the TransformView::Iterator functions as a normal forward iterator" ) {

        CHECK( nano::input_iterator< decltype( begin ) > );
        CHECK( nano::input_iterator< decltype( second ) > );
        CHECK( nano::input_iterator< decltype( end ) > );

        CHECK( nano::forward_iterator< decltype( begin ) > );
        CHECK( nano::forward_iterator< decltype( second ) > );
        CHECK( nano::forward_iterator< decltype( end ) > );

        CHECK( ! nano::bidirectional_iterator< decltype( begin ) > );
        CHECK( ! nano::bidirectional_iterator< decltype( second ) > );
        CHECK( ! nano::bidirectional_iterator< decltype( end ) > );

        CHECK( ! nano::random_access_iterator< decltype( begin ) > );
        CHECK( ! nano::random_access_iterator< decltype( second ) > );
        CHECK( ! nano::random_access_iterator< decltype( end ) > );

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

      AnyBidirectionalIterator< int > begin( values.begin() );
      AnyBidirectionalIterator< int > second( ++values.begin() );
      AnyBidirectionalIterator< int > end( values.end() );

      THEN( "the TransformView::Iterator functions as a normal bidirectional iterator" ) {

        CHECK( nano::input_iterator< decltype( begin ) > );
        CHECK( nano::input_iterator< decltype( second ) > );
        CHECK( nano::input_iterator< decltype( end ) > );

        CHECK( nano::forward_iterator< decltype( begin ) > );
        CHECK( nano::forward_iterator< decltype( second ) > );
        CHECK( nano::forward_iterator< decltype( end ) > );

        CHECK( nano::bidirectional_iterator< decltype( begin ) > );
        CHECK( nano::bidirectional_iterator< decltype( second ) > );
        CHECK( nano::bidirectional_iterator< decltype( end ) > );

        CHECK( ! nano::random_access_iterator< decltype( begin ) > );
        CHECK( ! nano::random_access_iterator< decltype( second ) > );
        CHECK( ! nano::random_access_iterator< decltype( end ) > );

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

      AnyRandomAccessIterator< int > begin( values.begin() );
      AnyRandomAccessIterator< int > second( ++values.begin() );
      AnyRandomAccessIterator< int > end( values.end() );

      const AnyRandomAccessIterator< int > begin2( values.begin() );

      THEN( "the TransformView::Iterator functions as a normal random access "
            "iterator" ) {

        CHECK( nano::input_iterator< decltype( begin ) > );
        CHECK( nano::input_iterator< decltype( second ) > );
        CHECK( nano::input_iterator< decltype( end ) > );

        CHECK( nano::forward_iterator< decltype( begin ) > );
        CHECK( nano::forward_iterator< decltype( second ) > );
        CHECK( nano::forward_iterator< decltype( end ) > );

        CHECK( nano::bidirectional_iterator< decltype( begin ) > );
        CHECK( nano::bidirectional_iterator< decltype( second ) > );
        CHECK( nano::bidirectional_iterator< decltype( end ) > );

CHECK( nano::derived_from<nano::iterator_category_t<decltype( begin )>, nano::random_access_iterator_tag> );
CHECK( nano::totally_ordered<decltype( begin )> );
CHECK( nano::sized_sentinel_for<decltype( begin ), decltype( begin )> );
CHECK( nano::same_as<decltype(begin += 1), decltype(begin)&> );
CHECK( nano::same_as<decltype(begin2 + 1), decltype(begin)> );
CHECK( nano::same_as<decltype(1 + begin2), decltype(begin)> );
CHECK( nano::same_as<decltype(begin -= 1), decltype(begin)&> );
CHECK( nano::same_as<decltype(begin2 - 1), decltype(begin)> );
CHECK( nano::same_as<decltype(begin2[1]), nano::iter_reference_t<decltype(begin)>> );

        CHECK( nano::random_access_iterator< decltype( begin ) > );
        CHECK( nano::random_access_iterator< decltype( second ) > );
        CHECK( nano::random_access_iterator< decltype( end ) > );

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

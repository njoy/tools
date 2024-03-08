// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/views/AnyView.hpp"

// other includes
#include <forward_list>
#include <list>
#include <vector>

// convenience typedefs
using namespace njoy::tools::views;

SCENARIO( "AnyView" ) {

  GIVEN( "a container with forward iterators" ) {

    std::forward_list< int > values = { -2, -1, 0, 1, 2 };

    WHEN( "when iterators are used" ) {

      AnyForwardView< int& > chunk( values );

      THEN( "an AnyView can be constructed and members can be tested" ) {

        CHECK( nano::range< decltype(chunk) > );
        CHECK( nano::forward_range< decltype(chunk) > );
        CHECK( ! nano::bidirectional_range< decltype(chunk) > );
        CHECK( ! nano::random_access_range< decltype(chunk) > );

        CHECK( nano::view< decltype(chunk) > );

//        CHECK( 5 == chunk.size() );
        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

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

    std::list< int > values = { -2, -1, 0, 1, 2 };

    WHEN( "when iterators are used" ) {

      AnyBidirectionalView< int& > chunk( values );

      THEN( "an AnyView can be constructed and members can be tested" ) {

        CHECK( nano::range< decltype(chunk) > );
        CHECK( nano::bidirectional_range< decltype(chunk) > );
        CHECK( nano::view< decltype(chunk) > );

//        CHECK( 5 == chunk.size() );
        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

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

    std::vector< int > values = { -2, -1, 0, 1, 2 };

    WHEN( "when iterators are used" ) {

      AnyRandomAccessView< int& > chunk( values );

      THEN( "an AnyView can be constructed and members can be tested" ) {

        CHECK( nano::range< decltype(chunk) > );
        CHECK( nano::random_access_range< decltype(chunk) > );
        CHECK( nano::view< decltype(chunk) > );

        CHECK( 5 == chunk.size() );
        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

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

        CHECK( -2 == chunk.front() );
        CHECK(  2 == chunk.back() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

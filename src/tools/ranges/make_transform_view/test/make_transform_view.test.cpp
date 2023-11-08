// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/ranges/make_transform_view.hpp"

// other includes
#include <forward_list>
#include <list>
#include <vector>

// convenience typedefs
using namespace njoy::tools::ranges;

SCENARIO( "make_view" ) {

  auto transform = [] ( auto&& value ) { return value - 2; };

  GIVEN( "a container with forward iterators" ) {

    std::forward_list< int > values = { 0, 1, 2, 3, 4 };

    WHEN( "when the container and the transformation are used" ) {

      auto chunk = make_transform_view( values, transform );

      THEN( "an IteratorView can be constructed and members can be tested" ) {

        CHECK( 5 == chunk.size() );
        CHECK( false == chunk.empty() );
        CHECK( false == bool( chunk ) );

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

      auto chunk = make_transform_view( values, transform );

      THEN( "an IteratorView can be constructed and members can be tested" ) {

        CHECK( 5 == chunk.size() );
        CHECK( false == chunk.empty() );
        CHECK( false == bool( chunk ) );

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

      auto chunk = make_transform_view( values, transform );

      THEN( "an IteratorView can be constructed and members can be tested" ) {

        CHECK( 5 == chunk.size() );
        CHECK( false == chunk.empty() );
        CHECK( false == bool( chunk ) );

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

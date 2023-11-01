// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/ranges/make_view.hpp"

// other includes
#include <forward_list>
#include <list>
#include <vector>

// convenience typedefs
using namespace njoy::tools::ranges;

SCENARIO( "make_view" ) {

  GIVEN( "a container with bidirectional iterators" ) {

    std::list< int > values = { -2, -1, 0, 1, 2 };

    WHEN( "when using iterators" ) {

      auto chunk = make_view( values.begin(), values.end() );

      THEN( "an IteratorView can be constructed and members can be tested" ) {

        CHECK( values.begin() == chunk.begin() );
        CHECK( values.end() == chunk.end() );

        CHECK( 5 == chunk.size() );
        CHECK( false == chunk.empty() );

        // the following should not compile: no random access iterator
        // CHECK( -2 == chunk[0] );
        // CHECK( -2 == chunk.at(0) );

        CHECK( -2 == chunk.front() );
        CHECK(  2 == chunk.back() );
      } // THEN
    } // WHEN

    WHEN( "when using the container" ) {

      auto chunk = make_view( values );

      THEN( "an IteratorView can be constructed and members can be tested" ) {

        CHECK( values.begin() == chunk.begin() );
        CHECK( values.end() == chunk.end() );

        CHECK( 5 == chunk.size() );
        CHECK( false == chunk.empty() );

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

    WHEN( "when using iterators" ) {

      auto chunk = make_view( values.begin(), values.end() );

      THEN( "an IteratorView can be constructed and members can be tested" ) {

        CHECK( values.begin() == chunk.begin() );
        CHECK( values.end() == chunk.end() );

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

    WHEN( "when using the container" ) {

      auto chunk = make_view( values );

      THEN( "an IteratorView can be constructed and members can be tested" ) {

        CHECK( values.begin() == chunk.begin() );
        CHECK( values.end() == chunk.end() );

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

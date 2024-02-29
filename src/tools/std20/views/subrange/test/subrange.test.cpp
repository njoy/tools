// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/views.hpp"

// other includes
#include <forward_list>
#include <list>
#include <vector>

// convenience typedefs
//using namespace njoy::tools;
namespace std20 = nano::ranges;

SCENARIO( "subrange" ) {

  GIVEN( "a container with forward iterators" ) {

    std::forward_list< int > values = { -2, -1, 0, 1, 2 };

    WHEN( "when iterators are used" ) {

      using Range = std20::subrange< std::forward_list< int >::iterator >;
      Range chunk( values.begin(), values.end() );

      THEN( "the subrange satisfies the required consepcts" ) {

		CHECK( std20::view< Range > );
		CHECK( ! std20::sized_range < Range > );
		CHECK( ! std20::contiguous_range < Range > );
		CHECK( ! std20::random_access_range < Range > );
		CHECK( std20::common_range < Range > );
      }

      THEN( "a subrange can be constructed and members can be tested" ) {

        CHECK( values.begin() == chunk.begin() );
        CHECK( values.end() == chunk.end() );

        // the following should not compile: no random access iterator
        // CHECK( 5 == chunk.size() );
        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        unsigned int counter = 0;
        for ( auto value : chunk ) {

          ++counter;
        }
        CHECK( 5 == counter );

        // the following should not compile: no random access iterator
        // CHECK( -2 == chunk[0] );

        CHECK( -2 == chunk.front() );

        // the following should not compile: no bidirectional iterator
        // CHECK(  2 == chunk.back() );
      } // THEN
    } // WHEN
  } // GIVEN*/

  GIVEN( "a container with bidirectional iterators" ) {

    std::list< int > values = { -2, -1, 0, 1, 2 };

    WHEN( "when iterators are used" ) {

      using Range = std20::subrange< std::list< int >::iterator >;
      Range chunk( values.begin(), values.end() );

      THEN( "the subrange satisfies the required consepcts" ) {

		CHECK( std20::view< Range > );
		CHECK( ! std20::sized_range < Range > );
		CHECK( ! std20::contiguous_range < Range > );
		CHECK( ! std20::random_access_range < Range > );
		CHECK( std20::common_range < Range > );
      }

      THEN( "a subrange can be constructed and members can be tested" ) {

        CHECK( values.begin() == chunk.begin() );
        CHECK( values.end() == chunk.end() );

        // the following should not compile: no random access iterator
        // CHECK( 5 == chunk.size() );
        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        unsigned int counter = 0;
        for ( auto value : chunk ) {

          ++counter;
        }
        CHECK( 5 == counter );

        // the following should not compile: no random access iterator
        // CHECK( -2 == chunk[0] );

        CHECK( -2 == chunk.front() );
        CHECK(  2 == chunk.back() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a container with random access iterators" ) {

    std::vector< int > values = { -2, -1, 0, 1, 2 };

    WHEN( "when iterators are used" ) {

      using Range = std20::subrange< std::vector< int >::iterator >;
      Range chunk( values.begin(), values.end() );

      THEN( "the subrange satisfies the required consepcts" ) {

		CHECK( std20::view< Range > );
		CHECK( std20::sized_range < Range > );
		CHECK( ! std20::contiguous_range < Range > );
		CHECK( std20::random_access_range < Range > );
		CHECK( std20::common_range < Range > );
      }

      THEN( "a subrange can be constructed and members can be tested" ) {

        CHECK( values.begin() == chunk.begin() );
        CHECK( values.end() == chunk.end() );

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

// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/views.hpp"

// other includes
#include <forward_list>
#include <list>
#include <vector>
#include "tools/std20/algorithm.hpp"

// convenience typedefs
//using namespace njoy::tools;
namespace std20 = nano;

SCENARIO( "subrange" ) {

  GIVEN( "a container with forward iterators" ) {

    std::forward_list< int > values = { -2, -1, 0, 1, 2 };

    WHEN( "when iterators are used" ) {

      using Range = std20::ranges::subrange< std::forward_list< int >::iterator,
                                             std::forward_list< int >::iterator,
                                             std20::ranges::subrange_kind::sized >;

      auto size = std::distance( values.begin(), values.end() );
      Range chunk( values.begin(), values.end(),size );

      THEN( "the subrange satisfies the required consepcts" ) {

		    CHECK( std20::ranges::view< Range > );
		    CHECK( std20::ranges::sized_range < Range > );
		    CHECK( ! std20::ranges::contiguous_range < Range > );
		    CHECK( ! std20::ranges::random_access_range < Range > );
		    CHECK( std20::ranges::common_range < Range > );
      }

      THEN( "a subrange can be constructed and members can be tested" ) {

        CHECK( values.begin() == chunk.begin() );
        CHECK( values.end() == chunk.end() );

        CHECK( 5 == chunk.size() );
        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        CHECK( std20::ranges::equal( chunk, std::initializer_list< int >{ -2, -1, 0, 1, 2 } ) );

        // the following should not compile: no random access iterator
        // CHECK( -1 == chunk[1] );
        CHECK( -2 == chunk.front() );

        // the following should not compile: no random access iterator
        // CHECK(  2 == chunk.back() );

        unsigned int counter = 0;
        for ( auto&& value : chunk ) {

          value += counter;
          ++counter;
        }
        CHECK( 5 == counter );

        CHECK( std20::ranges::equal( chunk, std::initializer_list< int >{ -2, 0, 2, 4, 6 } ) );

        // the following should not compile: no random access iterator
        // CHECK( -2 == chunk[0] );
      } // THEN
    } // WHEN
  } // GIVEN*/

  GIVEN( "a container with bidirectional iterators" ) {

    std::list< int > values = { -2, -1, 0, 1, 2 };

    WHEN( "when iterators are used" ) {

      using Range = std20::ranges::subrange< std::list< int >::iterator,
                                             std::list< int >::iterator,
                                             std20::ranges::subrange_kind::sized >;

      auto size = std::distance( values.begin(), values.end() );
      Range chunk( values.begin(), values.end(),size );

      THEN( "the subrange satisfies the required consepcts" ) {

		    CHECK( std20::ranges::view< Range > );
		    CHECK( std20::ranges::sized_range < Range > );
		    CHECK( ! std20::ranges::contiguous_range < Range > );
		    CHECK( ! std20::ranges::random_access_range < Range > );
		    CHECK( std20::ranges::common_range < Range > );
      }

      THEN( "a subrange can be constructed and members can be tested" ) {

        CHECK( values.begin() == chunk.begin() );
        CHECK( values.end() == chunk.end() );

        CHECK( 5 == chunk.size() );
        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        CHECK( std20::ranges::equal( chunk, std::initializer_list< int >{ -2, -1, 0, 1, 2 } ) );

        // the following should not compile: no random access iterator
        // CHECK( -1 == chunk[1] );
        CHECK( -2 == chunk.front() );
        CHECK(  2 == chunk.back() );

        unsigned int counter = 0;
        for ( auto&& value : chunk ) {

          value += counter;
          ++counter;
        }
        CHECK( 5 == counter );

        CHECK( std20::ranges::equal( chunk, std::initializer_list< int >{ -2, 0, 2, 4, 6 } ) );

        // the following should not compile: no random access iterator
        // CHECK( -2 == chunk[0] );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a container with random access iterators" ) {

    std::vector< int > values = { -2, -1, 0, 1, 2 };

    WHEN( "when iterators are used" ) {

      using Range = std20::ranges::subrange< std::vector< int >::iterator >;

      auto size = std::distance( values.begin(), values.end() );
      Range chunk( values.begin(), values.end(),size );

      THEN( "the subrange satisfies the required consepcts" ) {

		    CHECK( std20::ranges::view< Range > );
		    CHECK( std20::ranges::sized_range < Range > );
		    CHECK( ! std20::ranges::contiguous_range < Range > );
		    CHECK( std20::ranges::random_access_range < Range > );
		    CHECK( std20::ranges::common_range < Range > );
      }

      THEN( "a subrange can be constructed and members can be tested" ) {

        CHECK( values.begin() == chunk.begin() );
        CHECK( values.end() == chunk.end() );

        CHECK( 5 == chunk.size() );
        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        CHECK( std20::ranges::equal( chunk, std::initializer_list< int >{ -2, -1, 0, 1, 2 } ) );

        CHECK( -1 == chunk[1] );
        CHECK(  0 == chunk[2] );
        CHECK(  1 == chunk[3] );
        CHECK(  2 == chunk[4] );

        CHECK( -2 == chunk.front() );
        CHECK(  2 == chunk.back() );

        unsigned int counter = 0;
        for ( auto&& value : chunk ) {

          value += counter;
          ++counter;
        }
        CHECK( 5 == counter );

        CHECK( std20::ranges::equal( chunk, std::initializer_list< int >{ -2, 0, 2, 4, 6 } ) );

        CHECK( -2 == chunk[0] );
        CHECK(  0 == chunk[1] );
        CHECK(  2 == chunk[2] );
        CHECK(  4 == chunk[3] );
        CHECK(  6 == chunk[4] );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

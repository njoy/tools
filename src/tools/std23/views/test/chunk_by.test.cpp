// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std23/views.hpp"

// other includes
#include <forward_list>
#include <list>
#include <vector>
#include "tools/std20/algorithm.hpp"

// convenience typedefs
using namespace njoy::tools;

SCENARIO( "chunk_by_view" ) {

  const std::vector< std::vector< int > > equal = { { 1, 2, 3 }, { 1, 2, 3 }, { 3 }, { 3 }, { 1, 2, 3 } };
  const std::vector< int > modified = { -2, 0, 2, 4, 6 };

  GIVEN( "a container with random access iterators" ) {

    std::vector< int > values = { 1, 2, 3, 1, 2, 3, 3, 3, 1, 2, 3 };

    WHEN( "when iterators are used" ) {

      auto chunk = values | std23::views::chunk_by( std::less{} );
      using Range = decltype(chunk);
      using Iterator = std20::iterator_t< Range >;

      THEN( "the chunk_by_view satisfies the required concepts" ) {

        CHECK( std20::ranges::range< Range > );
        CHECK( std20::ranges::view< Range > );
//        CHECK( std20::ranges::sized_range< Range > );
//        CHECK( std20::ranges::forward_range< Range > );
//        CHECK( std20::ranges::bidirectional_range< Range > );
//        CHECK( std20::ranges::random_access_range< Range > );
//        CHECK( std20::ranges::contiguous_range< Range > );
//        CHECK( std20::ranges::common_range< Range > );
      }

/*      THEN( "an chunk_by_view can be constructed and members can be tested" ) {

        CHECK( 5 == chunk.size() );
        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        CHECK( std20::ranges::equal( chunk, equal ) );

        CHECK( 1 == chunk[0][0] );
        CHECK( 2 == chunk[0][1] );
        CHECK( 3 == chunk[0][2] );
        CHECK( 1 == chunk[1][0] );
        CHECK( 2 == chunk[1][1] );
        CHECK( 3 == chunk[1][2] );
        CHECK( 3 == chunk[2][0] );
        CHECK( 3 == chunk[3][0] );
        CHECK( 1 == chunk[4][0] );
        CHECK( 2 == chunk[4][1] );
        CHECK( 3 == chunk[4][2] );

        CHECK( std20::ranges::equal( equal[0], chunk.front() ) );
        CHECK( std20::ranges::equal( equal[4], chunk.back() ) );

        CHECK( std20::ranges::equal( chunk, modified ) );
        CHECK( std20::ranges::equal( values, modified ) );

        CHECK( -2 == chunk[0] );
        CHECK(  0 == chunk[1] );
        CHECK(  2 == chunk[2] );
        CHECK(  4 == chunk[3] );
        CHECK(  6 == chunk[4] );
      } // THEN*/
    } // WHEN
  } // GIVEN
} // SCENARIO

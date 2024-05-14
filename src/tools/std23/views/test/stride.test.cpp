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

SCENARIO( "stride_view" ) {

  const std::vector< int > equal = { 1, 3, 5, 7, 9 };

  GIVEN( "a container with forward iterators" ) {

    std::forward_list< int > values = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    WHEN( "when iterators are used" ) {

      auto chunk = values | std23::views::stride( 2 );
      using Range = decltype(chunk);
      using Iterator = std20::iterator_t< Range >;

      THEN( "the stride_view satisfies the required concepts" ) {

        CHECK( std20::ranges::viewable_range< Range > );

        CHECK( std20::ranges::range< Range > );
        CHECK( std20::ranges::view< Range > );
        CHECK( ! std20::ranges::sized_range< Range > );
        CHECK( std20::ranges::forward_range< Range > );
        CHECK( ! std20::ranges::bidirectional_range< Range > );
        CHECK( ! std20::ranges::random_access_range< Range > );
        CHECK( ! std20::ranges::contiguous_range< Range > );
        CHECK( ! std20::ranges::common_range< Range > );
      }

      THEN( "a stride_view can be constructed and members can be tested" ) {

        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        CHECK( std20::ranges::equal( equal, chunk ) );

        CHECK( equal[0] == chunk.front() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a container with bidirectional iterators" ) {

    std::list< int > values = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    WHEN( "when iterators are used" ) {

      auto chunk = values | std23::views::stride( 2 );
      using Range = decltype(chunk);
      using Iterator = std20::iterator_t< Range >;

      THEN( "the stride_view satisfies the required concepts" ) {

        CHECK( std20::ranges::viewable_range< Range > );

        CHECK( std20::ranges::range< Range > );
        CHECK( std20::ranges::view< Range > );
        CHECK( std20::ranges::sized_range< Range > );
        CHECK( std20::ranges::forward_range< Range > );
        CHECK( std20::ranges::bidirectional_range< Range > );
        CHECK( ! std20::ranges::random_access_range< Range > );
        CHECK( ! std20::ranges::contiguous_range< Range > );
        CHECK( ! std20::ranges::common_range< Range > );
      }

      THEN( "a stride_view can be constructed and members can be tested" ) {

        CHECK( 5 == chunk.size() );

        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        CHECK( std20::ranges::equal( equal, chunk ) );

        CHECK( equal[0] == chunk.front() );
        CHECK( equal[4] == chunk.back() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a container with random access iterators" ) {

    std::vector< int > values = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    WHEN( "when iterators are used" ) {

      auto chunk = values | std23::views::stride( 2 );
      using Range = decltype(chunk);
      using Iterator = std20::iterator_t< Range >;

      THEN( "the stride_view satisfies the required concepts" ) {

        CHECK( std20::ranges::viewable_range< Range > );

        CHECK( std20::ranges::range< Range > );
        CHECK( std20::ranges::view< Range > );
        CHECK( std20::ranges::sized_range< Range > );
        CHECK( std20::ranges::forward_range< Range > );
        CHECK( std20::ranges::bidirectional_range< Range > );
        CHECK( std20::ranges::random_access_range< Range > );
        CHECK( ! std20::ranges::contiguous_range< Range > );
        CHECK( ! std20::ranges::common_range< Range > );
      }

      THEN( "a stride_view can be constructed and members can be tested" ) {

        CHECK( 5 == chunk.size() );

        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        CHECK( std20::ranges::equal( equal, chunk ) );

        CHECK( equal[0] == chunk.front() );
        CHECK( equal[4] == chunk.back() );

        CHECK( 1 == chunk[0] );
        CHECK( 3 == chunk[1] );
        CHECK( 5 == chunk[2] );
        CHECK( 7 == chunk[3] );
        CHECK( 9 == chunk[4] );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

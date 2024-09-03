// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std23/views.hpp"

// other includes
#include <forward_list>
#include <list>
#include <vector>
#include "tools/std20/algorithm.hpp"
#include <string_view>
#include "tools/std20/iterator/unreachable.hpp"
// convenience typedefs
using namespace njoy::tools;

SCENARIO( "repeat_view" ) {

  // Use a single bound limit for all bound tests
  int boundLimit = 4;

  GIVEN( "repeating an integer" ) {

    int repeated = 9;

    WHEN( "sized repeat_view" ) {

      auto chunk = std23::views::repeat( repeated, boundLimit );
      using Range = decltype(chunk);
      using Iterator = std20::iterator_t< Range >;

      THEN( "the repeat_view satisfies the required concepts" ) {

        CHECK( std20::ranges::viewable_range< Range > );

        CHECK( std20::ranges::range< Range > );
        CHECK( std20::ranges::view< Range > );
        CHECK( std20::ranges::sized_range< Range > );
        CHECK( std20::ranges::forward_range< Range > );
        CHECK( std20::ranges::bidirectional_range< Range > );
        CHECK( std20::ranges::random_access_range< Range > );
        CHECK( ! std20::ranges::contiguous_range< Range > );
        CHECK( std20::ranges::common_range< Range > );
      }

      THEN ( "a repeat_view can be constructed and members can be tested" ) {

        CHECK( boundLimit == chunk.size() );
        for ( int i : chunk ) {

          CHECK( i == repeated );
        }

        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        CHECK( repeated == chunk.front() );
        CHECK( repeated == chunk.back() );

        CHECK( repeated == chunk[0] );
        CHECK( repeated == chunk[1] );
        CHECK( repeated == chunk[2] );
        CHECK( repeated == chunk[3] );
      } //THEN
    } //WHEN

    WHEN( "unsized repeat_view" ) {

      auto chunk = std23::views::repeat( repeated );
      using Range = decltype(chunk);
      using Iterator = std20::iterator_t< Range >;

      THEN( "the repeat_view satisfies the required concepts" ) {

        CHECK( std20::same_as< std::remove_cv_t<decltype(std20::unreachable_sentinel)>,
                               decltype(chunk.end()) >);

        CHECK( std20::ranges::viewable_range< Range > );

        CHECK( std20::ranges::range< Range > );
        CHECK( std20::ranges::view< Range > );
        CHECK( ! std20::ranges::sized_range< Range > );
        CHECK( std20::ranges::forward_range< Range > );
        CHECK( std20::ranges::bidirectional_range< Range > );
        CHECK( std20::ranges::random_access_range< Range > );
        CHECK( ! std20::ranges::contiguous_range< Range > );
        CHECK( ! std20::ranges::common_range< Range > );
      }

      THEN ( "a repeat_view can be constructed and members can be tested" ) {

        int UnboundLimit = 0;
        for ( int i : chunk ) {

          ++UnboundLimit;
          CHECK( i == repeated );
          if ( UnboundLimit > 2 * boundLimit ) {

            break;
          }
        }

        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        CHECK( repeated == chunk.front() );

        CHECK( repeated == chunk[0] );
        CHECK( repeated == chunk[1] );
        CHECK( repeated == chunk[2] );
        CHECK( repeated == chunk[3] );
      } //THEN
    } //WHEN
  } //GIVEN

  GIVEN( "repeating a float" ) {

    float repeated = 9;

    WHEN( "sized repeat_view" ) {

      auto chunk = std23::views::repeat( repeated, boundLimit );
      using Range = decltype(chunk);
      using Iterator = std20::iterator_t< Range >;

      THEN( "the repeat_view satisfies the required concepts" ) {

        CHECK( std20::ranges::viewable_range< Range > );

        CHECK( std20::ranges::range< Range > );
        CHECK( std20::ranges::view< Range > );
        CHECK( std20::ranges::sized_range< Range > );
        CHECK( std20::ranges::forward_range< Range > );
        CHECK( std20::ranges::bidirectional_range< Range > );
        CHECK( std20::ranges::random_access_range< Range > );
        CHECK( ! std20::ranges::contiguous_range< Range > );
        CHECK( std20::ranges::common_range< Range > );
      }

      THEN ( "a repeat_view can be constructed and members can be tested" ) {

        CHECK( boundLimit == chunk.size() );
        for ( int i : chunk ) {

          CHECK( i == repeated );
        }

        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        CHECK( repeated == chunk.front() );
        CHECK( repeated == chunk.back() );

        CHECK( repeated == chunk[0] );
        CHECK( repeated == chunk[1] );
        CHECK( repeated == chunk[2] );
        CHECK( repeated == chunk[3] );
      } //THEN
    } //WHEN

    WHEN( "unsized repeat_view" ) {

      auto chunk = std23::views::repeat( repeated );
      using Range = decltype(chunk);
      using Iterator = std20::iterator_t< Range >;

      THEN( "the repeat_view satisfies the required concepts" ) {

        CHECK( std20::same_as< std::remove_cv_t<decltype(std20::unreachable_sentinel)>,
                               decltype(chunk.end()) >);

        CHECK( std20::ranges::viewable_range< Range > );

        CHECK( std20::ranges::range< Range > );
        CHECK( std20::ranges::view< Range > );
        CHECK( ! std20::ranges::sized_range< Range > );
        CHECK( std20::ranges::forward_range< Range > );
        CHECK( std20::ranges::bidirectional_range< Range > );
        CHECK( std20::ranges::random_access_range< Range > );
        CHECK( ! std20::ranges::contiguous_range< Range > );
        CHECK( ! std20::ranges::common_range< Range > );
      }

      THEN ( "a repeat_view can be constructed and members can be tested" ) {

        int UnboundLimit = 0;
        for ( int i : chunk ) {

          ++UnboundLimit;
          CHECK( i == repeated );
          if ( UnboundLimit > 2 * boundLimit ) {

            break;
          }
        }

        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        CHECK( repeated == chunk.front() );

        CHECK( repeated == chunk[0] );
        CHECK( repeated == chunk[1] );
        CHECK( repeated == chunk[2] );
        CHECK( repeated == chunk[3] );
      } //THEN
    } //WHEN
  } //GIVEN
} //SCENARIO

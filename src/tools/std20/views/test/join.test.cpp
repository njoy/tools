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

SCENARIO( "join_view" ) {

  const std::vector< int > equal = { -2, -1, 0, 1, 2 };
  const std::vector< int > modified = { -2, 0, 2, 4, 6 };

  GIVEN( "a container with forward iterators" ) {

    std::forward_list< std::forward_list< int > > values = { { -2, -1 }, { 0 }, { 1, 2 } };

    WHEN( "when iterators are used" ) {

      auto chunk = values | std20::views::join;
      using Range = decltype(chunk);
      using Iterator = nano::iterator_t< Range >;

      THEN( "the join_view satisfies the required concepts" ) {

		    CHECK( std20::ranges::view< Range > );
		    CHECK( ! std20::ranges::sized_range< Range > );
        CHECK( std20::ranges::forward_range< Range > );
        CHECK( ! std20::ranges::bidirectional_range< Range > );
		    CHECK( ! std20::ranges::random_access_range< Range > );
		    CHECK( ! std20::ranges::contiguous_range< Range > );
		    CHECK( std20::ranges::common_range< Range > );
      }

      THEN( "the join_view range and iterator associated types are correct" ) {

        CHECK( std20::same_as< nano::ranges::range_value_t< Range >, int > );
        CHECK( std20::same_as< nano::ranges::range_reference_t< Range >, int& > );
        CHECK( std20::same_as< nano::ranges::range_difference_t< Range >, std::ptrdiff_t > );

        CHECK( std20::same_as< nano::ranges::iter_value_t< Iterator >, int > );
        CHECK( std20::same_as< nano::ranges::iter_reference_t< Iterator >, int& > );
        CHECK( std20::same_as< nano::ranges::iter_difference_t< Iterator >, std::ptrdiff_t > );
      }

      THEN( "an join_view can be constructed and members can be tested" ) {

        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        CHECK( std20::ranges::equal( chunk, equal ) );

        CHECK( -2 == chunk.front() );

        unsigned int counter = 0;
        for ( auto&& value : chunk ) {

          value += counter;
          ++counter;
        }
        CHECK( 5 == counter );

        CHECK( std20::ranges::equal( chunk, modified ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a container with bidirectional iterators" ) {

    std::list< std::list< int > > values = { { -2, -1 }, { 0} , { 1, 2 } };

    WHEN( "when iterators are used" ) {

      auto chunk = values | std20::views::join;
      using Range = decltype(chunk);
      using Iterator = nano::iterator_t< Range >;

      THEN( "the join_view satisfies the required concepts" ) {

		    CHECK( std20::ranges::view< Range > );
		    CHECK( ! std20::ranges::sized_range< Range > );
        CHECK( std20::ranges::forward_range< Range > );
        CHECK( std20::ranges::bidirectional_range< Range > );
		    CHECK( ! std20::ranges::random_access_range< Range > );
		    CHECK( ! std20::ranges::contiguous_range< Range > );
		    CHECK( std20::ranges::common_range< Range > );
      }

      THEN( "the join_view range and iterator associated types are correct" ) {

        CHECK( std20::same_as< nano::ranges::range_value_t< Range >, int > );
        CHECK( std20::same_as< nano::ranges::range_reference_t< Range >, int& > );
        CHECK( std20::same_as< nano::ranges::range_difference_t< Range >, std::ptrdiff_t > );

        CHECK( std20::same_as< nano::ranges::iter_value_t< Iterator >, int > );
        CHECK( std20::same_as< nano::ranges::iter_reference_t< Iterator >, int& > );
        CHECK( std20::same_as< nano::ranges::iter_difference_t< Iterator >, std::ptrdiff_t > );
      }

      THEN( "an join_view can be constructed and members can be tested" ) {

        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        CHECK( std20::ranges::equal( chunk, equal ) );

        CHECK( -2 == chunk.front() );

        unsigned int counter = 0;
        for ( auto&& value : chunk ) {

          value += counter;
          ++counter;
        }
        CHECK( 5 == counter );

        CHECK( std20::ranges::equal( chunk, modified ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a container with random access iterators" ) {

    std::vector< std::vector< int > > values = { { -2, -1 }, { 0 }, { 1, 2 } };

    WHEN( "when iterators are used" ) {

      auto chunk = values | std20::views::join;
      using Range = decltype(chunk);
      using Iterator = nano::iterator_t< Range >;

      THEN( "the join_view satisfies the required concepts" ) {

		    CHECK( std20::ranges::view< Range > );
		    CHECK( ! std20::ranges::sized_range< Range > );
        CHECK( std20::ranges::forward_range< Range > );
        CHECK( std20::ranges::bidirectional_range< Range > );
		    CHECK( ! std20::ranges::random_access_range< Range > );
		    CHECK( ! std20::ranges::contiguous_range< Range > );
		    CHECK( std20::ranges::common_range< Range > );
      }

      THEN( "the join_view range and iterator associated types are correct" ) {

        CHECK( std20::same_as< nano::ranges::range_value_t< Range >, int > );
        CHECK( std20::same_as< nano::ranges::range_reference_t< Range >, int& > );
        CHECK( std20::same_as< nano::ranges::range_difference_t< Range >, std::ptrdiff_t > );

        CHECK( std20::same_as< nano::ranges::iter_value_t< Iterator >, int > );
        CHECK( std20::same_as< nano::ranges::iter_reference_t< Iterator >, int& > );
        CHECK( std20::same_as< nano::ranges::iter_difference_t< Iterator >, std::ptrdiff_t > );
      }

      THEN( "an join_view can be constructed and members can be tested" ) {

        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        CHECK( std20::ranges::equal( chunk, equal ) );

        CHECK( -2 == chunk.front() );

        unsigned int counter = 0;
        for ( auto&& value : chunk ) {

          value += counter;
          ++counter;
        }
        CHECK( 5 == counter );

        CHECK( std20::ranges::equal( chunk, modified ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

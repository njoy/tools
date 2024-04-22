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

SCENARIO( "drop_while_view" ) {

  const std::vector< int > equal = { 0, 1, 2 };

  auto predicate = [] ( const auto& value ) { return value < 0; };

  GIVEN( "a container with forward iterators" ) {

    std::forward_list< int > values = { -2, -1, 0, 1, 2 };

    WHEN( "when iterators are used" ) {

      auto chunk = values | std20::views::drop_while( predicate );
      using Range = decltype(chunk);
      using Iterator = nano::iterator_t< Range >;

      THEN( "the drop_while_view satisfies the required concepts" ) {

		    CHECK( std20::ranges::view< Range > );
		    CHECK( ! std20::ranges::sized_range< Range > );
        CHECK( std20::ranges::forward_range< Range > );
        CHECK( ! std20::ranges::bidirectional_range< Range > );
		    CHECK( ! std20::ranges::random_access_range< Range > );
		    CHECK( ! std20::ranges::contiguous_range< Range > );
		    CHECK( std20::ranges::common_range< Range > );
      }

      THEN( "the drop_while_view range and iterator associated types are correct" ) {

        CHECK( std20::same_as< nano::ranges::range_value_t< Range >, int > );
        CHECK( std20::same_as< nano::ranges::range_reference_t< Range >, int& > );
        CHECK( std20::same_as< nano::ranges::range_difference_t< Range >, std::ptrdiff_t > );

        CHECK( std20::same_as< nano::ranges::iter_value_t< Iterator >, int > );
        CHECK( std20::same_as< nano::ranges::iter_reference_t< Iterator >, int& > );
        CHECK( std20::same_as< nano::ranges::iter_difference_t< Iterator >, std::ptrdiff_t > );
      }

      THEN( "an drop_while_view can be constructed and members can be tested" ) {

        // the following should not compile: no random access iterator
        // CHECK( 5 == chunk.size() );

        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        CHECK( std20::ranges::equal( chunk, equal ) );

        // the following should not compile: no random access iterator
        // CHECK( -2 == chunk[0] );

        CHECK( 0 == chunk.front() );

        // the following should not compile: no random access iterator
        // CHECK(  2 == chunk.back() );
      } // THEN
    } // WHEN
  } // GIVEN*/

  GIVEN( "a container with bidirectional iterators" ) {

    std::list< int > values = { -2, -1, 0, 1, 2 };

    WHEN( "when iterators are used" ) {

      auto chunk = values | std20::views::drop_while( predicate );
      using Range = decltype(chunk);
      using Iterator = nano::iterator_t< Range >;

      THEN( "the drop_while_view satisfies the required concepts" ) {

		    CHECK( std20::ranges::view< Range > );
		    CHECK( ! std20::ranges::sized_range< Range > );
        CHECK( std20::ranges::forward_range< Range > );
        CHECK( std20::ranges::bidirectional_range< Range > );
		    CHECK( ! std20::ranges::random_access_range< Range > );
		    CHECK( ! std20::ranges::contiguous_range< Range > );
		    CHECK( std20::ranges::common_range< Range > );
      }

      THEN( "the drop_while_view range and iterator associated types are correct" ) {

        CHECK( std20::same_as< nano::ranges::range_value_t< Range >, int > );
        CHECK( std20::same_as< nano::ranges::range_reference_t< Range >, int& > );
        CHECK( std20::same_as< nano::ranges::range_difference_t< Range >, std::ptrdiff_t > );

        CHECK( std20::same_as< nano::ranges::iter_value_t< Iterator >, int > );
        CHECK( std20::same_as< nano::ranges::iter_reference_t< Iterator >, int& > );
        CHECK( std20::same_as< nano::ranges::iter_difference_t< Iterator >, std::ptrdiff_t > );
      }

      THEN( "an drop_while_view can be constructed and members can be tested" ) {

        // the following should not compile: not sized
        // CHECK( 3 == chunk.size() );
        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        CHECK( std20::ranges::equal( chunk, equal ) );

        // the following should not compile: no random access iterator
        // CHECK( -2 == chunk[0] );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a container with random access iterators" ) {

    std::vector< int > values = { -2, -1, 0, 1, 2 };

    WHEN( "when iterators are used" ) {

      auto chunk = values | std20::views::drop_while( predicate );
      using Range = decltype(chunk);
      using Iterator = nano::iterator_t< Range >;

      THEN( "the drop_while_view satisfies the required concepts" ) {

        CHECK( std20::ranges::view< Range > );
        CHECK( std20::ranges::sized_range< Range > );
        CHECK( std20::ranges::forward_range< Range > );
        CHECK( std20::ranges::bidirectional_range< Range > );
        CHECK( std20::ranges::random_access_range< Range > );
        CHECK( ! std20::ranges::contiguous_range< Range > );
        CHECK( std20::ranges::common_range< Range > );
      }

      THEN( "the drop_while_view range and iterator associated types are correct" ) {

        CHECK( std20::same_as< nano::ranges::range_value_t< Range >, int > );
        CHECK( std20::same_as< nano::ranges::range_reference_t< Range >, int& > );
        CHECK( std20::same_as< nano::ranges::range_difference_t< Range >, std::ptrdiff_t > );

        CHECK( std20::same_as< nano::ranges::iter_value_t< Iterator >, int > );
        CHECK( std20::same_as< nano::ranges::iter_reference_t< Iterator >, int& > );
        CHECK( std20::same_as< nano::ranges::iter_difference_t< Iterator >, std::ptrdiff_t > );
      }

      THEN( "an drop_while_view can be constructed and members can be tested" ) {

        CHECK( 3 == chunk.size() );
        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        CHECK( std20::ranges::equal( chunk, equal ) );

        CHECK( 0 == chunk[0] );
        CHECK( 1 == chunk[1] );
        CHECK( 2 == chunk[2] );

        CHECK( 0 == chunk.front() );
        CHECK( 2 == chunk.back() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

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
using namespace njoy::tools;

SCENARIO( "transform_view" ) {

  const std::vector< int > equal = { -2, -1, 0, 1, 2 };

  auto transform = [] ( auto&& value ) { return value - 2; };

  GIVEN( "a container with forward iterators" ) {

    std::forward_list< int > values = { 0, 1, 2, 3, 4 };

    WHEN( "when the container and the transformation are used" ) {

      auto chunk = values | std20::views::transform( transform );
      using Range = decltype( chunk );
      using Iterator = std20::iterator_t< Range >;

      THEN( "the transform_view satisfies the required concepts" ) {

        CHECK( std20::ranges::view< Range > );
        CHECK( ! std20::ranges::sized_range< Range > );
        CHECK( std20::ranges::forward_range< Range > );
        CHECK( ! std20::ranges::bidirectional_range< Range > );
        CHECK( ! std20::ranges::random_access_range< Range > );
        CHECK( ! std20::ranges::contiguous_range< Range > );
        CHECK( std20::ranges::common_range< Range > );
      }

      THEN( "the transform_view range and iterator associated types are correct" ) {

        CHECK( std20::same_as< std20::ranges::range_value_t< Range >, int > );
        CHECK( std20::same_as< std20::ranges::range_reference_t< Range >, int > );
        CHECK( std20::same_as< std20::ranges::range_difference_t< Range >, std::ptrdiff_t > );

        CHECK( std20::same_as< std20::ranges::iter_value_t< Iterator >, int > );
        CHECK( std20::same_as< std20::ranges::iter_reference_t< Iterator >, int > );
        CHECK( std20::same_as< std20::ranges::iter_difference_t< Iterator >, std::ptrdiff_t > );
      }

      THEN( "an transform_view can be constructed and members can be tested" ) {

        // the following should not compile: no random access iterator
        // CHECK( 5 == chunk.size() );

        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        CHECK( std20::ranges::equal( chunk, equal ) );

        // the following should not compile: no random access iterator
        // CHECK( -2 == chunk[0] );

        CHECK( -2 == chunk.front() );

        // the following should not compile: no random access iterator
        // CHECK(  2 == chunk.back() );
      } // THEN

      THEN( "it can be transformed into a vector using iterators" ) {

        std::vector< int > constructed( chunk.begin(), chunk.end() );
        CHECK( std20::ranges::equal( constructed, chunk ) );

        std::vector< int > inserted;
        inserted.insert( inserted.end(), chunk.begin(), chunk.end() );
        CHECK( std20::ranges::equal( inserted, chunk ) );
      }
    } // WHEN
  } // GIVEN

  GIVEN( "a container with bidirectional iterators" ) {

    std::list< int > values = { 0, 1, 2, 3, 4 };

    WHEN( "when the container and the transformation are used" ) {

      auto chunk = values | std20::views::transform( transform );
      using Range = decltype( chunk );
      using Iterator = std20::iterator_t< Range >;

      THEN( "the transform_view satisfies the required concepts" ) {

        CHECK( std20::ranges::view< Range > );
        CHECK( std20::ranges::sized_range< Range > );
        CHECK( std20::ranges::forward_range< Range > );
        CHECK( std20::ranges::bidirectional_range< Range > );
        CHECK( ! std20::ranges::random_access_range< Range > );
        CHECK( ! std20::ranges::contiguous_range< Range > );
        CHECK( std20::ranges::common_range< Range > );
      }

      THEN( "the transform_view range and iterator associated types are correct" ) {

        CHECK( std20::same_as< std20::ranges::range_value_t< Range >, int > );
        CHECK( std20::same_as< std20::ranges::range_reference_t< Range >, int > );
        CHECK( std20::same_as< std20::ranges::range_difference_t< Range >, std::ptrdiff_t > );

        CHECK( std20::same_as< std20::ranges::iter_value_t< Iterator >, int > );
        CHECK( std20::same_as< std20::ranges::iter_reference_t< Iterator >, int > );
        CHECK( std20::same_as< std20::ranges::iter_difference_t< Iterator >, std::ptrdiff_t > );
      }

      THEN( "a transform_view can be constructed and members can be tested" ) {

        CHECK( 5 == chunk.size() );
        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        CHECK( std20::ranges::equal( chunk, equal ) );

        // the following should not compile: no random access iterator
        // CHECK( -2 == chunk[0] );

        CHECK( -2 == chunk.front() );
        CHECK(  2 == chunk.back() );
      } // THEN

      THEN( "it can be transformed into a vector using iterators" ) {

        std::vector< int > constructed( chunk.begin(), chunk.end() );
        CHECK( std20::ranges::equal( constructed, chunk ) );

        std::vector< int > inserted;
        inserted.insert( inserted.end(), chunk.begin(), chunk.end() );
        CHECK( std20::ranges::equal( inserted, chunk ) );
      }
    } // WHEN
  } // GIVEN

  GIVEN( "a container with random access iterators" ) {

    std::vector< int > values = { 0, 1, 2, 3, 4 };

    WHEN( "when the container and the transformation are used" ) {

      auto chunk = values | std20::views::transform( transform );
      using Range = decltype( chunk );
      using Iterator = std20::iterator_t< Range >;

      THEN( "the transform_view satisfies the required concepts" ) {

        CHECK( std20::ranges::view< Range > );
        CHECK( std20::ranges::sized_range< Range > );
        CHECK( std20::ranges::forward_range< Range > );
        CHECK( std20::ranges::bidirectional_range< Range > );
        CHECK( std20::ranges::random_access_range< Range > );
        CHECK( ! std20::ranges::contiguous_range< Range > );
        CHECK( std20::ranges::common_range< Range > );
      }

      THEN( "the transform_view range and iterator associated types are correct" ) {

        CHECK( std20::same_as< std20::ranges::range_value_t< Range >, int > );
        CHECK( std20::same_as< std20::ranges::range_reference_t< Range >, int > );
        CHECK( std20::same_as< std20::ranges::range_difference_t< Range >, std::ptrdiff_t > );

        CHECK( std20::same_as< std20::ranges::iter_value_t< Iterator >, int > );
        CHECK( std20::same_as< std20::ranges::iter_reference_t< Iterator >, int > );
        CHECK( std20::same_as< std20::ranges::iter_difference_t< Iterator >, std::ptrdiff_t > );
      }

      THEN( "a transform_view can be constructed and members can be tested" ) {

        CHECK( 5 == chunk.size() );
        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        CHECK( std20::ranges::equal( chunk, equal ) );

        CHECK( -2 == chunk[0] );
        CHECK( -1 == chunk[1] );
        CHECK(  0 == chunk[2] );
        CHECK(  1 == chunk[3] );
        CHECK(  2 == chunk[4] );

        CHECK( -2 == chunk.front() );
        CHECK(  2 == chunk.back() );
      } // THEN

      THEN( "it can be transformed into a vector using iterators" ) {

        std::vector< int > constructed( chunk.begin(), chunk.end() );
        CHECK( std20::ranges::equal( constructed, chunk ) );

        std::vector< int > inserted;
        inserted.insert( inserted.end(), chunk.begin(), chunk.end() );
        CHECK( std20::ranges::equal( inserted, chunk ) );
      }
    } // WHEN
  } // GIVEN
} // SCENARIO

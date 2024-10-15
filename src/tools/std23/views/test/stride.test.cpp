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
        CHECK( std20::ranges::common_range< Range > );
      }

      THEN( "the stride_view range and iterator associated types are correct" ) {

        CHECK( std20::same_as< std20::ranges::range_value_t< Range >, int > );
        CHECK( std20::same_as< std20::ranges::range_reference_t< Range >, int& > );
        CHECK( std20::same_as< std20::ranges::range_difference_t< Range >, std::ptrdiff_t > );

        CHECK( std20::same_as< std20::ranges::iter_value_t< Iterator >, int > );
        CHECK( std20::same_as< std20::ranges::iter_reference_t< Iterator >, int& > );
        CHECK( std20::same_as< std20::ranges::iter_difference_t< Iterator >, std::ptrdiff_t > );
      }

      THEN( "a stride_view can be constructed and members can be tested" ) {

        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        auto iter = chunk.begin();
        CHECK( equal[0] == *iter );
        ++iter;
        CHECK( equal[1] == *iter );
        ++iter;
        CHECK( equal[2] == *iter );
        ++iter;
        CHECK( equal[3] == *iter );
        ++iter;
        CHECK( equal[4] == *iter );
        ++iter;
        CHECK( chunk.end() == iter );

        CHECK( std20::ranges::equal( equal, chunk ) );

        CHECK( equal[0] == chunk.front() );
      } // THEN

//      THEN( "it can be transformed into a vector using iterators" ) {
//
//        std::vector< int > constructed( chunk.begin(), chunk.end() );
//        CHECK( std20::ranges::equal( constructed, chunk ) );
//
//        std::vector< int > inserted;
//        inserted.insert( inserted.end(), chunk.begin(), chunk.end() );
//        CHECK( std20::ranges::equal( inserted, chunk ) );
//      }
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
        CHECK( std20::ranges::common_range< Range > );
      }

      THEN( "the stride_view range and iterator associated types are correct" ) {

        CHECK( std20::same_as< std20::ranges::range_value_t< Range >, int > );
        CHECK( std20::same_as< std20::ranges::range_reference_t< Range >, int& > );
        CHECK( std20::same_as< std20::ranges::range_difference_t< Range >, std::ptrdiff_t > );

        CHECK( std20::same_as< std20::ranges::iter_value_t< Iterator >, int > );
        CHECK( std20::same_as< std20::ranges::iter_reference_t< Iterator >, int& > );
        CHECK( std20::same_as< std20::ranges::iter_difference_t< Iterator >, std::ptrdiff_t > );
      }

      THEN( "a stride_view can be constructed and members can be tested" ) {

        CHECK( 5 == chunk.size() );

        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        auto iter = chunk.begin();
        CHECK( equal[0] == *iter );
        ++iter;
        CHECK( equal[1] == *iter );
        ++iter;
        CHECK( equal[2] == *iter );
        ++iter;
        CHECK( equal[3] == *iter );
        ++iter;
        CHECK( equal[4] == *iter );
        ++iter;
        CHECK( chunk.end() == iter );

        --iter;
        CHECK( equal[4] == *iter );
        --iter;
        CHECK( equal[3] == *iter );
        --iter;
        CHECK( equal[2] == *iter );
        --iter;
        CHECK( equal[1] == *iter );
        --iter;
        CHECK( equal[0] == *iter );
        CHECK( chunk.begin() == iter );

        CHECK( std20::ranges::equal( equal, chunk ) );

        CHECK( equal[0] == chunk.front() );
        CHECK( equal[4] == chunk.back() );
      } // THEN

//      THEN( "it can be transformed into a vector using iterators" ) {
//
//        std::vector< int > constructed( chunk.begin(), chunk.end() );
//        CHECK( std20::ranges::equal( constructed, chunk ) );
//
//        std::vector< int > inserted;
//        inserted.insert( inserted.end(), chunk.begin(), chunk.end() );
//        CHECK( std20::ranges::equal( inserted, chunk ) );
//      }
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
        CHECK( std20::ranges::common_range< Range > );
      }

      THEN( "the stride_view range and iterator associated types are correct" ) {

        CHECK( std20::same_as< std20::ranges::range_value_t< Range >, int > );
        CHECK( std20::same_as< std20::ranges::range_reference_t< Range >, int& > );
        CHECK( std20::same_as< std20::ranges::range_difference_t< Range >, std::ptrdiff_t > );

        CHECK( std20::same_as< std20::ranges::iter_value_t< Iterator >, int > );
        CHECK( std20::same_as< std20::ranges::iter_reference_t< Iterator >, int& > );
        CHECK( std20::same_as< std20::ranges::iter_difference_t< Iterator >, std::ptrdiff_t > );
      }

      THEN( "a stride_view can be constructed and members can be tested" ) {

        CHECK( 5 == chunk.size() );
        CHECK( 5 == chunk.end() - chunk.begin() );

        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        auto iter = chunk.begin();
        CHECK( equal[0] == *iter );
        ++iter;
        CHECK( equal[1] == *iter );
        ++iter;
        CHECK( equal[2] == *iter );
        ++iter;
        CHECK( equal[3] == *iter );
        ++iter;
        CHECK( equal[4] == *iter );
        ++iter;
        CHECK( chunk.end() == iter );

        iter = chunk.end();
        --iter;
        CHECK( equal[4] == *iter );
        --iter;
        CHECK( equal[3] == *iter );
        --iter;
        CHECK( equal[2] == *iter );
        --iter;
        CHECK( equal[1] == *iter );
        --iter;
        CHECK( equal[0] == *iter );
        CHECK( chunk.begin() == iter );

        CHECK( std20::ranges::equal( equal, chunk ) );

        CHECK( equal[0] == chunk.front() );
        CHECK( equal[4] == chunk.back() );

        CHECK( 1 == chunk[0] );
        CHECK( 3 == chunk[1] );
        CHECK( 5 == chunk[2] );
        CHECK( 7 == chunk[3] );
        CHECK( 9 == chunk[4] );
      } // THEN

//      THEN( "it can be transformed into a vector using iterators" ) {
//
//        std::vector< int > constructed( chunk.begin(), chunk.end() );
//        CHECK( std20::ranges::equal( constructed, chunk ) );
//
//        std::vector< int > inserted;
//        inserted.insert( inserted.end(), chunk.begin(), chunk.end() );
//        CHECK( std20::ranges::equal( inserted, chunk ) );
//      }
    } // WHEN
  } // GIVEN
} // SCENARIO

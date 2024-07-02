// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/iterator.hpp"
#include "tools/std20/views.hpp"

// other includes
#include "tools/std20/algorithm.hpp"

// convenience typedefs
using namespace njoy::tools;

SCENARIO( "iota_view" ) {

  const std::vector< int > equal = { 1, 2, 3, 4, 5 };

  GIVEN( "a value" ) {

    WHEN( "creating an iota view" ) {

      auto chunk = std20::ranges::iota_view< int, int >( 1 );
      using Range = decltype( chunk );
      using Iterator = std20::iterator_t< Range >;

      THEN( "the iota_view satisfies the required concepts" ) {

        CHECK( std20::ranges::view< Range > );
        CHECK( std20::ranges::sized_range< Range > );
        CHECK( std20::ranges::forward_range< Range > );
        CHECK( std20::ranges::bidirectional_range< Range > );
        CHECK( std20::ranges::random_access_range< Range > );
        CHECK( ! std20::ranges::contiguous_range< Range > );
        CHECK( std20::ranges::common_range< Range > );
      }

      THEN( "the iota_view range and iterator associated types are correct" ) {

        CHECK( std20::same_as< std20::ranges::range_value_t< Range >, int > );
        CHECK( std20::same_as< std20::ranges::range_reference_t< Range >, int > );
        CHECK( std20::same_as< std20::ranges::range_difference_t< Range >, int > );

        CHECK( std20::same_as< std20::ranges::iter_value_t< Iterator >, int > );
        CHECK( std20::same_as< std20::ranges::iter_reference_t< Iterator >, int > );
        CHECK( std20::same_as< std20::ranges::iter_difference_t< Iterator >, int > );
      }

      THEN( "a iota_view can be constructed and members can be tested" ) {

        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );


        CHECK( 1 == chunk[0] );
        CHECK( 2 == chunk[1] );
        CHECK( 3 == chunk[2] );
        CHECK( 4 == chunk[3] );
        CHECK( 5 == chunk[4] );

        CHECK( 1 == chunk.front() );

        auto begin = std20::ranges::begin( chunk );
        auto end = begin + 5;

        CHECK( std20::ranges::equal( begin, end, equal.begin(), equal.end() ) );

        CHECK( begin == begin );
        CHECK( begin != end );
        CHECK( begin < end );
        CHECK( end > begin );
        CHECK( begin <= end );
        CHECK( end >= begin );
        CHECK( begin[2] == 3 );
        CHECK( *( begin + 1 ) == 2 );
        CHECK( *( end - 1 ) == 5 );

        CHECK( *( begin + 5 ) == 6 );
        CHECK( *( begin + 99 ) == 100 );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a value and size" ) {

    WHEN( "creating an iota view" ) {

      auto chunk = std20::ranges::iota_view< int, int >( 1, 6 );
      using Range = decltype( chunk );
      using Iterator = std20::iterator_t< Range >;

      THEN( "the iota_view satisfies the required concepts" ) {

        CHECK( std20::ranges::view< Range > );
        CHECK( std20::ranges::sized_range< Range > );
        CHECK( std20::ranges::forward_range< Range > );
        CHECK( std20::ranges::bidirectional_range< Range > );
        CHECK( std20::ranges::random_access_range< Range > );
        CHECK( ! std20::ranges::contiguous_range< Range > );
        CHECK( std20::ranges::common_range< Range > );
      }

      THEN( "the iota_view range and iterator associated types are correct" ) {

        CHECK( std20::same_as< std20::ranges::range_value_t< Range >, int > );
        CHECK( std20::same_as< std20::ranges::range_reference_t< Range >, int > );
        CHECK( std20::same_as< std20::ranges::range_difference_t< Range >, int > );

        CHECK( std20::same_as< std20::ranges::iter_value_t< Iterator >, int > );
        CHECK( std20::same_as< std20::ranges::iter_reference_t< Iterator >, int > );
        CHECK( std20::same_as< std20::ranges::iter_difference_t< Iterator >, int > );
      }

      THEN( "a iota_view can be constructed and members can be tested" ) {

        CHECK( 5 == chunk.size() );
        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        CHECK( std20::ranges::equal( chunk, equal ) );

        CHECK( 1 == chunk[0] );
        CHECK( 2 == chunk[1] );
        CHECK( 3 == chunk[2] );
        CHECK( 4 == chunk[3] );
        CHECK( 5 == chunk[4] );

        CHECK( 1 == chunk.front() );
        CHECK( 5 == chunk.back() );

        auto begin = std20::ranges::begin( chunk );
        auto end = std20::ranges::end( chunk );
        CHECK( begin == begin );
        CHECK( begin != end );
        CHECK( begin < end );
        CHECK( end > begin );
        CHECK( begin <= end );
        CHECK( end >= begin );
        CHECK( begin[2] == 3 );
        CHECK( *( begin + 1 ) == 2 );
        CHECK( *( end - 1 ) == 5 );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

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

SCENARIO( "zip_view" ) {

  std::vector< int > equal = { 26, 29, 32, 35, 38, 41, 44 };

  auto transform = [] ( int a, int b, int c ) { return a + b + c; };

  GIVEN( "a container with forward iterators" ) {

    std::forward_list< int > values1 = { 1, 2, 3, 4, 5, 6, 7 };
    std::forward_list< int > values2 = { 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    std::forward_list< int > values3 = { 17, 18, 19, 20, 21, 22, 23, 24 };

    WHEN( "when iterators are used" ) {

      auto chunk = std23::views::zip_transform( transform, values1, values2, values3 );
      using Range = decltype(chunk);
      using Iterator = std20::iterator_t< Range >;

      THEN( "the stride_view satisfies the required concepts" ) {

        CHECK( std20::ranges::range< Range > );
        CHECK( std20::ranges::view< Range > );
        CHECK( ! std20::ranges::sized_range< Range > );
        CHECK( std20::ranges::forward_range< Range > );
        CHECK( ! std20::ranges::bidirectional_range< Range > );
        CHECK( ! std20::ranges::random_access_range< Range > );
        CHECK( ! std20::ranges::contiguous_range< Range > );
        CHECK( std20::ranges::common_range< Range > );
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

    std::list< int > values1 = { 1, 2, 3, 4, 5, 6, 7 };
    std::list< int > values2 = { 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    std::list< int > values3 = { 17, 18, 19, 20, 21, 22, 23, 24 };

    WHEN( "when iterators are used" ) {

      auto chunk = std23::views::zip_transform( transform, values1, values2, values3 );
      using Range = decltype(chunk);
      using Iterator = std20::iterator_t< Range >;

      THEN( "the stride_view satisfies the required concepts" ) {

        CHECK( std20::ranges::range< Range > );
        CHECK( std20::ranges::view< Range > );
        CHECK( std20::ranges::sized_range< Range > );
        CHECK( std20::ranges::forward_range< Range > );
        CHECK( std20::ranges::bidirectional_range< Range > );
        CHECK( ! std20::ranges::random_access_range< Range > );
        CHECK( ! std20::ranges::contiguous_range< Range > );
//        CHECK( std20::ranges::common_range< Range > );
      }

      THEN( "a stride_view can be constructed and members can be tested" ) {

        CHECK( 7 == chunk.size() );

        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        CHECK( std20::ranges::equal( equal, chunk ) );

        CHECK( equal[0] == chunk.front() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a container with random access iterators" ) {

    std::vector< int > values1 = { 1, 2, 3, 4, 5, 6, 7 };
    std::vector< int > values2 = { 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    std::vector< int > values3 = { 17, 18, 19, 20, 21, 22, 23, 24 };

    WHEN( "when iterators are used" ) {

      auto chunk = std23::views::zip_transform( transform, values1, values2, values3 );
      using Range = decltype(chunk);
      using Iterator = std20::iterator_t< Range >;

      THEN( "the stride_view satisfies the required concepts" ) {

        CHECK( std20::ranges::range< Range > );
        CHECK( std20::ranges::view< Range > );
        CHECK( std20::ranges::sized_range< Range > );
        CHECK( std20::ranges::forward_range< Range > );
        CHECK( std20::ranges::bidirectional_range< Range > );
//        CHECK( std20::ranges::random_access_range< Range > );
        CHECK( ! std20::ranges::contiguous_range< Range > );
        CHECK( std20::ranges::common_range< Range > );
      }

      THEN( "a stride_view can be constructed and members can be tested" ) {

        CHECK( 7 == chunk.size() );

        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        CHECK( std20::ranges::equal( equal, chunk ) );

        CHECK( equal[0] == chunk.front() );
        CHECK( equal[6] == chunk.back() );

//        CHECK( 26 == chunk[0] );
//        CHECK( 29 == chunk[1] );
//        CHECK( 32 == chunk[2] );
//        CHECK( 35 == chunk[3] );
//        CHECK( 38 == chunk[4] );
//        CHECK( 41 == chunk[5] );
//        CHECK( 44 == chunk[6] );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

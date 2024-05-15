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

  GIVEN( "a container with random access iterators" ) {

    std::vector< int > values1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::vector< char > values2 = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i' };
    std::vector< std::string > values3 = { "ab", "cd", "ef", "gh", "ij", "kl", "mn", "op", "qr" };

    WHEN( "when iterators are used" ) {

      auto chunk = std23::views::zip( values1, values2, values3 );
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

      THEN( "a stride_view can be constructed and members can be tested" ) {

        CHECK( 9 == chunk.size() );

        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

//        CHECK( std20::ranges::equal( equal, chunk ) );
//
//        CHECK( equal[0] == chunk.front() );
//        CHECK( equal[4] == chunk.back() );
//
//        CHECK( 1 == chunk[0] );
//        CHECK( 3 == chunk[1] );
//        CHECK( 5 == chunk[2] );
//        CHECK( 7 == chunk[3] );
//        CHECK( 9 == chunk[4] );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

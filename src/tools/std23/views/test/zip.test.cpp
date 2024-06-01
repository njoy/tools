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

  GIVEN( "a container with forward iterators" ) {

    std::vector< std::tuple< int, char, std::string > > equal = {

      { 1, 'a', "ab" },
      { 2, 'b', "cd" },
      { 3, 'c', "ef" },
      { 4, 'd', "gh" },
      { 5, 'e', "ij" },
      { 6, 'f', "kl" },
      { 7, 'g', "mn" }
    };

    std::forward_list< int > values1 = { 1, 2, 3, 4, 5, 6, 7 };
    std::forward_list< char > values2 = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i' };
    std::forward_list< std::string > values3 = { "ab", "cd", "ef", "gh", "ij", "kl", "mn", "op" };

    WHEN( "when iterators are used" ) {

      auto chunk = std23::views::zip( values1, values2, values3 );
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

//        CHECK( false == chunk.empty() );
//        CHECK( true == bool( chunk ) );

        CHECK( std20::ranges::equal( equal, chunk ) );

        CHECK( equal[0] == chunk.front() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a container with bidirectional iterators" ) {

    std::vector< std::tuple< int, char, std::string > > equal = {

      { 1, 'a', "ab" },
      { 2, 'b', "cd" },
      { 3, 'c', "ef" },
      { 4, 'd', "gh" },
      { 5, 'e', "ij" },
      { 6, 'f', "kl" },
      { 7, 'g', "mn" }
    };

    std::list< int > values1 = { 1, 2, 3, 4, 5, 6, 7 };
    std::list< char > values2 = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i' };
    std::list< std::string > values3 = { "ab", "cd", "ef", "gh", "ij", "kl", "mn", "op" };

    WHEN( "when iterators are used" ) {

      auto chunk = std23::views::zip( values1, values2, values3 );
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
        CHECK( std20::ranges::common_range< Range > );
      }

      THEN( "a stride_view can be constructed and members can be tested" ) {

        CHECK( 7 == chunk.size() );

//        CHECK( false == chunk.empty() );
//        CHECK( true == bool( chunk ) );

        CHECK( std20::ranges::equal( equal, chunk ) );

        CHECK( equal[0] == chunk.front() );
//        CHECK( equal[6] == chunk.back() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a container with random access iterators" ) {

    std::vector< std::tuple< int, char, std::string > > equal = {

      { 1, 'a', "ab" },
      { 2, 'b', "cd" },
      { 3, 'c', "ef" },
      { 4, 'd', "gh" },
      { 5, 'e', "ij" },
      { 6, 'f', "kl" },
      { 7, 'g', "mn" }
    };

    std::vector< int > values1 = { 1, 2, 3, 4, 5, 6, 7 };
    std::vector< char > values2 = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i' };
    std::vector< std::string > values3 = { "ab", "cd", "ef", "gh", "ij", "kl", "mn", "op" };

    WHEN( "when iterators are used" ) {

      auto chunk = std23::views::zip( values1, values2, values3 );
      using Range = decltype(chunk);
      using Iterator = std20::iterator_t< Range >;

      THEN( "the stride_view satisfies the required concepts" ) {

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

        CHECK( 7 == chunk.size() );

        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        CHECK( std20::ranges::equal( equal, chunk ) );

        CHECK( equal[0] == chunk.front() );
        CHECK( equal[6] == chunk.back() );

        CHECK( std::tuple< int, char, std::string >{ 1, 'a', "ab" } == chunk[0] );
        CHECK( std::tuple< int, char, std::string >{ 2, 'b', "cd" } == chunk[1] );
        CHECK( std::tuple< int, char, std::string >{ 3, 'c', "ef" } == chunk[2] );
        CHECK( std::tuple< int, char, std::string >{ 4, 'd', "gh" } == chunk[3] );
        CHECK( std::tuple< int, char, std::string >{ 5, 'e', "ij" } == chunk[4] );
        CHECK( std::tuple< int, char, std::string >{ 6, 'f', "kl" } == chunk[5] );
        CHECK( std::tuple< int, char, std::string >{ 7, 'g', "mn" } == chunk[6] );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

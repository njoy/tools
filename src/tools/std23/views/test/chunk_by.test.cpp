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

SCENARIO( "chunk_by_view" ) {

  const std::vector< std::vector< int > > equal = { { 1, 2, 3 }, { 1, 2, 3 }, { 3 }, { 3 }, { 1, 2, 3 } };

  GIVEN( "a container with forward iterators" ) {

    std::forward_list< int > values = { 1, 2, 3, 1, 2, 3, 3, 3, 1, 2, 3 };

    WHEN( "when iterators are used" ) {

      auto chunk = values | std23::views::chunk_by( std::less{} );
      using Range = decltype(chunk);
      using Iterator = std20::iterator_t< Range >;

      THEN( "the chunk_by_view satisfies the required concepts" ) {

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

      THEN( "a chunk_by_view can be constructed and members can be tested" ) {

        // should not compile: not sized
        // CHECK( 5 == chunk.size() );

        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        auto iter = chunk.begin();
        CHECK( std20::ranges::equal( equal[0], *iter ) );
        ++iter;
        CHECK( std20::ranges::equal( equal[1], *iter ) );
        ++iter;
        CHECK( std20::ranges::equal( equal[2], *iter ) );
        ++iter;
        CHECK( std20::ranges::equal( equal[3], *iter ) );
        ++iter;
        CHECK( std20::ranges::equal( equal[4], *iter ) );

        CHECK( std20::ranges::equal( equal[0], chunk.front() ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a container with bidirectional iterators" ) {

    std::list< int > values = { 1, 2, 3, 1, 2, 3, 3, 3, 1, 2, 3 };

    WHEN( "when iterators are used" ) {

      auto chunk = values | std23::views::chunk_by( std::less{} );
      using Range = decltype(chunk);
      using Iterator = std20::iterator_t< Range >;

      THEN( "the chunk_by_view satisfies the required concepts" ) {

        CHECK( std20::ranges::viewable_range< Range > );

        CHECK( std20::ranges::range< Range > );
        CHECK( std20::ranges::view< Range > );
        CHECK( ! std20::ranges::sized_range< Range > );
        CHECK( std20::ranges::forward_range< Range > );
        CHECK( std20::ranges::bidirectional_range< Range > );
        CHECK( ! std20::ranges::random_access_range< Range > );
        CHECK( ! std20::ranges::contiguous_range< Range > );
        CHECK( std20::ranges::common_range< Range > );
      }

      THEN( "a chunk_by_view can be constructed and members can be tested" ) {

        // should not compile: not sized
        // CHECK( 5 == chunk.size() );

        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        auto iter = chunk.begin();
        CHECK( std20::ranges::equal( equal[0], *iter ) );
        ++iter;
        CHECK( std20::ranges::equal( equal[1], *iter ) );
        ++iter;
        CHECK( std20::ranges::equal( equal[2], *iter ) );
        ++iter;
        CHECK( std20::ranges::equal( equal[3], *iter ) );
        ++iter;
        CHECK( std20::ranges::equal( equal[4], *iter ) );

        iter = chunk.end();
        --iter;
        CHECK( std20::ranges::equal( equal[4], *iter ) );
        --iter;
        CHECK( std20::ranges::equal( equal[3], *iter ) );
        --iter;
        CHECK( std20::ranges::equal( equal[2], *iter ) );
        --iter;
        CHECK( std20::ranges::equal( equal[1], *iter ) );
        --iter;
        CHECK( std20::ranges::equal( equal[0], *iter ) );
        CHECK( (*iter).begin() == values.begin() );
        CHECK( chunk.begin() == iter );

        CHECK( std20::ranges::equal( equal[0], chunk.front() ) );
        CHECK( std20::ranges::equal( equal[4], chunk.back() ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a container with random access iterators" ) {

    std::vector< int > values = { 1, 2, 3, 1, 2, 3, 3, 3, 1, 2, 3 };

    WHEN( "when iterators are used" ) {

      auto chunk = values | std23::views::chunk_by( std::less{} );
      using Range = decltype(chunk);
      using Iterator = std20::iterator_t< Range >;
      using Subrange = std20::ranges::subrange< Iterator >;

      THEN( "the chunk_by_view satisfies the required concepts" ) {

        CHECK( std20::ranges::viewable_range< Range > );

        CHECK( std20::ranges::range< Range > );
        CHECK( std20::ranges::view< Range > );
        CHECK( ! std20::ranges::sized_range< Range > );
        CHECK( std20::ranges::forward_range< Range > );
        CHECK( std20::ranges::bidirectional_range< Range > );
        CHECK( ! std20::ranges::random_access_range< Range > );
        CHECK( ! std20::ranges::contiguous_range< Range > );
        CHECK( std20::ranges::common_range< Range > );
      }

      THEN( "a chunk_by_view can be constructed and members can be tested" ) {

        // should not compile: not sized
        // CHECK( 5 == chunk.size() );

        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        auto iter = chunk.begin();
        CHECK( std20::ranges::equal( equal[0], *iter ) );
        CHECK( 1 == (*iter)[0] );
        CHECK( 2 == (*iter)[1] );
        CHECK( 3 == (*iter)[2] );
        ++iter;
        CHECK( std20::ranges::equal( equal[1], *iter ) );
        CHECK( 1 == (*iter)[0] );
        CHECK( 2 == (*iter)[1] );
        CHECK( 3 == (*iter)[2] );
        ++iter;
        CHECK( std20::ranges::equal( equal[2], *iter ) );
        CHECK( 3 == (*iter)[0] );
        ++iter;
        CHECK( std20::ranges::equal( equal[3], *iter ) );
        CHECK( 3 == (*iter)[0] );
        ++iter;
        CHECK( std20::ranges::equal( equal[4], *iter ) );
        CHECK( 1 == (*iter)[0] );
        CHECK( 2 == (*iter)[1] );
        CHECK( 3 == (*iter)[2] );

        iter = chunk.end();
        --iter;
        CHECK( std20::ranges::equal( equal[4], *iter ) );
        CHECK( 1 == (*iter)[0] );
        CHECK( 2 == (*iter)[1] );
        CHECK( 3 == (*iter)[2] );
        --iter;
        CHECK( std20::ranges::equal( equal[3], *iter ) );
        CHECK( 3 == (*iter)[0] );
        --iter;
        CHECK( std20::ranges::equal( equal[2], *iter ) );
        CHECK( 3 == (*iter)[0] );
        --iter;
        CHECK( std20::ranges::equal( equal[1], *iter ) );
        CHECK( 1 == (*iter)[0] );
        CHECK( 2 == (*iter)[1] );
        CHECK( 3 == (*iter)[2] );
        --iter;
        CHECK( std20::ranges::equal( equal[0], *iter ) );
        CHECK( 1 == (*iter)[0] );
        CHECK( 2 == (*iter)[1] );
        CHECK( 3 == (*iter)[2] );
        CHECK( chunk.begin() == iter );

        CHECK( std20::ranges::equal( equal[0], chunk.front() ) );
        CHECK( std20::ranges::equal( equal[4], chunk.back() ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

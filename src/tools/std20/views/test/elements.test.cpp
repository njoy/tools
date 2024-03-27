// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/views.hpp"

// other includes
#include <map>
#include "tools/std20/algorithm.hpp"

// convenience typedefs
//using namespace njoy::tools;
namespace std20 = nano;

SCENARIO( "elements - keys - values" ) {

  const std::vector< char > keys_equal = { 'a', 'b', 'c', 'd', 'e' };
  const std::vector< int > values_equal = { -2, -1, 0, 1, 2 };

  GIVEN( "a map with values" ) {

    std::map< char, int > map = { { 'a', -2 }, { 'b', -1 }, { 'c', 0 }, { 'd', 1 }, { 'e', 2 } };

    WHEN( "when using the keys view" ) {

      auto chunk = map | std20::views::keys;
      using Range = decltype(chunk);
      using Iterator = nano::iterator_t< Range >;

      THEN( "the keys view satisfies the required concepts" ) {

		    CHECK( std20::ranges::view< Range > );
		    CHECK( std20::ranges::sized_range< Range > );
        CHECK( std20::ranges::forward_range< Range > );
        CHECK( std20::ranges::bidirectional_range< Range > );
		    CHECK( ! std20::ranges::random_access_range< Range > );
		    CHECK( ! std20::ranges::contiguous_range< Range > );
		    CHECK( ! std20::ranges::common_range< Range > );
      }

      THEN( "the keys view and iterator associated types are correct" ) {

        CHECK( std20::same_as< nano::ranges::range_value_t< Range >, char > );
        CHECK( std20::same_as< nano::ranges::range_reference_t< Range >, const char& > );
        CHECK( std20::same_as< nano::ranges::range_difference_t< Range >, std::ptrdiff_t > );

        CHECK( std20::same_as< nano::ranges::iter_value_t< Iterator >, char > );
        CHECK( std20::same_as< nano::ranges::iter_reference_t< Iterator >, const char& > );
        CHECK( std20::same_as< nano::ranges::iter_difference_t< Iterator >, std::ptrdiff_t > );
      }

      THEN( "a keys view can be constructed and members can be tested" ) {

        CHECK( 5 == chunk.size() );
        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        CHECK( std20::ranges::equal( chunk, keys_equal ) );

        // the following should not compile: no random access iterator
        // CHECK( 'a' == chunk[0] );

        CHECK( 'a' == chunk.front() );

        // the following should not compile: no random access iterator
        // CHECK(  2 == chunk.back() );
      } // THEN
    } // WHEN

    WHEN( "when using the values view" ) {

      auto chunk = map | std20::views::values;
      using Range = decltype(chunk);
      using Iterator = nano::iterator_t< Range >;

      THEN( "the values view satisfies the required concepts" ) {

		    CHECK( std20::ranges::view< Range > );
		    CHECK( std20::ranges::sized_range< Range > );
        CHECK( std20::ranges::forward_range< Range > );
        CHECK( std20::ranges::bidirectional_range< Range > );
		    CHECK( ! std20::ranges::random_access_range< Range > );
		    CHECK( ! std20::ranges::contiguous_range< Range > );
		    CHECK( ! std20::ranges::common_range< Range > );
      }

      THEN( "the values view and iterator associated types are correct" ) {

        CHECK( std20::same_as< nano::ranges::range_value_t< Range >, int > );
        CHECK( std20::same_as< nano::ranges::range_reference_t< Range >, int& > );
        CHECK( std20::same_as< nano::ranges::range_difference_t< Range >, std::ptrdiff_t > );

        CHECK( std20::same_as< nano::ranges::iter_value_t< Iterator >, int > );
        CHECK( std20::same_as< nano::ranges::iter_reference_t< Iterator >, int& > );
        CHECK( std20::same_as< nano::ranges::iter_difference_t< Iterator >, std::ptrdiff_t > );
      }

      THEN( "a values view can be constructed and members can be tested" ) {

        CHECK( 5 == chunk.size() );
        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        CHECK( std20::ranges::equal( chunk, values_equal ) );

        // the following should not compile: no random access iterator
        // CHECK( 'a' == chunk[0] );

        CHECK( -2 == chunk.front() );

        // the following should not compile: no random access iterator
        // CHECK(  2 == chunk.back() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

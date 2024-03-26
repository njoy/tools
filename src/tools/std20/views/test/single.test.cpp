// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/views.hpp"

// other includes

// convenience typedefs
//using namespace njoy::tools;
namespace std20 = nano;

SCENARIO( "single_view" ) {

  auto chunk = std20::views::single( 3 );
  using Range = decltype(chunk);
  using Iterator = nano::iterator_t< Range >;

  THEN( "the take_view satisfies the required concepts" ) {

    CHECK( std20::ranges::view< Range > );
    CHECK( std20::ranges::sized_range< Range > );
    CHECK( std20::ranges::forward_range< Range > );
    CHECK( std20::ranges::bidirectional_range< Range > );
    CHECK( std20::ranges::random_access_range< Range > );
    CHECK( std20::ranges::contiguous_range< Range > );
    CHECK( std20::ranges::common_range< Range > );
  }

  THEN( "the take_view range and iterator associated types are correct" ) {

    CHECK( std20::same_as< nano::ranges::range_value_t< Range >, int > );
    CHECK( std20::same_as< nano::ranges::range_reference_t< Range >, int& > );
    CHECK( std20::same_as< nano::ranges::range_difference_t< Range >, std::ptrdiff_t > );

    CHECK( std20::same_as< nano::ranges::iter_value_t< Iterator >, int > );
    CHECK( std20::same_as< nano::ranges::iter_reference_t< Iterator >, int& > );
    CHECK( std20::same_as< nano::ranges::iter_difference_t< Iterator >, std::ptrdiff_t > );
  }
} // SCENARIO
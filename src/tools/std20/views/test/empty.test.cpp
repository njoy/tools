// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/views.hpp"

// other includes

// convenience typedefs
//using namespace njoy::tools;
namespace std20 = nano;

SCENARIO( "empty_view" ) {

  auto chunk = std20::views::empty< int >;

  CHECK( nullptr == std20::ranges::begin( chunk ) );
  CHECK( nullptr == chunk.begin() );
  CHECK( nullptr == std20::ranges::end( chunk ) );
  CHECK( nullptr == chunk.end() );
  CHECK( 0 == std20::ranges::size( chunk ) );
  CHECK( 0 == chunk.size() );
} // SCENARIO

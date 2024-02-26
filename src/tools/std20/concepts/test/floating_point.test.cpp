// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/concepts.hpp"

// other includes

// convenience typedefs
//using namespace njoy::tools;
namespace std20 = nano::ranges;

SCENARIO( "floating_point" ) {

  CHECK( std20::floating_point< float > );
  CHECK( std20::floating_point< double > );

  CHECK( ! std20::floating_point< bool > );
  CHECK( ! std20::floating_point< char > );
  CHECK( ! std20::floating_point< int > );
  CHECK( ! std20::floating_point< unsigned int > );
  CHECK( ! std20::floating_point< std::ptrdiff_t > );
  CHECK( ! std20::floating_point< std::size_t > );
  CHECK( ! std20::floating_point< decltype("") > );
  CHECK( ! std20::floating_point< void > );
} // SCENARIO

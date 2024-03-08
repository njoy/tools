// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/functional.hpp"

// other includes

// convenience typedefs
//using namespace njoy::tools;
namespace std20 = nano;

SCENARIO( "invoke" ) {

  CHECK( std20::identity{}( 10 ) == 10 );
} // SCENARIO

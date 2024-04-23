// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/algorithm.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools;

SCENARIO( "mismatch" ) {

  int a[] = { 1, 2, 3, 4, 5, 6, 7 };
  int b[] = { 1, 2, 3, 8, 9 };

  std::vector< int > va = { 1, 2, 3, 4, 5, 6, 7 };
  std::vector< int > vb = { 1, 2, 3, 8, 9 };

  auto result = std20::ranges::mismatch( a, b );
  CHECK( a + 3 == result.in1 );
  CHECK( b + 3 == result.in2 );

  auto vresult = std20::ranges::mismatch( va, vb );
  CHECK( va.begin() + 3 == vresult.in1 );
  CHECK( vb.begin() + 3 == vresult.in2 );
} // SCENARIO

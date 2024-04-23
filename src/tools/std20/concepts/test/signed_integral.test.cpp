// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/concepts.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools;

SCENARIO( "signed_integral" ) {

  CHECK( std20::signed_integral< int > );
  CHECK( std20::signed_integral< std::ptrdiff_t > );

  CHECK( ! std20::signed_integral< void > );
  CHECK( ! std20::signed_integral< float > );
  CHECK( ! std20::signed_integral< int* > );
  CHECK( ! std20::signed_integral< int& > );
  CHECK( ! std20::signed_integral< int&& > );
  CHECK( ! std20::signed_integral< const int& > );
  CHECK( ! std20::signed_integral< int[] > );
  CHECK( ! std20::signed_integral< int[2] > );
  CHECK( ! std20::signed_integral< int() > );
  CHECK( ! std20::signed_integral< int(*)() > );
  CHECK( ! std20::signed_integral< int(&)() > );

  CHECK( ! std20::signed_integral< std::size_t > );
  CHECK( ! std20::signed_integral< bool > );
  CHECK( ! std20::signed_integral< unsigned int > );
  CHECK( ! std20::signed_integral< double > );
  CHECK( ! std20::signed_integral< decltype("") > );
  CHECK( ! std20::signed_integral< void > );
} // SCENARIO
